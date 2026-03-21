#include "stm32f10x.h"
#include <math.h>
#include "main.h"
#include "Pwm.h"

static void Pwm_SetDutyU16(uint16_t duty_a, uint16_t duty_b, uint16_t duty_c);

static float Pwm_tick = 0;
static float Pwm_Arr = 0.0f;
static float m = 0.3f;

/**
 * @brief PWM 模块初始化
 *
 * 当前 PWM 占空比映射规则说明：
 *
 * 1. 本工程采用 “ARR+1” 作为占空比的满量程基准：
 *      pwm_full_scale = TIM1->ARR + 1
 *
 * 2. 占空比计算方式：
 *      CCR = duty * (ARR + 1)
 *
 * 3. 对应关系：
 *      duty = 0.0f  → CCR = 0          → 0%
 *      duty = 1.0f  → CCR = ARR + 1    → 100%（始终高电平）
 *
 * 4. 硬件行为（PWM1模式）：
 *      CNT < CCR → 输出高电平
 *      当 CCR > ARR 时，CNT 始终小于 CCR，因此输出为全高
 *
 * 5. 注意事项：
 *      - CCR 的“正常范围”是 0 ~ ARR
 *      - 本设计允许 CCR = ARR+1 作为“强制100%输出”的特殊情况
 *      - 后续如在底层做限幅/保护逻辑，需要注意不要误截断该值
 *
 * 6. 设计目的：
 *      - 保证 duty=1.0f 时输出真正100%
 *      - 避免 ARR 映射导致的 99% 上限问题
 *
 * 7. 上层控制建议：
 *      - 若不希望进入“强制100%”状态，可在上层限制 duty < 1.0f
 *      - 电机控制中通常不建议长期运行在 100% 占空比
 */
void Pwm_Init(void)
{
    Pwm_Arr = (float)(TIM1->ARR + 1);
}

void Pwm_SetDuty3(float duty_a, float duty_b, float duty_c)
{
    /*未来外部调用可以做到同样的限幅就删掉这里*/
    duty_a = CLAMP(duty_a,0.0f,1.0f);
    duty_b = CLAMP(duty_b,0.0f,1.0f);
    duty_c = CLAMP(duty_c,0.0f,1.0f);

    uint16_t a,b,c;
    a = (uint16_t)(duty_a*Pwm_Arr);
    b = (uint16_t)(duty_b*Pwm_Arr);
    c = (uint16_t)(duty_c*Pwm_Arr);

    TIM_SetCompare1(TIM1,a);
    TIM_SetCompare2(TIM1,b);
    TIM_SetCompare3(TIM1,c);
}

void Pwm_OutputSine3(float theta)
{
    float u = sinf(theta);
    float v = sinf(theta - TWO_PI_3);
    float w = sinf(theta + TWO_PI_3);

    float duty_u = 0.5f + 0.5f * m * u;
    float duty_v = 0.5f + 0.5f * m * v;
    float duty_w = 0.5f + 0.5f * m * w;

    Pwm_SetDuty3(duty_u,duty_v,duty_w);
}

#ifdef Pwm_Test

    static void  Pwm_SetDutyU16(uint16_t duty_a, uint16_t duty_b, uint16_t duty_c)
    {
        TIM_SetCompare1(TIM1,duty_a);
        TIM_SetCompare2(TIM1,duty_b);
        TIM_SetCompare3(TIM1,duty_c);
    }

    void Pwm_OnTimerTickISR(void)
    {
        Pwm_tick++;
    }

    void Pwm_RunIfPending(void)
    {
        static float theta = 0;
        if(Pwm_tick >= 20)
        {
            Pwm_tick -= 50;
            theta +=0.5f;
            if(theta >= TWO_PI)
            {
                theta -= TWO_PI;
            }
            Pwm_OutputSine3(theta);
        }
    }
#endif
uint16_t Pwm_GetPeriod(void)
{
    return TIM1->ARR + 1;
}

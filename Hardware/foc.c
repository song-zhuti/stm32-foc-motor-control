#include "foc.h"

static volatile uint8_t foc_enable = 0;
static volatile uint32_t foc_pending_tick = 0;
static  uint32_t foc_run_count = 0;

static void Foc_ControlStep(void)
{
    /*真正的控制算法*/
    return;
}

void FOC_Init(void)
{
    foc_enable = 0;
    foc_pending_tick = 0;
    foc_run_count = 0;
}

void FOC_OnTimerTickISR(void)
{
    if(foc_enable)
    {
        foc_pending_tick++;
    }
}

void FOC_RunIfPending(void)
{
    if(foc_pending_tick >= 50 && foc_enable)
    {
        Foc_ControlStep();
        foc_pending_tick -= 50;
        foc_run_count++;
    }
}

void FOC_SetEnable(uint8_t status)
{
    foc_enable = (status != 0)?1:0;
    if(!foc_enable)
    {
        foc_pending_tick = 0;
    }
}
/**
 * @brief 函数用于检查执行频率，临时用的
 */
uint32_t FOC_GetRunCount(void)
{
    uint32_t temp = foc_run_count;
    foc_run_count = 0;
    return temp;
}

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_it.h"
#include "Periph_Init.h"
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

/* 三相UVW换向表：每行表示一个换向步，列顺序为 {U, V, W} */
/* 值含义： */

static const BitAction BLDC_xxx[6][3] = {
	{ Bit_SET, Bit_RESET, Bit_RESET }, /* Step1: A+ / B- (C浮空) */
	{ Bit_SET, Bit_RESET, Bit_RESET  }, /* Step2: A+ / C- (B浮空) */
	{ Bit_RESET, Bit_SET, Bit_RESET  }, /* Step3: B+ / C- (A浮空) */
	{ Bit_RESET,  Bit_SET, Bit_RESET }, /* Step4: B+ / A- (C浮空) */
	{ Bit_RESET,  Bit_RESET, Bit_SET }, /* Step5: C+ / A- (B浮空) */
	{ Bit_RESET, Bit_RESET,  Bit_SET }  /* Step6: C+ / B- (A浮空) */
};

void BLDC_Six(void)
{
	static uint8_t step = 0;
	GPIO_WriteBit(GPIOA, GPIO_Pin_8, BLDC_xxx[step][0]); //U相
	GPIO_WriteBit(GPIOA, GPIO_Pin_9, BLDC_xxx[step][1]); //V相
	GPIO_WriteBit(GPIOA, GPIO_Pin_10, BLDC_xxx[step][2]); //W相
	step++;
	if(step >= 6)
	{
		step = 0;
	}
}

int main(void)
{
	/*模块初始化*/
	OLED_Init();			//OLED初始化
	Perioh_gpioinit();	//GPIO初始化
	Perioh_nvicinit();	//NVIC初始化
	Perioh_tim3init();	//TIM初始化
	ad_init(16);

	/*显示静态字符串*/
	OLED_ShowString(1, 1, "Hello World");	//1行1列显示字符串Count:
	GPIO_SetBits(GPIOA,GPIO_Pin_11);  	//simplefoc_enable置1
	
	while (1)
	{
		OLED_ShowNum(2, 1, (uint32_t)(get_ad_filter(X_AXIS)->prev_output), 4);
		OLED_ShowNum(2, 6, (uint32_t)(get_ad_filter(Y_AXIS)->prev_output), 4);
		// BLDC_Six();
		Delay_ms(200);
	}
}

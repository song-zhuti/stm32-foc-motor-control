#include "stm32f10x.h"                  // Device header
#include "stm32f10x_it.h"
#include "Periph_Init.h"
#include "Delay.h"
#include "OLED.h"

int main(void)
{
	uint16_t data[2];

	/*模块初始化*/
	OLED_Init();			//OLED初始化
	Perioh_gpioinit();	//GPIO初始化
	Perioh_nvicinit();	//NVIC初始化
	Perioh_tim3init();	//TIM初始化
	Perioh_ad1init();	//ADC初始化
	Perioh_dma1init((uint32_t)&ADC1->DR,(uint32_t)&data[0], 2);	//DMA初始化
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);                       //使能ADC1的软件触发转换

	
	/*显示静态字符串*/
	OLED_ShowString(1, 1, "Hello World");	//1行1列显示字符串Count:
	
	while (1)
	{
		OLED_ShowNum(2, 1, data[0], 4);
		OLED_ShowNum(2, 6, data[1], 4);
		Delay_ms(200);
	}
}

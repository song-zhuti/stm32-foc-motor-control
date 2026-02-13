#include "AD.h"

static 	uint16_t data[2];
static  low_pass_filter_state_i x_axis_filter;
static  low_pass_filter_state_i y_axis_filter;
low_pass_filter_state_i* filter_state_data[2] = {&x_axis_filter, &y_axis_filter};

int ad_init(uint16_t alpha)
{
    if(low_pass_filer_init_i(filter_state_data[0], alpha) != 0) // 初始化X轴滤波器，alpha值为0.1
    {
        return -1; // 错误：初始化失败
    }

    if(low_pass_filer_init_i(&y_axis_filter, alpha) != 0) // 初始化Y轴滤波器，alpha值为0.1
    {
        return -1; // 错误：初始化失败
    }

	Perioh_ad1init();	//ADC初始化
	Perioh_dma1init((uint32_t)&ADC1->DR,(uint32_t)&data[0], 2);	//DMA初始化
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);                       //使能ADC1的软件触发转换

    return 0;
}
/**
 * @brief 返回滤波器结构体指针
 * 
 * @param value 
 * @return low_pass_filter_state_i* 
 */
low_pass_filter_state_i* get_ad_filter(axis_t value)
{
    return filter_state_data[value];//返回滤波后的输出值
}

uint16_t* get_ad_data(axis_t value)
{
    return &data[value];//返回滤波后的输出值
}

#include "AD.h"

static 	volatile uint16_t data[AD_CH_COUNT];
static  low_pass_filter_state_i x_axis_filter;
static  low_pass_filter_state_i y_axis_filter;
static  low_pass_filter_state_i encoder_filter;
static  low_pass_filter_state_i* filter_state_data[AD_CH_COUNT] = {&x_axis_filter, &y_axis_filter, &encoder_filter};

int ad_init(uint16_t alpha)
{
    if(low_pass_filer_init_i(filter_state_data[0], alpha) != 0) // 初始化X轴滤波器，alpha值为0.1
    {
        return -1; // 错误：初始化失败
    }

    if(low_pass_filer_init_i(filter_state_data[1], alpha) != 0) // 初始化Y轴滤波器，alpha值为0.1
    {
        return -1; // 错误：初始化失败
    }

    if(low_pass_filer_init_i(filter_state_data[2], alpha) != 0) // 初始化编码器滤波器，alpha值为0.1
    {
        return -1; // 错误：初始化失败
    }

	Perioh_ad1init();	//ADC初始化
	Perioh_dma1init((uint32_t)&ADC1->DR,(uint32_t)&data[0], AD_CH_COUNT);	//DMA初始化
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);                       //使能ADC1的软件触发转换

    return 0;
}
/**
 * @brief 返回滤波器结构体指针
 * 
 * @param value 轴或编码器
 * @return low_pass_filter_state_i* 滤波器结构体指针
 */
low_pass_filter_state_i* get_ad_filter(axis_t value)
{
    if(value>=AD_CH_COUNT)
    {
        return NULL;
    }
    else
    {
        return filter_state_data[value];//返回滤波后的输出值
    }
}
/**
 * @brief 返回原始ADC值指针
 * 
 * @param value 轴或编码器
 * @return uint16_t* 原始ADC值指针
 */
volatile uint16_t* get_ad_data(axis_t value)
{
    if(value >= AD_CH_COUNT)
    {
        return NULL;
    }
    else
    {
    return &data[value];//返回滤波后的输出值
    }
}

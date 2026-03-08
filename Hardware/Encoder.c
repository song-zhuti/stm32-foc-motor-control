#include "Encoder.h"

static uint16_t encoder_raw_adc;            //编码器原始ADC值
static float encoder_angle;                 //编码器角度值

void Encoder_Init(void)
{
    return;
}
/**
 * @brief 更新编码器角度值
 * 
 */
void Encoder_Update(void)
{
    encoder_raw_adc = *get_ad_data(ENCODER);
    //angle = adc_value * 360.0 / 4095.0
    encoder_angle = (float)encoder_raw_adc * 360.0f / 4095.0f;
}
/**
 * @brief 返回编码器角度值
 * 
 * @return float 编码器角度值
 */
float Encoder_GetAngle(void)
{
    return encoder_angle;
}
/**
 * @brief 返回编码器原始ADC值
 * 
 * @return uint16_t 编码器原始ADC值
 */
uint16_t Encoder_GetRawAdc(void)
{
    return encoder_raw_adc;
}

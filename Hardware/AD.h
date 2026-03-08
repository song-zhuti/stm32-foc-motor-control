#ifndef __AD_H
#define __AD_H

#include "stm32f10x.h"
#include "main.h"
#include "mathoperation.h"
#include "Periph_Init.h"

typedef enum
{
    X_AXIS = 0,         //X轴
    Y_AXIS = 1,         //Y轴
    ENCODER = 2,        //编码器
    AD_CH_COUNT = 3,    //通道总数
} axis_t;

int ad_init(uint16_t alpha);
low_pass_filter_state_i* get_ad_filter(axis_t value);
volatile uint16_t* get_ad_data(axis_t value);

#endif // __AD_H

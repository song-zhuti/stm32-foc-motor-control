#ifndef __AD_H
#define __AD_H

#include "stm32f10x.h"
#include "main.h"
#include "mathoperation.h"
#include "Periph_Init.h"

typedef enum
{
    X_AXIS = 0,
    Y_AXIS = 1,
} axis_t;

int ad_init(uint16_t alpha);
low_pass_filter_state_i* get_ad_filter(axis_t value);
uint16_t* get_ad_data(axis_t value);

#endif // __AD_H

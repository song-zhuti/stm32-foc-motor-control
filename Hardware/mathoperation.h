#ifndef __MATHOPERATION_H__
#define __MATHOPERATION_H__

#include "stm32f10x.h"
#include "main.h"
/**
 * @brief 低通滤波结构体
 */
typedef struct
{
    float alpha,        // 滤波系数，范围为0到1，值越大滤波效果越明显
    alpha_complement,   // 1 - alpha，预计算以提高效率
    prev_output;        // 上一次滤波后的输出值
}low_pass_filter_state_f;

typedef struct
{
    uint16_t alpha,        // 滤波系数，范围为0到10，值越大滤波效果越明显
    alpha_complement, // 1 - alpha，预计算以提高效率
    prev_output;      // 上一次滤波后的输出值
}low_pass_filter_state_i;

int low_pass_filer_init_f(low_pass_filter_state_f *state, float alpha);
void low_pass_filter_update_f(low_pass_filter_state_f *state, float input);

int low_pass_filer_init_i(low_pass_filter_state_i *state, uint8_t alpha);
void low_pass_filer_update_i(low_pass_filter_state_i *state, uint16_t input);

#endif /* __MATHOPERATION_H__ */

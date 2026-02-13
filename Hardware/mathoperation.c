#include "mathoperation.h"

int low_pass_filer_init_f(low_pass_filter_state_f *state, float alpha)
{
    if (state == NULL) {
        return -1; // 错误：空指针
    }
    
    state->alpha = CLAMP(alpha, 0.0f, 1.0f);    // 确保alpha在0到1之间
    state->alpha_complement = 1.0f - alpha; // 预计算1 - alpha
    state->prev_output = 0.0f; // 初始输出设为0

    return 0; // 成功
}

void low_pass_filter_update_f(low_pass_filter_state_f *state, float input)
{    
    state->prev_output = state->alpha * input + state->alpha_complement * state->prev_output;
}

int low_pass_filer_init_i(low_pass_filter_state_i *state, uint8_t alpha)
{
    if (state == NULL) {
        return -1; // 错误：空指针
    }
    state->alpha = CLAMP(alpha, 1, 64);   // 确保alpha在1到64之间
    state->alpha_complement = 64 - alpha; // 预计算1 - alpha
    state->prev_output = 0; // 初始输出设为0

    return 0; // 成功
}
/**
 * @brief 更新低通滤波器的输出值
 * @note 该函数不涉及浮点数运算，适用于C99标准
 * @param state 低通滤波器状态指针
 * @param input 新的输入值
 */
void low_pass_filer_update_i(low_pass_filter_state_i *state, uint16_t input)
{
    state->prev_output = (state->alpha * input + state->alpha_complement * state->prev_output) >> 6;
}

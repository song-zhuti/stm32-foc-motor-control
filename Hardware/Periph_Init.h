#ifndef __PERIPH_INIT_H
#define __PERIPH_INIT_H

#include "stm32f10x.h"

void Perioh_gpioinit(void);
void Perioh_tim3init(void);
void Perioh_nvicinit(void);
void Perioh_ad1init(void);
uint16_t ADC1_GetValue(uint8_t ADC_Channel);
void Perioh_dma1init(uint32_t peripheaddr,uint32_t memoryaddr,uint16_t buffer_size);
void Perioh_dmatransfer(DMA_Channel_TypeDef* DMAy_Channelx,uint16_t buffer_size);

#endif

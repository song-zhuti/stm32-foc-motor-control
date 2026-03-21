#ifndef __FOC_H__
#define __FOC_H__

#include "stm32f10x.h"
#include "stdint.h"

void FOC_Init(void);
void FOC_OnTimerTickISR(void);
void FOC_RunIfPending(void);
void FOC_SetEnable(uint8_t status);
uint32_t FOC_GetRunCount(void);

#endif

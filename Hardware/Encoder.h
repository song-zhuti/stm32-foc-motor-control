#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "stm32f10x.h"
#include "stdio.h"
#include "AD.h"

void Encoder_Init(void);
void Encoder_Update(void);
float Encoder_GetAngle(void);
uint16_t Encoder_GetRawAdc(void);

#endif

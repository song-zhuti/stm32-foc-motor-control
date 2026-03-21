#ifndef __PWM_H__
#define __PWM_H__

#include "stdint.h"

// #define Pwm_Test

void Pwm_Init(void);
void Pwm_cmd(void);
void Pwm_SetDuty3(float duty_a, float duty_b, float duty_c);
void Pwm_OutputSine3(float theta);
void Pwm_OnTimerTickISR(void);
void Pwm_RunIfPending(void);
uint16_t Pwm_GetPeriod(void);

#endif

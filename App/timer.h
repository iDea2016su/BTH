#ifndef TIMER_H
#define TIMER_H

#include "main.h"
#include "sys.h"

void TIM2_Init(u16 psc,u16 arr);
void TIM_Set(u32 compare);
#endif
#ifndef __TIME_H
#define __TIME_H

#include "string.h"
#include "stm32f4xx_hal.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "steer.h"
#include "motor.h"
#include "datou.h"
#include "stdio.h"

extern int pulse4_flag1;
extern int pulse4_1;
extern int pulse4_set1;
extern int pulse4_flag2;
extern int pulse4_2;
extern int pulse4_set2;
extern int pulse4_flag3;
extern int pulse4_3;
extern int pulse4_set3;
extern int pulse4_flag4;
extern int pulse4_4;
extern int pulse4_set4;
extern int pulse4_flag5;
extern int pulse4_5;
extern int pulse4_set5;
extern int pulse2_flag2;
extern int pulse2_2;
extern int pulse2_set2;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif

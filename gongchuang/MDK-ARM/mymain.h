#ifndef _MYMAIN_H
#define _MYMAIN_H

#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "steer.h"
#include "motor.h"

#define GAP_TIM htim5

void mymain(void);
void system_init(void);
void state_machine(void);

#endif

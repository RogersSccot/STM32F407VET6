#ifndef _MYMAIN_H
#define _MYMAIN_H

#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "steer.h"
#include "motor.h"

#define GAP_TIM htim5

#define START 0
#define MOVE_1 1
#define SCAN 2
#define MOVE_2 3
#define MATERIAL_AREA 4
#define DEAL_AREA 5
#define STORE_AREA 6
#define PICKUP 7
#define PUTDOWN 8

void mymain(void);
void system_init(void);
void state_machine(void);

#endif

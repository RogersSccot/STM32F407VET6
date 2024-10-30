#ifndef _MYMAIN_H
#define _MYMAIN_H

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
#include "time.h"
#include "uart.h"

#define GAP_TIM htim5
#define GAP_LENGTH 100 //两个圈的间隔，100mm
//这些是状态
#define START 0
#define MOVE_1 1
#define SCAN 2
#define MOVE_2 3
#define MATERIAL_AREA 4
#define MOVE_3 5
#define DEAL_AREA 6
#define MOVE_4 7
#define STORE_AREA 8
#define MOVE_5 9


extern long long int time_Tick;
extern double time_Tick_s;
extern uint8_t state_flag;
extern uint8_t received_flag;
extern int goods_num;

extern void mymain(void);
extern void system_init(void);
extern void state_machine(void);

#endif

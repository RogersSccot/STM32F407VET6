#ifndef _MYMAIN_H
#define _MYMAIN_H

#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "string.h"

#include "steer.h"
#include "motor.h"
#include "datou.h"

#define GAP_TIM htim5

#define GAP_LENGTH 0

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

extern uint8_t receive_buff_1[50];
extern uint8_t receive_buff_2[50];
extern uint8_t receive_buff_3[50];
extern uint8_t receive_buff_6[50];

void mymain(void);
void system_init(void);
void state_machine(void);

void Bluetooth_UART_IRQHandler(UART_HandleTypeDef * huart);

#endif

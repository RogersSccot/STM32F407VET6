#ifndef __UART_H
#define __UART_H

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
#include "mymain.h"
#include "main.h"

extern uint8_t receive_buff_1[50];
extern uint8_t receive_buff_2[50];
extern uint8_t receive_buff_3[50];
extern uint8_t receive_buff_6[50];

void DMA_USART_Init(UART_HandleTypeDef *huart);
void Bluetooth_UART_IRQHandler(UART_HandleTypeDef * huart);

#endif

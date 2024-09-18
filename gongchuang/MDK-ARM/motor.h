#ifndef _MOTOR_H
#define _MOTOR_H

#include "stm32f4xx_hal.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#define MOTOR_MOVE_TIM htim1
#define MOTOR_ROTATE_TIM htim3

#define MOTOR_LF_CHANNEL TIM_CHANNEL_1
#define MOTOR_RF_CHANNEL TIM_CHANNEL_2
#define MOTOR_LB_CHANNEL TIM_CHANNEL_3
#define MOTOR_RB_CHANNEL TIM_CHANNEL_4

#define MOTOR_ROTATE_CHANNEL TIM_CHANNEL_1

typedef struct _Motor
{
    float angle;
    float speed;
    uint8_t direct; 
} Motor;

extern Motor motor_lf;
extern Motor motor_rf;
extern Motor motor_lb;
extern Motor motor_rb;
extern Motor motor_rotate;

void motor_init(Motor motor);

void motor_control(Motor motor);

void move_foward(float distance);
	
void move_back(float distance);
	
void move_left(float distance);
	
void move_right(float distance);

#endif

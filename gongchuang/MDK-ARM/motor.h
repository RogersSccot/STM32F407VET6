#ifndef _MOTOR_H
#define _MOTOR_H

#include "stm32f4xx_hal.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#define MOTOR_MOVE_TIM htim1
#define MOTOR_UP_TIM htim3

#define MOTOR_LF_CHANNEL TIM_CHANNEL_1
#define MOTOR_RF_CHANNEL TIM_CHANNEL_2
#define MOTOR_BACK_CHANNEL TIM_CHANNEL_3

#define MOTOR_UP_CHANNEL TIM_CHANNEL_1


#define angle_floor 0
#define angle_lift_low 0
#define angle_lift_high 0
#define angle_plate 0

typedef struct _Motor
{
    float angle;
    float speed;
    uint8_t direct; 
} Motor;

extern Motor motor_lf;
extern Motor motor_rf;
extern Motor motor_back;
extern Motor motor_up;

void motor_init(Motor motor);

void motor_control(Motor motor,float angle);

void move_foward(float distance);
	
void move_back(float distance);
	
void move_left(float distance);
	
void move_right(float distance);

void turn_left(float angle);
	
void turn_right(float angle);

#endif

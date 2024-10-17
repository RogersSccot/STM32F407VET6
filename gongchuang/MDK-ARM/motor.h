#ifndef _MOTOR_H
#define _MOTOR_H

#include "stm32f4xx_hal.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#define MOTOR_MOVE_TIM htim1
#define MOTOR_UP_TIM htim3
#define GAP_TIM htim5

#define MOTOR_LF_CHANNEL TIM_CHANNEL_3
#define MOTOR_RF_CHANNEL TIM_CHANNEL_4
#define MOTOR_BACK_CHANNEL TIM_CHANNEL_2
#define MOTOR_ROTATE_CHANNEL TIM_CHANNEL_1
#define MOTOR_UP_CHANNEL TIM_CHANNEL_1

#define angle_floor 0
#define angle_lift_low 0
#define angle_lift_high 0
#define angle_plate 0

// accelerate time (s)
#define t_acc 0.1
// acceleratime value (cm/s/s)
#define a_acc_k 10

typedef struct _Motor
{
  // the fixed value of motor
  // motor identifier
  int num;
  // channel of TIM
  unsigned int channel;
  // TIM
  TIM_HandleTypeDef tim;

  // changing value of motor
  // the rotation angle of motor
  double angle;
  // speed of motor(corresponding to reload value of TIM)
  double speed;
  // direction of motor
  GPIO_PinState direct;
} Motor;

extern double a4_acc1;
extern double begin4_time1;
extern double end4_time1;

// motor 1
extern Motor motor_lf;
// motor 2
extern Motor motor_rf;
// motor 3
extern Motor motor_back;
// motor under rotate
extern Motor motor_rotate;
// motor up and down
extern Motor motor_up;
// 
void motor_init(Motor *motor);
// 
void motor_control(Motor motor, double speed, double x);

void move_foward(double speed, double distance);

void move_back(double speed, double distance);

void move_left(double speed, double distance);

void move_right(double speed, double distance);

void turn_left(double angle);

void turn_right(double angle);

#endif

#include "motor.h"
#include "datou.h"
#include "mymain.h"

/*
长度单位cm
速度单位cm/s
时间单位s
*/

Motor motor_lf;
Motor motor_rf;
Motor motor_back;
Motor motor_up;
Motor motor_rotate;

// 梯形加减速用的变量，每个电机区分开
double begin4_time1;
double end4_time1;
double a4_acc1;
double begin4_time2;
double end4_time2;
double a4_acc2;
double begin4_time3;
double end4_time3;
double a4_acc3;
double begin4_time4;
double end4_time4;
double a4_acc4;
double begin4_time5;
double end4_time5;
double a4_acc5;

// 步进电机初始化函数，可能没什么用
void motor_init(Motor *motor)
{
	motor->angle = 0.0;
	motor->direct = GPIO_PIN_RESET;
	motor->speed = 0;
}

// 步进电机控制函数，不要轻易改
void motor_control(Motor motor, double speed, double x)
{
	if (x > 0)
	{
		motor.direct = GPIO_PIN_SET;
	}
	if (x < 0)
	{
		motor.direct = GPIO_PIN_RESET;
		x = -x;
	}

	// front left motor
	if (motor.num == 0)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, motor.direct);
		pulse4_flag1 = 1;
		pulse4_set1 = (int)x * 134.41;
		__HAL_TIM_SetAutoreload(&motor.tim, (int)(3106.7 / speed));
		__HAL_TIM_SetCompare(&motor.tim, motor.channel, (int)(1035.0 / speed));
		HAL_TIM_PWM_Start(&motor.tim, motor.channel);
	}

	// front right motor
	if (motor.num == 1)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, motor.direct);
		pulse4_flag2 = 1;
		pulse4_set2 = (int)x * 134.41;
		__HAL_TIM_SetAutoreload(&motor.tim, (int)(3106.7 / speed));
		__HAL_TIM_SetCompare(&motor.tim, motor.channel, (int)(1035.0 / speed));
		HAL_TIM_PWM_Start(&motor.tim, motor.channel);
	}

	// back motor
	if (motor.num == 2)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, motor.direct);
		pulse4_flag3 = 1;
		pulse4_set3 = (int)x * 134.41;
		__HAL_TIM_SetAutoreload(&motor.tim, (int)(3106.7 / speed));
		__HAL_TIM_SetCompare(&motor.tim, motor.channel, (int)(1035.0 / speed));
		HAL_TIM_PWM_Start(&motor.tim, motor.channel);
	}

	// motor_rotate
	 if (motor.num == 3)
	 {
	 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, motor.direct);
	 	pulse4_flag4 = 1;
	 	pulse4_set4 = (int)x * 134.41;
	 	__HAL_TIM_SetAutoreload(&motor.tim, (int)(3106.7 / speed));
		__HAL_TIM_SetCompare(&motor.tim, motor.channel, (int)(1035.0 / speed));
	 	HAL_TIM_PWM_Start(&motor.tim, motor.channel);
	 }

	 // motor_up
	 if (motor.num == 4)
	 {
	 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, motor.direct);
	 	pulse4_flag5 = 1;
	 	pulse4_set5 = (int)x * 134.41;
	 	__HAL_TIM_SetAutoreload(&motor.tim, (int)(3106.7 / speed));
		__HAL_TIM_SetCompare(&motor.tim, motor.channel, (int)(1035.0 / speed));
	 	HAL_TIM_PWM_Start(&motor.tim, motor.channel);
	 }
}

// 各种复合指令，操作整辆车运动
void move_foward(double speed, double distance)
{
	motor_control(motor_lf, (double)1.155 * speed, -1.155 * distance);
	motor_control(motor_rf, (double)1.155 * speed, (double)1.155 * distance);
}

void move_back(double speed, double distance)
{
	motor_control(motor_lf, (double)1.155 * speed, (double)1.155 * distance);
	motor_control(motor_rf, (double)1.155 * speed, -1.155 * distance);
}

void move_left(double speed, double distance)
{
	motor_control(motor_lf, speed, distance);
	motor_control(motor_rf, speed, distance);
	motor_control(motor_back, 2 * speed, -2 * distance);
}

void move_right(double speed, double distance)
{
	motor_control(motor_lf, speed, -distance);
	motor_control(motor_rf, speed, -distance);
	motor_control(motor_back, 2*2 * speed, 2 *2* distance);
}

void turn_left(double angle)
{
	motor_control(motor_lf, 10, 2.618 * 1.5 * angle);
	motor_control(motor_rf, 10, 2.618 * 1.5 * angle);
	motor_control(motor_back, 10, 2.618 * 1.5 * angle);
}

void turn_right(double angle)
{
	motor_control(motor_lf, 10, -2.618 * 1.5 * angle);
	motor_control(motor_rf, 10, -2.618 * 1.5 * angle);
	motor_control(motor_back, 10, -2.618 * 1.5 * angle);
}

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

double begin4_time1;
double end4_time1;
double a4_acc1;

void motor_init(Motor *motor) 
{  
    motor->angle = 0.0;  
    motor->direct = GPIO_PIN_RESET;  
    motor->speed = 0;  
}

void motor_control(Motor motor,double speed,double x)
{
	if(x >0)
	{
		motor.direct = GPIO_PIN_SET;
	}
	if(x <0)
	{
		motor.direct = GPIO_PIN_RESET;
		x = -x;
	}
	if(motor.num == 0)
	{
		printf("motor_lf");
		// set the direction of motor
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, motor.direct);
		// allow to move
		pulse4_flag1 = 1;
		// set the PWM pulse
		pulse4_set1 = (int)x * 94.76;
		// set the acceleration
		a4_acc1 = (double)speed/t_acc;
		// record the begin time
		begin4_time1 = HAL_GetTick()/1000;
		// calculate the end time
		end4_time1 = begin4_time1+x/speed+t_acc;
		HAL_TIM_PWM_Start(&motor.tim, motor.channel);
	}

	if(motor.num == 1)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, motor.direct);
		pulse4_flag2 = 1;
		pulse4_set2 = (int)x * 94.76;
		__HAL_TIM_SetAutoreload(&motor.tim, (int)6990.0/speed);
		__HAL_TIM_SetCompare(&motor.tim, motor.channel, (int)2330.0/speed);
		HAL_TIM_PWM_Start(&motor.tim, motor.channel);
	}
	if(motor.num == 2)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, motor.direct);
		pulse4_flag3 = 1;
		pulse4_set3 = (int)x * 94.76;
		__HAL_TIM_SetAutoreload(&motor.tim, (int)6990.0/speed);
		__HAL_TIM_SetCompare(&motor.tim, motor.channel, (int)2330.0/speed);
		HAL_TIM_PWM_Start(&motor.tim, motor.channel);
	}
	if(motor.num == 3)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, motor.direct);
		pulse4_flag3 = 1;
		pulse4_set3 = (int)x * 94.76;
		__HAL_TIM_SetAutoreload(&motor.tim, (int)6990.0/speed);
		__HAL_TIM_SetCompare(&motor.tim, motor.channel, (int)2330.0/speed);
		HAL_TIM_PWM_Start(&motor.tim, motor.channel);
	}
	if(motor.num == 4)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, motor.direct);
		pulse4_flag3 = 1;
		pulse4_set3 = (int)x * 94.76;
		__HAL_TIM_SetAutoreload(&motor.tim, (int)6990.0/speed);
		__HAL_TIM_SetCompare(&motor.tim, motor.channel, (int)2330.0/speed);
		HAL_TIM_PWM_Start(&motor.tim, motor.channel);
	}
}

void move_foward(double speed,double distance)
{
	motor_control(motor_lf,(double)1.155*speed,-1.155*distance);
	motor_control(motor_rf,(double)1.155*speed,(double)1.155*distance);
}

void move_back(double speed,double distance)
{
	motor_control(motor_lf,(double)1.155*speed,(double)1.155*distance);
	motor_control(motor_rf,(double)1.155*speed,-1.155*distance);
}

void move_left(double speed,double distance)
{
	motor_control(motor_lf,speed,distance);
	motor_control(motor_rf,speed,distance);
	motor_control(motor_back,2*speed,-2*distance);
}

void move_right(double speed,double distance)
{
	motor_control(motor_lf,speed,-distance);
	motor_control(motor_rf,speed,-distance);
	motor_control(motor_back,2*speed,2*distance);
}

void turn_left(double angle)
{
	motor_control(motor_lf,10,2.618*1.5*angle);
	motor_control(motor_rf,10,2.618*1.5*angle);
	motor_control(motor_back,10,2.618*1.5*angle);
}

void turn_right(double angle)
{
	motor_control(motor_lf,10,-2.618*1.5*angle);
	motor_control(motor_rf,10,-2.618*1.5*angle);
	motor_control(motor_back,10,-2.618*1.5*angle);
}



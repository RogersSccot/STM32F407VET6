#include "steer.h"
#include "motor.h"
#include "stdio.h"

Steer steer_rotate;
Steer steer_plate;
Steer steer_catch;

double plate_pulse,catch_pulse;

void steer_init(Steer *steer)
{
	steer->angle = angle_drop;
	steer->num = 0;
}

void steer_control(Steer steer,double angle)
{
	printf("1\n");
	if(steer.num == 0)
	{
		printf("3\n");
		plate_pulse = 50.0f+(angle)*200.0f/180.0f;
		__HAL_TIM_SET_COMPARE(&STEER_TIM,TIM_CHANNEL_3,(int)plate_pulse);
	}
	if(steer.num == 1)
	{
		printf("2\n");
		catch_pulse = 50.0f+(angle)*200.0f/180.0f;
		__HAL_TIM_SET_COMPARE(&STEER_TIM,TIM_CHANNEL_2,(int)catch_pulse);
	}
}

void pick_up_high(int color)
{
	motor_control(motor_rotate,50,angle_outside);
	motor_control(motor_up,50,angle_floor);
	steer_control(steer_catch,angle_catch);
	motor_control(motor_up,50,angle_lift_low);
	switch(color)
	{
		case 1:
			motor_control(motor_rotate,50,angle_inside);
			break;
	}
	motor_control(motor_up,50,angle_plate);
	steer_control(steer_catch,angle_drop);
	motor_control(motor_up,50,angle_lift_low);
}

void pick_up_low(int color)
{
	motor_control(motor_rotate,50,angle_outside);
	motor_control(motor_up,50,angle_floor);
	steer_control(steer_catch,angle_catch);
	motor_control(motor_up,50,angle_lift_low);
	motor_control(motor_rotate,50,angle_inside);
	motor_control(motor_up,50,angle_plate);
	steer_control(steer_catch,angle_drop);
	motor_control(motor_up,50,angle_lift_low);
}

void put_down_low(int color)
{
	motor_control(motor_rotate,50,angle_inside);
	motor_control(motor_up,50,angle_plate);
	steer_control(steer_catch,angle_catch);
	motor_control(motor_up,50,angle_lift_low);
	motor_control(motor_rotate,50,angle_outside);
	motor_control(motor_up,50,angle_floor);
	steer_control(steer_catch,angle_drop);
	motor_control(motor_up,50,angle_lift_low);
}

void put_down_high(int color)
{
	motor_control(motor_rotate,50,angle_inside);
	motor_control(motor_up,50,angle_plate);
	steer_control(steer_catch,angle_catch);
	motor_control(motor_up,50,angle_lift_low);
	motor_control(motor_rotate,50,angle_outside);
	motor_control(motor_up,50,angle_floor);
	steer_control(steer_catch,angle_drop);
	motor_control(motor_up,50,angle_lift_low);
}

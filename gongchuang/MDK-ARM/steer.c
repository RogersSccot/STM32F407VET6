#include "steer.h"
#include "motor.h"

Steer steer_rotate;
Steer steer_plate;
Steer steer_catch;

float plate_pulse,catch_pulse;

void steer_init(Steer steer)
{
	steer.angle = angle_drop;
	steer.num = 0;
}

void steer_control(Steer steer,float angle)
{
	if(steer.num == 0)
	{
		plate_pulse = 500.0f+(angle)*2000.0f/180.0f;
		__HAL_TIM_SET_COMPARE(&STEER_TIM,TIM_CHANNEL_1,(int)plate_pulse);
	}
	if(steer.num == 1)
	{
		catch_pulse = 500.0f+(angle)*2000.0f/180.0f;
		__HAL_TIM_SET_COMPARE(&STEER_TIM,TIM_CHANNEL_1,(int)catch_pulse);
	}
}

void pick_up_high(int color)
{
	motor_control(motor_rotate,angle_outside);
	motor_control(motor_up,angle_floor);
	steer_control(steer_catch,angle_catch);
	motor_control(motor_up,angle_lift_low);
	motor_control(motor_rotate,angle_inside);
	motor_control(motor_up,angle_plate);
	steer_control(steer_catch,angle_drop);
	motor_control(motor_up,angle_lift_low);
}

void pick_up_low(int color)
{
	motor_control(motor_rotate,angle_outside);
	motor_control(motor_up,angle_floor);
	steer_control(steer_catch,angle_catch);
	motor_control(motor_up,angle_lift_low);
	motor_control(motor_rotate,angle_inside);
	motor_control(motor_up,angle_plate);
	steer_control(steer_catch,angle_drop);
	motor_control(motor_up,angle_lift_low);
}

void put_down_low(int color)
{
	motor_control(motor_rotate,angle_inside);
	motor_control(motor_up,angle_plate);
	steer_control(steer_catch,angle_catch);
	motor_control(motor_up,angle_lift_low);
	motor_control(motor_rotate,angle_outside);
	motor_control(motor_up,angle_floor);
	steer_control(steer_catch,angle_drop);
	motor_control(motor_up,angle_lift_low);
}

void put_down_high(int color)
{
	motor_control(motor_rotate,angle_inside);
	motor_control(motor_up,angle_plate);
	steer_control(steer_catch,angle_catch);
	motor_control(motor_up,angle_lift_low);
	motor_control(motor_rotate,angle_outside);
	motor_control(motor_up,angle_floor);
	steer_control(steer_catch,angle_drop);
	motor_control(motor_up,angle_lift_low);
}

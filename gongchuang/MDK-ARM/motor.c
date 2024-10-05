#include "motor.h"
#include "datou.h"

Motor motor_lf;
Motor motor_rf;
Motor motor_back;
Motor motor_up;
Motor motor_rotate;


void motor_init(Motor motor)
{
	motor.angle = 0;
	motor.speed = 0;
}

void motor_control(Motor motor,float angle)
{
	if(angle >0)
	{
		motor.direct = 1;
	}
	if(angle <0)
	{
		motor.direct = 0;
	}
	//HAL_GPIO_WritePin();
}

void move_foward(float distance)
{
	motor_control(motor_lf,90*distance);
	motor_control(motor_rf,90*distance);
}

void move_back(float distance)
{
	motor_control(motor_lf,-90*distance);
	motor_control(motor_rf,-90*distance);
}

void move_left(float distance)
{
	motor_control(motor_lf,-60*distance);
	motor_control(motor_rf,60*distance);
	motor_control(motor_back,60*0.866*distance);
}

void move_right(float distance)
{
	motor_control(motor_lf,60*distance);
	motor_control(motor_rf,-60*distance);
	motor_control(motor_back,-60*0.866*distance);
}

void turn_left(float angle)
{
	motor_control(motor_lf,60*angle);
	motor_control(motor_rf,-60*angle);
	motor_control(motor_back,60*angle);
}

void turn_right(float angle)
{
	motor_control(motor_lf,-60*angle);
	motor_control(motor_rf,60*angle);
	motor_control(motor_back,-60*angle);
}

#include "steer.h"
#include "motor.h"

Steer steer_rotate;
Steer steer_plate;
Steer steer_catch;

void steer_init(Steer steer)
{
	steer.angle = angle_drop;
}

void steer_control(Steer steer,float angle)
{
	
}

void pick_up(void)
{
	steer_control(steer_rotate,angle_outside);
	motor_control(motor_up,angle_floor);
	steer_control(steer_catch,angle_catch);
	motor_control(motor_up,angle_lift_low);
	steer_control(steer_rotate,angle_inside);
	motor_control(motor_up,angle_plate);
	steer_control(steer_catch,angle_drop);
	motor_control(motor_up,angle_lift_low);
}

void put_down_low(void)
{
	steer_control(steer_rotate,angle_inside);
	motor_control(motor_up,angle_plate);
	steer_control(steer_catch,angle_catch);
	motor_control(motor_up,angle_lift_low);
	steer_control(steer_rotate,angle_outside);
	motor_control(motor_up,angle_floor);
	steer_control(steer_catch,angle_drop);
	motor_control(motor_up,angle_lift_low);
}

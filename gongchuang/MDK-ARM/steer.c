#include "steer.h"
#include "motor.h"
#include "stdio.h"
#include "time.h"

Steer steer_rotate;
Steer steer_plate;
Steer steer_catch;

double plate_pulse,catch_pulse,rotate_pulse;

void steer_init(Steer *steer)
{
	steer->angle = angle_drop;
	steer->num = 0;
}

void steer_control_catch(double angle,double speed)
{
		catch_pulse = 500.0f+(90+speed)*2000.0f/180.0f;
		pulse2_flag2 = 1;
		pulse2_set2 = (int)angle/9.0;
		__HAL_TIM_SetCompare(&STEER_TIM, TIM_CHANNEL_2, (int)catch_pulse);
		HAL_TIM_PWM_Start(&STEER_TIM, TIM_CHANNEL_2);
}

void steer_control(Steer steer,double angle)
{
	// 物料盘
	if(steer.num == 0)
	{
		//printf("plate");
		plate_pulse = 500.0f+(angle)*2000.0f/180.0f;
		//printf("%f",plate_pulse);
		__HAL_TIM_SET_COMPARE(&STEER_TIM,TIM_CHANNEL_1,(int)plate_pulse);
		HAL_TIM_PWM_Start(&STEER_TIM, TIM_CHANNEL_1);
	}
	//抓手
	if(steer.num == 1)
	{
		printf("1");
		catch_pulse = 500.0f+(angle)*2000.0f/180.0f;
		//printf("%f",plate_pulse);
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,(int)catch_pulse);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	}
	// 下方转盘
	if(steer.num == 2)
	{
		//printf("plate");
		rotate_pulse = 500.0f+(angle)*2000.0f/180.0f;
		//printf("%f",plate_pulse);
		__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,(int)rotate_pulse);
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	}
}

//从物料区抓取物体
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

//从地上抓取物体
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

//把物体放在地上
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

//把物体放在第一层物体上
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

void test_catch(void)
{
	steer_control(steer_catch,130);
	printf("1\n");
	HAL_Delay(800);
	motor_control(motor_up, 70, 12);
	//while(pulse4_flag5){printf("%d\n",pulse4_flag5);}
	HAL_Delay(500);
	steer_control(steer_plate,68);
	steer_control(steer_rotate,60);
	printf("2\n");
	HAL_Delay(500);
	motor_control(motor_up, 50, -6);
	HAL_Delay(700);
	
	steer_control(steer_catch,030);
	printf("3\n");
	HAL_Delay(500);
	motor_control(motor_up, 50, 6);
	HAL_Delay(50);
	steer_control(steer_rotate,158);
	HAL_Delay(700);
	printf("4\n");
	motor_control(motor_up, 70, -12);
}

void test_put(void)
{
	steer_control(steer_catch,030);
	printf("1\n");
	HAL_Delay(800);
	motor_control(motor_up, 70, 10);
	//while(pulse4_flag5){printf("%d\n",pulse4_flag5);}
	HAL_Delay(500);
	steer_control(steer_plate,65);
	steer_control(steer_rotate,60);
	printf("2\n");
	HAL_Delay(700);
	motor_control(motor_up, 70, -4);
	HAL_Delay(700);
	
	steer_control(steer_catch,130);
	printf("3\n");
	HAL_Delay(500);
	motor_control(motor_up, 70, 4);
	HAL_Delay(100);
	steer_control(steer_rotate,158);
	HAL_Delay(700);
	printf("4\n");
	motor_control(motor_up, 70, -10);
	HAL_Delay(400);
	steer_control(steer_catch,030);
}

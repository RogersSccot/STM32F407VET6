#include "mymain.h"

uint8_t state_flag;


uint8_t rgb_stack[3] = {1,2,3};

//int fputc(int ch, FILE *f) // printf
//{
//	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xffff);
//	return ch;
//}

//int fgetc(FILE *f) // getchar
//{
//	uint8_t ch = 0;
//	HAL_UART_Receive(&huart1, &ch, 1, 0xffff);
//	return ch;
//}


void mymain(void)
{
	state_machine();
}

void system_init(void)
{
	motor_init(motor_lf);
	motor_init(motor_rf);
	motor_init(motor_back);
	steer_init(steer_rotate);
	steer_init(steer_catch);
	motor_init(motor_up);
}

void state_machine(void)
{
	switch (state_flag)
	{
		case START:
			break;
		case MOVE_1:
			break;
		case SCAN:
			break;
		case MOVE_2:
			break;
		case MATERIAL_AREA:
			break;
		case STORE_AREA:
			break;
		case DEAL_AREA:
			break;
	}
}

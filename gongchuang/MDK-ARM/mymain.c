#include "mymain.h"


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
	motor_init(motor_lb);
	motor_init(motor_rb);
	motor_init(motor_rotate);
}

void state_machine(void)
{
	
}

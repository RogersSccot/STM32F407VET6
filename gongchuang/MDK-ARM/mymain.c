#include "mymain.h"

uint8_t state_flag;
uint8_t received_flag;

uint8_t receive_buff_1[50];
uint8_t USART1_buffer[50];
uint8_t receive_buff_2[50];
uint8_t USART2_buffer[50];
uint8_t receive_buff_3[50];
uint8_t USART3_buffer[50];
uint8_t receive_buff_6[50];
uint8_t USART6_buffer[50];


uint8_t rgb_stack_1[3] = {1,2,3};
uint8_t rgb_stack_2[3] = {1,2,3};

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
	system_init();
	HAL_Delay(500);
	HAL_UART_Transmit(&huart1,"START", 5, 0xff);
	state_machine();
}

void system_init(void)
{
	motor_init(motor_lf);
	motor_init(motor_rf);
	motor_init(motor_back);
	steer_init(steer_plate);
	steer_plate.num = 0;
	steer_init(steer_rotate);
	steer_init(steer_catch);
	steer_catch.num = 1;
	motor_init(motor_up);
}

void state_machine(void)
{
	switch (state_flag)
	{
		case START:
			break;
		case MOVE_1:
			move_foward(10);
			HAL_UART_Transmit(&huart1, "SCANF", 5, 0xff);
			state_flag = SCAN;
			break;
		case SCAN:
			if(received_flag == 1)
			{
				state_flag = MOVE_2;
				received_flag = 0;
			}	
			break;
		case MOVE_2:
			move_foward(10);
			turn_left(90);
			move_foward(15);
			HAL_UART_Transmit(&huart1, "LWLQ1", 5, 0xff);
			state_flag = MATERIAL_AREA;
			break;
		case MATERIAL_AREA:
			if(received_flag == 2)
			{
				state_flag = MOVE_3;
				received_flag = 0;
			}	
			break;
		case MOVE_3:
			move_foward(10);
			turn_left(90);
			move_foward(15);
			HAL_UART_Transmit(&huart1, "LCJG1", 5, 0xff);
			state_flag = DEAL_AREA;
			break;
		case DEAL_AREA:
			if(received_flag == 2)
			{
				state_flag = MOVE_4;
				received_flag = 0;
			}
		case MOVE_4:
			move_foward(10);
			turn_left(90);
			move_foward(15);
			HAL_UART_Transmit(&huart1, "LZCQ1", 5, 0xff);
			state_flag = STORE_AREA;
			break;
		case STORE_AREA:
			state_flag = START;
			break;
	}
}

int i = 0;

void buffer_hadle_USART1(uint8_t *buffer)
{
  HAL_UART_Transmit(&huart1, buffer, 4, 0xff);
	if((buffer[0] == 'Q')&&(buffer[1] == 'R'))
	{
		rgb_stack_1[0] = buffer[2] - '0';
		rgb_stack_1[1] = buffer[3] - '0';
		rgb_stack_1[2] = buffer[4] - '0';
		rgb_stack_2[0] = buffer[6] - '0';
		rgb_stack_2[1] = buffer[7] - '0';
		rgb_stack_2[2] = buffer[8] - '0';
		received_flag = 1;
	}
	
	if((buffer[0] == 'C')&&(buffer[1] == 'A')&&(buffer[2] == 'T')&&(buffer[3] == 'C')&&(buffer[4] == 'H'))
	{
		pick_up_high((buffer[5]-'0'));
		i++;
	}
	if((buffer[0] == 'C')&&(buffer[1] == 'A')&&(buffer[2] == 'T')&&(buffer[3] == 'L'))
	{
		pick_up_low((buffer[4]-'0'));
		i++;
	}
	if((buffer[0] == 'P')&&(buffer[1] == 'U')&&(buffer[2] == 'T')&&(buffer[3] == 'L'))
	{
		put_down_low((buffer[4]-'0'));
		i++;
	}
	if((buffer[0] == 'P')&&(buffer[1] == 'U')&&(buffer[2] == 'T')&&(buffer[3] == 'H'))
	{
		put_down_high((buffer[4]-'0'));
		i++;
	}
	if((buffer[0] == 'M')&&(buffer[1] == 'O')&&(buffer[2] == 'V')&&(buffer[3] == 'L'))
	{
		move_left((buffer[4]-'0')*GAP_LENGTH);
	}
	if((buffer[0] == 'M')&&(buffer[1] == 'O')&&(buffer[2] == 'V')&&(buffer[3] == 'R'))
	{
		move_right((buffer[4]-'0')*GAP_LENGTH);
	}
	if(i>=3)
	{
		i=0;
		received_flag = 2;
	}
}

void buffer_hadle_USART2(uint8_t *buffer)
{
  HAL_UART_Transmit(&huart2, buffer, 4, 0xff);
}

void buffer_hadle_USART3(uint8_t *buffer)
{
  HAL_UART_Transmit(&huart3, buffer, 4, 0xff);
}

void buffer_hadle_USART6(uint8_t *buffer)
{
  HAL_UART_Transmit(&huart6, buffer, 4, 0xff);
}

void DMA_USART_Init(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
  {
    __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
    HAL_UART_Receive_DMA(huart, receive_buff_1, 50);
  }

  if (huart->Instance == USART2)
  {
    __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
    HAL_UART_Receive_DMA(huart, receive_buff_2, 50);
  }

  if (huart->Instance == USART3)
  {
    __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
    HAL_UART_Receive_DMA(huart, receive_buff_3, 50);
  }
	
	if (huart->Instance == USART6)
  {
    __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
    HAL_UART_Receive_DMA(huart, receive_buff_6, 50);
  }
}

void USAR_UART_IDLECallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
  {
    // ????DMA??
    HAL_UART_DMAStop(huart);

    // ??????????
    uint8_t data_length = 50 - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);

    // ????:???????????
    // printf("Receive Data(length = %d): ",data_length);
    //    HAL_UART_Transmit(huart,receive_Buff,data_length,0x200);
    // ????????????????
    memcpy(USART1_buffer, receive_buff_1, 50);
    // printf("%s\r\n",receive_buff);
    buffer_hadle_USART1(USART1_buffer);
    // ??????
    memset(receive_buff_1, 0, data_length);
    data_length = 0;

    // ???DMA?? ??255????
    HAL_UART_Receive_DMA(huart, (uint8_t *)receive_buff_1, 50);
  }

  if (huart->Instance == USART2)
  {
    // ????DMA??
    HAL_UART_DMAStop(huart);

    // ??????????
    uint8_t data_length = 50 - __HAL_DMA_GET_COUNTER(&hdma_usart2_rx);

    // ????:???????????
    // printf("Receive Data(length = %d): ",data_length);
    //    HAL_UART_Transmit(huart,receive_Buff,data_length,0x200);
    // ????????????????
    memcpy(USART2_buffer, receive_buff_2, 50);
    buffer_hadle_USART2(USART2_buffer);
    // ??????
    memset(receive_buff_2, 0, data_length);
    data_length = 0;

    // ???DMA?? ??255????
    HAL_UART_Receive_DMA(huart, (uint8_t *)receive_buff_2, 50);
  }

  if (huart->Instance == USART3)
  {
    //    led_Big.LED_Flip();
    // ????DMA??
    HAL_UART_DMAStop(huart);

    // ??????????
    uint8_t data_length = 50 - __HAL_DMA_GET_COUNTER(&hdma_usart3_rx);

    // ????:???????????
    // printf("Receive Data(length = %d): ",data_length);
    //    HAL_UART_Transmit(huart,rx_buffer,data_length,0x200);
    // ????????????????
    memcpy(USART3_buffer, receive_buff_3, 50);
    // printf("%s",rx_buffer);
    buffer_hadle_USART3(USART3_buffer);
    // ??????
    memset(receive_buff_3, 0, data_length);
    data_length = 0;

    // ???DMA?? ??255????
    HAL_UART_Receive_DMA(huart, (uint8_t *)receive_buff_3, 50);
  }
	
	if (huart->Instance == USART6)
  {
    //    led_Big.LED_Flip();
    // ????DMA??
    HAL_UART_DMAStop(huart);

    // ??????????
    uint8_t data_length = 50 - __HAL_DMA_GET_COUNTER(&hdma_usart6_rx);

    // ????:???????????
    // printf("Receive Data(length = %d): ",data_length);
    //    HAL_UART_Transmit(huart,rx_buffer,data_length,0x200);
    // ????????????????
    memcpy(USART6_buffer, receive_buff_6, 50);
    // printf("%s",rx_buffer);
    buffer_hadle_USART3(USART6_buffer);
    // ??????
    memset(receive_buff_6, 0, data_length);
    data_length = 0;

    // ???DMA?? ??255????
    HAL_UART_Receive_DMA(huart, (uint8_t *)receive_buff_6, 50);
  }
}

/*
 * ????????,????stm32f4xx_it.c
 */
void Bluetooth_UART_IRQHandler(UART_HandleTypeDef *huart)
{ // ??????1
  if (huart->Instance == USART1)
  { // ????????
    if (RESET != __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))
    { // ????????(??????????)
      __HAL_UART_CLEAR_IDLEFLAG(huart);
      // ????????
      USAR_UART_IDLECallback(&huart1);
    }
  }

  if (huart->Instance == USART2)
  { // ????????
    if (RESET != __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))
    { // ????????(??????????)
      __HAL_UART_CLEAR_IDLEFLAG(huart);
      // ????????
      USAR_UART_IDLECallback(&huart2);
    }
  }

  if (huart->Instance == USART3)
  { // ????????
    if (RESET != __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))
    { // ????????(??????????)
      __HAL_UART_CLEAR_IDLEFLAG(huart);
      // ????????
      USAR_UART_IDLECallback(&huart3);
    }
  }
	
	if (huart->Instance == USART6)
  { // ????????
    if (RESET != __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))
    { // ????????(??????????)
      __HAL_UART_CLEAR_IDLEFLAG(huart);
      // ????????
      USAR_UART_IDLECallback(&huart6);
    }
  }
}



#include "uart.h"


uint8_t bad_order = 0;
uint8_t bad_begin = 0;
uint8_t buffer1[4];

uint8_t rgb_stack_1[3] = {1, 2, 3};
uint8_t rgb_stack_2[3] = {1, 2, 3};

uint8_t receive_buff_1[50];
uint8_t USART1_buffer[50];
uint8_t receive_buff_2[50];
uint8_t USART2_buffer[50];
uint8_t receive_buff_3[50];
uint8_t USART3_buffer[50];
uint8_t receive_buff_6[50];
uint8_t USART6_buffer[50];

int catch_flag;
int put_flag;

double dis_set;
double sp2;

void chelk_buffer(uint8_t *buffer)
{
  // 首先判断之前是否有不完整指令
  if (bad_order == 0)
  {
    // 此时没有不完整指令，接下来判断这一条指令是否完整
    if (buffer[3] == 00)
    {
      // 进入这里说明这一条指令为不完整指令
      bad_order = 1;
      for (int i = 0; i < 4; i++)
      {
        if (buffer[i] != 00)
        {
          // 这一位还是正常的
          buffer1[i] = buffer[i];
        }
        else
        {
          // 这一位是不对的
          bad_begin = i;
          break;
        }
      }
    }
    else
    {
      // 进入这里说明这一条指令为完整指令
      bad_order = 0;
    }
  }
  // 这里就说明已经存在不完整指令
  else
  {
    // 此时我们需要将两条指令拼接起来
    for (int i = bad_begin; i < 4; i++)
    {
      buffer1[i] = buffer[i - bad_begin];
    }
    // 结束后将buffer设为新的buffer1
    for (int i = 0; i < 4; i++)
    {
      buffer[i] = buffer1[i];
    }
    bad_order = 0;
    bad_begin = 0;
  }
}

// uart1 buffer handle
void buffer_hadle_USART1(uint8_t *buffer)
{
		chelk_buffer(buffer);
  
    //HAL_UART_Transmit(&huart1, buffer, 4, 0xff);
    // reveal the QR on screen
    if ((buffer[0] == 'Q') && (buffer[1] == 'R'))
    {
        rgb_stack_1[0] = buffer[2] - '0';
        rgb_stack_1[1] = buffer[3] - '0';
        rgb_stack_1[2] = buffer[4] - '0';
        rgb_stack_2[0] = buffer[6] - '0';
        rgb_stack_2[1] = buffer[7] - '0';
        rgb_stack_2[2] = buffer[8] - '0';
        printf("t1.txt=\"%d%d%d-%d%d%d\"\xff\xff\xff", rgb_stack_1[0], rgb_stack_1[1], rgb_stack_1[2], rgb_stack_2[0], rgb_stack_2[1], rgb_stack_2[2]);
        received_flag = 1;
    }

    // catch the goods from the material area (WLQ)
    if ((buffer[0] == 'C') && (buffer[1] == 'A') && (buffer[2] == 'T') && (buffer[3] == 'C') && (buffer[4] == 'H'))
    {
        catch_flag = 1;
        goods_num++;
    }

    // catch the goods from the deal area (CJG)
    if ((buffer[0] == 'C') && (buffer[1] == 'A') && (buffer[2] == 'T') && (buffer[3] == 'L'))
    {
        catch_flag = 1;
        goods_num++;
    }

    // put down the goods to the deal area (CJG)
    if ((buffer[0] == 'P') && (buffer[1] == 'U') && (buffer[2] == 'T') && (buffer[3] == 'L'))
    {
        put_flag = 1;
        goods_num++;
    }

    // put down the goods to the store area (ZCQ)
    if ((buffer[0] == 'P') && (buffer[1] == 'U') && (buffer[2] == 'T') && (buffer[3] == 'H'))
    {
        put_flag = 1;
        goods_num++;
    }

    // move to the left
    if ((buffer[0] == 'M') && (buffer[1] == 'O') && (buffer[2] == 'V') && (buffer[3] == 'L'))
    {
        move_left(10, (buffer[4] - '0') * GAP_LENGTH);
    }

    // move to the right
    if ((buffer[0] == 'M') && (buffer[1] == 'O') && (buffer[2] == 'V') && (buffer[3] == 'R'))
    {
        move_right(10, (buffer[4] - '0') * GAP_LENGTH);
    }

    // move foward
    if ((buffer[0] == 'M') && (buffer[1] == 'F'))
    {
        dis_set = (buffer[2] - '0') * 100 + (buffer[3] - '0') * 10 + (buffer[4] - '0');
        move_foward(10, dis_set);
    }

    // move back
    if ((buffer[0] == 'M') && (buffer[1] == 'B'))
    {
        dis_set = (buffer[2] - '0') * 100 + (buffer[3] - '0') * 10 + (buffer[4] - '0');
        move_back(10, dis_set);
    }

    // move left
    if ((buffer[0] == 'M') && (buffer[1] == 'L'))
    {
        dis_set = (buffer[2] - '0') * 100 + (buffer[3] - '0') * 10 + (buffer[4] - '0');
        move_left(10, dis_set);
    }

    // move right
    if ((buffer[0] == 'M') && (buffer[1] == 'R'))
    {
        dis_set = (buffer[2] - '0') * 100 + (buffer[3] - '0') * 10 + (buffer[4] - '0');
        move_right(10, dis_set);
    }
    // 单独控制上下运动的电机，格式为UP+xxxyyy,+为向上，xxx为距离，yyy为速度（这个电机值非常小，绝对不要给太多）
		if ((buffer[0] == 'U') && (buffer[1] == 'P'))
    {
        // ZS200030
			if((buffer[2] == '+'))
			{
        dis_set = (buffer[3] - '0') * 100 + (buffer[4] - '0') * 10 + (buffer[5] - '0');
        sp2 = (buffer[6] - '0') * 100 + (buffer[7] - '0') * 10 + (buffer[8] - '0');
			}
			if((buffer[2] == '-'))
			{
        dis_set = -(buffer[3] - '0') * 100 - (buffer[4] - '0') * 10 - (buffer[5] - '0');
        sp2 = (buffer[6] - '0') * 100 + (buffer[7] - '0') * 10 + (buffer[8] - '0');
			}
        motor_control(motor_up, sp2, dis_set);
			HAL_UART_Transmit(&huart1, buffer, 9, 0xff);
    }
		// 单独控制抓手旋转的电机，格式为ROxxx
		if ((buffer[0] == 'R') && (buffer[1] == 'O'))
    {
			dis_set = (buffer[2] - '0') * 100 + (buffer[3] - '0') * 10 + (buffer[4] - '0');
			steer_control(steer_rotate,dis_set);
//        printf("%f\n", HAL_GetTick() / 1000.0);
//        // ZS200030
//			if((buffer[2] == '+'))
//			{
//        dis_set = (buffer[3] - '0') * 100 + (buffer[4] - '0') * 10 + (buffer[5] - '0');
//        sp2 = (buffer[6] - '0') * 100 + (buffer[7] - '0') * 10 + (buffer[8] - '0');
//			}
//			if((buffer[2] == '-'))
//			{
//        dis_set = -(buffer[3] - '0') * 100 - (buffer[4] - '0') * 10 - (buffer[5] - '0');
//        sp2 = (buffer[6] - '0') * 100 + (buffer[7] - '0') * 10 + (buffer[8] - '0');
//			}
//        motor_control(motor_rotate, sp2, dis_set);
    }
		 // 单独控制左前轮电机，格式为UP+xxxyyy，xxx为距离，yyy为速度
		if ((buffer[0] == 'L') && (buffer[1] == 'F'))
    {
        printf("%f\n", HAL_GetTick() / 1000.0);
        // ZS200030
			if((buffer[2] == '+'))
			{
        dis_set = (buffer[3] - '0') * 100 + (buffer[4] - '0') * 10 + (buffer[5] - '0');
        sp2 = (buffer[6] - '0') * 100 + (buffer[7] - '0') * 10 + (buffer[8] - '0');
			}
			if((buffer[2] == '-'))
			{
        dis_set = -(buffer[3] - '0') * 100 - (buffer[4] - '0') * 10 - (buffer[5] - '0');
        sp2 = (buffer[6] - '0') * 100 + (buffer[7] - '0') * 10 + (buffer[8] - '0');
			}
        motor_control(motor_lf, sp2, dis_set);
    }
		// 单独控制右前轮电机，格式为UP+xxxyyy，xxx为距离，yyy为速度
		if ((buffer[0] == 'R') && (buffer[1] == 'F'))
    {
        printf("%f\n", HAL_GetTick() / 1000.0);
        // ZS200030
			if((buffer[2] == '+'))
			{
        dis_set = (buffer[3] - '0') * 100 + (buffer[4] - '0') * 10 + (buffer[5] - '0');
        sp2 = (buffer[6] - '0') * 100 + (buffer[7] - '0') * 10 + (buffer[8] - '0');
			}
			if((buffer[2] == '-'))
			{
        dis_set = -(buffer[3] - '0') * 100 - (buffer[4] - '0') * 10 - (buffer[5] - '0');
        sp2 = (buffer[6] - '0') * 100 + (buffer[7] - '0') * 10 + (buffer[8] - '0');
			}
        motor_control(motor_rf, sp2, dis_set);
    }
		// 单独控制后轮电机，格式为UP+xxxyyy，xxx为距离，yyy为速度
		if ((buffer[0] == 'B') && (buffer[1] == 'K'))
    {
        printf("%f\n", HAL_GetTick() / 1000.0);
        // ZS200030
			if((buffer[2] == '+'))
			{
        dis_set = (buffer[3] - '0') * 100 + (buffer[4] - '0') * 10 + (buffer[5] - '0');
        sp2 = (buffer[6] - '0') * 100 + (buffer[7] - '0') * 10 + (buffer[8] - '0');
			}
			if((buffer[2] == '-'))
			{
        dis_set = -(buffer[3] - '0') * 100 - (buffer[4] - '0') * 10 - (buffer[5] - '0');
        sp2 = (buffer[6] - '0') * 100 + (buffer[7] - '0') * 10 + (buffer[8] - '0');
			}
        motor_control(motor_back, sp2, dis_set);
    }
		// 控制物料盘舵机，格式为PTxxx，xxx为固定角度
		if ((buffer[0] == 'P') && (buffer[1] == 'T'))
    {
			dis_set = (buffer[2] - '0') * 100 + (buffer[3] - '0') * 10 + (buffer[4] - '0');
			steer_control(steer_plate,dis_set);
		}
		// 控制抓手舵机，格式为CA+xxx，+为抓，xxx为相对角度（千万不要给大值）
		if ((buffer[0] == 'C') && (buffer[1] == 'A'))
    {
//			if(buffer[2] == '+')
//			{
//			dis_set = (buffer[3] - '0') * 100 + (buffer[4] - '0') * 10 + (buffer[5] - '0');
//			}
//			if(buffer[2] == '-')
//			{
//			dis_set = -(buffer[3] - '0') * 100 - (buffer[4] - '0') * 10 - (buffer[5] - '0');
//			}
			dis_set = (buffer[2] - '0') * 100 + (buffer[3] - '0') * 10 + (buffer[4] - '0');
			steer_control(steer_catch,dis_set);
		}
    buffer[0] = '0';
}

void buffer_hadle_USART2(uint8_t *buffer)
{
		chelk_buffer(buffer);
    HAL_UART_Transmit(&huart2, buffer, 4, 0xff);
}

void buffer_hadle_USART3(uint8_t *buffer)
{		
		chelk_buffer(buffer);
    HAL_UART_Transmit(&huart3, buffer, 4, 0xff);
}

void buffer_hadle_USART6(uint8_t *buffer)
{
		chelk_buffer(buffer);
    HAL_UART_Transmit(&huart6, buffer, 4, 0xff);
}

// The code below is able to work normally, Do not change it
// The code below is able to work normally, Do not change it
// The code below is able to work normally, Do not change it
// The code below is able to work normally, Do not change it
// The code below is able to work normally, Do not change it
// The code below is able to work normally, Do not change it
// The code below is able to work normally, Do not change it
// The code below is able to work normally, Do not change it
// The code below is able to work normally, Do not change it
// The code below is able to work normally, Do not change it
// The code below is able to work normally, Do not change it
// The code below is able to work normally, Do not change it
// The code below is able to work normally, Do not change it
// The code below is able to work normally, Do not change it
// The code below is able to work normally, Do not change it
// The code below is able to work normally, Do not change it
// The code below is able to work normally, Do not change it
// The code below is able to work normally, Do not change it
// The code below is able to work normally, Do not change it
// The code below is able to work normally, Do not change it

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
        HAL_UART_DMAStop(huart);
        uint8_t data_length = 50 - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);
        memcpy(USART1_buffer, receive_buff_1, 50);
        buffer_hadle_USART1(USART1_buffer);
        memset(receive_buff_1, 0, data_length);
        data_length = 0;
        HAL_UART_Receive_DMA(huart, (uint8_t *)receive_buff_1, 50);
    }

    if (huart->Instance == USART2)
    {
        HAL_UART_DMAStop(huart);
        uint8_t data_length = 50 - __HAL_DMA_GET_COUNTER(&hdma_usart2_rx);
        memcpy(USART2_buffer, receive_buff_2, 50);
        buffer_hadle_USART2(USART2_buffer);
        memset(receive_buff_2, 0, data_length);
        data_length = 0;
        HAL_UART_Receive_DMA(huart, (uint8_t *)receive_buff_2, 50);
    }

    if (huart->Instance == USART3)
    {
        HAL_UART_DMAStop(huart);
        uint8_t data_length = 50 - __HAL_DMA_GET_COUNTER(&hdma_usart3_rx);
        memcpy(USART3_buffer, receive_buff_3, 50);
        buffer_hadle_USART3(USART3_buffer);
        memset(receive_buff_3, 0, data_length);
        data_length = 0;
        HAL_UART_Receive_DMA(huart, (uint8_t *)receive_buff_3, 50);
    }

    if (huart->Instance == USART6)
    {
        HAL_UART_DMAStop(huart);
        uint8_t data_length = 50 - __HAL_DMA_GET_COUNTER(&hdma_usart6_rx);
        memcpy(USART6_buffer, receive_buff_6, 50);
        buffer_hadle_USART3(USART6_buffer);
        memset(receive_buff_6, 0, data_length);
        data_length = 0;
        HAL_UART_Receive_DMA(huart, (uint8_t *)receive_buff_6, 50);
    }
}

/*
 * ,stm32f4xx_it.c
 */
void Bluetooth_UART_IRQHandler(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        if (RESET != __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))
        {
            __HAL_UART_CLEAR_IDLEFLAG(huart);
            USAR_UART_IDLECallback(&huart1);
        }
    }

    if (huart->Instance == USART2)
    {
        if (RESET != __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))
        {
            __HAL_UART_CLEAR_IDLEFLAG(huart);
            USAR_UART_IDLECallback(&huart2);
        }
    }

    if (huart->Instance == USART3)
    {
        if (RESET != __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))
        {
            __HAL_UART_CLEAR_IDLEFLAG(huart);
            USAR_UART_IDLECallback(&huart3);
        }
    }

    if (huart->Instance == USART6)
    {
        if (RESET != __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))
        {
            __HAL_UART_CLEAR_IDLEFLAG(huart);
            USAR_UART_IDLECallback(&huart6);
        }
    }
}

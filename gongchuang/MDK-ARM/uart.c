#include "uart.h"

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

double dis_set;

// uart1 buffer handle
void buffer_hadle_USART1(uint8_t *buffer)
{
		HAL_UART_Transmit(&huart1, buffer, 4, 0xff);
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
        pick_up_high((buffer[5] - '0'));
        goods_num++;
    }

    // catch the goods from the deal area (CJG)
    if ((buffer[0] == 'C') && (buffer[1] == 'A') && (buffer[2] == 'T') && (buffer[3] == 'L'))
    {
        pick_up_low((buffer[4] - '0'));
        goods_num++;
    }

    // put down the goods to the deal area (CJG)
    if ((buffer[0] == 'P') && (buffer[1] == 'U') && (buffer[2] == 'T') && (buffer[3] == 'L'))
    {
        put_down_low((buffer[4] - '0'));
        goods_num++;
    }

    // put down the goods to the store area (ZCQ)
    if ((buffer[0] == 'P') && (buffer[1] == 'U') && (buffer[2] == 'T') && (buffer[3] == 'H'))
    {
        put_down_high((buffer[4] - '0'));
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
        dis_set = (buffer[2] - '0') * 10 + (buffer[3] - '0') * 10 + (buffer[4] - '0');
        move_foward(10, dis_set);
    }

    // move back
    if ((buffer[0] == 'M') && (buffer[1] == 'B'))
    {
        dis_set = (buffer[2] - '0') * 10 + (buffer[3] - '0') * 10 + (buffer[4] - '0');
        move_back(10, dis_set);
    }

    // move left
    if ((buffer[0] == 'M') && (buffer[1] == 'L'))
    {
        dis_set = (buffer[2] - '0') * 10 + (buffer[3] - '0') * 10 + (buffer[4] - '0');
        move_left(10, dis_set);
    }

    // move right
    if ((buffer[0] == 'M') && (buffer[1] == 'R'))
    {
        dis_set = (buffer[2] - '0') * 10 + (buffer[3] - '0') * 10 + (buffer[4] - '0');
        move_right(10, dis_set);
    }
    if ((buffer[0] == 'Z') && (buffer[1] == 'S'))
    {
        printf("ZS");
        dis_set = (buffer[2] - '0') * 10 + (buffer[3] - '0') * 10 + (buffer[4] - '0');
        double sp1 = (buffer[5] - '0') * 10 + (buffer[6] - '0') * 10 + (buffer[7] - '0');
        motor_control(motor_lf, sp1, dis_set);
    }
		buffer[0] = '0';
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

// the code below is able to work normally do not change it
// the code below is able to work normally do not change it
// the code below is able to work normally do not change it
// the code below is able to work normally do not change it
// the code below is able to work normally do not change it

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

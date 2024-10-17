#include "mymain.h"

uint8_t state_flag;
uint8_t received_flag;

int goods_num = 0;

void mymain(void)
{
	//steer_control(steer_catch,20);
	//steer_control(steer_plate,20);
  state_machine();
}

void system_init(void)
{
  HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_3);
  HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_4);
	HAL_TIM_PWM_Stop_IT(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop_IT(&htim2, TIM_CHANNEL_3);
  HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
  // start the timer4
  HAL_TIM_Base_Start_IT(&htim1);
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_Base_Start_IT(&htim3);

  motor_init(&motor_lf);
  motor_lf.num = 0;
  motor_lf.tim = htim1;
  motor_lf.channel = TIM_CHANNEL_3;

  motor_init(&motor_rf);
  motor_rf.num = 1;
  motor_rf.tim = htim1;
  motor_rf.channel = TIM_CHANNEL_4;

  motor_init(&motor_back);
  motor_back.num = 2;
  motor_back.tim = htim3;
  motor_back.channel = TIM_CHANNEL_1;

  motor_init(&motor_rotate);
  motor_rotate.num = 3;
  motor_rotate.tim = htim1;
  motor_rotate.channel = TIM_CHANNEL_1;

  motor_init(&motor_up);
  motor_up.num = 4;
  motor_up.tim = htim1;
  motor_up.channel = TIM_CHANNEL_2;

  steer_init(&steer_plate);
  steer_plate.num = 0;
  steer_init(&steer_catch);
  steer_catch.num = 1;
}

void state_machine(void)
{
  if (goods_num >= 3)
  {
    goods_num = 0;
    received_flag = 2;
  }
  switch (state_flag)
  {
  case START:
    break;
  case MOVE_1:
    while ((pulse4_flag3 != 0) || (pulse4_flag2 != 0) || (pulse4_flag1 != 0))
    {
    }
    move_foward(10, 65);
    HAL_UART_Transmit(&huart1, "SCANF", 5, 0xff);
    state_flag = SCAN;
    break;
  case SCAN:
    if (received_flag == 1)
    {
      state_flag = MOVE_2;
      received_flag = 0;
    }
    break;
  case MOVE_2:
    while ((pulse4_flag3 != 0) || (pulse4_flag2 != 0) || (pulse4_flag1 != 0))
    {
    }
    move_foward(10, 80);
    HAL_UART_Transmit(&huart1, "LWLQ1", 5, 0xff);
    state_flag = MATERIAL_AREA;
    break;
  case MATERIAL_AREA:
    if (received_flag == 2)
    {
      state_flag = MOVE_3;
      received_flag = 0;
    }
    break;
  case MOVE_3:
    while ((pulse4_flag3 != 0) || (pulse4_flag2 != 0) || (pulse4_flag1 != 0))
    {
    }
    move_back(10, 40);
    while ((pulse4_flag3 != 0) || (pulse4_flag2 != 0) || (pulse4_flag1 != 0))
    {
    }
    turn_left(180);
    while ((pulse4_flag3 != 0) || (pulse4_flag2 != 0) || (pulse4_flag1 != 0))
    {
    }
    move_right(10, 214);
    HAL_UART_Transmit(&huart1, "LCJG1", 5, 0xff);
    state_flag = DEAL_AREA;
    break;
  case DEAL_AREA:
    if (received_flag == 3)
    {
      state_flag = MOVE_4;
      received_flag = 0;
    }
  case MOVE_4:
    while ((pulse4_flag3 != 0) || (pulse4_flag2 != 0) || (pulse4_flag1 != 0))
    {
    }
    move_back(10, 102); // plus car length
    while ((pulse4_flag3 != 0) || (pulse4_flag2 != 0) || (pulse4_flag1 != 0))
    {
    }
    move_left(10, 102);
    while ((pulse4_flag3 != 0) || (pulse4_flag2 != 0) || (pulse4_flag1 != 0))
    {
    }
    turn_right(90);
    HAL_UART_Transmit(&huart1, "LZCQ1", 5, 0xff);
    state_flag = STORE_AREA;
    break;
  case STORE_AREA:
    if (received_flag == 2)
    {
      state_flag = MOVE_5;
      received_flag = 0;
    }
  case MOVE_5:
    while ((pulse4_flag3 != 0) || (pulse4_flag2 != 0) || (pulse4_flag1 != 0))
    {
    }
    move_back(10, 102);
    while ((pulse4_flag3 != 0) || (pulse4_flag2 != 0) || (pulse4_flag1 != 0))
    {
    }
    move_left(10, 42.5);
    while ((pulse4_flag3 != 0) || (pulse4_flag2 != 0) || (pulse4_flag1 != 0))
    {
    }
    turn_right(90);
    HAL_UART_Transmit(&huart1, "LWLQ1", 5, 0xff);
    state_flag = MATERIAL_AREA;
    break;
  }
}

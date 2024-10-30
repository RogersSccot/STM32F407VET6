#include "time.h"

int pulse4_flag1;
int pulse4_1;
int pulse4_set1;
int pulse4_flag2;
int pulse4_2;
int pulse4_set2;
int pulse4_flag3;
int pulse4_3;
int pulse4_set3;
int pulse4_flag4;
int pulse4_4;
int pulse4_set4;
int pulse4_flag5;
int pulse4_5;
int pulse4_set5;
int pulse2_flag2;
int pulse2_2;
int pulse2_set2;

long long int time_Tick = 0;
double time_Tick_s = 0;

// the timer interupt callback function
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    // 定时器1，现在是下面左右两个电机
    if (htim->Instance == MOTOR_MOVE_TIM.Instance)
    {
        // front left motor
        if (pulse4_flag1 == 1)
        {
            // printf("pulse4_flag1");
            pulse4_1++;
            if (pulse4_1 == pulse4_set1)
            {
                pulse4_1 = 0;
                pulse4_flag1 = 0;
                pulse4_set1 = 0;
                HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_3);
                //printf("%f\n", HAL_GetTick() / 1000.0);
            }
        }
        // front right motor
        if (pulse4_flag2 == 1)
        {
            pulse4_2++;
            if (pulse4_2 == pulse4_set2)
            {
                pulse4_2 = 0;
                pulse4_flag2 = 0;
                pulse4_set2 = 0;
                HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_4);
                //printf("%f\n", HAL_GetTick() / 1000.0);
            }
        }
    }

    // 定时器3 现在是底盘后方的电机
    if (htim->Instance == MOTOR_UP_TIM.Instance)
    {
        if (pulse4_flag3 == 1)
        {
            pulse4_3++;
            if (pulse4_3 == pulse4_set3)
            {
                pulse4_3 = 0;
                pulse4_flag3 = 0;
                pulse4_set3 = 0;
                HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
                //printf("%f\n", HAL_GetTick() / 1000.0);
            }
        }
    }
		//上面的电机，升降用的
		if (htim->Instance == htim8.Instance)
    {
        if (pulse4_flag5 == 1)
        {
            pulse4_5++;
						printf("%d    %d\n",pulse4_5,pulse4_set5);
            if (pulse4_5 == pulse4_set5)
            {
                pulse4_5 = 0;
                pulse4_flag5 = 0;
                pulse4_set5 = 0;
                HAL_TIM_PWM_Stop_IT(&htim8, TIM_CHANNEL_3);
                //printf("%f\n", HAL_GetTick() / 1000.0);
            }
        }
    }

    // 间隔定时器，频率固定，可以用来刷PID陀螺仪之类的（可能）
    if (htim->Instance == GAP_TIM.Instance)
    {
        time_Tick++;
        time_Tick_s = time_Tick / 10.0;
    }
}

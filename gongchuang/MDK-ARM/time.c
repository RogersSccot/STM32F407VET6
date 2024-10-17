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

long long int time_Tick = 0;
double time_Tick_s = 0;

// the timer interupt callback function
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == MOTOR_MOVE_TIM.Instance)
    {
        // pulse4_flag1 only used to stepper motor
        if (pulse4_flag1 == 1)
        {
            pulse4_1++;
            // accelerate
            if (((HAL_GetTick() / 1000.0 - begin4_time1) < t_acc) && (((HAL_GetTick() / 1000.0 - begin4_time1) > 0)))
            {
                __HAL_TIM_SetAutoreload(&htim1, (int)6990.0 / (a4_acc1 * time_Tick_s));
                __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, (int)2330.0 / (a4_acc1 * time_Tick_s));
            }
            // now we are at a constant speed
            // decelerate
            if (((end4_time1 - HAL_GetTick() / 1000.0) < t_acc) && (((end4_time1 - HAL_GetTick() / 1000.0) > 0)))
            {
                __HAL_TIM_SetAutoreload(&htim1, (int)6990.0 / (a4_acc1 * time_Tick_s));
                __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, (int)2330.0 / (a4_acc1 * time_Tick_s));
            }
            if (pulse4_1 == pulse4_set1)
            {
                pulse4_1 = 0;
                pulse4_flag1 = 0;
                pulse4_set1 = 0;
                HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_3);
            }
        }

        if (pulse4_flag2 == 1)
        {
            pulse4_2++;
            if (pulse4_2 == pulse4_set2)
            {
                pulse4_2 = 0;
                pulse4_flag2 = 0;
                pulse4_set2 = 0;
                HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_4);
            }
        }
    }
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
            }
        }
    }
    if (htim->Instance == GAP_TIM.Instance)
    {
        time_Tick++;
        time_Tick_s = time_Tick / 10.0;
    }
}

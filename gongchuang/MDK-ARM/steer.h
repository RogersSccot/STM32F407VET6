#ifndef _STEER_H
#define _STEER_H


#define STEER_UP_CHANNEL TIM_CHANNEL_1
#define STEER_CATCH_CHANNEL TIM_CHANNEL_2

#define STEER_TIM htim2

typedef struct _STEER
{
    float angle; 
} Steer;

void steer_init(Steer steer);
void pick_up(void);
void put_down(void);

#endif

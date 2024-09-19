#ifndef _STEER_H
#define _STEER_H


#define STEER_ROTATE_CHANNEL TIM_CHANNEL_1
#define STEER_CATCH_CHANNEL TIM_CHANNEL_2
#define STEER_PLATE_CHANNEL TIM_CHANNEL_3

#define STEER_TIM htim2

#define angle_inside 0
#define angle_outside 0

#define angle_catch 0
#define angle_drop 0

#define angle_red
#define angle_blue
#define angle_green

typedef struct _STEER
{
    float angle; 
} Steer;

extern Steer steer_rotate;
extern Steer steer_plate;
extern Steer steer_catch;

void steer_init(Steer steer);
void steer_control(Steer steer,float angle);
void pick_up(void);
void put_down_low(void);

#endif

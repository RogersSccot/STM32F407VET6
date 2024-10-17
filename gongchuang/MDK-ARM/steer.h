#ifndef _STEER_H
#define _STEER_H


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
    double angle;
		int num;
} Steer;

extern Steer steer_rotate;
extern Steer steer_plate;
extern Steer steer_catch;

void steer_init(Steer *steer);
void steer_control(Steer steer,double angle);
void pick_up_high(int color);
void pick_up_low(int color);
void put_down_low(int color);
void put_down_high(int color);

#endif

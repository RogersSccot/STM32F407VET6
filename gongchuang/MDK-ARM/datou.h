#ifndef __DATOU_H
#define __DATOU_H

#include "main.h"

typedef struct 
{
    uint8_t controlBytes[6];
    uint8_t lastControlBytes[6];

} StepperMotorControl;
typedef struct 
{
    uint8_t controlBytes[9];
    uint8_t lastControlBytes[9];
	float now_angle;
} StepperMotorControl_location;
typedef  enum 
{
	forward=0x12,		//?
	reverse=0x02		//?
}Command;
extern StepperMotorControl moto1;
extern StepperMotorControl moto2;
extern StepperMotorControl moto3;
extern StepperMotorControl moto4;
void StepperMotorControl_init(StepperMotorControl *control, uint8_t address);
void set_speed(StepperMotorControl *control, uint8_t direction, uint16_t speed);
void set_acceleration(StepperMotorControl *control, uint16_t acceleration);
extern StepperMotorControl_location moto_9;//?
extern StepperMotorControl_location moto_8;//?
void StepperMotorControl_init_location(StepperMotorControl_location *control, uint8_t address) ;
void set_angle_control_location(StepperMotorControl_location *control, float target_angle_num);

#endif

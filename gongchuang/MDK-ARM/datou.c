#include "datou.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <usart.h>
StepperMotorControl moto1;//???
StepperMotorControl moto2;//???
StepperMotorControl moto3;//???
StepperMotorControl moto4;//???
/******************************************************
Function:    		void StepperMotorControl_init(StepperMotorControl *control, uint8_t address) 
Description: 		?????????(???????????????)
Calls:				 	NONE 
Input: 					StepperMotorControl *control??????????,????????2???
								????????????,???????
								address	????????
******************************************************/

void StepperMotorControl_init(StepperMotorControl *control, uint8_t address) 
{
    uint8_t defaultBytes[6] = {0x00, 0xF6, 0x10, 0x00, 0xaf, 0x6B};
    memcpy(control->controlBytes, defaultBytes, 6);
    memcpy(control->lastControlBytes, defaultBytes, 6);
    control->controlBytes[0] = address;
}

static uint8_t hasChanged(StepperMotorControl *control) 
{
    for (uint8_t i = 0; i < 6; i++) {
        if (control->controlBytes[i] != control->lastControlBytes[i]) 
				{
            return 1;
        }
    }
    return 0;
}

static void updateLastControlBytes(StepperMotorControl *control) 
{
    for (uint8_t i = 0; i < 6; i++) {
        control->lastControlBytes[i] = control->controlBytes[i];
    }
}

static void sendCommand(StepperMotorControl *control) 
{
    if (hasChanged(control)) {

				HAL_UART_Transmit(&huart3, control->controlBytes, 6, 100);
        updateLastControlBytes(control);
    }
}
/******************************************************
Function:    		void set_speed(StepperMotorControl *control, uint8_t direction, uint16_t speed) 
Description: 		???????
Calls:				 	static void sendCommand(StepperMotorControl *control) 
Input: 					StepperMotorControl *control??????????,????????2???
								????????????,???????
								direction ??????
								speed	??????
******************************************************/
void set_speed(StepperMotorControl *control, uint8_t direction, uint16_t speed) 
{
    if (direction) {
        control->controlBytes[2] = (0x10) | ((speed >> 8) & 0x0F); // ?????
    } else {
        control->controlBytes[2] = (0x00) | ((speed >> 8) & 0x0F); // ?????
    }
    control->controlBytes[3] = speed & 0xFF;
    sendCommand(control);
}
/******************************************************
Function:    		void set_acceleration(StepperMotorControl *control, uint16_t acceleration) 
Description: 		????????
Calls:				 	static void sendCommand(StepperMotorControl *control) 
Input: 					StepperMotorControl *control??????????,????????2???
								????????????,???????
								acceleration	???????
******************************************************/
void set_acceleration(StepperMotorControl *control, uint16_t acceleration) 
{
    control->controlBytes[4] = acceleration;
    sendCommand(control);
}

StepperMotorControl_location moto_9;//?
StepperMotorControl_location moto_8;//?


/******************************************************
Function:    		void StepperMotorControl_init_location(StepperMotorControl_location *control, uint8_t address) 
Description: 		?????????(???????????????)
Calls:				 	NONE 
Input: 					StepperMotorControl_location *control??????????,????????3???
								????????????,???????,????????
								address	????????
******************************************************/

void StepperMotorControl_init_location(StepperMotorControl_location *control, uint8_t address) 
{
	
	
    uint8_t defaultBytes[9] = {0x00, 0xFD, 0x12, 0x00, 0xaf,0x00,0x00,0x00,0x6B};
    memcpy(control->controlBytes, defaultBytes, 9);
    memcpy(control->lastControlBytes, defaultBytes, 9);
    control->controlBytes[0] = address;
}
static uint8_t hasChanged_location(StepperMotorControl_location *control) 
{
    for (uint8_t i = 0; i < 9; i++) {
        if (control->controlBytes[i] != control->lastControlBytes[i]) 
				{
            return 1;
        }
    }
    return 0;
}
static void updateLastControlBytes_location(StepperMotorControl_location *control) 
{
    for (uint8_t i = 0; i < 9; i++) {
        control->lastControlBytes[i] = control->controlBytes[i];
    }
}

static void sendCommand_location(StepperMotorControl_location *control) 
{
    if (hasChanged_location(control)) {

				HAL_UART_Transmit(&huart3, control->controlBytes, 9, 100);
        updateLastControlBytes_location(control);
    }
}

static void set_location(StepperMotorControl_location *control, Command com, int pulse_num) 
{		
	control->controlBytes[2] =com;
	
	control->controlBytes[6] = pulse_num>>8;/* ?????? */
	control->controlBytes[7] = pulse_num-((pulse_num>>8)<<8);	/* ?????? */

    sendCommand_location(control);
}


/******************************************************
Function:    	void set_angle_control_location(StepperMotorControl_location *control, float target_angle_num)
Description: 	?????????
Calls:				 static void set_location(StepperMotorControl_location *control, Command com, int pulse_num) 
Input: 					StepperMotorControl_location *control??????????,????????3???
								????????????,???????,????????(??????????????????,???????????)
								target_angle_num	?????
******************************************************/
#define a_circle_pulse 3200.0//??????????
void set_angle_control_location(StepperMotorControl_location *control, float target_angle_num)
{
	double error_angle=target_angle_num-(control->now_angle);
	int need_pulse=(int)(error_angle/360.0*a_circle_pulse);
	if(error_angle!=0)
	{
		if(need_pulse<0)
		{
			set_location(control,reverse, -need_pulse);//?????reverse??????forward,?????????????
		}
		else
		{
			set_location(control,forward, need_pulse);//?????forward??????reverse,?????????????
		}
		control->now_angle=target_angle_num;
		
	}
}

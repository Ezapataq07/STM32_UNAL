/*
 * PwmDriver.h
 *
 *  Created on: 19/05/2022
 *      Author: ezapataq
 */

#ifndef PWMDRIVER_H_
#define PWMDRIVER_H_

#include "BasicTimer.h"

#define		CHANNEL1		1
#define		CHANNEL2		2
#define		CHANNEL3		3
#define		CHANNEL4		4

#define TIMER_INCR_SPEED_1ms	100000
#define TIMER_INCR_SPEED_100us	10000
#define TIMER_INCR_SPEED_10us	1000

typedef struct
{
	uint8_t		PWM_channel;
	uint16_t	PWM_prescaler;
	uint16_t 	PWM_period;
	uint16_t	PWM_dutyCycle;
}PWM_Config_t;

typedef struct
{
	TIM_TypeDef		*ptrTIMx;
	PWM_Config_t	pwmConfig;
}PWM_Handler_t;


void PWM_Config(PWM_Handler_t	*pPwmConfig);
void setPwmDuty(PWM_Handler_t *pPwmConfig, uint16_t newDuty);
void startPWM(PWM_Handler_t *ptrHandlerPWM);
void stopPWM(PWM_Handler_t *ptrHandlerPWM);

#endif /* PWMDRIVER_H_ */

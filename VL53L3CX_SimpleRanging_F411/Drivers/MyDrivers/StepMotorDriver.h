/*
 * StepMotorDriver.h
 *
 *  Created on: Jun 18, 2022
 *      Author: ezapataq
 */

#ifndef STEPMOTORDRIVER_H_
#define STEPMOTORDRIVER_H_

#include "stm32f4xx.h"
#include "GPIOxDriver.h"
#include "ExtiDriver.h"


#define CLOCKWISE			0
#define COUNTERCLOCKWISE	1

#define NO_WARNING				1
#define WARNING_WRONG_DIRECTION	0

typedef struct
{
	GPIO_Handler_t* IN1;
	GPIO_Handler_t* IN2;
	GPIO_Handler_t* IN3;
	GPIO_Handler_t* IN4;
}StepMotor_Handler_t;

uint16_t moveStepMotor(StepMotor_Handler_t *pStepMotorHandler, uint16_t numSteps, uint8_t direction);
void initStepMotor(void);
void restartPulses(void);
float getPulses(void);
void readEncoder(uint8_t *pEncoderChannels);
void Exti7_Callback(void);
void Exti13_Callback(void);

#endif /* STEPMOTORDRIVER_H_ */

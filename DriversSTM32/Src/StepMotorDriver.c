/*
 * StepMotorDriver.c
 *
 *  Created on: Jun 18, 2022
 *      Author: ezapataq
 */

#include "StepMotorDriver.h"
#include "SysTickDriver.h"


uint8_t				step					= 1;
int16_t				numStepsLeft			= 0;

EXTI_Config_t		encoderCHA				= {0};
EXTI_Config_t		encoderCHB				= {0};
GPIO_Handler_t		encoderCHAPin			= {0};

uint16_t			pulses = 0;
uint8_t				directionCheck = 0;

uint8_t moveStepMotor(StepMotor_Handler_t *pStepMotorHandler, uint16_t numSteps, uint8_t direction){
	numStepsLeft = numSteps;
	directionCheck = direction;
	while(numStepsLeft > 0){
		switch (step){
		case 1:
		{
			GPIO_WritePin(pStepMotorHandler->IN1, SET);
			GPIO_WritePin(pStepMotorHandler->IN2, RESET);
			GPIO_WritePin(pStepMotorHandler->IN3, RESET);
			GPIO_WritePin(pStepMotorHandler->IN4, RESET);
			break;
		}
		case 2:
		{
			GPIO_WritePin(pStepMotorHandler->IN1, SET);
			GPIO_WritePin(pStepMotorHandler->IN2, SET);
			GPIO_WritePin(pStepMotorHandler->IN3, RESET);
			GPIO_WritePin(pStepMotorHandler->IN4, RESET);
			break;
		}
		case 3:
		{
			GPIO_WritePin(pStepMotorHandler->IN1, RESET);
			GPIO_WritePin(pStepMotorHandler->IN2, SET);
			GPIO_WritePin(pStepMotorHandler->IN3, RESET);
			GPIO_WritePin(pStepMotorHandler->IN4, RESET);
			break;
		}
		case 4:
		{
			GPIO_WritePin(pStepMotorHandler->IN1, RESET);
			GPIO_WritePin(pStepMotorHandler->IN2, SET);
			GPIO_WritePin(pStepMotorHandler->IN3, SET);
			GPIO_WritePin(pStepMotorHandler->IN4, RESET);
			break;
		}
		case 5:
		{
			GPIO_WritePin(pStepMotorHandler->IN1, RESET);
			GPIO_WritePin(pStepMotorHandler->IN2, RESET);
			GPIO_WritePin(pStepMotorHandler->IN3, SET);
			GPIO_WritePin(pStepMotorHandler->IN4, RESET);
			break;
		}
		case 6:
		{
			GPIO_WritePin(pStepMotorHandler->IN1, RESET);
			GPIO_WritePin(pStepMotorHandler->IN2, RESET);
			GPIO_WritePin(pStepMotorHandler->IN3, SET);
			GPIO_WritePin(pStepMotorHandler->IN4, SET);
			break;
		}
		case 7:
		{
			GPIO_WritePin(pStepMotorHandler->IN1, RESET);
			GPIO_WritePin(pStepMotorHandler->IN2, RESET);
			GPIO_WritePin(pStepMotorHandler->IN3, RESET);
			GPIO_WritePin(pStepMotorHandler->IN4, SET);
			break;
		}
		case 8:
		{
			GPIO_WritePin(pStepMotorHandler->IN1, SET);
			GPIO_WritePin(pStepMotorHandler->IN2, RESET);
			GPIO_WritePin(pStepMotorHandler->IN3, RESET);
			GPIO_WritePin(pStepMotorHandler->IN4, SET);
			break;
		}
		default:
		{
			break;
		}
		}
//		if (pulses > 3){
//			numStepsLeft -= pulses - 3;
//		}
		switch (direction){
		case CLOCKWISE:
		{
			if (step == 8){
				step = 1;
				if (pulses == 0){
					numStepsLeft++;
					continue;
				}
				else {
					numStepsLeft--;
					pulses = 0;
				}
				if (direction ^ directionCheck){
					return WARNING_WRONG_DIRECTION;
					break;
				}
			}else if ((step % 2) == 0){
				step++;
				numStepsLeft--;
			}else {
				step++;
			}
			break;
		}
		case COUNTERCLOCKWISE:
		{
			if (step == 1){
				step = 8;
				if (pulses == 0){
					numStepsLeft++;
					continue;
				}
				else {
					pulses = 0;
				}
				if (direction ^ directionCheck){
					return WARNING_WRONG_DIRECTION;
					continue;
				}
			}else if ((step % 2) == 0){
				step--;
				numStepsLeft--;
			}else {
				step--;
			}
			break;
		}
		default:
		{
			break;
		}
		}
		delay_ms(10);
	}
	return NO_WARNING;
}

void initStepMotor(void){
	encoderCHA.EXTIx			= EXTI7;
	encoderCHA.pinPort			= PB;
	encoderCHA.pinPUPD_Mode		= GPIO_PUPDR_NOTHING;
	encoderCHA.triggerMode		= FALLING_RISING_TRIGGER;
	exti_Config(&encoderCHA);
	encoderCHAPin = encoderCHA.handlerEXTIPin;

	encoderCHB.EXTIx			= EXTI13;
	encoderCHB.pinPort			= PC;
	encoderCHB.pinPUPD_Mode		= GPIO_PUPDR_NOTHING;
	encoderCHB.triggerMode		= FALLING_TRIGGER;
	exti_Config(&encoderCHB);
}

void Exti7_Callback(void){
	pulses++;
}

void Exti13_Callback(void){
	if (GPIO_ReadPin(&encoderCHAPin)){
		directionCheck = CLOCKWISE;
	}
	else {
		directionCheck = COUNTERCLOCKWISE;
	}
}


/**
 ******************************************************************************
 * @file           : StepMotorDriver.c
 * @author         : Emanuel Zapata Querubin
 * @brief          : Desarrollo del driver para el motor paso a paso 28BYJ-48 con 2048 pasos por vuelta
 ******************************************************************************
 ******************************************************************************
 */


/* Se incluyen las librerías necesarias */
#include "StepMotorDriver.h"
#include "SysTickDriver.h"


/* Definición de Handlers */
EXTI_Config_t		encoderCHA				= {0};
EXTI_Config_t		encoderCHB				= {0};
GPIO_Handler_t		encoderCHAPin			= {0};
GPIO_Handler_t		encoderCHBPin			= {0};

/* Definición de variables */
uint8_t				step					= 1;
int16_t				numStepsLeft			= 0;
uint16_t			pulses = 0;
uint16_t			totalPulses = 0;
uint8_t				directionCheck = 0;

/* Función que controla el paso del motor */
uint16_t moveStepMotor(StepMotor_Handler_t *pStepMotorHandler, uint16_t numSteps, uint8_t direction){
	numStepsLeft = numSteps;
	directionCheck = direction;

	while(numStepsLeft > 0){
		// En este ciclo se alterna la alimentación de las bobinas para conseguir el paso deseado
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
		// En esta sección se elige el siguiente paso a realizar según la dirección de movimiento
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
			}else if ((step % 2) == 0){
				step++;
				numStepsLeft--;
				// En caso de que haya un movimiento en la dirección incorrecta, se retorna un Warning
				if (direction ^ directionCheck){
					step--;
					step--;
					return WARNING_WRONG_DIRECTION;
				}
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
			}else if ((step % 2) == 0){
				step--;
				numStepsLeft--;
				if (direction ^ directionCheck){
					step++;
					step++;
					return WARNING_WRONG_DIRECTION;
				}
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
		HAL_Delay(7);
	}
	return NO_WARNING;
}

/* Esta función inicializa los Exti que ayudarán al control del motor. Se debe llamar desde el Main*/
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
	encoderCHBPin = encoderCHB.handlerEXTIPin;
}

void readEncoder(uint8_t *pEncoderChannels){
	/**
	 * readEncoder es una función que se encarga de leer los estados de las salidas del encoder, y mostrarlas por consola
	 */
	pEncoderChannels[0] = (uint8_t) GPIO_ReadPin(&encoderCHAPin);
	pEncoderChannels[1] = (uint8_t) GPIO_ReadPin(&encoderCHBPin);
}

/* Función para reiniciar el número de pulsos contados del encoder */
void restartPulses(void){
	totalPulses = 0;
}

/* Función para leer el número de pulsos contados del encoder */
float getPulses(void){
	return (float) totalPulses;
}

/* Implementació del Callback para el Exti7 */
void Exti7_Callback(void){
	// Este Exti pertenece a uno de los canales del Encoder, la funcionalidad será el conteo de pulsos
	pulses++;
	totalPulses++;
}

/* Implementació del Callback para el Exti13 */
void Exti13_Callback(void){
	// Este Exti pertenece a uno de los canales del Encoder, la funcionalidad será chequear continuamente la dirección de movimiento
	if (GPIO_ReadPin(&encoderCHAPin)){
		directionCheck = CLOCKWISE;
	}
	else {
		directionCheck = COUNTERCLOCKWISE;
	}
}


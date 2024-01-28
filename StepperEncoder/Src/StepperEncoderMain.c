/**
 ******************************************************************************
 * @file           : StepMotorControlMain.c
 * @author         : Emanuel Zapata Querubin
 * @brief          : Desarrollo del controlador para el motor paso a paso
 ******************************************************************************
 * - Desarrollo de las librerías para el manejo del EXTI
 * - Implementación del EXTI que consiste en controlar dos Displays de 7 segmentos,
 * 	 en los cuales se aumenta el valor con cada interrupción generada por pulsar un botón
 *
 ******************************************************************************
 */

#include <stm32f4xx.h>

/* Se incluyen las librerías para el manejo de variables */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* Se incluyen los drivers de los periféricos a utilizar */
#include "GPIOxDriver.h"
#include "BasicTimer.h"
#include "StepMotorDriver.h"
#include "SysTickDriver.h"
#include "ExtiDriver.h"



/* Definición de handlers */
GPIO_Handler_t 		handlerStateLED 		= {0};
BTIMER_Handler_t	handlerStateLedTimer	= {0};
BTIMER_Handler_t	handlerMotorTimer		= {0}; // Timer que controla el suicheo entre ambos Displays
//EXTI_Config_t		encoderCHA				= {0};
//EXTI_Config_t		encoderCHB				= {0};
//GPIO_Handler_t		encoderCHAPin			= {0};

/* Definición de los handlers que controlan los LEDs de los Displays */
GPIO_Handler_t		IN1 					= {0};
GPIO_Handler_t		IN2 					= {0};
GPIO_Handler_t		IN3 					= {0};
GPIO_Handler_t		IN4 					= {0};

StepMotor_Handler_t StepMotor = {0};
uint8_t motorStatus = 0;


uint16_t			totalStepNumber			= 2048;
uint8_t				speedRpm				= 5;
uint16_t			MotorTimerPeriod		= 15; // ms
uint16_t			encoderInterrupt		= 0;

uint16_t i = 0;

//uint8_t				step					= 1;
//uint16_t			numStepsLeft			= 0;
//
//EXTI_Config_t		encoderCHA				= {0};
//EXTI_Config_t		encoderCHB				= {0};
//GPIO_Handler_t		encoderCHAPin			= {0};
//
//uint16_t			pulses = 0;
//uint8_t				directionCheck = 0;

char warning[6] = {0};

//uint16_t			pulses = 0;
//uint8_t				direction = 0;




/* Definición de los prototipos de las funciones */
void initSystem(void);


int main(void){
	// Se inicializa la configuración
	initSystem();
	/* Ciclo principal del programa */
	for(i = 0; i < 256; i++){
		motorStatus = moveStepMotor(&StepMotor, 8, COUNTERCLOCKWISE);
		if (motorStatus){
			sprintf(warning, "%s", "Wrong");
		}
		delay_ms(20);
	}
	motorStatus = moveStepMotor(&StepMotor, 2048, CLOCKWISE);
	while(1){
//		encoderInterrupt = 0;
//		moveStepMotor(&StepMotor, 512, CLOCKWISE);
//		moveStepMotor(&StepMotor, 515, COUNTERCLOCKWISE);
	}


	return 0;
}

void initSystem(void){

	config_SysTickMs();
	/* Configuración del State LED */
	handlerStateLED.pGPIOx 								= GPIOA;
	handlerStateLED.GPIO_PinConfig.GPIO_PinNumber		= PIN_5;
	handlerStateLED.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_OUT;		// Se configura el PIN en modo OUTPUT
	handlerStateLED.GPIO_PinConfig.GPIO_PinOPType		= GPIO_OTYPE_PUSHPULL;	// Se define el OUTPUT TYPE como Push-Pull, para poder hacer el blinky
	handlerStateLED.GPIO_PinConfig.GPIO_PinSpeed		= GPIO_OSPEED_MEDIUM;	// Se configura el OUTPUT con una velocidad MEDIUM
	// Se carga la configuración del State LED
	GPIO_Config(&handlerStateLED);


	/* Configuración del LED correspondiente a la segmento A */
	IN1.pGPIOx 										= GPIOC;
	IN1.GPIO_PinConfig.GPIO_PinNumber				= PIN_0;
	IN1.GPIO_PinConfig.GPIO_PinMode					= GPIO_MODE_OUT;
	IN1.GPIO_PinConfig.GPIO_PinOPType				= GPIO_OTYPE_PUSHPULL;
	IN1.GPIO_PinConfig.GPIO_PinSpeed				= GPIO_OSPEED_HIGH;
	// Se carga la configuración de dicho segmento
	GPIO_Config(&IN1);

	/* Configuración del LED correspondiente a la segmento B */
	IN2.pGPIOx 										= GPIOC;
	IN2.GPIO_PinConfig.GPIO_PinNumber				= PIN_1;
	IN2.GPIO_PinConfig.GPIO_PinMode					= GPIO_MODE_OUT;
	IN2.GPIO_PinConfig.GPIO_PinOPType				= GPIO_OTYPE_PUSHPULL;
	IN2.GPIO_PinConfig.GPIO_PinSpeed				= GPIO_OSPEED_HIGH;
	// Se carga la configuración de dicho segmento

	GPIO_Config(&IN2);

	/* Configuración del LED correspondiente a la segmento C */
	IN3.pGPIOx 										= GPIOC;
	IN3.GPIO_PinConfig.GPIO_PinNumber				= PIN_2;
	IN3.GPIO_PinConfig.GPIO_PinMode					= GPIO_MODE_OUT;
	IN3.GPIO_PinConfig.GPIO_PinOPType				= GPIO_OTYPE_PUSHPULL;
	IN3.GPIO_PinConfig.GPIO_PinSpeed				= GPIO_OSPEED_HIGH;
	// Se carga la configuración de dicho segmento

	GPIO_Config(&IN3);

	/* Configuración del LED correspondiente a la segmento D */
	IN4.pGPIOx 										= GPIOC;
	IN4.GPIO_PinConfig.GPIO_PinNumber				= PIN_3;
	IN4.GPIO_PinConfig.GPIO_PinMode					= GPIO_MODE_OUT;
	IN4.GPIO_PinConfig.GPIO_PinOPType				= GPIO_OTYPE_PUSHPULL;
	IN4.GPIO_PinConfig.GPIO_PinSpeed				= GPIO_OSPEED_HIGH;
	// Se carga la configuración de dicho segmento

	GPIO_Config(&IN4);

	StepMotor.IN1 = &IN1;
	StepMotor.IN2 = &IN2;
	StepMotor.IN3 = &IN3;
	StepMotor.IN4 = &IN4;

	/* Configuración del Timer2, que controla el blinky del StateLED */
	handlerStateLedTimer.ptrTIMx					= TIM2;
	handlerStateLedTimer.timerConfig.Timer_mode		= TIMER_MODE_UP;
	handlerStateLedTimer.timerConfig.Timer_speed	= TIMER_INCR_SPEED_1ms;
	handlerStateLedTimer.timerConfig.Timer_period	= 250;
	// Se carga la configuración del Timer2
	BTimer_Config(&handlerStateLedTimer);
	initStepMotor();

//	encoderCHA.EXTIx			= EXTI7;
//	encoderCHA.pinPort			= PB;
//	encoderCHA.pinPUPD_Mode		= GPIO_PUPDR_NOTHING;
//	encoderCHA.triggerMode		= FALLING_RISING_TRIGGER;
//	exti_Config(&encoderCHA);
//	encoderCHAPin = encoderCHA.handlerEXTIPin;
//
//	encoderCHB.EXTIx			= EXTI13;
//	encoderCHB.pinPort			= PC;
//	encoderCHB.pinPUPD_Mode		= GPIO_PUPDR_NOTHING;
//	encoderCHB.triggerMode		= FALLING_TRIGGER;
//	exti_Config(&encoderCHB);

}

/* Implementacion del Callback para el timer2 */
void BTimer2_Callback(void){
	handlerStateLED.pGPIOx->ODR ^= GPIO_ODR_OD5;
}

//uint8_t moveStepMotor(StepMotor_Handler_t *pStepMotorHandler, uint16_t numSteps, uint8_t direction){
//	numStepsLeft = numSteps;
//	directionCheck = direction;
//	pulses = 0;
//	while(numStepsLeft > 0){
//		switch (step){
//		case 1:
//		{
//			GPIO_WritePin(pStepMotorHandler->IN1, SET);
//			GPIO_WritePin(pStepMotorHandler->IN2, RESET);
//			GPIO_WritePin(pStepMotorHandler->IN3, RESET);
//			GPIO_WritePin(pStepMotorHandler->IN4, RESET);
//			break;
//		}
//		case 2:
//		{
//			GPIO_WritePin(pStepMotorHandler->IN1, SET);
//			GPIO_WritePin(pStepMotorHandler->IN2, SET);
//			GPIO_WritePin(pStepMotorHandler->IN3, RESET);
//			GPIO_WritePin(pStepMotorHandler->IN4, RESET);
//			break;
//		}
//		case 3:
//		{
//			GPIO_WritePin(pStepMotorHandler->IN1, RESET);
//			GPIO_WritePin(pStepMotorHandler->IN2, SET);
//			GPIO_WritePin(pStepMotorHandler->IN3, RESET);
//			GPIO_WritePin(pStepMotorHandler->IN4, RESET);
//			break;
//		}
//		case 4:
//		{
//			GPIO_WritePin(pStepMotorHandler->IN1, RESET);
//			GPIO_WritePin(pStepMotorHandler->IN2, SET);
//			GPIO_WritePin(pStepMotorHandler->IN3, SET);
//			GPIO_WritePin(pStepMotorHandler->IN4, RESET);
//			break;
//		}
//		case 5:
//		{
//			GPIO_WritePin(pStepMotorHandler->IN1, RESET);
//			GPIO_WritePin(pStepMotorHandler->IN2, RESET);
//			GPIO_WritePin(pStepMotorHandler->IN3, SET);
//			GPIO_WritePin(pStepMotorHandler->IN4, RESET);
//			break;
//		}
//		case 6:
//		{
//			GPIO_WritePin(pStepMotorHandler->IN1, RESET);
//			GPIO_WritePin(pStepMotorHandler->IN2, RESET);
//			GPIO_WritePin(pStepMotorHandler->IN3, SET);
//			GPIO_WritePin(pStepMotorHandler->IN4, SET);
//			break;
//		}
//		case 7:
//		{
//			GPIO_WritePin(pStepMotorHandler->IN1, RESET);
//			GPIO_WritePin(pStepMotorHandler->IN2, RESET);
//			GPIO_WritePin(pStepMotorHandler->IN3, RESET);
//			GPIO_WritePin(pStepMotorHandler->IN4, SET);
//			break;
//		}
//		case 8:
//		{
//			GPIO_WritePin(pStepMotorHandler->IN1, SET);
//			GPIO_WritePin(pStepMotorHandler->IN2, RESET);
//			GPIO_WritePin(pStepMotorHandler->IN3, RESET);
//			GPIO_WritePin(pStepMotorHandler->IN4, SET);
//			break;
//		}
//		default:
//		{
//			break;
//		}
//		}
//
////		if (pulses > 3){
////			numStepsLeft -= pulses - 3;
////		}
//		switch (direction){
//		case CLOCKWISE:
//		{
//			if (step == 8){
//				step = 1;
//				numStepsLeft--;
//			}else if ((step % 2) == 0){
//				step++;
//				numStepsLeft--;
//			}else {
//				step++;
//			}
//			break;
//		}
//		case COUNTERCLOCKWISE:
//		{
//			if (step == 1){
//				step = 8;
//			}else if ((step % 2) == 0){
//				step--;
//				numStepsLeft--;
//			}else {
//				step--;
//			}
//			break;
//		}
//		default:
//		{
//			break;
//		}
//		}
////		if ((direction ^ directionCheck)){
////			return WARNING_WRONG_DIRECTION;
////			break;
////		}
//		delay_ms(10);
//	}
//	//		if (directionCheck != direction){
//	//			return WARNING_WRONG_DIRECTION;
//	//		}
//	return NO_WARNING;
//}
//
//void Exti7_Callback(void){
//	pulses++;
//}
//
//void Exti13_Callback(void){
//	if (GPIO_ReadPin(&encoderCHAPin)){
//		directionCheck = CLOCKWISE;
//	}
//	else {
//		directionCheck = COUNTERCLOCKWISE;
//	}
//}



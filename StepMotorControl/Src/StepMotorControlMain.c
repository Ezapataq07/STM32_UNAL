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



/* Definición de handlers */
GPIO_Handler_t 		handlerStateLED 		= {0};
BTIMER_Handler_t	handlerStateLedTimer	= {0};
BTIMER_Handler_t	handlerMotorTimer		= {0}; // Timer que controla el suicheo entre ambos Displays

/* Definición de los handlers que controlan los LEDs de los Displays */
GPIO_Handler_t		IN1 					= {0};
GPIO_Handler_t		IN2 					= {0};
GPIO_Handler_t		IN3 					= {0};
GPIO_Handler_t		IN4 					= {0};

StepMotor_Handler_t StepMotor = {0};


uint16_t			totalStepNumber			= 2048;
uint8_t				speedRpm				= 5;
uint16_t			MotorTimerPeriod		= 15; // ms



/* Definición de los prototipos de las funciones */
void initSystem(void);


int main(void){
	// Se inicializa la configuración
	initSystem();
//	moveStepMotor(&StepMotor, 1024, CLOCKWISE);
//	moveStepMotor(&StepMotor, 2048, COUNTERCLOCKWISE);
//	moveStepMotor(&StepMotor, 512, CLOCKWISE);
	/* Ciclo principal del programa */
	while(1){
		moveStepMotor(&StepMotor, 512, CLOCKWISE);
		moveStepMotor(&StepMotor, 512, COUNTERCLOCKWISE);
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
	IN1.pGPIOx 										= GPIOB;
	IN1.GPIO_PinConfig.GPIO_PinNumber				= PIN_4;
	IN1.GPIO_PinConfig.GPIO_PinMode					= GPIO_MODE_OUT;
	IN1.GPIO_PinConfig.GPIO_PinOPType				= GPIO_OTYPE_PUSHPULL;
	IN1.GPIO_PinConfig.GPIO_PinSpeed				= GPIO_OSPEED_HIGH;
	// Se carga la configuración de dicho segmento
	GPIO_Config(&IN1);

	/* Configuración del LED correspondiente a la segmento B */
	IN2.pGPIOx 										= GPIOB;
	IN2.GPIO_PinConfig.GPIO_PinNumber				= PIN_10;
	IN2.GPIO_PinConfig.GPIO_PinMode					= GPIO_MODE_OUT;
	IN2.GPIO_PinConfig.GPIO_PinOPType				= GPIO_OTYPE_PUSHPULL;
	IN2.GPIO_PinConfig.GPIO_PinSpeed				= GPIO_OSPEED_HIGH;
	// Se carga la configuración de dicho segmento

	GPIO_Config(&IN2);

	/* Configuración del LED correspondiente a la segmento C */
	IN3.pGPIOx 										= GPIOA;
	IN3.GPIO_PinConfig.GPIO_PinNumber				= PIN_8;
	IN3.GPIO_PinConfig.GPIO_PinMode					= GPIO_MODE_OUT;
	IN3.GPIO_PinConfig.GPIO_PinOPType				= GPIO_OTYPE_PUSHPULL;
	IN3.GPIO_PinConfig.GPIO_PinSpeed				= GPIO_OSPEED_HIGH;
	// Se carga la configuración de dicho segmento

	GPIO_Config(&IN3);

	/* Configuración del LED correspondiente a la segmento D */
	IN4.pGPIOx 										= GPIOA;
	IN4.GPIO_PinConfig.GPIO_PinNumber				= PIN_9;
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

}

/* Implementacion del Callback para el timer2 */
void BTimer2_Callback(void){
	handlerStateLED.pGPIOx->ODR ^= GPIO_ODR_OD5;
}




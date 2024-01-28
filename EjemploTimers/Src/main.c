/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Emanuel Zapata Querubin
 * @brief          : Desarrollo del driver para el USART
 ******************************************************************************
 * - Implementación de las librerías CMSIS
 * - Migración del GPIO Driver
 * - Desarrollo de las librerías para el manejo del USART
 *
 ******************************************************************************
 */

#include <stm32f4xx.h>
#include <stdint.h>
#include "GPIOxDriver.h"
#include "USARTxDriver.h"
#include "BasicTimer.h"

/* Definición de variables */
GPIO_Handler_t handlerLedOK = {0};
BTIMER_Handler_t handlerBTimerEjemplo = {0};
GPIO_Handler_t handlerUserLedPin = {0};

int main(void){


	// Deseamos trabajar con el puerto GPIOA
	handlerUserLedPin.pGPIOx = GPIOA;
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinNumber			= PIN_5;				// De acuerdo al Reference Diagram el User LED está conectado al PIN A5
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_OUT;		// Se configura el PIN en modo OUTPUT
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;	// Se define el OUTPUT TYPE como Push-Pull, para poder hacer el blinky
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;	// Está configuración no es relevante para el PIN en este caso
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_MEDIUM;	// Se configura el OUTPUT con una velocidad MEDIUM
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinAltFunMode		= AF0;					// Está configuración no es relevante para el PIN en este caso

	//Cargamos la configuración del PIN específico
	GPIO_Config(&handlerUserLedPin);

	handlerBTimerEjemplo.ptrTIMx = TIM2;
	handlerBTimerEjemplo.timerConfig.Timer_mode		= TIMER_MODE_UP;
	handlerBTimerEjemplo.timerConfig.Timer_speed	= TIMER_INCR_SPEED_1ms;
	handlerBTimerEjemplo.timerConfig.Timer_period	= 500;

	//Cargamos la configuración en los registros del periférico
	BTimer_Config(&handlerBTimerEjemplo);

	while(1){

	}


	return 0;
}

/* Implementacion del Callback para el timer2 */

void BTimer_Callback(void){
	handlerUserLedPin.pGPIOx->ODR ^= GPIO_ODR_OD5;
}

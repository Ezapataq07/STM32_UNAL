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
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "GPIOxDriver.h"
#include "USARTxDriver.h"
#include "BasicTimer.h"
#include "AdcDriver.h"
#include "RccDriver.h"

#define ADC_SIGNAL_SIZE 	512



/* Definición de variables */
GPIO_Handler_t 		handlerStateLED 		= {0};
GPIO_Handler_t		handlerPLLPIN			= {0};
BTIMER_Handler_t	handlerTIM2				= {0};




void initSystem(void);

int main(void){

	initSystem();
	while(1){

	}


	return 0;
}

void initSystem(void){

	RCC_Config();

	// Configuración para el State LED
	handlerStateLED.pGPIOx 								= GPIOA;
	handlerStateLED.GPIO_PinConfig.GPIO_PinNumber		= PIN_5;
	handlerStateLED.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_OUT;		// Se configura el PIN en modo OUTPUT
	handlerStateLED.GPIO_PinConfig.GPIO_PinOPType		= GPIO_OTYPE_PUSHPULL;	// Se define el OUTPUT TYPE como Push-Pull, para poder hacer el blinky
	handlerStateLED.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;	// Está configuración no es relevante para el PIN en este caso
	handlerStateLED.GPIO_PinConfig.GPIO_PinSpeed		= GPIO_OSPEED_MEDIUM;	// Se configura el OUTPUT con una velocidad MEDIUM
	handlerStateLED.GPIO_PinConfig.GPIO_PinAltFunMode	= AF0;					// Está configuración no es relevante para el PIN en este caso

	// Se carga la configuración del State LED
	GPIO_Config(&handlerStateLED);


	// Configuración para el PLLPIN
	handlerPLLPIN.pGPIOx 								= GPIOC;
	handlerPLLPIN.GPIO_PinConfig.GPIO_PinNumber			= PIN_9;
	handlerPLLPIN.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_ALTFN;		// Se configura el PIN en modo OUTPUT
	handlerPLLPIN.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;	// Se define el OUTPUT TYPE como Push-Pull, para poder hacer el blinky
	handlerPLLPIN.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;	// Está configuración no es relevante para el PIN en este caso
	handlerPLLPIN.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_HIGH;	// Se configura el OUTPUT con una velocidad MEDIUM
	handlerPLLPIN.GPIO_PinConfig.GPIO_PinAltFunMode		= AF0;					// Está configuración no es relevante para el PIN en este caso

	// Se carga la configuración del State LED
	GPIO_Config(&handlerPLLPIN);

	// Configuración del Timer 2
	handlerTIM2.ptrTIMx						= TIM2;
	handlerTIM2.timerConfig.Timer_mode		= TIMER_MODE_UP;
	handlerTIM2.timerConfig.Timer_speed		= TIMER_INCR_SPEED_1ms;
	handlerTIM2.timerConfig.Timer_period	= 250;

	//Cargamos la configuración TIM2
	BTimer_Config(&handlerTIM2);

}

/* Implementacion del Callback para el timer2 */
void BTimer2_Callback(void){
	handlerStateLED.pGPIOx->ODR ^= GPIO_ODR_OD5;
}

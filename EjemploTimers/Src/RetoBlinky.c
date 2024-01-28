/*
 * RetoBlinky.c
 *
 *  Created on: 23/04/2022
 *      Author: ezapataq
 */

#include <stm32f4xx.h>
#include <stdint.h>
#include "GPIOxDriver.h"
#include "USARTxDriver.h"
#include "BasicTimer.h"

/* Definición de variables */
GPIO_Handler_t 		handlerLed1 = {0};
GPIO_Handler_t 		handlerLed2 = {0};
BTIMER_Handler_t 	handlerBTimerReto = {0};
uint32_t			counter = 0;

/* Prototipos de las funciones */
void initSystem(void);

int main(void){
	initSystem();

	while(1){

	}
	return 0;
}

void initSystem(void){

	// Se configura el handler para el LED 1
	handlerLed1.pGPIOx = GPIOA;
	handlerLed1.GPIO_PinConfig.GPIO_PinNumber			= PIN_5;				// De acuerdo al Reference Diagram el User LED está conectado al PIN A5
	handlerLed1.GPIO_PinConfig.GPIO_PinMode				= GPIO_MODE_OUT;		// Se configura el PIN en modo OUTPUT
	handlerLed1.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;	// Se define el OUTPUT TYPE como Push-Pull, para poder hacer el blinky
	handlerLed1.GPIO_PinConfig.GPIO_PinPuPdControl		= GPIO_PUPDR_NOTHING;	// Está configuración no es relevante para el PIN en este caso
	handlerLed1.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_MEDIUM;	// Se configura el OUTPUT con una velocidad MEDIUM
	handlerLed1.GPIO_PinConfig.GPIO_PinAltFunMode		= AF0;					// Está configuración no es relevante para el PIN en este caso

	// Se configura el handler para el LED 2
	handlerLed2.pGPIOx = GPIOB;
	handlerLed2.GPIO_PinConfig.GPIO_PinNumber			= PIN_9;				// De acuerdo al Reference Diagram el User LED está conectado al PIN A5
	handlerLed2.GPIO_PinConfig.GPIO_PinMode				= GPIO_MODE_OUT;		// Se configura el PIN en modo OUTPUT
	handlerLed2.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;	// Se define el OUTPUT TYPE como Push-Pull, para poder hacer el blinky
	handlerLed2.GPIO_PinConfig.GPIO_PinPuPdControl		= GPIO_PUPDR_NOTHING;	// Está configuración no es relevante para el PIN en este caso
	handlerLed2.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_MEDIUM;	// Se configura el OUTPUT con una velocidad MEDIUM
	handlerLed2.GPIO_PinConfig.GPIO_PinAltFunMode		= AF0;					// Está configuración no es relevante para el PIN en este caso

	// Cargamos la configuración de los PINES de los LEDs
	GPIO_Config(&handlerLed1);
	GPIO_Config(&handlerLed2);

	// Se configura el handler para el Timer 2
	handlerBTimerReto.ptrTIMx 					= TIM2;
	handlerBTimerReto.timerConfig.Timer_mode	= TIMER_MODE_UP;
	handlerBTimerReto.timerConfig.Timer_speed	= TIMER_INCR_SPEED_1ms;
	handlerBTimerReto.timerConfig.Timer_period	= 200;

	//Cargamos la configuración en los registros del periférico

	BTimer_Config(&handlerBTimerReto);
}


/* Implementacion del Callback para el timer2 */
void BTimer_Callback(void){
	handlerLed1.pGPIOx->ODR ^= GPIO_ODR_OD5;
	if ((counter % 3) == 0){
		handlerLed2.pGPIOx->ODR ^= GPIO_ODR_OD9;
	}
	counter += 1;
	if (counter > 100000){
		counter=1;
	}
}

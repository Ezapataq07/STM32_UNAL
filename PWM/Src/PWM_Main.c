/**
 ******************************************************************************
 * @file           : EXTI_Main.c
 * @author         : Emanuel Zapata Querubin
 * @brief          : Desarrollo de la Tarea 4
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
#include "ExtiDriver.h"
#include "PwmDriver.h"

PWM_Handler_t 		handlerPWM 				= {0};
GPIO_Handler_t		handlerPwmPin			= {0};
GPIO_Handler_t		handlerStateLED 		= {0};
BTIMER_Handler_t	handlerStateLedTimer	= {0};

/* Definición de los prototipos de las funciones */
void initSystem(void);

int main(void){
	// Se inicializa la configuración
	initSystem();

	/* Ciclo principal del programa */
	while(1){


	}


	return 0;
}

void initSystem(void){

	/* Configuración del State LED */
	handlerStateLED.pGPIOx 								= GPIOA;
	handlerStateLED.GPIO_PinConfig.GPIO_PinNumber		= PIN_5;
	handlerStateLED.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_OUT;		// Se configura el PIN en modo OUTPUT
	handlerStateLED.GPIO_PinConfig.GPIO_PinOPType		= GPIO_OTYPE_PUSHPULL;	// Se define el OUTPUT TYPE como Push-Pull, para poder hacer el blinky
	handlerStateLED.GPIO_PinConfig.GPIO_PinSpeed		= GPIO_OSPEED_MEDIUM;	// Se configura el OUTPUT con una velocidad MEDIUM
	// Se carga la configuración del State LED
	GPIO_Config(&handlerStateLED);

	/* Configuración del Display1 */
	handlerPwmPin.pGPIOx 								= GPIOA;
	handlerPwmPin.GPIO_PinConfig.GPIO_PinNumber			= PIN_6;
	handlerPwmPin.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_ALTFN;
	handlerPwmPin.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;
	handlerPwmPin.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_HIGH;
	handlerPwmPin.GPIO_PinConfig.GPIO_PinAltFunMode		= AF2;
	// Se carga la configuración del Display1
	GPIO_Config(&handlerPwmPin);

	/* Configuración del Timer2, que controla el blinky del StateLED */
	handlerStateLedTimer.ptrTIMx					= TIM2;
	handlerStateLedTimer.timerConfig.Timer_mode		= TIMER_MODE_UP;
	handlerStateLedTimer.timerConfig.Timer_speed	= TIMER_INCR_SPEED_1ms;
	handlerStateLedTimer.timerConfig.Timer_period	= 250;
	// Se carga la configuración del Timer2
	BTimer_Config(&handlerStateLedTimer);

	handlerPWM.ptrTIMx 					= TIM3;
	handlerPWM.pwmConfig.PWM_channel 	= CHANNEL1;
	handlerPWM.pwmConfig.PWM_prescaler	= TIMER_INCR_SPEED_10us;
	handlerPWM.pwmConfig.PWM_period		= 10;
	handlerPWM.pwmConfig.PWM_dutyCycle	= 8;
	PWM_Config(&handlerPWM);

}

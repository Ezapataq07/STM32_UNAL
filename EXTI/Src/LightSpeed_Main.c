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
#include "USARTxDriver.h"



/* Definición de handlers */
GPIO_Handler_t 		handlerStateLED 		= {0};
BTIMER_Handler_t	handlerStateLedTimer	= {0};

BTIMER_Handler_t	handlerLightTimer		= {0};
USART_Handler_t		handlerUSART2			= {0};
GPIO_Handler_t 		handlerRxPIN	 		= {0};
GPIO_Handler_t 		handlerTxPIN	 		= {0};


/* Definición de las variables */
EXTI_Config_t		extiEmision				= {0}; 		// Para configurar el EXTI
EXTI_Config_t		extiReception			= {0};

uint32_t		timeStamp = 0;
char			bufferData[20] = {0};

/* Definición de los prototipos de las funciones */
void initSystem(void);

int main(void){
	// Se inicializa la configuración
	initSystem();
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

	/* Configuración del Timer2, que controla el blinky del StateLED */
	handlerStateLedTimer.ptrTIMx					= TIM2;
	handlerStateLedTimer.timerConfig.Timer_mode		= TIMER_MODE_UP;
	handlerStateLedTimer.timerConfig.Timer_speed	= TIMER_INCR_SPEED_1ms;
	handlerStateLedTimer.timerConfig.Timer_period	= 250;
	// Se carga la configuración del Timer2
	BTimer_Config(&handlerStateLedTimer);


	/* Configuración del Timer2, que controla el blinky del StateLED */
	handlerStateLedTimer.ptrTIMx					= TIM5;
	handlerStateLedTimer.timerConfig.Timer_mode		= TIMER_MODE_UP;
	handlerStateLedTimer.timerConfig.Timer_speed	= 16-1;
	handlerStateLedTimer.timerConfig.Timer_period	= 4294967296 - 1;
	// Se carga la configuración del Timer2
	BTimer_Config(&handlerStateLedTimer);
	//TIM5->DIER &= ~TIM_DIER_UIE;
	__NVIC_DisableIRQ(TIM5_IRQn);

	/* Configuración del EXTI10 */
	extiEmision.EXTIx			= EXTI10;
	extiEmision.pinPort			= PC;
	extiEmision.pinPUPD_Mode    = GPIO_PUPDR_PULLDOWN;
	extiEmision.triggerMode		= RISING_TRIGGER;
	// Se carga la configuración del EXTI
	exti_Config(&extiEmision);

	/* Configuración del EXTI10 */
	extiReception.EXTIx			= EXTI12;
	extiReception.pinPort		= PC;
	extiReception.pinPUPD_Mode  = GPIO_PUPDR_PULLDOWN;
	extiReception.triggerMode	= RISING_TRIGGER;
	// Se carga la configuración del EXTI
	exti_Config(&extiReception);

	/* Configuración del PIN que recibe la información por la USB */
	handlerRxPIN.pGPIOx								= GPIOA;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinNumber		= PIN_3;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinMode		= GPIO_MODE_ALTFN;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinOPType		= GPIO_OTYPE_PUSHPULL;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinSpeed		= GPIO_OSPEED_MEDIUM;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinAltFunMode	= AF7;
	// Se carga la configuración del Rx PIN
	GPIO_Config(&handlerRxPIN);

	/* Configuración del PIN que envía la información por la USB (TX) */
	handlerTxPIN.pGPIOx								= GPIOA;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinNumber		= PIN_2;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinMode		= GPIO_MODE_ALTFN;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinOPType		= GPIO_OTYPE_PUSHPULL;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinSpeed		= GPIO_OSPEED_MEDIUM;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinAltFunMode	= AF7;
	// Se carga la configuración del Tx PIN
	GPIO_Config(&handlerTxPIN);

	/* Configuración del USART2 */
	handlerUSART2.ptrUSARTx							= USART2;
	handlerUSART2.USART_Config.USART_mode			= USART_MODE_RXTX;
	handlerUSART2.USART_Config.USART_baudrate		= USART_BAUDRATE_115200;
	handlerUSART2.USART_Config.USART_datasize		= USART_DATASIZE_8BIT;
	handlerUSART2.USART_Config.USART_parity			= USART_PARITY_NONE;
	handlerUSART2.USART_Config.USART_stopbits		= USART_STOPBIT_1;
	handlerUSART2.USART_Config.USART_interrupt		= USART_INTERRUPT_RX;
	// Se carga la configuración del USART
	USART_Config(&handlerUSART2);


}

/* Implementacion del Callback para el timer2 */
void BTimer2_Callback(void){
	handlerStateLED.pGPIOx->ODR ^= GPIO_ODR_OD5;
}

/* Implementación del Callback para el EXTI10 */
void Exti10_Callback(void){
	timeStamp = handlerLightTimer.ptrTIMx->CNT;
}

/* Implementación del Callback para el EXTI10 */
void Exti12_Callback(void){
	sprintf(bufferData,"Time = %lu us\n", handlerLightTimer.ptrTIMx->CNT - timeStamp);
	writeMsg(&handlerUSART2, bufferData);
}




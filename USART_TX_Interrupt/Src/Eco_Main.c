/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Emanuel Zapata Querubin
 * @brief          : Desarrollo del driver para el USART
 ******************************************************************************
 * - Implementación de las librerías CMSIS
 * - Migración del GPIO Driver
 * - Desarrollo de las librerías para el manejo del USART
 ******************************************************************************
 */

#include <stm32f4xx.h>
#include <stdint.h>
#include "GPIOxDriver.h"
#include "USARTxDriver.h"
#include "BasicTimer.h"

/* Definición de variables */
GPIO_Handler_t 		handlerStateLED 	= {0};
GPIO_Handler_t 		handlerRxPIN	 	= {0};
GPIO_Handler_t 		handlerTxPIN	 	= {0};
USART_Handler_t		handlerUSART2		= {0};
BTIMER_Handler_t	handlerTIM2			= {0};
char				dataToSend			= '\0';
char				receivedChar		= '\0';


void initSystem(void);

int main(void){

	initSystem();

	while(1){
		if (receivedChar != '\0'){
			dataToSend = receivedChar;
			writeChar(&handlerUSART2, dataToSend);
			receivedChar = '\0';
		}
	}


	return 0;
}

void initSystem(void){

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

	// Configuración del PIN que recibe la información por la USB (RX)
	handlerRxPIN.pGPIOx								= GPIOA;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinNumber		= PIN_10;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinMode		= GPIO_MODE_ALTFN;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinOPType		= GPIO_OTYPE_PUSHPULL;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinSpeed		= GPIO_OSPEED_MEDIUM;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinAltFunMode	= AF7;

	// Se carga la configuración del Rx PIN
	GPIO_Config(&handlerRxPIN);

	// Configuración del PIN que envía la información por la USB (TX)
	handlerTxPIN.pGPIOx								= GPIOA;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinNumber		= PIN_9;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinMode		= GPIO_MODE_ALTFN;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinOPType		= GPIO_OTYPE_PUSHPULL;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinSpeed		= GPIO_OSPEED_MEDIUM;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinAltFunMode	= AF7;

	// Se carga la configuración del Tx PIN
	GPIO_Config(&handlerTxPIN);

	// Configuración del USART2
	handlerUSART2.ptrUSARTx							= USART1;
	handlerUSART2.USART_Config.USART_mode			= USART_MODE_RXTX; //Arreglar
	handlerUSART2.USART_Config.USART_baudrate		= USART_BAUDRATE_115200;
	handlerUSART2.USART_Config.USART_datasize		= USART_DATASIZE_8BIT;
	handlerUSART2.USART_Config.USART_parity			= USART_PARITY_NONE;
	handlerUSART2.USART_Config.USART_stopbits		= USART_STOPBIT_1;
	handlerUSART2.USART_Config.USART_interrupt		= USART_INTERRUPT_RX;

	// Se carga la configuración del USART
	USART_Config(&handlerUSART2);

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

/* Implementacion del Callback para el Usart2 */
void Usart1_RX_Callback(void){
	receivedChar = getRxData();
}

void Usart1_TX_Callback(void){
	__NOP();
}

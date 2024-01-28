/*
 * PruebaMain.c
 *
 *  Created on: 13/04/2022
 *      Author: ezapataq
 */

#include <stm32f4xx.h>
#include <stdint.h>
#include "GPIOxDriver.h"
#include "USARTxDriver.h"

int main(void){
	GPIO_Handler_t handlerTxPin 	= {0};
	USART_Handler_t handlerUsart2 	= {0};

	handlerTxPin.pGPIOx = GPIOA;
	handlerTxPin.GPIO_PinConfig.GPIO_PinNumber		= PIN_2;
	handlerTxPin.GPIO_PinConfig.GPIO_PinMode		= GPIO_MODE_ALTFN;
	handlerTxPin.GPIO_PinConfig.GPIO_PinOPType		= GPIO_OTYPE_PUSHPULL;
	handlerTxPin.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;
	handlerTxPin.GPIO_PinConfig.GPIO_PinSpeed		= GPIO_OSPEED_MEDIUM;
	handlerTxPin.GPIO_PinConfig.GPIO_PinAltFunMode	= AF7;

	handlerUsart2.ptrUSARTx = USART2;
	handlerUsart2.USART_Config.USART_mode			= USART_MODE_TX;
	handlerUsart2.USART_Config.USART_baudrate		= USART_BAUDRATE_115200;
	handlerUsart2.USART_Config.USART_datasize		= USART_DATASIZE_8BIT;
	handlerUsart2.USART_Config.USART_parity			= USART_PARITY_EVEN;
	handlerUsart2.USART_Config.USART_stopbits		= USART_STOPBIT_2;

	GPIO_Config(&handlerTxPin);
	USART_Config(&handlerUsart2);

	while(1){
		writeChar(&handlerUsart2, 'S');
		writeChar(&handlerUsart2, 'E');
		writeChar(&handlerUsart2, 'R');
		writeChar(&handlerUsart2, ' ');
		writeChar(&handlerUsart2, 'O');
		writeChar(&handlerUsart2, ' ');
		writeChar(&handlerUsart2, 'N');
		writeChar(&handlerUsart2, 'O');
		writeChar(&handlerUsart2, ' ');
		writeChar(&handlerUsart2, 'S');
		writeChar(&handlerUsart2, 'E');
		writeChar(&handlerUsart2, 'R');
		writeChar(&handlerUsart2, '\n');
		writeChar(&handlerUsart2, '\r');
	}
}

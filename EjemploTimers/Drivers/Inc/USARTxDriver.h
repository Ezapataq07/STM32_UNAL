/*
 * USARTxDriver.h
 *
 *  Created on: Apr 13, 2022
 *      Author: Emanuel Zapata
 */

#include <stdio.h>
// Incluyendo este archivo estamos incluyendo tambien el correspondiente al GPIOx
#include "stm32f4xx.h"

#ifndef INC_USARTXDRIVER_H_
#define INC_USARTXDRIVER_H_

#define USART_MODE_TX			0
#define USART_MODE_RX			1
#define USART_MODE_RXTX			2
#define USART_MODE_DISABLE		3

#define USART_BAUDRATE_9600			0
#define USART_BAUDRATE_19200		1
#define USART_BAUDRATE_115200		2

#define USART_DATASIZE_8BIT		0
#define USART_DATASIZE_9BIT		1

#define USART_PARITY_NONE		0
#define USART_PARITY_ODD		1
#define USART_PARITY_EVEN		2

#define USART_STOPBIT_1			0
#define USART_STOPBIT_0_5		1
#define USART_STOPBIT_2			2
#define USART_STOPBIT_1_5		3

/* Estructura para la configuración de la comunicación:
 * Velocidad (baudrate)
 * Tamaño de los datos
 * Control de errores
 * Bit de parada
 */

typedef struct
{
	uint8_t USART_mode;
	uint8_t USART_baudrate;
	uint8_t USART_datasize;
	uint8_t USART_parity;
	uint8_t USART_stopbits;
}USART_Config_t;

/* Definición del Handler para un USART:
 * 	- Estructura que contiene los SFR que controlan el periférico
 * 	- Estructura que contiene la configuración específica del objeto
 * 	- Buffer de recepción de datos
 * 	- Elemento que indica cuántos datos se recibieron
 * 	- Buffer de transmisión de datos
 * 	- Elemento que indica cuantos datos se deben enviar
 */

typedef struct
{
	USART_TypeDef	*ptrUSARTx;
	USART_Config_t	USART_Config;
	uint8_t			receptionBuffer[64];
	uint8_t			dataInputSize;
	uint8_t			transmisionBuffer[64];
	uint8_t			dataOutputSize;
}USART_Handler_t;

/* Definición de los prototipos para las funciones del USART */
void USART_Config(USART_Handler_t *ptrUsartHandler);
int writeChar(USART_Handler_t *ptrUsartHandler, int dataToSend);

#endif /* INC_USARTXDRIVER_H_ */

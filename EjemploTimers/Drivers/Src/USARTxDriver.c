/*
 * USARTxDriver.c
 *
 *  Created on: Apr 13, 2022
 *      Author: Emanuel Zapata
 */

#include <stm32f4xx.h>
#include "USARTxDriver.h"

/**
 * Configurando el puerto Serial...
 * Recordar que siempre se debe comenzar con activar la señal de reloj del periférico que se está utilizando
 */

void USART_Config(USART_Handler_t *ptrUsartHandler){
	/* 1. Activamos la señal del reloj que viene desde el BUS al que pertenece el periférico */
	/* Lo debemos hacer para cada uno de las posibles opciones que tengamos (USART1, USART2, USART6) */
	/* 1.1 Configuramos el USART1 */
	if (ptrUsartHandler->ptrUSARTx == USART1){
		RCC->APB2ENR |= (RCC_APB2ENR_USART1EN);
	}
	/* Configuramos el USART2 */
	else if (ptrUsartHandler->ptrUSARTx == USART2){
		RCC->APB1ENR |= (RCC_APB1ENR_USART2EN);
	}
	/* Configuramos el USART6 */
	else if (ptrUsartHandler->ptrUSARTx == USART6){
		RCC->APB2ENR |= (RCC_APB2ENR_USART6EN);
	}

	/* 2. Configuramos el tamaño del dato, la paridad y los bit de parada
	 * En el CR1 están parity (PCE y PS) y tamaño del dato (M)
	 * Mientras que en CR2 están los stopbit (STOP)
	 * Configuramos el Baudrate (registro BRR)
	 * Configuramos el modo: only TX, only RX, o RXTX
	 * Por último activamos el módulo USART cuando to-do está correctamente configurado
	 */


	/* 2.1 Comienzo por limpiar los registros, para cargar la configuración desde 0 */
	ptrUsartHandler->ptrUSARTx->CR1	= 0;
	ptrUsartHandler->ptrUSARTx->CR2	= 0;

	/* 2.2. Configuración del Parity: */
	//Verificamos si el parity está activado o no
	if (ptrUsartHandler->USART_Config.USART_parity != USART_PARITY_NONE){
		// Si se entra aquí, entonces se desea el parity-check, así que lo activamos
		ptrUsartHandler->ptrUSARTx->CR1 |= (USART_CR1_PCE);
		//Verificamos si se ha seleccionado ODD or EVEN
		if (ptrUsartHandler->USART_Config.USART_parity == USART_PARITY_EVEN){
			// Es Even, entonces cargamos la configuración adecuada
			ptrUsartHandler->ptrUSARTx->CR1 &= ~(USART_CR1_PS);
		} else{
			// Si es "else" significa que la paridad seleccionada es ODD, y cargamos esta configuración
			ptrUsartHandler->ptrUSARTx->CR1 |= (USART_CR1_PS);
		}
	} else{
		// Si llegamos acá, es porque no deseamos tener el parity-check
		ptrUsartHandler->ptrUSARTx->CR1 &= ~(USART_CR1_PCE);
	}

	/* 2.3. Configuramos el tamaño del dato */
	// Verificamos si el tamaño es de 8 bits
	if (ptrUsartHandler->USART_Config.USART_datasize == USART_DATASIZE_8BIT){
		// El registro CR1, bit M (Word length) es 0: 8 Data Bits; 1: 9  Data Bits
		ptrUsartHandler->ptrUSARTx->CR1 &= ~ (USART_CR1_M);
	} else{
		// Else significa que se desean 9 bits de datos
		ptrUsartHandler->ptrUSARTx->CR1 |= (USART_CR1_M);
	}

	/* 2.4. Configuramos los stop bits (SFR USART_CR2) */
	switch (ptrUsartHandler->USART_Config.USART_stopbits){
	case USART_STOPBIT_1: {
		// Debemos cargar el valor 0b00 en los dos bits del STOP
		ptrUsartHandler->ptrUSARTx->CR2 &= ~(USART_CR2_STOP);
		break;
	}
	case USART_STOPBIT_0_5: {
		// Debemos cargar el valor 0b01 en los dos bits del STOP
		ptrUsartHandler->ptrUSARTx->CR2 |= (USART_CR2_STOP_0);
		break;
	}
	case USART_STOPBIT_2: {
		// Debemos cargar el valor 0b10 en los dos bits del STOP
		ptrUsartHandler->ptrUSARTx->CR2 |= (USART_CR2_STOP_1);
		break;
	}
	case USART_STOPBIT_1_5: {
		// Debemos cargar el valor 0b11 en los dos bits del STOP
		ptrUsartHandler->ptrUSARTx->CR2 |= (USART_CR2_STOP);
		break;
	}
	}

	/* 2.5. Configuración del Baudrate (SFR USART_BRR) */
	// Ver tabla de valores (Tabla 75), Frec= 16MHz, overr = 0;
	if (ptrUsartHandler->USART_Config.USART_baudrate == USART_BAUDRATE_9600){
		// El valor a cargar es 104.1875 -> Mantiza = 104, fraction = 0.1875
		// Mantiza = 104 = 0x68, fraction = 16 * 0.1875 = 3
		// Valor a cargar 0x0683
		// Configurando el Baudrate generator para una velocidad de 9600bps
		ptrUsartHandler->ptrUSARTx->BRR = 0x0683;
	}
	else if (ptrUsartHandler->USART_Config.USART_baudrate == USART_BAUDRATE_19200){
		// El valor a cargar es 52.0625 -> Mantiza = 52, fraction = 0.0625
		// Mantiza = 52 = 0x34, fraction = 16 * 0.0625 = 1
		// El valor a cargar es 0x0341
		ptrUsartHandler->ptrUSARTx->BRR = 0x0341;
	}
	else if (ptrUsartHandler->USART_Config.USART_baudrate == USART_BAUDRATE_115200){
		// El valor a cargar es 8.6875 -> Mantiza = 8, fraction = 0.6875
		// Mantiza = 8 = 0x8, fraction = 16 * 0.6875 = 11
		// El valor a cargar es 0x0811
		ptrUsartHandler->ptrUSARTx->BRR = 0x08B;
	}

	/* 2.6. Configuramos el modo: TX only, RX only, RXTX, disable */
	switch (ptrUsartHandler->USART_Config.USART_mode){
	case USART_MODE_TX:
	{
		// Activamos la parte del sistema encargada de enviar
		ptrUsartHandler->ptrUSARTx->CR1 |= (USART_CR1_TE);
		break;
	}
	case USART_MODE_RX:
	{
		// Activamos la parte del sistema encargada de recibir
		ptrUsartHandler->ptrUSARTx->CR1 |= (USART_CR1_RE);
		break;
	}
	case USART_MODE_RXTX:
	{
		// Activamos ambas partes, tanto transmisión como recepción
		ptrUsartHandler->ptrUSARTx->CR1 |= (USART_CR1_TE);
		ptrUsartHandler->ptrUSARTx->CR1 |= (USART_CR1_RE);
		break;
	}
	case USART_MODE_DISABLE:
	{
		// Desactivamos ambos canales
		ptrUsartHandler->ptrUSARTx->CR1 &= ~(USART_CR1_TE);
		ptrUsartHandler->ptrUSARTx->CR1 &= ~(USART_CR1_RE);
		ptrUsartHandler->ptrUSARTx->CR1 &= ~(USART_CR1_UE);
		break;
	}
	default:
	{
		// Actuando por defecto, desactivamos ambos canales
		ptrUsartHandler->ptrUSARTx->CR1 &= ~(USART_CR1_TE);
		ptrUsartHandler->ptrUSARTx->CR1 &= ~(USART_CR1_RE);
		ptrUsartHandler->ptrUSARTx->CR1 &= ~(USART_CR1_UE);
		break;
	}
	}

	/* 2.6. Activamos el módulo serial */
	if (ptrUsartHandler->USART_Config.USART_mode != USART_MODE_DISABLE){
		ptrUsartHandler->ptrUSARTx->CR1 |= (USART_CR1_UE);
	}
}

/* Función para escribir un solo char */
int writeChar(USART_Handler_t *ptrUsartHandler, int dataToSend){
	while (!(ptrUsartHandler->ptrUSARTx->SR & USART_SR_TXE)){
		__NOP();
	}
	// Escribimos el dataToSend en el Data Register
	ptrUsartHandler->ptrUSARTx->DR |= (0b111111111 & dataToSend);
	return dataToSend;
}

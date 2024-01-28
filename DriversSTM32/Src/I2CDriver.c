/*
 * I2CDriver.c
 *
 *  Created on: 26/05/2022
 *      Author: ezapataq
 */


#include <stdint.h>
#include "I2CDriver.h"

/*
 * Recordar que se debe configurar los pines para el I2C (SDA y SCL) para lo cual se necesita el módulo GPIO y los pines configurados en el modo Alternate Function.
 * Además, estos pines deben ser configurados como salidas open-drain y con las resistencias en modo pull-up
 */

uint8_t auxByte = 0;

void I2C_Config(I2C_Handler_t	*ptrHandlerI2C){

	/* 1. Activamos la señal de reloj para el módulo I2C seleccionado */
	if (ptrHandlerI2C->ptrI2Cx == I2C1){
		RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	}
	else if (ptrHandlerI2C->ptrI2Cx == I2C2){
		RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
	}
	else if (ptrHandlerI2C->ptrI2Cx == I2C3){
		RCC->APB1ENR |= RCC_APB1ENR_I2C3EN;
	}

	/* 2. Reiniciamos el periférico, de forma que inicia en un estado conocido */
	ptrHandlerI2C->ptrI2Cx->CR1 |= I2C_CR1_SWRST;
	__NOP();
	ptrHandlerI2C->ptrI2Cx->CR1 &= ~I2C_CR1_SWRST;

	/* 3. Indicamos cual es la velocidad del reloj principal, que es la señal utilizada por el periférico para generar la señal de reloj para el bus I2C */
	ptrHandlerI2C->ptrI2Cx->CR2 &= ~(0b111111 << I2C_CR2_FREQ_Pos); // Borramos la configuración anterior
	ptrHandlerI2C->ptrI2Cx->CR2 |= (MAIN_CLOCK_16MHz_FOR_I2C << I2C_CR2_FREQ_Pos);

	/* 4. Configuramos el modo I2C en el que el sistema funciona
	 * En esta configuración se incluye también la velocidad del reloj y el tiempo máximo para el cambio de la señal (T-Rise)
	 * To.do comienza con los dos registros en 0
	 */
	ptrHandlerI2C->ptrI2Cx->CCR = 0;
	ptrHandlerI2C->ptrI2Cx->TRISE = 0;

	if (ptrHandlerI2C->modeI2C == I2C_MODE_SM){
		// Estamos en el modo "standar"
		// Seleccionamos el modo estándar
		ptrHandlerI2C->ptrI2Cx->CCR &= ~I2C_CCR_FS;

		// Configuramos el registro que se encarga de generar la señal del reloj
		ptrHandlerI2C->ptrI2Cx->CCR |= (I2C_MODE_SM_SPEED_100KHz << I2C_CCR_CCR_Pos);

		// Configuramos el registro que controla el tiempo T-Rise máximo
		ptrHandlerI2C->ptrI2Cx->TRISE |= I2C_MAX_RISE_TIME_SM;
	}
	else {
		// Estamos en el modo "fast"
		// Seleccionamos el modo rápido
		ptrHandlerI2C->ptrI2Cx->CCR |= I2C_CCR_FS;

		// Configuramos el registro que se encarga de generar la señal del reloj
		ptrHandlerI2C->ptrI2Cx->CCR |= (I2C_MODE_FM_SPEED_400KHz << I2C_CCR_CCR_Pos);

		// Configuramos el registro que controla el tiempo T-Rise máximo
		ptrHandlerI2C->ptrI2Cx->TRISE |= I2C_MAX_RISE_TIME_FM;
	}

	/* 5. Activamos el módulo I2C */
	ptrHandlerI2C->ptrI2Cx->CR1 |= I2C_CR1_PE;
}


void I2C_startTransaction(I2C_Handler_t *ptrHandlerI2C){
	/* Verificamos que la línea no está ocupada - bit "busy" en I2C_CR2 */
	while (ptrHandlerI2C->ptrI2Cx->SR2 & I2C_SR2_BUSY){
		__NOP();
	}
	/* Generamos la señal "start" */
	ptrHandlerI2C->ptrI2Cx->CR1 |= I2C_CR1_START;

	/* Esperamos a que la bander del evento "start" se levante
	 * Mientras esperamos, el valor de SB es 0, entonces la negación (!) es 1 */
	while ( !(ptrHandlerI2C->ptrI2Cx->SR1 & I2C_SR1_SB)){
		__NOP();
	}
}

void I2C_sendSlaveAddressRW(I2C_Handler_t *ptrHandlerI2C, uint8_t readOrWrite){
	/* Enviamos la dirección del Slave y el bit que indica que deseamos escribir (0)
	 * (en el siguiente pase se envia la direccion de memoria que se desea leer */
	ptrHandlerI2C->ptrI2Cx->DR = (ptrHandlerI2C->slaveAddress << 1) | readOrWrite;

	/* Esperamos hasta que la bandera del evento "addr" se levante (esto nos indica que la dirección fue enviada satisfactoriamente) */
	while ( !(ptrHandlerI2C->ptrI2Cx->SR1 & I2C_SR1_ADDR)){
		__NOP();
	}

	/* Debemos limpiar la bandera de la recepción de ACK de la "addr", para lo cual debemos leer en secuencia primero el I2C_SR1 y luego I2C_SR2 */
	auxByte = ptrHandlerI2C->ptrI2Cx->SR1;
	auxByte = ptrHandlerI2C->ptrI2Cx->SR2;
}

void I2C_sendMemoryAddress(I2C_Handler_t *ptrHandlerI2C, uint8_t memAddr){
	/* Enviaamos la dirección de memoria que deseamos leer */
	ptrHandlerI2C->ptrI2Cx->DR = memAddr;

	/* Esperamos hasta que el byte sea transmitido */
	while ( !(ptrHandlerI2C->ptrI2Cx->SR1 & I2C_SR1_TXE)){
		__NOP();
	}
}

void I2C_reStartTransaction(I2C_Handler_t *ptrHandlerI2C){
	/* Debemos generar una señal de RESTART, o sea, enviar un nuevo START */
	ptrHandlerI2C->ptrI2Cx->CR1 |= I2C_CR1_START;

	/* Esperamos a que la bandera del evento "start" se levante
	 * Mientras esperamos, el valor de SB es 0, entoncs la negación (!) es 1 */
	while ( !(ptrHandlerI2C->ptrI2Cx->SR1 & I2C_SR1_SB)){
		__NOP();
	}
}

void I2C_sendNoAck(I2C_Handler_t *ptrHandlerI2C){
	/* Activamos la indicación para la no-ACK (indicación para el Slave de terminar)
	 * (Debemos escribir cero en la posición ACK del CR1 */
	ptrHandlerI2C->ptrI2Cx->CR1 &= ~I2C_CR1_ACK;
}

void I2C_sendAck(I2C_Handler_t *ptrHandlerI2C){
	/* Activamos la indicación para la ACK (indicación para el Slave de seguir enviando datos)
	 * (Debemos escribir 1 en la posición ACK del CR1) */
	ptrHandlerI2C->ptrI2Cx->CR1 |= I2C_CR1_ACK;
}

void I2C_stopTransaction(I2C_Handler_t *ptrHandlerI2C){
	/* Generamos la condición de STOP */
	ptrHandlerI2C->ptrI2Cx->CR1 |= I2C_CR1_STOP;
}

uint8_t I2C_readDataByte(I2C_Handler_t *ptrHandlerI2C){
	/* Esperamos hasta que el byte entrante sea recibido */
	while ( !(ptrHandlerI2C->ptrI2Cx->SR1 & I2C_SR1_RXNE)){
		__NOP();
	}

	/* Leemos el byte recibido */
	ptrHandlerI2C->dataI2C = ptrHandlerI2C->ptrI2Cx->DR;
	return ptrHandlerI2C->dataI2C;
}

void I2C_sendDataByte(I2C_Handler_t *ptrHandlerI2C, uint8_t dataToWrite){
	/* Cargamos el valor que deseamos escribir */
	ptrHandlerI2C->ptrI2Cx->DR =  dataToWrite;

	/* Esperamos hasta que el byte sea transmitido */
	while ( !(ptrHandlerI2C->ptrI2Cx->SR1 & I2C_SR1_BTF)){
		__NOP();
	}
}

/**/
uint8_t I2C_readByte(I2C_Handler_t *ptrHandlerI2C, uint8_t memAddr){
	uint8_t readData = '\0';
	/* 1 */
	I2C_startTransaction(ptrHandlerI2C);

	/* 2 */
	I2C_sendSlaveAddressRW(ptrHandlerI2C, I2C_WRITE_DATA);

	/* 3 */
	I2C_sendMemoryAddress(ptrHandlerI2C, memAddr);

	/* 4 */
	I2C_reStartTransaction(ptrHandlerI2C);

	/* 5 */
	I2C_sendSlaveAddressRW(ptrHandlerI2C, I2C_READ_DATA);

	/* 6 */
	I2C_sendNoAck(ptrHandlerI2C);

	/* 7 */
	I2C_stopTransaction(ptrHandlerI2C);

	/* 8 */
	readData=I2C_readDataByte(ptrHandlerI2C);

	return readData;
}


uint8_t readBytes[64] = {0};

uint8_t* I2C_readBurstBytes(I2C_Handler_t *ptrHandlerI2C, uint8_t memAddr, uint8_t numBytesToRead){

	I2C_startTransaction(ptrHandlerI2C);

	I2C_sendSlaveAddressRW(ptrHandlerI2C, I2C_WRITE_DATA);

	I2C_sendMemoryAddress(ptrHandlerI2C, memAddr);

	I2C_reStartTransaction(ptrHandlerI2C);

	I2C_sendSlaveAddressRW(ptrHandlerI2C, I2C_READ_DATA);

	for (uint8_t i = 0; i < numBytesToRead; i++){
		I2C_sendAck(ptrHandlerI2C);
		readBytes[i] = I2C_readDataByte(ptrHandlerI2C);
	}

	I2C_sendNoAck(ptrHandlerI2C);

	I2C_stopTransaction(ptrHandlerI2C);

	return readBytes;
}

/**/
void I2C_writeByte(I2C_Handler_t *ptrHandlerI2C, uint8_t memAddr, uint8_t dataToWrite){

	I2C_startTransaction(ptrHandlerI2C);

	I2C_sendSlaveAddressRW(ptrHandlerI2C, I2C_WRITE_DATA);

	I2C_sendMemoryAddress(ptrHandlerI2C, memAddr);

	I2C_sendDataByte(ptrHandlerI2C, dataToWrite);

	I2C_stopTransaction(ptrHandlerI2C);
}






























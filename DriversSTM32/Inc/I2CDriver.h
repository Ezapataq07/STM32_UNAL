/*
 * I2CDriver.h
 *
 *  Created on: 26/05/2022
 *      Author: ezapataq
 */

#ifndef I2CDRIVER_H_
#define I2CDRIVER_H_

#include <stm32f4xx.h>

#define I2C_WRITE_DATA			0
#define I2C_READ_DATA			1

#define MAIN_CLOCK_4MHz_FOR_I2C		4
#define MAIN_CLOCK_16MHz_FOR_I2C		16
#define MAIN_CLOCK_20MHz_FOR_I2C		20

#define I2C_MODE_SM			0
#define I2C_MODE_FM			1

#define I2C_MODE_SM_SPEED_100KHz		80
#define I2C_MODE_FM_SPEED_400KHz		14

#define I2C_MAX_RISE_TIME_SM			17
#define I2C_MAX_RISE_TIME_FM			6


typedef struct
{
	I2C_TypeDef			*ptrI2Cx;
	uint8_t				slaveAddress;
	uint8_t				modeI2C;
	uint8_t				dataI2C;
}I2C_Handler_t;


/* Prototipos de las funciones públicas */
void I2C_Config(I2C_Handler_t	*ptrHandlerI2C);
void I2C_startTransaction(I2C_Handler_t *ptrHandlerI2C);
void I2C_sendSlaveAddressRW(I2C_Handler_t *ptrHandlerI2C, uint8_t readOrWrite);
void I2C_sendMemoryAddress(I2C_Handler_t *ptrHandlerI2C, uint8_t memAddr);
void I2C_reStartTransaction(I2C_Handler_t *ptrHandlerI2C);
void I2C_sendNoAck(I2C_Handler_t *ptrHandlerI2C);
void I2C_sendAck(I2C_Handler_t *ptrHandlerI2C);
void I2C_stopTransaction(I2C_Handler_t *ptrHandlerI2C);
uint8_t I2C_readDataByte(I2C_Handler_t *ptrHandlerI2C);
void I2C_sendDataByte(I2C_Handler_t *ptrHandlerI2C, uint8_t dataToWrite);
uint8_t I2C_readByte(I2C_Handler_t *ptrHandlerI2C, uint8_t memAddr);
void I2C_writeByte(I2C_Handler_t *ptrHandlerI2C, uint8_t memAddr, uint8_t dataToWrite);

uint8_t* I2C_readBurstBytes(I2C_Handler_t *ptrHandlerI2C, uint8_t memAddr, uint8_t numBytesToRead);





#endif /* I2CDRIVER_H_ */

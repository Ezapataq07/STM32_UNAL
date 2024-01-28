/*
 * LCD_Driver.c
 *
 *  Created on: 4/06/2022
 *      Author: ezapataq
 */

#include "LCD_Driver.h"
#include "SysTickDriver.h"

void initLCD(I2C_Handler_t *ptrHandlerI2C){
	/**
	 * La función initLCD se encarga de inicializar y sincronizar la LCD
	 */
	// Se activa el Systick para realizar delays
	config_SysTickMs();
	// Se hace una comunicación inicial por I2C para resetear todos los pines
	I2C_startTransaction(ptrHandlerI2C);
	I2C_sendSlaveAddressRW(ptrHandlerI2C, I2C_WRITE_DATA);
	I2C_sendDataByte(ptrHandlerI2C, 0x00);
	I2C_stopTransaction(ptrHandlerI2C);

	delay_ms(15);
	// Se envía tres veces 0b0011 con el fin de sincronizar la LCD
	for (uint8_t i = 0; i < 3; i++){
		I2C_sendDataLCD(ptrHandlerI2C, 0, 0x03); //0b0011
		delay_ms(5);
 	}
	// Se envia 0x02, que es un comando par comenzar la inicialización con interfaz de 4 bits
	I2C_sendDataLCD(ptrHandlerI2C, 0, 0x02);
	// Se envía 0x2C, indicando que se trabajará con 2 líneas del Display y con
	LCD_writeByte(ptrHandlerI2C, 0, 0x2C);
	delay_ms(5);
	// Se envía 0x08 que es un comando que apaga el Display de la LCD
	LCD_writeByte(ptrHandlerI2C, 0, 0x08);
	delay_ms(5);
	// Se envía 0x01, comando que borra to.do lo que haya en la pantalla
	LCD_writeByte(ptrHandlerI2C, 0, 0x01);
	delay_ms(5);
	// Se envía 0x06, comando que configura el modo de entrada, cada vez que se escriba el cursor se mueve a la derecha,
	LCD_writeByte(ptrHandlerI2C, 0, 0x06);
	delay_ms(5);
	// Se enciende el Display
	LCD_writeByte(ptrHandlerI2C, 0, 0x0C);
	delay_ms(5);
}

void I2C_writePCF(I2C_Handler_t *ptrHandlerI2C, uint8_t data){
	/**
	 * La función I2C_writePCF hace la comunicacion I2C con el modulo PCF y envía los bits de data
	 */
	I2C_startTransaction(ptrHandlerI2C);
	I2C_sendSlaveAddressRW(ptrHandlerI2C, I2C_WRITE_DATA);
	I2C_sendDataByte(ptrHandlerI2C, data | LED_LCD);
	I2C_stopTransaction(ptrHandlerI2C);
}

void I2C_sendDataLCD(I2C_Handler_t *ptrHandlerI2C, uint8_t ctrl, uint8_t data){
	/**
	 * La función sendDataLCD toma los primeros 4 bits de data para enviarlos a la LCD
	 */
	uint8_t dataToSend = 0;

	// Se hace un shift de data para poner los primeros 4 bits en los últimos 4, siguiendo la manera de conexión de la LCD con el PCF
	dataToSend = (data << 4) & 0xF0;
	// Ctrl indica si se desea enviar un comando (0) o un dato (1)
	if (ctrl == 1){
		dataToSend |= LCD_RS;
	} else {
		dataToSend &= ~LCD_RS;
	}
	// Se envía el dato con el bit LCD_E encendido y luego en reset, con lo cual se logra que la LCD lo lea correctamente
	I2C_writePCF(ptrHandlerI2C, dataToSend | LCD_E);
	I2C_writePCF(ptrHandlerI2C, dataToSend & ~LCD_E);
}

void LCD_writeByte(I2C_Handler_t *ptrHandlerI2C, uint8_t ctrl, uint8_t byte){
	/**
	 * La función LCD_writeByte se encarga de enviar un byte completo a la LCD, teniendo en cuenta el formato de 4 bits
	 */
	// Se envían los 4 bits bajos
	I2C_sendDataLCD(ptrHandlerI2C, ctrl, byte >> 4);
	// Se envían los 4 bits altos
	I2C_sendDataLCD(ptrHandlerI2C, ctrl, byte & 0x0F);
}

void LCD_writeCharacter(I2C_Handler_t *ptrHandlerI2C, uint8_t character){
	/**
	 * La función LCD_writeCharacte envía un Dato a la LCD
	 */
	LCD_writeByte(ptrHandlerI2C, 1, character);
}

void LCD_writeCommand(I2C_Handler_t *ptrHandlerI2C, uint8_t command){
	/**
	 * La función LCD_writeCommand envía un Comando a la LCD
	 */
	LCD_writeByte(ptrHandlerI2C, 0, command);
}

void LCD_cursorPosition(I2C_Handler_t *ptrHandlerI2C, uint8_t row, uint8_t column){
	/**
	 * La función LCD_cursorPosition ubica el cursor de la LCD en la fila y columnas indicadas en la entrada
	 */
	switch (row){
	case 1:
	{
		LCD_writeCommand(ptrHandlerI2C, 0x80 + (column-1));
		break;
	}
	case 2:
	{
		LCD_writeCommand(ptrHandlerI2C, 0xC0 + (column-1));
		break;
	}
	case 3:
	{
		LCD_writeCommand(ptrHandlerI2C, 0x94 + (column-1));
		break;
	}
	case 4:
	{
		LCD_writeCommand(ptrHandlerI2C, 0xD4 + (column-1));
		break;
	}
	default:
	{
		break;
	}
	}
	delay_ms(5);
}

void LCD_writeString(I2C_Handler_t *ptrHandlerI2C, char* bufferData){
	/**
	 * La función LCD_writeString envía un String a la LCD
	 */
	// Se recorre el buffer de datos hasta que se encuantre un caracter nulo
	while(*bufferData != '\0'){
		LCD_writeCharacter(ptrHandlerI2C, *bufferData);
		bufferData++;
	}
}

void LCD_writeStringXY(I2C_Handler_t *ptrHandlerI2C, char* bufferData, uint8_t row, uint8_t column){
	/**
	 * La función LCD_writeStringXY envía un String a la LCD y lo ubica en la fila y columna indicadas
	 */
	LCD_cursorPosition(ptrHandlerI2C, row, column);
	LCD_writeString(ptrHandlerI2C, bufferData);
}

void LCD_writeCharacterXY(I2C_Handler_t *ptrHandlerI2C, uint8_t character, uint8_t row, uint8_t column){
	/**
	 * La función LCD_writeCharacterXY envía un caracter a la LCD y lo ubica en la fila y columna indicadas
	 */
	LCD_cursorPosition(ptrHandlerI2C, row, column);
	LCD_writeByte(ptrHandlerI2C, 1, character);
}



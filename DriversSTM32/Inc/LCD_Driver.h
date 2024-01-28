/*
 * LCD_Driver.h
 *
 *  Created on: 4/06/2022
 *      Author: ezapataq
 */

#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

#include "stm32f4xx.h"
#include "I2CDriver.h"
#include "BasicTimer.h"

#define P0 		0b00000001
#define P1 		0b00000010
#define P2 		0b00000100
#define P3 		0b00001000
#define P4 		0b00010000
#define P5 		0b00100000
#define P6 		0b01000000
#define P7 		0b10000000

#define PCF_ADDR	0b0100111
#define	LED_LCD		P3
#define LCD_RS		P0
#define LCD_RW		P1
#define LCD_E		P2
#define LCD_D4		P4
#define LCD_D5		P5
#define LCD_D6		P6
#define LCD_D7		P7


#define CLEAR_DISPLAY		0b00000001
#define RETURN_HOME			0b00000010
#define DISPLAY_ON			0b00001110
#define DISPLAY_OFF			0b00001000
#define CURSOR_SHIFT_RIGTH	0b00010100
#define CURSOR_SHIFT_LEFT	0b00010000
#define ENTRY_MODE_SET		0b00000110
#define FUNCTION_SET_8BIT	0b00111100
#define FUNCTION_SET_4BIT	0b00101100
#define HIGH_BITS			0b11110000
#define LOW_BITS			0b00001111

void initTimer(void);
void initLCD(I2C_Handler_t *ptrHandlerI2C);
void I2C_writePCF(I2C_Handler_t *ptrHandlerI2C, uint8_t data);
void I2C_sendDataLCD(I2C_Handler_t *ptrHandlerI2C, uint8_t ctrl, uint8_t data);
void LCD_writeByte(I2C_Handler_t *ptrHandlerI2C, uint8_t ctrl, uint8_t byte);
void delay_5us(uint16_t time);
void LCD_writeCharacter(I2C_Handler_t *ptrHandlerI2C, uint8_t character);
void LCD_writeCommand(I2C_Handler_t *ptrHandlerI2C, uint8_t command);
void LCD_cursorPosition(I2C_Handler_t *ptrHandlerI2C, uint8_t row, uint8_t column);
void LCD_writeString(I2C_Handler_t *ptrHandlerI2C, char* bufferData);
void LCD_writeStringXY(I2C_Handler_t *ptrHandlerI2C, char* bufferData, uint8_t row, uint8_t column);
void LCD_writeCharacterXY(I2C_Handler_t *ptrHandlerI2C, uint8_t character, uint8_t row, uint8_t column);


#endif /* LCD_DRIVER_H_ */

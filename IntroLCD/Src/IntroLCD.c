/**
 ******************************************************************************
 * @file           : StepMotorControlMain.c
 * @author         : Emanuel Zapata Querubin
 * @brief          : Desarrollo del controlador para el motor paso a paso
 ******************************************************************************
 * - Desarrollo de las librerías para el manejo del EXTI
 * - Implementación del EXTI que consiste en controlar dos Displays de 7 segmentos,
 * 	 en los cuales se aumenta el valor con cada interrupción generada por pulsar un botón
 *
 ******************************************************************************
 */

#include <stm32f4xx.h>

/* Se incluyen las librerías para el manejo de variables */
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

/* Se incluyen los drivers de los periféricos a utilizar */
#include "GPIOxDriver.h"
#include "USARTxDriver.h"
#include "BasicTimer.h"
#include "SysTickDriver.h"
#include "I2CDriver.h"
#include "LCD_Driver.h"


/* Definición de Variables */
GPIO_Handler_t	handlerStateLED = {0};
GPIO_Handler_t	handlerPinTX	= {0};
GPIO_Handler_t 	handlerPinRX	= {0};

BTIMER_Handler_t	handlerStateLEDTimer = {0};

USART_Handler_t		handlerCommTerminal  = {0};
uint8_t rxData = 0;

/* Configuración para el I2C */
GPIO_Handler_t	handlerI2CSDA			= {0};
GPIO_Handler_t	handlerI2CSCL 			= {0};
I2C_Handler_t	handlerLCD			 	= {0};
uint8_t			i2cBuffer				= 0;
char bufferData[64] = {0};



/* Definición de los prototipos de las funciones */
void initSystem(void);

/**
 * Función principal del programa
 */
int main(void){
	// Se inicializa la configuración
	initSystem();
	initLCD(&handlerLCD);
	LCD_writeString(&handlerLCD, "Julian Hpta");
	LCD_cursorPosition(&handlerLCD, 2, 3);
	LCD_writeCharacter(&handlerLCD, 'H');
	LCD_writeStringXY(&handlerLCD, "HOli", 4, 10);
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

//	/* Configurando los pines sobre los que funciona el USART */
//	handlerPinTX.pGPIOx								= GPIOA;
//	handlerPinTX.GPIO_PinConfig.GPIO_PinNumber		= PIN_2;
//	handlerPinTX.GPIO_PinConfig.GPIO_PinMode		= GPIO_MODE_ALTFN;
//	handlerPinTX.GPIO_PinConfig.GPIO_PinOPType		= GPIO_OTYPE_PUSHPULL;
//	handlerPinTX.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;
//	handlerPinTX.GPIO_PinConfig.GPIO_PinSpeed		= GPIO_OSPEED_FAST;
//	handlerPinTX.GPIO_PinConfig.GPIO_PinAltFunMode	= AF7;
//
//	// Llamamos a la función config, para que se encargue de cargar las configuración en los registros adecuados
//	GPIO_Config(&handlerPinTX);
//
//
//	/* Configurando los pines sobre los que funciona el USART */
//	handlerPinRX.pGPIOx								= GPIOA;
//	handlerPinRX.GPIO_PinConfig.GPIO_PinNumber		= PIN_3;
//	handlerPinRX.GPIO_PinConfig.GPIO_PinMode		= GPIO_MODE_ALTFN;
//	handlerPinRX.GPIO_PinConfig.GPIO_PinOPType		= GPIO_OTYPE_PUSHPULL;
//	handlerPinRX.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;
//	handlerPinRX.GPIO_PinConfig.GPIO_PinSpeed		= GPIO_OSPEED_FAST;
//	handlerPinRX.GPIO_PinConfig.GPIO_PinAltFunMode	= AF7;
//
//	// Llamamos a la función config, para que se encargue de cargar las configuración en los registros adecuados
//	GPIO_Config(&handlerPinRX);
//
//	/* Configuramos la comunicación serial */
//	handlerCommTerminal.ptrUSARTx						= USART2;
//	handlerCommTerminal.USART_Config.USART_datasize		= USART_DATASIZE_8BIT;
//	handlerCommTerminal.USART_Config.USART_parity		= USART_PARITY_NONE;
//	handlerCommTerminal.USART_Config.USART_stopbits		= USART_STOPBIT_1;
//	handlerCommTerminal.USART_Config.USART_baudrate		= USART_BAUDRATE_115200;
//	handlerCommTerminal.USART_Config.USART_mode			= USART_MODE_RXTX;
//	handlerCommTerminal.USART_Config.USART_interrupt	= USART_INTERRUPT_RX;
//
//	USART_Config(&handlerCommTerminal);

	/* Configuramos el Timer */
	handlerStateLEDTimer.ptrTIMx					= TIM2;
	handlerStateLEDTimer.timerConfig.Timer_mode		= TIMER_MODE_UP;
	handlerStateLEDTimer.timerConfig.Timer_speed	= TIMER_INCR_SPEED_100us;
	handlerStateLEDTimer.timerConfig.Timer_period	= 2500;

	BTimer_Config(&handlerStateLEDTimer);


	/* Configurando los pines sobre los que funciona el I2C1 */
	handlerI2CSCL.pGPIOx								= GPIOB;
	handlerI2CSCL.GPIO_PinConfig.GPIO_PinNumber			= PIN_6;
	handlerI2CSCL.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_ALTFN;
	handlerI2CSCL.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_OPENDRAIN;
	handlerI2CSCL.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_PULLUP;
	handlerI2CSCL.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_FAST;
	handlerI2CSCL.GPIO_PinConfig.GPIO_PinAltFunMode		= AF4;

	GPIO_Config(&handlerI2CSCL);

	/* Configurando los pines sobre los que funciona el I2C1 */
	handlerI2CSDA.pGPIOx								= GPIOB;
	handlerI2CSDA.GPIO_PinConfig.GPIO_PinNumber			= PIN_7;
	handlerI2CSDA.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_ALTFN;
	handlerI2CSDA.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_OPENDRAIN;
	handlerI2CSDA.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_PULLUP;
	handlerI2CSDA.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_FAST;
	handlerI2CSDA.GPIO_PinConfig.GPIO_PinAltFunMode		= AF4;

	GPIO_Config(&handlerI2CSDA);

	handlerLCD.ptrI2Cx		= I2C1;
	handlerLCD.modeI2C		= I2C_MODE_FM;
	handlerLCD.slaveAddress	= 0b0100111;
	I2C_Config(&handlerLCD);


}

/* Callback para la recepción del USART2 */

void Usart2_RX_Callback(void){
	rxData = getRxData();
}

/**/
void BTimer2_Callback(void){
	handlerStateLED.pGPIOx->ODR ^= GPIO_ODR_OD5;
}


/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Emanuel Zapata Querubin
 * @brief          : Desarrollo del driver para el USART
 ******************************************************************************
 * - Implementación de las librerías CMSIS
 * - Migración del GPIO Driver
 * - Desarrollo de las librerías para el manejo del USART
 *
 ******************************************************************************
 */

#include <stm32f4xx.h>

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "GPIOxDriver.h"
#include "USARTxDriver.h"
#include "BasicTimer.h"
#include "AdcDriver.h"
#include "PwmDriver.h"



/* Definición de variables */
GPIO_Handler_t 		handlerStateLED 		= {0};
GPIO_Handler_t 		handlerRxPIN	 		= {0};
GPIO_Handler_t 		handlerTxPIN	 		= {0};
BTIMER_Handler_t	handlerStateLedTimer	= {0};
USART_Handler_t		handlerUSART1			= {0};

char				bufferReception[32]					= {0};
char				bufferData[64]						= {0};
char				rxData 								= '\0';
bool				stringComplete						= false;
uint16_t			counterReception					= 0;
uint16_t			firstParameter = 0;
uint16_t			secondParameter = 0;
char				cmd[32] = {0};


void initSystem(void);
void setPeriod(BTIMER_Handler_t *ptrTimerHandler, uint16_t period);
void parseCommands(char *ptrBufferReception);

int main(void){

	initSystem();
	while(1){

		if (rxData != '\0'){
			bufferReception[counterReception] = rxData;
			counterReception++;

			if (rxData == '@'){
				stringComplete = true;

				bufferReception[counterReception-1] = '\0';
				counterReception = 0;
			}

			rxData = '\0';
		}

		if (stringComplete){
			parseCommands(bufferReception);
			stringComplete = false;
		}
	}

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
	handlerUSART1.ptrUSARTx							= USART1;
	handlerUSART1.USART_Config.USART_mode			= USART_MODE_RXTX; //Arreglar
	handlerUSART1.USART_Config.USART_baudrate		= USART_BAUDRATE_115200;
	handlerUSART1.USART_Config.USART_datasize		= USART_DATASIZE_8BIT;
	handlerUSART1.USART_Config.USART_parity			= USART_PARITY_NONE;
	handlerUSART1.USART_Config.USART_stopbits		= USART_STOPBIT_1;
	handlerUSART1.USART_Config.USART_interrupt		= USART_INTERRUPT_RX;

	// Se carga la configuración del USART
	USART_Config(&handlerUSART1);

	// Configuración del Timer 2
	handlerStateLedTimer.ptrTIMx						= TIM2;
	handlerStateLedTimer.timerConfig.Timer_mode		= TIMER_MODE_UP;
	handlerStateLedTimer.timerConfig.Timer_speed		= TIMER_INCR_SPEED_1ms;
	handlerStateLedTimer.timerConfig.Timer_period	= 250;

	//Cargamos la configuración TIM2
	BTimer_Config(&handlerStateLedTimer);

}

/* Implementacion del Callback para el timer2 */
void BTimer2_Callback(void){
	handlerStateLED.pGPIOx->ODR ^= GPIO_ODR_OD5;
}

/* Implementacion del Callback para el Usart2 */
void Usart1_RX_Callback(void){
	rxData = getRxData();
}

void Usart1_TX_Callback(void){
	__NOP();
}

void parseCommands(char *ptrBufferReception){
	sscanf(ptrBufferReception, "%s %u ", cmd, (unsigned int*) &firstParameter);
	if (strcmp(cmd, "Menu") == 0){
		writeMsg(&handlerUSART1, "\nHelp Menu CMDS:\n");
		writeMsg(&handlerUSART1, "1)  Menu              -- Print this menu\n");
		writeMsg(&handlerUSART1, "2)  Start             -- Start Servomotor control with Joystick\n");
		writeMsg(&handlerUSART1, "3)  Stop              -- Stop Servomotor control with Joystick\n");
		writeMsg(&handlerUSART1, "4)  initLcd           -- Steps to initialize Lcd\n");
		writeMsg(&handlerUSART1, "5)  autoUpdateLcd #   -- Automatic LCD Update (# = 0, 1)\n");
		writeMsg(&handlerUSART1, "6)  servoPosition #   -- Set Servomotor Position to # degrees (# = [0, 180])\n");
		writeMsg(&handlerUSART1, "7)  minServoPos       -- Set Servomotor Position to 0 degrees\n");
		writeMsg(&handlerUSART1, "8)  maxServoPos       -- Set Servomotor Position to 180 degrees\n");
		writeMsg(&handlerUSART1, "9)  setLedPeriod #    -- Set blinky period of State LED to # ms (# > 1)\n");
		writeMsg(&handlerUSART1, "10) startServoParty   -- Set Servomotor in Party Mode\n");
		writeMsg(&handlerUSART1, "11) stopServoParty    -- Stop Servomotor Party Mode\n");
		writeMsg(&handlerUSART1, "12) dummy\n");
	}
	else if (strcmp(cmd, "dummy") == 0){
		writeMsg(&handlerUSART1, "CMD: dummy\n");
		sprintf(bufferData, "number A = %u \n", firstParameter);
		writeMsg(&handlerUSART1, bufferData);
//		sprintf(bufferData, "number B = %u \n", secondParameter);
//		writeMsg(&handlerUSART1, bufferData);
	}
	else if (strcmp(cmd, "setLedPeriod") == 0){
		writeMsg(&handlerUSART1, "CMD: setLedPeriod\n");
	}
}

void setPeriod(BTIMER_Handler_t *ptrTimerHandler, uint16_t period){
	/**
	 * La función setPeriod cambia el periodo del Timer correspondiente al handler indicado, a un valor indicado por el usuario
	 */
	ptrTimerHandler->timerConfig.Timer_period = period;
	BTimer_Config(ptrTimerHandler);		// Se vuelve a cargar la cofiguración del Timer con el nuevo periodo
}


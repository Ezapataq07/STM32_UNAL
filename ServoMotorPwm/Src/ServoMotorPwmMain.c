/**
 ******************************************************************************
 * @file           : EXTI_Main.c
 * @author         : Emanuel Zapata Querubin
 * @brief          : Desarrollo de la Tarea 4
 ******************************************************************************
 * - Desarrollo de las librerías para el manejo del EXTI
 * - Implementación del EXTI que consiste en controlar dos Displays de 7 segmentos,
 * 	 en los cuales se aumenta el valor con cada interrupción generada por pulsar un botón
 *
 ******************************************************************************
 */

#include <stm32f4xx.h>

/* Se incluyen las librerías para el manejo de variables */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* Se incluyen los drivers de los periféricos a utilizar */
#include "GPIOxDriver.h"
#include "BasicTimer.h"
#include "ExtiDriver.h"
#include "PwmDriver.h"
#include "USARTxDriver.h"

PWM_Handler_t 		handlerPWM 				= {0};
GPIO_Handler_t		handlerPwmPin			= {0};
GPIO_Handler_t		handlerStateLED 		= {0};
BTIMER_Handler_t	handlerStateLedTimer	= {0};
USART_Handler_t		handlerUSART2			= {0};
GPIO_Handler_t 		handlerRxPIN	 		= {0};
GPIO_Handler_t 		handlerTxPIN	 		= {0};

uint8_t siuu = 0;

char				bufferData[64]		    = "Comencemos";
char				rxData					= 0;
uint16_t			oldDuty					= 0;

/* Definición de los prototipos de las funciones */
void initSystem(void);

int main(void){
	// Se inicializa la configuración
	initSystem();
	sprintf(bufferData, "Duty = %u\n\r",(unsigned int) oldDuty);
	writeMsg(&handlerUSART2, bufferData);

	/* Ciclo principal del programa */
	while(1){
		if (rxData != '\0'){
			writeChar(&handlerUSART2, rxData);
			if (rxData == 'u'){
				oldDuty = oldDuty + 1;
				sprintf(bufferData, "Duty = %u\n\r",(unsigned int) oldDuty);
				writeMsg(&handlerUSART2, bufferData);
				setPwmDuty(&handlerPWM, oldDuty);
			}
			if (rxData == 'd'){
				oldDuty = oldDuty - 1;
				sprintf(bufferData, "Duty = %u\n\r",(unsigned int) oldDuty);
				writeMsg(&handlerUSART2, bufferData);
				setPwmDuty(&handlerPWM, oldDuty);

			}
			if (rxData == 's'){
				if(siuu){
					setPwmDuty(&handlerPWM, 50);
				}
				else {
					setPwmDuty(&handlerPWM, 235);
				}

			}
			rxData = '\0';
		}


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

	/* Configuración del Display1 */
	handlerPwmPin.pGPIOx 								= GPIOA;
	handlerPwmPin.GPIO_PinConfig.GPIO_PinNumber			= PIN_6;
	handlerPwmPin.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_ALTFN;
	handlerPwmPin.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;
	handlerPwmPin.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_HIGH;
	handlerPwmPin.GPIO_PinConfig.GPIO_PinAltFunMode		= AF2;
	// Se carga la configuración del Display1
	GPIO_Config(&handlerPwmPin);

	/* Configuración del Timer2, que controla el blinky del StateLED */
	handlerStateLedTimer.ptrTIMx					= TIM2;
	handlerStateLedTimer.timerConfig.Timer_mode		= TIMER_MODE_UP;
	handlerStateLedTimer.timerConfig.Timer_speed	= TIMER_INCR_SPEED_1ms;
	handlerStateLedTimer.timerConfig.Timer_period	= 250;
	// Se carga la configuración del Timer2
	BTimer_Config(&handlerStateLedTimer);

	handlerPWM.ptrTIMx 					= TIM3;
	handlerPWM.pwmConfig.PWM_channel 	= CHANNEL1;
	handlerPWM.pwmConfig.PWM_prescaler	= TIMER_INCR_SPEED_10us;
	handlerPWM.pwmConfig.PWM_period		= 2000;
	handlerPWM.pwmConfig.PWM_dutyCycle	= 100;
	PWM_Config(&handlerPWM);
	oldDuty = 100;

	// Configuración del PIN que recibe la información por la USB
	handlerRxPIN.pGPIOx								= GPIOA;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinNumber		= PIN_3;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinMode		= GPIO_MODE_ALTFN;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinOPType		= GPIO_OTYPE_PUSHPULL;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinSpeed		= GPIO_OSPEED_MEDIUM;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinAltFunMode	= AF7;

	// Se carga la configuración del Rx PIN
	GPIO_Config(&handlerRxPIN);

	// Configuración del PIN que envía la información por la USB (TX)
	handlerTxPIN.pGPIOx								= GPIOA;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinNumber		= PIN_2;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinMode		= GPIO_MODE_ALTFN;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinOPType		= GPIO_OTYPE_PUSHPULL;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinSpeed		= GPIO_OSPEED_MEDIUM;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinAltFunMode	= AF7;

	// Se carga la configuración del Tx PIN
	GPIO_Config(&handlerTxPIN);

	// Configuración del USART2
	handlerUSART2.ptrUSARTx							= USART2;
	handlerUSART2.USART_Config.USART_mode			= USART_MODE_RXTX;
	handlerUSART2.USART_Config.USART_baudrate		= USART_BAUDRATE_115200;
	handlerUSART2.USART_Config.USART_datasize		= USART_DATASIZE_8BIT;
	handlerUSART2.USART_Config.USART_parity			= USART_PARITY_NONE;
	handlerUSART2.USART_Config.USART_stopbits		= USART_STOPBIT_1;
	handlerUSART2.USART_Config.USART_interrupt		= USART_INTERRUPT_RX;

	// Se carga la configuración del USART
	USART_Config(&handlerUSART2);

}

/* Implementacion del Callback para el timer2 */
void BTimer2_Callback(void){
	handlerStateLED.pGPIOx->ODR ^= GPIO_ODR_OD5;
}

/* Implementacion del Callback para el Usart2 */
void Usart2_RX_Callback(void){
	rxData = getRxData();
	siuu = !(siuu);
}

void Usart2_TX_Callback(void){
	__NOP();
}

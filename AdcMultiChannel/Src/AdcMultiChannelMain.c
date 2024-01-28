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



/* Definición de variables */
GPIO_Handler_t 		handlerStateLED 	= {0};
GPIO_Handler_t 		handlerTestLED	 	= {0};
GPIO_Handler_t 		handlerRxPIN	 	= {0};
GPIO_Handler_t 		handlerTxPIN	 	= {0};
BTIMER_Handler_t	handlerTIM2			= {0};
USART_Handler_t		handlerUSART2		= {0};
ADC_Config_t		adcConfig1			= {0};
ADC_Config_t		adcConfig2			= {0};
ADC_Config_t		adcConfig3			= {0};

char				bufferData[20]		= "Hola mundo!";
uint16_t			adcData				= 0;
uint16_t			counter				= 0;
char				rxData 				= 0;
bool				adcIsComplete		= false;



void initSystem(void);
void setPeriod(BTIMER_Handler_t *ptrUsartHandler, uint16_t period);

int main(void){

	initSystem();
	char hola[10] = "Hola";
	writeMsg(&handlerUSART2, hola);

	while(1){

		// Hacemos un "eco" con el valor que nos llega por el serial
		if (rxData != '\0'){
			writeChar(&handlerUSART2, rxData);
			if (rxData == 's'){
				// Lanzamos una nueva conversión ADC
				startSingleConversion();
			}
			if (rxData == 'c'){
				startContinuousConversion();
			}
			if (rxData == 'p'){
				stopContinuousConversion();
			}

			rxData = '\0';
		}

		if (adcIsComplete == true){
			sprintf(bufferData, "%u\n\r", (unsigned int) adcData);
			writeMsg(&handlerUSART2, bufferData);
			counter++;
			adcIsComplete = false;
		}

	}


	return 0;
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

	// Configuración para el Test LED
	handlerTestLED.pGPIOx 								= GPIOB;
	handlerTestLED.GPIO_PinConfig.GPIO_PinNumber		= PIN_9;
	handlerTestLED.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_OUT;		// Se configura el PIN en modo OUTPUT
	handlerTestLED.GPIO_PinConfig.GPIO_PinOPType		= GPIO_OTYPE_PUSHPULL;	// Se define el OUTPUT TYPE como Push-Pull, para poder hacer el blinky
	handlerTestLED.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;	// Está configuración no es relevante para el PIN en este caso
	handlerTestLED.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_MEDIUM;	// Se configura el OUTPUT con una velocidad MEDIUM
	handlerTestLED.GPIO_PinConfig.GPIO_PinAltFunMode	= AF0;					// Está configuración no es relevante para el PIN en este caso

	// Se carga la configuración del State LED
	GPIO_Config(&handlerTestLED);

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

	// Configuración del Timer 2
	handlerTIM2.ptrTIMx						= TIM2;
	handlerTIM2.timerConfig.Timer_mode		= TIMER_MODE_UP;
	handlerTIM2.timerConfig.Timer_speed		= TIMER_INCR_SPEED_1ms;
	handlerTIM2.timerConfig.Timer_period	= 250;

	//Cargamos la configuración TIM2
	BTimer_Config(&handlerTIM2);

	// Configuracion del ADC
	adcConfig1.channel			= ADC_CHANNEL_0;
	adcConfig1.dataAlignment	= ADC_ALIGNMENT_RIGHT;
	adcConfig1.resolution		= ADC_RESOLUTION_12_BIT;
	adcConfig1.samplingPeriod	= ADC_SAMPLING_PERIOD_144_CYCLES;
	adcConfig1.scanMode			= SCAN_MODE_ON;
	adcConfig1.scanSequencePos	= 1;
	adc_Config(&adcConfig1);

	adcConfig2.channel			= ADC_CHANNEL_8;
	adcConfig2.dataAlignment	= ADC_ALIGNMENT_RIGHT;
	adcConfig2.resolution		= ADC_RESOLUTION_12_BIT;
	adcConfig2.samplingPeriod	= ADC_SAMPLING_PERIOD_144_CYCLES;
	adcConfig2.scanMode			= SCAN_MODE_ON;
	adcConfig2.scanSequencePos	= 2;
	adc_Config(&adcConfig2);

	adcConfig3.channel			= ADC_CHANNEL_10;
	adcConfig3.dataAlignment	= ADC_ALIGNMENT_RIGHT;
	adcConfig3.resolution		= ADC_RESOLUTION_12_BIT;
	adcConfig3.samplingPeriod	= ADC_SAMPLING_PERIOD_144_CYCLES;
	adcConfig3.scanMode			= SCAN_MODE_ON;
	adcConfig3.scanSequencePos	= 3;
	adc_Config(&adcConfig3);


	ScanModeConfig(3);
}

/* Implementacion del Callback para el timer2 */
void BTimer2_Callback(void){
	handlerStateLED.pGPIOx->ODR ^= GPIO_ODR_OD5;
}

/* Implementacion del Callback para el Usart2 */
void Usart2_RX_Callback(void){
	rxData = getRxData();
}

void Usart2_TX_Callback(void){
	__NOP();
}

void adcComplete_Callback(void){
	GPIO_WritePin(&handlerTestLED, 1);
	adcIsComplete = true;
	adcData = getADC();
	GPIO_WritePin(&handlerTestLED, 0);
}
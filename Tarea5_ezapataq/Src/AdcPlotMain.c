/**
 ******************************************************************************
 * @file           : AdcPlotMain.c
 * @author         : Emanuel Zapata Querubin
 * @brief          : Desarrollo de programa para muestreo y reconstrucción de señal con ADC
 * @result		   : Se logra reconstruir por medio de Python una señal sinusoidal de 1.27kHz, para esto se imprimen y guardan los valores por USART para
 * 					 posteriormente graficarlos.
 * 					 La señal utilizada fue una señal sinusoidal de Vpp=2.5V, y Voff=1.75V, teniendo un máximo en 3.0V y mínimos en 0.5V.
 * 					 Así, de la imagen se puede rescatar que a lo largo de un periodo hay 41 puntos; además, con la ayuda de un timer se encontró que el
 * 					 tiempo de muestreo es de 9us, por lo tanto, se obtiene que el periodo de la señal es de 774us, y su frecuencia de 1.29kHz. El error
 * 					 porcentual es entonces de 1.57%
 ******************************************************************************
 *
 ******************************************************************************
 */

/* Se incluyen las librerías necesarias */
#include <stm32f4xx.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* Se incluyen los drivers */
#include "GPIOxDriver.h"
#include "USARTxDriver.h"
#include "BasicTimer.h"
#include "AdcDriver.h"
#include "PLL_Driver.h"

/* Se definen macros necesarios */
#define ADC_SIGNAL_SIZE 	128
#define NUM_SESNSORS		1


/* Definición de handlers */
GPIO_Handler_t 		handlerStateLED 		= {0};
GPIO_Handler_t 		handlerRxPIN	 		= {0};
GPIO_Handler_t 		handlerTxPIN	 		= {0};
BTIMER_Handler_t	handlerStateLedTimer	= {0};
BTIMER_Handler_t	handlerAdcSamplingTimer	= {0};
USART_Handler_t		handlerUSART2			= {0};

/* Definición de variables */
ADC_Config_t		adcSignalGenerator			= {0};
ADC_Config_t		sensores[NUM_SESNSORS]		= {0};
char				bufferData[32]				= "Hola mundo!";
uint16_t			adcData						= 0;
char				rxData 						= 0;
char				adcIsComplete				= false;
uint16_t 			adcSignal[ADC_SIGNAL_SIZE]	= {0};
uint16_t			dataPosition				= 0;
uint32_t			counter10us 					= 0;
uint32_t			samplingTime				= 0;

/* Se definen los prototipos de las funciones */
void initSystem(void);

int main(void){
	// Se inicializan los periféricos a utilizar
	initSystem();
	while(1){
		// Se revisa qué caracter ingresa por consola
		if (rxData != '\0'){
			// Si se ingresa "c" se comienza una conversión continua, la cual hará 128 conversiones y guarda los valores en un arreglo
			// También se inicializa un contador, con el fin de medir cuánto tiempo tardan en realizarse las 128 conversiones
			if (rxData == 'c'){
				counter10us = 0;
				startContinuousConversion();
			}
			// Si se ingresa "p" se detiene la conversión continua, sin embargo, la conversión continua termina si se llena el arreglo con 64 valores
			if (rxData == 'p'){
				stopContinuousConversion();
			}
			// Si se ingresa "s" se imprimen por consola las 128 conversiones realizadas
			if (rxData == 's'){
				for(uint16_t j = 0; j < ADC_SIGNAL_SIZE; j++){
					sprintf(bufferData, "%u\n\r",(unsigned int) adcSignal[j]);
					writeMsg(&handlerUSART2, bufferData);
				}
			}

			rxData = '\0';
		}
		// Cuando se terminan las 128 conversiones, se imprime el tiempo de muestreo calculado
		if (adcIsComplete){
			sprintf(bufferData, "The sampling time was %u us\n\r",(unsigned int) samplingTime);
			writeMsg(&handlerUSART2, bufferData);
			adcIsComplete = false;
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
	handlerStateLED.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;	// Está configuración no es relevante para el PIN en este caso
	handlerStateLED.GPIO_PinConfig.GPIO_PinSpeed		= GPIO_OSPEED_MEDIUM;	// Se configura el OUTPUT con una velocidad MEDIUM
	handlerStateLED.GPIO_PinConfig.GPIO_PinAltFunMode	= AF0;					// Está configuración no es relevante para el PIN en este caso
	// Se carga la configuración del State LED
	GPIO_Config(&handlerStateLED);

	/* Configuración del PIN que recibe la información por la USB */
	handlerRxPIN.pGPIOx								= GPIOA;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinNumber		= PIN_3;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinMode		= GPIO_MODE_ALTFN;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinOPType		= GPIO_OTYPE_PUSHPULL;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinSpeed		= GPIO_OSPEED_MEDIUM;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinAltFunMode	= AF7;
	// Se carga la configuración del Rx PIN
	GPIO_Config(&handlerRxPIN);

	/* Configuración del PIN que envía la información por la USB (TX) */
	handlerTxPIN.pGPIOx								= GPIOA;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinNumber		= PIN_2;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinMode		= GPIO_MODE_ALTFN;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinOPType		= GPIO_OTYPE_PUSHPULL;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinSpeed		= GPIO_OSPEED_MEDIUM;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinAltFunMode	= AF7;
	// Se carga la configuración del Tx PIN
	GPIO_Config(&handlerTxPIN);

	/* Configuración del USART2 */
	handlerUSART2.ptrUSARTx							= USART2;
	handlerUSART2.USART_Config.USART_mode			= USART_MODE_RXTX;
	handlerUSART2.USART_Config.USART_baudrate		= USART_BAUDRATE_115200;
	handlerUSART2.USART_Config.USART_datasize		= USART_DATASIZE_8BIT;
	handlerUSART2.USART_Config.USART_parity			= USART_PARITY_NONE;
	handlerUSART2.USART_Config.USART_stopbits		= USART_STOPBIT_1;
	handlerUSART2.USART_Config.USART_interrupt		= USART_INTERRUPT_RX;
	// Se carga la configuración del USART
	USART_Config(&handlerUSART2);

	/* Configuración del Timer 2 */
	handlerStateLedTimer.ptrTIMx					= TIM2;
	handlerStateLedTimer.timerConfig.Timer_mode		= TIMER_MODE_UP;
	handlerStateLedTimer.timerConfig.Timer_speed	= TIMER_INCR_SPEED_1ms;
	handlerStateLedTimer.timerConfig.Timer_period	= 250;
	//Cargamos la configuración TIM2
	BTimer_Config(&handlerStateLedTimer);

	/* Configuración del Timer para calcular el tiempo de muestreo */
	handlerAdcSamplingTimer.ptrTIMx						= TIM4;
	handlerAdcSamplingTimer.timerConfig.Timer_mode		= TIMER_MODE_UP;
	handlerAdcSamplingTimer.timerConfig.Timer_speed		= TIMER_INCR_SPEED_1us;
	handlerAdcSamplingTimer.timerConfig.Timer_period	= 10;
	//Cargamos la configuración TIM2
	BTimer_Config(&handlerAdcSamplingTimer);

	/* Configuracion del ADC */
	adcSignalGenerator.channel			= ADC_CHANNEL_0;
	adcSignalGenerator.dataAlignment	= ADC_ALIGNMENT_RIGHT;
	adcSignalGenerator.resolution		= ADC_RESOLUTION_12_BIT;
	adcSignalGenerator.samplingPeriod	= ADC_SAMPLING_PERIOD_3_CYCLES;
	sensores[0] = adcSignalGenerator;
	// Se carga la configuración del ADC
	adcSingle_Config(&adcSignalGenerator);
	adcSQRx_Config(sensores, NUM_SESNSORS);
}

/* Implementacion del Callback para el timer2 */
void BTimer2_Callback(void){
	handlerStateLED.pGPIOx->ODR ^= GPIO_ODR_OD5;
}

/* Implementacion del Callback para el timer4 */
void BTimer4_Callback(void){
	counter10us++;
}

/* Implementacion del Callback para el Usart2 */
void Usart2_RX_Callback(void){
	rxData = getRxData();
}


void adcComplete_Callback(void){
	// Se añade a adcSignal el valor ADC
	adcSignal[dataPosition] = getADC();
	dataPosition++;
	// Lo siguiente se ejecuta cuando se llena el arreglo adcSignal
	if (dataPosition >= ADC_SIGNAL_SIZE){
		// Se detienen las conversiones
		stopContinuousConversion();
		// Se calcula el tiempo de muestreo, teniendo en cuenta que counter10us se incrementa cada 10us y que en total se hicieron 128 conversiones
		samplingTime = (counter10us*10)/ADC_SIGNAL_SIZE;
		dataPosition = 0;
		adcIsComplete = true;
	}
}

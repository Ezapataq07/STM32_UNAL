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
#include "GPIOxDriver.h"

void delay(uint32_t miliSegundos){
	/**
	 * La función delay() tiene el objetivo de generar periodos de tiempo en los cuales el programa no va a hacer nada, esto por medio del uso de un ciclo
	 * for. Para tener un poco de exactitud con el tiempo de delay, se hicieron pruebas empíricas por las cuales se concluyo que para NUESTRO MICRO
	 * 10940000 ciclos de for equivalen aproximadamente a 7500 milisegundos
	 */

	uint32_t numRepeticiones = miliSegundos * (10940000/7500); // Se define el numero de repeticiones del ciclo for con la conversión mencionada

	// Se genera un ciclo for que no hace nada interiormente con el número de repeticiones calculadas
	for(uint32_t i = 0; i <= numRepeticiones; i++){
	}
}


int main(void)
{

	// Definimos el handler para el PIN que deseamos configurar
	GPIO_Handler_t handlerUserLedPin = {0};
	// Deseamos trabajar con el puerto GPIOA
	handlerUserLedPin.pGPIOx = GPIOA;
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinNumber			= PIN_5;				// De acuerdo al Reference Diagram el User LED está conectado al PIN A5
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_OUT;		// Se configura el PIN en modo OUTPUT
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;	// Se define el OUTPUT TYPE como Push-Pull, para poder hacer el blinky
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;	// Está configuración no es relevante para el PIN en este caso
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_MEDIUM;	// Se configura el OUTPUT con una velocidad MEDIUM
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinAltFunMode		= AF0;					// Está configuración no es relevante para el PIN en este caso

	//Cargamos la configuración del PIN específico
	GPIO_Config(&handlerUserLedPin);

	// En este ciclo principal se ejecuta el corazón del programa, que es hacer el blinky
	while(1){
		GPIO_WritePin(&handlerUserLedPin, SET); 	// Se hace que el PIN A5 (User LED) quede encendido
		delay(1000);									// Se genera un delay de aproximadamente 500ms (tiempo ON del User LED)
		GPIO_WritePin(&handlerUserLedPin, RESET);	// Se hace que el PIN A5 (User LED) quede apagado
		delay(500);									// Se genera un delay de aproximadamente 350ms (tiempo OFF del User LED)

	}
	return 0;
}

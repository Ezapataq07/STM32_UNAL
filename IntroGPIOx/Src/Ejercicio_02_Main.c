/*
 * Ejercicio_02_Main.c
 *
 * *************************************************
 *      Authors: - Luisa Fernanda Orozco López
 *      		 - Emanuel Zapata Querubín
 * *************************************************
 */

/* Se incluyen los módulos y drivers */
#include <stdint.h>
#include "stm32f411xx_hal.h"
#include "GPIOxDriver.h"

/* Se definen los prototipos de las funciones */
void delay(uint32_t miliSegundos);

/**
 *  Función principal del programa. Aquí se resuelve lo pedido en el Ejercicio 2: un blinky cuyo periodo está controlado por el User Button
 */
int main (void) {

	// Definimos los Handlers para el PIN que controla el User LED y para el User Button
	GPIO_Handler_t handlerUserLedPin = {0};
	GPIO_Handler_t handlerUserButtonPin = {0};

	/* Se definen las configuraciones para los pines a utilizar por medio de los handlers */

	// Configuración para el User LED, el cual se encuentra conectado al GPIOA
	handlerUserLedPin.pGPIOx = GPIOA;
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinNumber			= PIN_5;				// De acuerdo al Reference Diagram el User LED está conectado al PIN A5
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_OUT;		// Se configura el PIN en modo OUTPUT
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;	// Se define el OUTPUT TYPE como Push-Pull, para poder hacer el blinky
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;	// Está configuración no es relevante para el PIN en este caso
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_MEDIUM;	// Se configura el OUTPUT con una velocidad MEDIUM
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinAltFunMode		= AF0;					// Está configuración no es relevante para el PIN en este caso

	// Configuración para el User Button, el cual se encuentra en el periférico GPIOC
	handlerUserButtonPin.pGPIOx = GPIOC;
	handlerUserButtonPin.GPIO_PinConfig.GPIO_PinNumber			= PIN_13;				// De acuerdo al Reference Diagram (RD) el User Button está conectad al PIN C13
	handlerUserButtonPin.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_IN;			// Se configura el PIN en modo INPUT
	handlerUserButtonPin.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;	// Está configuración no es relevante para el PIN en este caso
	handlerUserButtonPin.GPIO_PinConfig.GPIO_PinPuPdControl		= GPIO_PUPDR_NOTHING;	// Se configura el INPUT para que no tenga ni Pull-Up ni Pull-Down
																						// Aclarando que según el RD, el PIN está por defecto en configuración Pull-Up
	handlerUserButtonPin.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_MEDIUM;	// Está configuración no es relevante para el PIN en este caso
	handlerUserButtonPin.GPIO_PinConfig.GPIO_PinAltFunMode		= AF0;					// Está configuración no es relevante para el PIN en este caso


	//Cargamos la configuración de cada uno de los Pines definidos
	GPIO_Config(&handlerUserLedPin);
	GPIO_Config(&handlerUserButtonPin);

	uint32_t buttonState = 0; 	// Se define la variable buttonState, la cual leerá el estado ON u OFF del UserButton


	// En este ciclo principal se ejecuta el blinky controlado por el User Button
	while(1){
		buttonState = ! GPIO_ReadPin(&handlerUserButtonPin);	// Se llama a la función GPIO_ReadPin para leer el estado del PIN al cual está conectado el UserButton
																// Como el PIN está en Pull-Up por defecto, se utiliza el "bang!" para que la variable sea 1 si el
																// botón está presionado y 0 si no lo está

		// En este condicional se evalúa si el User Button está presionado o no para elegir el periodo de oscilación del blinky
		// Si está presionado cada estado ON y OFF tienen 200ms de duración; Si no está presionado cada estado ON y OFF tienen 400ms de duración
		if (buttonState){
			delay(200);									//Se hace un delay de 200ms aproximadamente
			GPIO_WritePin(&handlerUserLedPin, SET);		// Se hace que el PIN A5 (User LED) quede encendido
			delay(200);									//Se hace un delay de 200ms aproximadamente
			GPIO_WritePin(&handlerUserLedPin, RESET);	// Se hace que el PIN A5 (User LED) quede apagado
		} else{
			delay(400);									//Se hace un delay de 400ms aproximadamente
			GPIO_WritePin(&handlerUserLedPin, SET);		// Se hace que el PIN A5 (User LED) quede encendido
			delay(400);									//Se hace un delay de 400ms aproximadamente
			GPIO_WritePin(&handlerUserLedPin, RESET);	// Se hace que el PIN A5 (User LED) quede apagado
		}
	}
	return 0;
}

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

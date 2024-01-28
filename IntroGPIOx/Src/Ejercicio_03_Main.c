/*
 * Ejercicio_03_Main.c
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
 *  Función principal del programa. Para este ejercicio, se definen diferentes comportamientos para el User LED y un LED externo,
 *  controlados por el User Button y un botón externo
 */
int main (void) {

	// Definimos los handlers para User LED, External LED, User Button y External Button
	GPIO_Handler_t handlerUserLedPin 	= {0};
	GPIO_Handler_t handlerUserButtonPin = {0};
	GPIO_Handler_t handlerExtLedPin 	= {0};
	GPIO_Handler_t handlerExtButtonPin 	= {0};


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
	handlerUserButtonPin.GPIO_PinConfig.GPIO_PinNumber			= PIN_13;				// De acuerdo al Reference Diagram (RD) el User Button está conectado al PIN C13
	handlerUserButtonPin.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_IN;			// Se configura el PIN en modo INPUT
	handlerUserButtonPin.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;	// Está configuración no es relevante para el PIN en este caso
	handlerUserButtonPin.GPIO_PinConfig.GPIO_PinPuPdControl		= GPIO_PUPDR_NOTHING;	// Se configura el INPUT para que no tenga ni Pull-Up ni Pull-Down
																						// Aclarando que según el RD, el PIN está por defecto en configuración Pull-Up
	handlerUserButtonPin.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_MEDIUM;	// Está configuración no es relevante para el PIN en este caso
	handlerUserButtonPin.GPIO_PinConfig.GPIO_PinAltFunMode		= AF0;					// Está configuración no es relevante para el PIN en este caso

	// Configuración para el External LED, el cual se encuentra conectado al GPIOB
	handlerExtLedPin.pGPIOx = GPIOB;
	handlerExtLedPin.GPIO_PinConfig.GPIO_PinNumber			= PIN_9;				// El External LED está conectado al PIN A9
	handlerExtLedPin.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_OUT;		// Se configura el PIN en modo OUTPUT
	handlerExtLedPin.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;	// Se define el OUTPUT TYPE como Push-Pull, para poder hacer el blinky
	handlerExtLedPin.GPIO_PinConfig.GPIO_PinPuPdControl		= GPIO_PUPDR_NOTHING;	// Está configuración no es relevante para el PIN en este caso
	handlerExtLedPin.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_MEDIUM;	// Se configura el OUTPUT con una velocidad MEDIUM
	handlerExtLedPin.GPIO_PinConfig.GPIO_PinAltFunMode		= AF0;					// Está configuración no es relevante para el PIN en este caso


	// Configuración para el External Button, el cual se encuentra en el periférico GPIOC
	handlerExtButtonPin.pGPIOx = GPIOC;
	handlerExtButtonPin.GPIO_PinConfig.GPIO_PinNumber			= PIN_6;				// El External Button está conectado al PIN C6
	handlerExtButtonPin.GPIO_PinConfig.GPIO_PinMode				= GPIO_MODE_IN;			// Se configura el PIN en modo INPUT
	handlerExtButtonPin.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;	// Está configuración no es relevante para el PIN en este caso
	handlerExtButtonPin.GPIO_PinConfig.GPIO_PinPuPdControl		= GPIO_PUPDR_PULLDOWN;	// Se configura el INPUT en modo Pull - Down y conectamos el botón a Vcc y al PIN
																						// Como es normalmente Abierto será 1 cuendo esté pulsado y 0 cuando no lo esté
	handlerExtButtonPin.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_MEDIUM;	// Está configuración no es relevante para el PIN en este caso
	handlerExtButtonPin.GPIO_PinConfig.GPIO_PinAltFunMode		= AF0;					// Está configuración no es relevante para el PIN en este caso



	//Cargamos la configuración para cada uno de los Pines
	GPIO_Config(&handlerUserLedPin);
	GPIO_Config(&handlerUserButtonPin);
	GPIO_Config(&handlerExtLedPin);
	GPIO_Config(&handlerExtButtonPin);

	uint32_t userButtonState = 0;	// Se define la variable userButtonState, la cual leerá el estado ON u OFF del UserButton
	uint32_t extButtonState = 0;	// Se define la variable extButtonState, la cual leerá el estado ON u OFF del ExtButton


	// En este ciclo principal se ejecuta el blinky de ambos LEDs controlados por ambos botones (User y External)
	while(1){

		userButtonState = ! GPIO_ReadPin(&handlerUserButtonPin);	// Se llama a la función GPIO_ReadPin para leer el estado del PIN al cual está conectado el UserButton
																	// Como el PIN está en Pull-Up por defecto, se utiliza el "bang!" para que la variable sea 1 si el
																	// botón está presionado y 0 si no lo está
		extButtonState	= GPIO_ReadPin(&handlerExtButtonPin);		// Se llama a la función GPIO_ReadPin para leer el estado del PIN al cual está conectado el ExtButton


		// En los siguiente condicionales, se evaluan la combianción de estados para los botones, y de acuerdo a esto se ejecutan diferentes tipos de blinky para
		// cada uno de los LEDs
		if (userButtonState == 1 && extButtonState == 0){			// Para el User Button pulsado y el External Botton sin pulsar
			GPIO_WritePin(&handlerUserLedPin, SET);		// Se hace que el PIN A5 (User LED) quede encendido
			GPIO_WritePin(&handlerExtLedPin, RESET);	// Se hace que el PIN B9 (Exteral LED) quede apagado
			delay(200);									// Se hace un delay de 200ms aproximadamente
			GPIO_WritePin(&handlerUserLedPin, RESET);	// Se hace que el PIN A5 (User LED) quede apagado
			GPIO_WritePin(&handlerExtLedPin, SET);		// Se hace que el PIN B9 (Exteral LED) quede encendido
			delay(200);									// Se hace un delay de 200ms aproximadamente
		}
		else if (userButtonState == 0 && extButtonState == 1){		// Para el User Button sin pulsar y el External Botton pulsado
			GPIO_WritePin(&handlerUserLedPin, SET);		// Se hace que el PIN A5 (User LED) quede encendido
			delay(200);									// Se hace un delay de 200ms aproximadamente
			GPIO_WritePin(&handlerExtLedPin, RESET);	// Se hace que el PIN B9 (Exteral LED) quede apagado
			delay(200);									// Se hace un delay de 200ms aproximadamente
			GPIO_WritePin(&handlerExtLedPin, SET);		// Se hace que el PIN B9 (Exteral LED) quede encendido
		}
		else if (userButtonState == 1 && extButtonState == 1){		// Para cuando ambos botones estén pulsados
			GPIO_WritePin(&handlerExtLedPin, RESET);	// Se hace que el PIN B9 (Exteral LED) quede apagado
			GPIO_WritePin(&handlerUserLedPin, RESET);	// Se hace que el PIN A5 (User LED) quede apagado
		}
		else {														// Para cuando ninguno de los botones esté pulsado
			GPIO_WritePin(&handlerUserLedPin, SET);		// Se hace que el PIN A5 (User LED) quede encendido
			GPIO_WritePin(&handlerExtLedPin, SET);		// Se hace que el PIN B9 (Exteral LED) quede encendido
			delay(400);									// Se hace un delay de 400ms aproximadamente
			GPIO_WritePin(&handlerUserLedPin, RESET);	// Se hace que el PIN A5 (User LED) quede apagado
			GPIO_WritePin(&handlerExtLedPin, RESET);	// Se hace que el PIN B9 (Exteral LED) quede apagado
			delay(400);									// Se hace un delay de 400ms aproximadamente
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

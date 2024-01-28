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



/* Definición de handlers */
GPIO_Handler_t 		handlerStateLED 		= {0};
BTIMER_Handler_t	handlerStateLedTimer	= {0};
BTIMER_Handler_t	handlerDisplayTimer		= {0}; // Timer que controla el suicheo entre ambos Displays
GPIO_Handler_t		handlerDisplay1			= {0}; // Controla el transistor que suichea el Display de las decenas
GPIO_Handler_t		handlerDisplay2			= {0}; // Controla el transistor que suichea el Display de las unidades

/* Definición de los handlers que controlan los LEDs de los Displays */
GPIO_Handler_t		LedA 					= {0};
GPIO_Handler_t		LedB 					= {0};
GPIO_Handler_t		LedC 					= {0};
GPIO_Handler_t		LedD 					= {0};
GPIO_Handler_t		LedE 					= {0};
GPIO_Handler_t		LedF					= {0};
GPIO_Handler_t		LedG 					= {0};
GPIO_Handler_t		LedDP 					= {0};

/* Definición de las variables */
EXTI_Config_t		extiEmision				= {0}; 		// Para configurar el EXTI
EXTI_Config_t		extiReception			= {0};

uint8_t				display2State 			= RESET;	// Contiene el estado del Display2
uint8_t				units 					= 0;
uint8_t				tens  					= 0;
uint8_t				displaySet 				= false;	// Controla si el Display que debe configurarse está configurado o no. Es necesaria ya que
														// el ciclo while se ejecuta varias veces antes de que haya que cambiar de Display.

// La siguiente variable es una arreglo que en la posición i contiene un binario de 8 bits que contiene la información necesaria para configurar
// el número i en el display. Dicha configuración consiste en un 1 en el LED del display que debe encenderse, siedo A el bit más significativo y DP el menos.
uint8_t			numbers[10] = {0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110,
							   0b10110110, 0b10111110, 0b11100000, 0b11111110, 0b11110110};

/* Definición de los prototipos de las funciones */
void initSystem(void);
void Display_WriteNumber(uint8_t number);

int main(void){
	// Se inicializa la configuración
	initSystem();

	/* Ciclo principal del programa */
	while(1){
		// Se verifica si el display (cualquiera que sea) está configurado o no
		if (displaySet == false){
			// Como no está configurado, se verifica el estado de uno de los Displays, en este caso el de las unidades
			display2State = GPIO_ReadPin(&handlerDisplay2);
			if(display2State == SET){
				// Como el display2 es el que está encendido, entonces se pone la configuración del número de las unidades
				Display_WriteNumber(numbers[units]);
				// La configuración del Display está lista, de manera que no es necesario configurarlo de nuevo hasta una nueva interrupción del Timer
				displaySet = true;
			}
			else{
				// En este caso el Display1 está encendido, entonces se pone la configuración del número de las decenas
				Display_WriteNumber(numbers[tens]);
				// La configuración del Display está lista, de manera que no es necesario configurarlo de nuevo hasta una nueva interrupción del Timer
				displaySet = true;
			}
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
	handlerDisplay1.pGPIOx 									= GPIOB;
	handlerDisplay1.GPIO_PinConfig.GPIO_PinNumber			= PIN_8;
	handlerDisplay1.GPIO_PinConfig.GPIO_PinMode				= GPIO_MODE_OUT;
	handlerDisplay1.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;
	handlerDisplay1.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_HIGH;
	// Se carga la configuración del Display1
	GPIO_Config(&handlerDisplay1);

	/* Configuración del Display2 */
	handlerDisplay2.pGPIOx 									= GPIOB;
	handlerDisplay2.GPIO_PinConfig.GPIO_PinNumber			= PIN_9;
	handlerDisplay2.GPIO_PinConfig.GPIO_PinMode				= GPIO_MODE_OUT;
	handlerDisplay2.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;
	handlerDisplay2.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_HIGH;
	// Se carga la configuración del Display2
	GPIO_Config(&handlerDisplay2);

	// Se inicializan los valores de los transistores que controlan los Displays, con el fin que siempre estén intercalados, pues más adelante
	// su suicheo será con un XOR
	GPIO_WritePin(&handlerDisplay1, RESET);
	GPIO_WritePin(&handlerDisplay2, SET);

	/* Configuración del LED correspondiente a la segmento A */
	LedA.pGPIOx 									= GPIOB;
	LedA.GPIO_PinConfig.GPIO_PinNumber				= PIN_4;
	LedA.GPIO_PinConfig.GPIO_PinMode				= GPIO_MODE_OUT;
	LedA.GPIO_PinConfig.GPIO_PinOPType				= GPIO_OTYPE_PUSHPULL;
	LedA.GPIO_PinConfig.GPIO_PinSpeed				= GPIO_OSPEED_HIGH;
	// Se carga la configuración de dicho segmento
	GPIO_Config(&LedA);

	/* Configuración del LED correspondiente a la segmento B */
	LedB.pGPIOx 									= GPIOB;
	LedB.GPIO_PinConfig.GPIO_PinNumber				= PIN_5;
	LedB.GPIO_PinConfig.GPIO_PinMode				= GPIO_MODE_OUT;
	LedB.GPIO_PinConfig.GPIO_PinOPType				= GPIO_OTYPE_PUSHPULL;
	LedB.GPIO_PinConfig.GPIO_PinSpeed				= GPIO_OSPEED_HIGH;
	// Se carga la configuración de dicho segmento

	GPIO_Config(&LedB);

	/* Configuración del LED correspondiente a la segmento C */
	LedC.pGPIOx 									= GPIOA;
	LedC.GPIO_PinConfig.GPIO_PinNumber				= PIN_8;
	LedC.GPIO_PinConfig.GPIO_PinMode				= GPIO_MODE_OUT;
	LedC.GPIO_PinConfig.GPIO_PinOPType				= GPIO_OTYPE_PUSHPULL;
	LedC.GPIO_PinConfig.GPIO_PinSpeed				= GPIO_OSPEED_HIGH;
	// Se carga la configuración de dicho segmento

	GPIO_Config(&LedC);

	/* Configuración del LED correspondiente a la segmento D */
	LedD.pGPIOx 									= GPIOC;
	LedD.GPIO_PinConfig.GPIO_PinNumber				= PIN_7;
	LedD.GPIO_PinConfig.GPIO_PinMode				= GPIO_MODE_OUT;
	LedD.GPIO_PinConfig.GPIO_PinOPType				= GPIO_OTYPE_PUSHPULL;
	LedD.GPIO_PinConfig.GPIO_PinSpeed				= GPIO_OSPEED_HIGH;
	// Se carga la configuración de dicho segmento

	GPIO_Config(&LedD);

	/* Configuración del LED correspondiente a la segmento E */
	LedE.pGPIOx 									= GPIOA;
	LedE.GPIO_PinConfig.GPIO_PinNumber				= PIN_9;
	LedE.GPIO_PinConfig.GPIO_PinMode				= GPIO_MODE_OUT;
	LedE.GPIO_PinConfig.GPIO_PinOPType				= GPIO_OTYPE_PUSHPULL;
	LedE.GPIO_PinConfig.GPIO_PinSpeed				= GPIO_OSPEED_HIGH;
	// Se carga la configuración de dicho segmento

	GPIO_Config(&LedE);

	/* Configuración del LED correspondiente a la segmento F */
	LedF.pGPIOx 									= GPIOA;
	LedF.GPIO_PinConfig.GPIO_PinNumber				= PIN_7;
	LedF.GPIO_PinConfig.GPIO_PinMode				= GPIO_MODE_OUT;
	LedF.GPIO_PinConfig.GPIO_PinOPType				= GPIO_OTYPE_PUSHPULL;
	LedF.GPIO_PinConfig.GPIO_PinSpeed				= GPIO_OSPEED_HIGH;
	// Se carga la configuración de dicho segmento

	GPIO_Config(&LedF);

	/* Configuración del LED correspondiente a la segmento G */
	LedG.pGPIOx 									= GPIOB;
	LedG.GPIO_PinConfig.GPIO_PinNumber				= PIN_6;
	LedG.GPIO_PinConfig.GPIO_PinMode				= GPIO_MODE_OUT;
	LedG.GPIO_PinConfig.GPIO_PinOPType				= GPIO_OTYPE_PUSHPULL;
	LedG.GPIO_PinConfig.GPIO_PinSpeed				= GPIO_OSPEED_HIGH;
	// Se carga la configuración de dicho segmento

	GPIO_Config(&LedG);

	/* Configuración del LED correspondiente a la segmento DP */
	LedDP.pGPIOx 									= GPIOB;
	LedDP.GPIO_PinConfig.GPIO_PinNumber				= PIN_10;
	LedDP.GPIO_PinConfig.GPIO_PinMode				= GPIO_MODE_OUT;
	LedDP.GPIO_PinConfig.GPIO_PinOPType				= GPIO_OTYPE_PUSHPULL;
	LedDP.GPIO_PinConfig.GPIO_PinSpeed				= GPIO_OSPEED_HIGH;
	// Se carga la configuración de dicho segmento
	GPIO_Config(&LedDP);

	/* Configuración del Timer2, que controla el blinky del StateLED */
	handlerStateLedTimer.ptrTIMx					= TIM2;
	handlerStateLedTimer.timerConfig.Timer_mode		= TIMER_MODE_UP;
	handlerStateLedTimer.timerConfig.Timer_speed	= TIMER_INCR_SPEED_1ms;
	handlerStateLedTimer.timerConfig.Timer_period	= 250;
	// Se carga la configuración del Timer2
	BTimer_Config(&handlerStateLedTimer);

	/* configuración del Timer4, que controla el suicheo entre los Displays */
	handlerDisplayTimer.ptrTIMx						= TIM4;
	handlerDisplayTimer.timerConfig.Timer_mode		= TIMER_MODE_UP;
	handlerDisplayTimer.timerConfig.Timer_speed		= TIMER_INCR_SPEED_1ms;
	handlerDisplayTimer.timerConfig.Timer_period	= 7;
	// Se carga la configuración del Timer4
	BTimer_Config(&handlerDisplayTimer);

	/* Configuración del EXTI10 */
	extiEmision.EXTIx			= EXTI10;
	extiEmision.pinPort			= PC;
	extiEmision.pinPUPD_Mode     = GPIO_PUPDR_PULLDOWN;
	extiEmision.triggerMode		= RISING_TRIGGER;
	// Se carga la configuración del EXTI
	exti_Config(&extiEmision);

	/* Configuración del EXTI10 */
	extiReception.EXTIx			= EXTI12;
	extiReception.pinPort			= PC;
	extiReception.pinPUPD_Mode     = GPIO_PUPDR_PULLDOWN;
	extiReception.triggerMode		= FALLING_TRIGGER;
	// Se carga la configuración del EXTI
	exti_Config(&extiReception);


}

/* Implementacion del Callback para el timer2 */
void BTimer2_Callback(void){
	handlerStateLED.pGPIOx->ODR ^= GPIO_ODR_OD5;
}

/* Implementación del Callback para el timer4 */
void BTimer4_Callback(void){
	// Se lleva la variable displaySet a false, indicando que debe cargarse una nueva configuración el respectivo display
	displaySet = false;
	// Se hace un XOR para cambiar el estado de ambos transistores, como están intercalados uno se desactiva y el otro se avtiva, o viceversa
	handlerDisplay1.pGPIOx->ODR ^= GPIO_ODR_OD8;
	handlerDisplay2.pGPIOx->ODR ^= GPIO_ODR_OD9;
}

/* Implementación del Callback para el EXTI10 */
void Exti10_Callback(void){
	if (units == 9 && tens == 9){ // Si se llegó al número 99, se reinician a cero las unidades y las decenas
		units 	= 0;
		tens 	= 0;
	}
	else if (units == 9){	// Cuando las unidades llegaron a 9, se hacen cero y se aumenta en una unidad las decenas
		units = 0;
		tens++;
	}
	else{ // En cualquier otro caso se aumenta en una unidad las unidades
		units++;
	}
}

/* Implementación del Callback para el EXTI10 */
void Exti12_Callback(void){
	if (units == 9 && tens == 9){ // Si se llegó al número 99, se reinician a cero las unidades y las decenas
		units 	= 0;
		tens 	= 0;
	}
	else if (units == 9){	// Cuando las unidades llegaron a 9, se hacen cero y se aumenta en una unidad las decenas
		units = 0;
		tens++;
	}
	else{ // En cualquier otro caso se aumenta en una unidad las unidades
		units++;
	}
}

/* Función para Configurar un número en el Display */
void Display_WriteNumber(uint8_t number){
	/**
	 * La función Display_WriteNumber toma un número del 0 al 9 y configura cada segmento del display que enciende dicho número
	 */

	// Como los Displays configurados son de ánodo común, debe cargarse un cero en los segmentos que se desean encender
	number = ~number;
	// Se define la variable state, que contendrá el estado de cada uno de los segmentos a configurar (tomando desde el bit menos significativo (DP) al
	// más significativo (A)
	uint8_t state = 0b1 & number;
	// Se escribe el estado correspondiente al segmento DP
	GPIO_WritePin(&LedDP, state);

	// Se hace un shift de number una vez a la derecha, para que en el bit menos significativo quede el estado del segmento G
	number >>= 1;
	// Se lee el estado del segmento G
	state = 0b1 & number;
	// Se carga el estado del segmento G
	GPIO_WritePin(&LedG, state);

	// Se hace un shift de number una vez a la derecha, para que en el bit menos significativo quede el estado del segmento F
	number >>= 1;
	// Se lee el estado del segmento F
	state = 0b1 & number;
	// Se carga el estado del segmento F
	GPIO_WritePin(&LedF, state);

	// Se hace un shift de number una vez a la derecha, para que en el bit menos significativo quede el estado del segmento E
	number >>= 1;
	// Se lee el estado del segmento E
	state = 0b1 & number;
	// Se carga el estado del segmento E
	GPIO_WritePin(&LedE, state);

	// Se hace un shift de number una vez a la derecha, para que en el bit menos significativo quede el estado del segmento D
	number >>= 1;
	// Se lee el estado del segmento D
	state = 0b1 & number;
	// Se carga el estado del segmento D
	GPIO_WritePin(&LedD, state);

	// Se hace un shift de number una vez a la derecha, para que en el bit menos significativo quede el estado del segmento C
	number >>= 1;
	// Se lee el estado del segmento C
	state = 0b1 & number;
	// Se carga el estado del segmento C
	GPIO_WritePin(&LedC, state);

	// Se hace un shift de number una vez a la derecha, para que en el bit menos significativo quede el estado del segmento B
	number >>= 1;
	// Se lee el estado del segmento B
	state = 0b1 & number;
	// Se carga el estado del segmento B
	GPIO_WritePin(&LedB, state);

	// Se hace un shift de number una vez a la derecha, para que en el bit menos significativo quede el estado del segmento A
	number >>= 1;
	// Se lee el estado del segmento A
	state = 0b1 & number;
	// Se carga el estado del segmento A
	GPIO_WritePin(&LedA, state);
}



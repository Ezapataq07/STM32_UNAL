/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Emanuel Zapata Querubin
 * @brief          : Desarrollo de la Tarea #3: Control de Timers con USART,
 * 					 recepción con interrupciones
 ******************************************************************************
 */

/* Se incluyen las librerías a utilizar */
#include <stm32f4xx.h>
#include <stdint.h>
#include "GPIOxDriver.h"
#include "USARTxDriver.h"
#include "BasicTimer.h"

/* Definición de variables */
GPIO_Handler_t 		handlerExtLED 		= {0};		// Handler para el LED Externo
GPIO_Handler_t 		handlerStateLED 	= {0};		// Handler para el LED de Estado
GPIO_Handler_t 		handlerRxPIN	 	= {0};		// Handler para el PIN encargado de la recepción con Usart
BTIMER_Handler_t	handlerTIM2			= {0};		// Handler para el TIMER 2, que controlará el blinky del LED de Estado
BTIMER_Handler_t	handlerTIM3			= {0};		// Handler para el TIMER 3, que controlará el blinky del LED Externo
USART_Handler_t		handlerUSART2		= {0};		// Handler para el USART 2
uint32_t			generalState		= 1;		// Variable de estado del programa, que indica si el LED externo esta apagado o en funcionamiento
char				receivedChar		= '\0';		// Variable que recibe los bits recibidos en el RX del USART

/* Prototipos de las funciones */
void initSystem(void);
void setPeriod(BTIMER_Handler_t *ptrUsartHandler, uint16_t period);
void setTimer3IntMode(uint8_t state);

int main(void){
	/**
	 * Función principal del programa, en esta se configura un blinky en el LED externo según el valor recibido por consola, de la siguiente manera:
	 * 		- 'n': Corresponde a un blinky de 300ms
	 * 		- 'f': Corresponde a un blinky de 200ms
	 * 		- 'u': Corresponde a un blinky de 100ms
	 * 		- 'O': Hace las veces de interruptor ON/OFF
	 */
	// Se inicializa la conficuración de los diferentes Handlers
	initSystem();

	// Ciclo principal del programa, la variable receivedChar será igual a '\0' hasta que se reciba un dato por interrupción, caso en el cual ingresa al condicional
	// correspondiente y se le asigna nuevamente '\0' luego de hacer la respectiva configuración
	while(1){
		// Se evalúa si la variable receivedChar ha recibido algún dato
		// En cada condicional se hace una operación AND con la variable generalState, esto con el fin de que no se cambie la configuración del Timer 3 cuando
		// este se encuentre apagado
		if (receivedChar != '\0'){
			if (receivedChar == 'n' && generalState){
				setPeriod(&handlerTIM3, 300); // En caso de que el dato recibido corresponda a 'n', se configura el periodo del Timer 3 a 300ms
			}
			else if (receivedChar == 'f' && generalState){
				setPeriod(&handlerTIM3, 200); // En caso de que el dato recibido corresponda a 'f', se configura el periodo del Timer 3 a 300ms
			}
			else if (receivedChar == 'u' && generalState){
				setPeriod(&handlerTIM3, 100); // En caso de que el dato recibido corresponda a 'u', se configura el periodo del Timer 3 a 300ms
			}
			else if (receivedChar == 'O'){
				// Cuando se recibe O se debe cambiar de ON a OFF o viceversa, por tanto se cambia el valor de la variable generalState mediante un bang!
				generalState = !(generalState);
				if (generalState){
					// Si generalState es 1, debe encenderse el LED Externo con el blinky correspondiente, por tanto se activan las interrupciones del Timer 3
					setTimer3IntMode(1);
				} else {
					// Si generalState es 0, debe apagarse el LED externo, de manera que se desactivan las interrupciones del Timer 3
					setTimer3IntMode(0);
					// Se asegura el apagado del LED externo, en caso de que se desactive el Timer mientras este está encendido
					GPIO_WritePin(&handlerExtLED, 0);
				}
			}
			// Se asigna nuevamente '\0'  a receivedChar
			receivedChar = '\0';
		}

	}


	return 0;
}

void initSystem(void){
	/**
	 * La función initSystem contiene la configuración de los diferentes Handlers declarados en la definición de variables
	 */

	/* Configuración para el State LED, correspondiente al Pin PA5 */
	handlerStateLED.pGPIOx 								= GPIOA;
	handlerStateLED.GPIO_PinConfig.GPIO_PinNumber		= PIN_5;
	handlerStateLED.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_OUT;		// Se configura el PIN en modo OUTPUT
	handlerStateLED.GPIO_PinConfig.GPIO_PinOPType		= GPIO_OTYPE_PUSHPULL;	// Se define el OUTPUT TYPE como Push-Pull, para poder hacer el blinky
	handlerStateLED.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;	// Está configuración no es relevante para el PIN en este caso
	handlerStateLED.GPIO_PinConfig.GPIO_PinSpeed		= GPIO_OSPEED_MEDIUM;	// Se configura el OUTPUT con una velocidad MEDIUM
	handlerStateLED.GPIO_PinConfig.GPIO_PinAltFunMode	= AF0;					// Está configuración no es relevante para el PIN en este caso

	// Se carga la configuración del State LED
	GPIO_Config(&handlerStateLED);

	/* Configuración para el Ext LED, correspondiente al Pin PB9 */
	handlerExtLED.pGPIOx 								= GPIOB;
	handlerExtLED.GPIO_PinConfig.GPIO_PinNumber			= PIN_9;
	handlerExtLED.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_OUT;		// Se configura el PIN en modo OUTPUT
	handlerExtLED.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;	// Se define el OUTPUT TYPE como Push-Pull, para poder hacer el blinky
	handlerExtLED.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;	// Está configuración no es relevante para el PIN en este caso
	handlerExtLED.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_MEDIUM;	// Se configura el OUTPUT con una velocidad MEDIUM
	handlerExtLED.GPIO_PinConfig.GPIO_PinAltFunMode		= AF0;					// Está configuración no es relevante para el PIN en este caso

	// Se carga la configuración del Ext LED
	GPIO_Config(&handlerExtLED);

	/* Configuración del PIN que recibe la información por la USB (PA3) */
	handlerRxPIN.pGPIOx								= GPIOA;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinNumber		= PIN_3;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinMode		= GPIO_MODE_ALTFN;			// Se configura en modo Alternate Function
	handlerRxPIN.GPIO_PinConfig.GPIO_PinOPType		= GPIO_OTYPE_PUSHPULL;		// Esta configuración no es relevante para este PIN
	handlerRxPIN.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;		// Esta configuración no es relevante para este PIN
	handlerRxPIN.GPIO_PinConfig.GPIO_PinSpeed		= GPIO_OSPEED_MEDIUM;		// Esta configuración no es relevante para este PIN
	handlerRxPIN.GPIO_PinConfig.GPIO_PinAltFunMode	= AF7;						// Se configura la función alternativa 7, que corresponde al USART RX

	// Se carga la configuración del Rx PIN
	GPIO_Config(&handlerRxPIN);

	/* Configuración del USART2 */
	handlerUSART2.ptrUSARTx							= USART2;
	handlerUSART2.USART_Config.USART_mode			= USART_MODE_RX;			// Se configura en modo recepción
	handlerUSART2.USART_Config.USART_baudrate		= USART_BAUDRATE_115200;
	handlerUSART2.USART_Config.USART_datasize		= USART_DATASIZE_8BIT;
	handlerUSART2.USART_Config.USART_parity			= USART_PARITY_NONE;
	handlerUSART2.USART_Config.USART_stopbits		= USART_STOPBIT_1;
	handlerUSART2.USART_Config.USART_interrupt		= USART_INTERRUPT_RX;		// Se activa las interrupciones por recepción

	// Se carga la configuración del USART
	USART_Config(&handlerUSART2);

	/* Configuración del Timer 2 */
	handlerTIM2.ptrTIMx						= TIM2;
	handlerTIM2.timerConfig.Timer_mode		= TIMER_MODE_UP;
	handlerTIM2.timerConfig.Timer_speed		= TIMER_INCR_SPEED_1ms;		// Se configura conteos cada 1ms
	handlerTIM2.timerConfig.Timer_period	= 250;						// Se configura un periodo de 250

	//Cargamos la configuración TIM2
	BTimer_Config(&handlerTIM2);

	/* Configuracion del Timer 3 */
	handlerTIM3.ptrTIMx						= TIM3;
	handlerTIM3.timerConfig.Timer_mode		= TIMER_MODE_UP;
	handlerTIM3.timerConfig.Timer_speed		= TIMER_INCR_SPEED_1ms;		// Se configura conteos cada 1ms
	handlerTIM3.timerConfig.Timer_period	= 300;						// Se configura un periodo de 300

	//Cargamos la configuración TIM2
	BTimer_Config(&handlerTIM3);

}

/* Implementacion del Callback para el timer2 */
void BTimer2_Callback(void){
	handlerStateLED.pGPIOx->ODR ^= GPIO_ODR_OD5;  // Se hace el blinky sobre el LED de estado
}


/* Implementacion del Callback para el timer3 */
void BTimer3_Callback(void){
	handlerExtLED.pGPIOx->ODR ^= GPIO_ODR_OD9;	// Se hace el blinky sobre el LED externo
}

/* Implementacion del Callback RX para el Usart2 */
void Usart2_RX_Callback(void){
	receivedChar = getRxData();		// Se rescata la variable recibida
}

void setPeriod(BTIMER_Handler_t *ptrTimerHandler, uint16_t period){
	/**
	 * La función setPeriod cambia el periodo del Timer correspondiente al handler indicado, a un valor indicado por el usuario
	 */
	ptrTimerHandler->timerConfig.Timer_period = period;
	BTimer_Config(ptrTimerHandler);		// Se vuelve a cargar la cofiguración del Timer con el nuevo periodo
}

void setTimer3IntMode(uint8_t state){
	/**
	 * La función setTimerIntMode activa y desactiva las interrupciones del Timer 3, según la variable de estado state
	 * 		- state = 1: activa las interrupciones
	 * 		- stare = 0: desactiva las interrupciones
	 */
	if (state){
		__NVIC_EnableIRQ(TIM3_IRQn);
	}
	else {
		__NVIC_DisableIRQ(TIM3_IRQn);
	}
}

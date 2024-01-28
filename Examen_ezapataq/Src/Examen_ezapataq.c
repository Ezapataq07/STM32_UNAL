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

/* Se incluyen las librerías necesarias */
#include <stm32f4xx.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* Se incluyen los Drivers Necesarios */
#include "GPIOxDriver.h"
#include "USARTxDriver.h"
#include "BasicTimer.h"
#include "AdcDriver.h"
#include "PwmDriver.h"
#include "I2CDriver.h"
#include "SysTickDriver.h"
#include "LCD_Driver.h"
#include "FPU_Driver.h"

/* Se definen Macros para la conversion ADC */
#define ADC_SIGNAL_SIZE 		2
#define NUM_ADC_CONVERSIONS		2


/* Definición de H */
GPIO_Handler_t 		handlerStateLED 					= {0};
GPIO_Handler_t 		handlerRxPIN	 					= {0};
GPIO_Handler_t 		handlerTxPIN	 					= {0};
BTIMER_Handler_t	handlerStateLedTimer				= {0};
BTIMER_Handler_t	handlerLcdRefreshTimer				= {0};
USART_Handler_t		handlerUSART1						= {0};
PWM_Handler_t 		handlerPWM 							= {0};
GPIO_Handler_t		handlerPwmPin						= {0};
GPIO_Handler_t		handlerI2CSDA						= {0};
GPIO_Handler_t		handlerI2CSCL 						= {0};
I2C_Handler_t		handlerLCD			 				= {0};
ADC_Config_t		adcVxJoystick						= {0};
ADC_Config_t		adcVyJoystick						= {0};
ADC_Config_t		joystickAxes[NUM_ADC_CONVERSIONS]	= {0};
uint16_t 			joystickAdcData[ADC_SIGNAL_SIZE]	= {0};

/* Definición de las variables */
// Variables involucradas en la conversión ADC
char				bufferAdcData[32]					= {0};
uint16_t			adcData								= 0;
bool				adcIsComplete						= false;
uint16_t			dataPosition						= 0;
uint16_t			counterAdcSampling 					= 0;
bool 				startAdc 							= false;
uint16_t 			AdcXLine 							= 0;
uint16_t			AdcYLine 							= 0;
bool 				AdcON 								= false;

// Variables involucradas en la señal PWM
uint16_t			newDuty								= 0;
bool				partyMode = false;
uint16_t 			counterParty = 0;
bool				ServoON = false;
uint8_t				LCD_segment = 0;
uint16_t			degree = 0;

// Variables involucradas con el control de la LCD
bool				stringComplete						= false;
bool				autoUpdateLcd 						= false;

// Variable para probar el funcionamiento de la FPU
float				Pi = 0;

// Variables de proposito general
char				bufferReception[32]					= {0};
char				bufferData[64]						= {0};
char				rxData 								= '\0';
uint16_t			counterReception					= 0;
uint16_t			firstParameter 						= 0;
char				cmd[32] 							= {0};
uint16_t 			counterStateLED = 0;
uint16_t 			stateLedPeriod = 250;

/* Definición de los prototipos de funciones */
void initSystem(void);
void parseCommands(char *ptrBufferReception);
void servoPartyMode(PWM_Handler_t *ptrHandlerPwm);

/* Función principal */
int main(void){
	// Se inicializa el sistema y los periféricos
	initSystem();
	stopTimer(&handlerLcdRefreshTimer); // Se detiene el Timer que controla el refresco de la LCD
	stopPWM(&handlerPWM);				// Se detiene la generación de la señal PWM
	autoUpdateLcd = false;
	/* Ciclo principal */
	while(1){
		// Las siguientes operaciones se ejecutan cuando el USART utilizado reciba información
		if (rxData != '\0'){
			// Se comienzan a acumular los caracteres recibidos en un buffer
			bufferReception[counterReception] = rxData;
			counterReception++;
			// Si se recibe el caracter @ se activa la variable de estado que indica que se recibió la información necesaria
			if (rxData == '@'){
				stringComplete = true;
				bufferReception[counterReception-1] = '\0';  // Se hace nulo la posición del caracter @
				counterReception = 0;
			}
			rxData = '\0'; // Se hace nulo la variable rxData con el fin de que sólo se entre a la condición cuando el Usart recibe datos
		}
		// Las siguientes operaciones se ejecutan cuando el buffer de recepción tiene la información completa
		if (stringComplete){
			// Se llama a la función parseCommands, la cual ejecuta el código correspondiente al comando enviado vía USART
			parseCommands(bufferReception);
			stringComplete = false;
		}
		// Las siguientes operaciones se ejecutan cuando se termina la conversión ADC (en la cual se hace conversión de dos canales y se guardan los datos en el
		// arreglo joystickAdcData
		if (adcIsComplete == true){
			stopContinuousConversion(); 						// Se detiene la conversión
			// Se calcula el Duty con el que se controlará el servomotor que depende de ambos ejes del joystick según la suma de ambos ejes
			// Además, el mínimo valor de Duty que puede ingresarse en el motor es 50, y el máximo 230, para un timer con una velocidad de 10us y 50Hz de frecuencia
			newDuty = joystickAdcData[0] + joystickAdcData[1];
			newDuty = (180*newDuty)/8190 + 50;
			// Las variables AdcXLine y AdcYLine contienen la longitud de la barra que muestra el valor de ADC en la LCD (en macropíxeles)
			AdcXLine = (8*joystickAdcData[0])/4095 + 1;
			AdcYLine = (8*joystickAdcData[1])/4095 + 1;
			// Si el control por PWM del ADC está activo, se actualiza el Duty según lo calculado anteriormente
			setPwmDuty(&handlerPWM, newDuty);
			adcIsComplete = false;
		}
		// Las siguientes operaciones se ejecutan si el auto refresco de la LCD está activado
		if (autoUpdateLcd){
			// Como el proceso de escritura en la LCD es lento respecto a los demás procesos llevados a cabo por el MCU, se hace el refresco de la misma por segmentos
			// De manera que en un ciclo del Timer que controla la velocidad de refresco, se actualicen las barras de ADC, y en otro se actualicen los valores numéricos
			if (LCD_segment){
				// En este caso se actualizan los valores numéricos
				// Se separa la actualización entre los datos de la conversión ADC y los datos del PWM que controla el motor, pues en algunos comandos solo estará
				// funcionando la conversión ADC, en otros solo estará funcionando el motor controlado con comandos, y en el caso más usual ambos pueden estar
				// trabajando en conjunto
				if (AdcON){
					// Se actualizan los datos de la conversión ADC
					sprintf(bufferData, "%u   ", (unsigned int) joystickAdcData[0]);
					LCD_writeStringXY(&handlerLCD, bufferData, 1, 16);
					sprintf(bufferData, "%u   ", (unsigned int) joystickAdcData[1]);
					LCD_writeStringXY(&handlerLCD, bufferData, 4, 16);
				}
				if (ServoON){
					degree = newDuty - 50;	// Se calcula el grado al que se encuentra el motor según su valor de Duty
					// Se actualizan los datos referentes al motor
					sprintf(bufferData, "%u  ", (unsigned int) newDuty);
					LCD_writeStringXY(&handlerLCD, bufferData, 2, 16);
					sprintf(bufferData, "%u%c  ", (unsigned int) degree, 0xDF);
					LCD_writeStringXY(&handlerLCD, bufferData, 3, 15);
				}
			} else {
				// Se actualizan las barras de ADC solo en el caso que la conversión ADC esté activada
				if (AdcON){
					// Se ubica el cursor de la LCD en el inicio de la barra para el ADCx
					LCD_cursorPosition(&handlerLCD, 2, 1);
					// Se llena la barra encendiendo to.do el macropíxel hasta el valor AdcXLine y se ponen los demas en blanco
					for (uint i = 1; i <= 9; i++){
						if (i <= AdcXLine){
							LCD_writeCharacter(&handlerLCD, 0xFF);
						} else {
							LCD_writeCharacter(&handlerLCD, ' ');
						}
					}
					// Se ubica el cursor de la LCD en el inicio de la barra para el ADCy
					LCD_cursorPosition(&handlerLCD, 4, 1);
					// Se llena la barra encendiendo to.do el macropíxel hasta el valor AdcYLine y se ponen los demas en blanco
					for (uint i = 1; i <= 9; i++){
						if (i <= AdcYLine){
							LCD_writeCharacter(&handlerLCD, 0xFF);
						} else {
							LCD_writeCharacter(&handlerLCD, ' ');
						}
					}
				}
			}
			autoUpdateLcd = false;
		}
		// La siguiente función se ejecuta si el Modo Party está activado
		if (partyMode){
			servoPartyMode(&handlerPWM);
		}
	}

}

void initSystem(void){
	/**
	 * La función initSystem se encarga de inicializar y configurar los periféricos a utilizar
	 */
	/* Configuración para el State LED */
	handlerStateLED.pGPIOx 								= GPIOA;
	handlerStateLED.GPIO_PinConfig.GPIO_PinNumber		= PIN_5;
	handlerStateLED.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_OUT;
	handlerStateLED.GPIO_PinConfig.GPIO_PinOPType		= GPIO_OTYPE_PUSHPULL;
	handlerStateLED.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;
	handlerStateLED.GPIO_PinConfig.GPIO_PinSpeed		= GPIO_OSPEED_MEDIUM;
	handlerStateLED.GPIO_PinConfig.GPIO_PinAltFunMode	= AF0;
	// Se carga la configuración del State LED
	GPIO_Config(&handlerStateLED);

	// Configuración del PIN que recibe la información por la USB (RX) */
	handlerRxPIN.pGPIOx								= GPIOA;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinNumber		= PIN_10;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinMode		= GPIO_MODE_ALTFN;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinOPType		= GPIO_OTYPE_PUSHPULL;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinSpeed		= GPIO_OSPEED_MEDIUM;
	handlerRxPIN.GPIO_PinConfig.GPIO_PinAltFunMode	= AF7;
	// Se carga la configuración del Rx PIN
	GPIO_Config(&handlerRxPIN);

	/* Configuración del PIN que envía la información por la USB (TX) */
	handlerTxPIN.pGPIOx								= GPIOA;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinNumber		= PIN_9;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinMode		= GPIO_MODE_ALTFN;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinOPType		= GPIO_OTYPE_PUSHPULL;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_NOTHING;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinSpeed		= GPIO_OSPEED_MEDIUM;
	handlerTxPIN.GPIO_PinConfig.GPIO_PinAltFunMode	= AF7;
	// Se carga la configuración del Tx PIN
	GPIO_Config(&handlerTxPIN);

	/* Configuración del USART1 */
	handlerUSART1.ptrUSARTx							= USART1;
	handlerUSART1.USART_Config.USART_mode			= USART_MODE_RXTX;
	handlerUSART1.USART_Config.USART_baudrate		= USART_BAUDRATE_115200;
	handlerUSART1.USART_Config.USART_datasize		= USART_DATASIZE_8BIT;
	handlerUSART1.USART_Config.USART_parity			= USART_PARITY_NONE;
	handlerUSART1.USART_Config.USART_stopbits		= USART_STOPBIT_1;
	handlerUSART1.USART_Config.USART_interrupt		= USART_INTERRUPT_RX;
	// Se carga la configuración del USART
	USART_Config(&handlerUSART1);

	/* Configuración del Timer 2 */
	handlerStateLedTimer.ptrTIMx						= TIM2;
	handlerStateLedTimer.timerConfig.Timer_mode			= TIMER_MODE_UP;
	handlerStateLedTimer.timerConfig.Timer_speed		= TIMER_INCR_SPEED_10us;
	handlerStateLedTimer.timerConfig.Timer_period		= 100;
	// Cargamos la configuración TIM2
	BTimer_Config(&handlerStateLedTimer);

	/* Configuración del Timer para el refresco de la LCD */
	handlerLcdRefreshTimer.ptrTIMx						= TIM4;
	handlerLcdRefreshTimer.timerConfig.Timer_mode		= TIMER_MODE_UP;
	handlerLcdRefreshTimer.timerConfig.Timer_speed		= TIMER_INCR_SPEED_1ms;
	handlerLcdRefreshTimer.timerConfig.Timer_period		= 250;
	// Cargamos la configuración TIM4
	BTimer_Config(&handlerLcdRefreshTimer);

	/* Configuracion del ADC para el eje X del Joystick */
	adcVxJoystick.channel			= ADC_CHANNEL_0;
	adcVxJoystick.dataAlignment		= ADC_ALIGNMENT_RIGHT;
	adcVxJoystick.resolution		= ADC_RESOLUTION_12_BIT;
	adcVxJoystick.samplingPeriod	= ADC_SAMPLING_PERIOD_144_CYCLES;
	joystickAxes[0] = adcVxJoystick;
	// Se carga la configuración del ADC
	adcSingle_Config(&adcVxJoystick);

	/* Configuracion del ADC para el eje Y del Joystick */
	adcVyJoystick.channel			= ADC_CHANNEL_8;
	adcVyJoystick.dataAlignment		= ADC_ALIGNMENT_RIGHT;
	adcVyJoystick.resolution		= ADC_RESOLUTION_12_BIT;
	adcVyJoystick.samplingPeriod	= ADC_SAMPLING_PERIOD_144_CYCLES;
	joystickAxes[1] = adcVyJoystick;
	// Se carga la configuración del ADC
	adcSingle_Config(&adcVyJoystick);
	// Se carga la configuración para hacer trabajar el ADC con 2 canales
	adcSQRx_Config(joystickAxes, NUM_ADC_CONVERSIONS);

	/* Configuración del Pin por el que se tomará el PWM para el servomotor */
	handlerPwmPin.pGPIOx 								= GPIOA;
	handlerPwmPin.GPIO_PinConfig.GPIO_PinNumber			= PIN_6;
	handlerPwmPin.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_ALTFN;
	handlerPwmPin.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_PUSHPULL;
	handlerPwmPin.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_HIGH;
	handlerPwmPin.GPIO_PinConfig.GPIO_PinAltFunMode		= AF2;
	// Se carga la configuración del Pin para el PWM
	GPIO_Config(&handlerPwmPin);

	/* Configuración del Timer 3 para el PWM */
	handlerPWM.ptrTIMx 					= TIM3;
	handlerPWM.pwmConfig.PWM_channel 	= CHANNEL1;
	handlerPWM.pwmConfig.PWM_prescaler	= TIMER_INCR_SPEED_10us;
	handlerPWM.pwmConfig.PWM_period		= 2000;
	handlerPWM.pwmConfig.PWM_dutyCycle	= 50;
	// Se carga la configuración del PWM
	PWM_Config(&handlerPWM);
	newDuty = 50;

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

	/* Configuración del I2C para la comunicación con la LCD */
	handlerLCD.ptrI2Cx		= I2C1;
	handlerLCD.modeI2C		= I2C_MODE_FM;
	handlerLCD.slaveAddress	= 0b0100111;
	// Se carga la configuración del I2C
	I2C_Config(&handlerLCD);

	// Se activa el SysTick
	config_SysTickMs();

	// Se activa la FPU
	FPU_Config();
}

void parseCommands(char *ptrBufferReception){
	/**
	 * La función parseCommands se encarga del control del programa por medio de comandos mediante el USART
	 */
	// Se toma la información del buffer recibido, leyendo el comando y el parámetro ingresado
	sscanf(ptrBufferReception, "%s %u ", cmd, (unsigned int*) &firstParameter);
	// Se ejecuta si el comando es "Menu"
	if (strcmp(cmd, "Menu") == 0){
		// Se imprime el Menu de comandos
		writeMsg(&handlerUSART1, "\nHelp Menu CMDS:\n");
		writeMsg(&handlerUSART1, "1)  Menu              -- Print this menu\n");
		writeMsg(&handlerUSART1, "2)  Start             -- Start Servomotor control with Joystick\n");
		writeMsg(&handlerUSART1, "3)  Stop              -- Stop Servomotor control with Joystick and ADC conversion\n");
		writeMsg(&handlerUSART1, "4)  stopServo         -- Stop Servomotor control with Joystick but ADC conversion continues\n");
		writeMsg(&handlerUSART1, "5)  stopAdc           -- Stop ADC conversion and Servomotor is controlled by commands\n");
		writeMsg(&handlerUSART1, "6)  initLcd           -- Steps to initialize Lcd\n");
		writeMsg(&handlerUSART1, "7)  testLcd           -- Writes a default message on LCD\n");
		writeMsg(&handlerUSART1, "8)  autoUpdateLcd #   -- Automatic LCD Update (# = 0, 1)\n");
		writeMsg(&handlerUSART1, "9)  servoPosition #   -- Set Servomotor Position to # degrees (# = [0, 180])\n");
		writeMsg(&handlerUSART1, "10) minServoPos       -- Set Servomotor Position to 0 degrees\n");
		writeMsg(&handlerUSART1, "11) maxServoPos       -- Set Servomotor Position to 180 degrees\n");
		writeMsg(&handlerUSART1, "12) setLedPeriod #    -- Set blinky period of State LED to # ms (# > 1)\n");
		writeMsg(&handlerUSART1, "13) startServoParty   -- Set Servomotor in Party Mode\n");
		writeMsg(&handlerUSART1, "14) getPi             -- Approximate Pi using the FPU\n");
	}
	// Se ejecuta si el comando es "Start"
	else if (strcmp(cmd, "Start") == 0){
		writeMsg(&handlerUSART1, "CMD: Start\n");
		// Se comienza el control del servomotor con el Joystick, para esto se activa el Timer que controla el PWM y se activan variables de estado cuya función
		// se describe en la función principal
		startPWM(&handlerPWM);
		startAdc = true;
		AdcON = true;
		ServoON = true;
	}
	// Se ejecuta si el comando es Stop
	else if (strcmp(cmd, "Stop") == 0){
		writeMsg(&handlerUSART1, "CMD: Stop\n");
		// Se detiene el control del servomotor con el Joystick
		startAdc = false;
		AdcON = false;
		ServoON = false;
	}
	// Se ejecuta si el comando es stopServo
	else if (strcmp(cmd, "stopServo") == 0){
		writeMsg(&handlerUSART1, "CMD: stopServo\n");
		// Se detiene el servomotor desactivando la salida PWM, y la conversión ADC sigue funcionando independientemente
		stopPWM(&handlerPWM);
		ServoON = false;
	}
	// Se ejecuta si el comando es stopAdc
	else if (strcmp(cmd, "stopAdc") == 0){
		writeMsg(&handlerUSART1, "CMD: stopAdc\n");
		// Se desactiva la conversión ADC, y el motor puede ser controlado mediante comandos
		startAdc = false;
	}
	// Se ejecuta si el comando es initLcd
	else if (strcmp(cmd, "initLcd") == 0){
		writeMsg(&handlerUSART1, "CMD: initLcd\n");
		// Se ejecuta la inicialización y sincronización de la LCD
		initLCD(&handlerLCD);
	}
	// Se ejecuta si el comando es testLcd
	else if (strcmp(cmd, "testLcd") == 0){
		writeMsg(&handlerUSART1, "CMD: testLcd\n");
		// Para comprobar el buen funcionamiento de la Lcd se imprime un texto de prueba durante 5 segundos
		LCD_writeCommand(&handlerLCD, CLEAR_DISPLAY);
		delay_ms(100);
		LCD_writeStringXY(&handlerLCD, "I'm Working =D", 3, 4);
		delay_ms(5000);
		LCD_writeCommand(&handlerLCD, CLEAR_DISPLAY);
	}
	// Se ejecuta si el comando es autoUpdateLcd
	else if (strcmp(cmd, "autoUpdateLcd") == 0){
		// Las siguientes condiciones dependen del parametro que se ingresó, siendo 1 el parametro que activa el auto refresco y 0 el que lo desactiva
		if (firstParameter){
			writeMsg(&handlerUSART1, "CMD: autoUpdateLcd\n");
			// Se imprimen los títulos de los datos que se mostrarán en la LCD
			LCD_writeStringXY(&handlerLCD, "ADCx", 1, 3);
			LCD_writeStringXY(&handlerLCD, "ADCy", 3, 3);
			LCD_writeStringXY(&handlerLCD, "|ADCx=", 1, 10);
			LCD_writeStringXY(&handlerLCD, "|Duty=", 2, 10);
			LCD_writeStringXY(&handlerLCD, "|ADCy=", 4, 10);
			LCD_writeStringXY(&handlerLCD, "|deg=", 3, 10);
			// Se activa el Timer que controla el refresco de la LCD
			startTimer(&handlerLcdRefreshTimer);
		} else {
			// Como se desactiva el auto refresco, entonces se desactiva el Timer que lo controla
			stopTimer(&handlerLcdRefreshTimer);
			autoUpdateLcd = false;
		}
	}
	// Se ejecuta si el comando es servoPosition
	else if (strcmp(cmd, "servoPosition") == 0){
		writeMsg(&handlerUSART1, "CMD: servoPosition\n");
		// Como el servomotor es de 180°, solo se acaptan parametros entre 0 y 180
		if ((firstParameter >= 0) && (firstParameter <= 180)){
			// Se activa la generación del PWM
			startPWM(&handlerPWM);
			ServoON = true;
			newDuty = firstParameter + 50;
			// Se mueve el motor a la posición indicada
			setPwmDuty(&handlerPWM, newDuty);
		}
		else {
			// En caso contrario se indica que el parametro es incorrecto
			writeMsg(&handlerUSART1, "Incorrect Parameter!!!\n");
		}
	}
	// Se ejecuta si el parámetro es minServoPos
	else if (strcmp(cmd, "minServoPos") == 0){
		writeMsg(&handlerUSART1, "CMD: minServoPos\n");
		// Lleva el motor a su mínima posición
		startPWM(&handlerPWM);
		ServoON = true;
		newDuty = 50;
		setPwmDuty(&handlerPWM, newDuty);
	}
	// Se ejecuta si el parámetro es maxServoPos
	else if (strcmp(cmd, "maxServoPos") == 0){
		writeMsg(&handlerUSART1, "CMD: maxServoPos\n");
		// Lleva el motor a su posición máxima
		startPWM(&handlerPWM);
		ServoON = true;
		newDuty = 230;
		setPwmDuty(&handlerPWM, newDuty);
	}
	// Se ejecuta si el comando es setLedPeriod
	else if (strcmp(cmd, "setLedPeriod") == 0){
		writeMsg(&handlerUSART1, "CMD: setLedPeriod\n");
		// Se cambia el periodo del blinky del stateLED, siempre que el parámetro ingresado sea mayor que 1
		if (firstParameter > 1){
			stateLedPeriod = firstParameter;
		} else {
			writeMsg(&handlerUSART1, "Incorrect Parameter!!!\n");
		}
	}
	// Se ejecuta si el comando es startServoParty
	else if (strcmp(cmd, "startServoParty") == 0){
		writeMsg(&handlerUSART1, "CMD: startServoParty\n");
		// Se activa el PWM y una variable de estado que activa la realización de un patrón musical en el movimiento del motor
		startPWM(&handlerPWM);
		partyMode = true;
	}
	// Se ejecuta si el comando es getPi
	else if (strcmp(cmd, "getPi") == 0){
		writeMsg(&handlerUSART1, "CMD: getPi\n");
		// Se comprueba el funcionamiento de la unidad de punto flotante mediante la aproximación de Pi por series
		Pi = 0;
		for (uint8_t j = 2; j < 250; j++){
			if ((j%2) == 0){
				Pi += 1.0/(2.0*((float)j - 2.0) + 1.0);
			} else {
				Pi += -1.0/(2.0*((float)j - 2.0) + 1.0);
			}
		}
		Pi = 4*Pi;
		// Se imprime por consola el valor de Pi aproximado
		sprintf(bufferData, "The approximation of Pi made via the FPU is %f\n", Pi);
		writeMsg(&handlerUSART1, bufferData);
	}
	else {
		// En caso de que el comando no sea ninguno de los anteriores, se indica por consola que es incorrecto
		writeMsg(&handlerUSART1, "Incorrect Command!!!\n");
	}
}

void servoPartyMode(PWM_Handler_t *ptrHandlerPwm){
	/**
	 * La función servoPartuMode genera un patrón musical de movimiento en el motor, el patrón se repite 3 veces
	 */
	for (uint8_t i = 1; i <= 3; i++){
		setPwmDuty(ptrHandlerPwm, 90);
		delay_ms(2000);
		setPwmDuty(ptrHandlerPwm, 190);
		delay_ms(800);
		setPwmDuty(ptrHandlerPwm, 140);
		delay_ms(700);
		setPwmDuty(ptrHandlerPwm, 180);
		delay_ms(350);
		setPwmDuty(ptrHandlerPwm, 140);
		delay_ms(350);
		setPwmDuty(ptrHandlerPwm, 180);
		delay_ms(750);
		setPwmDuty(ptrHandlerPwm, 220);
		delay_ms(350);
		setPwmDuty(ptrHandlerPwm, 180);
		delay_ms(350);
		setPwmDuty(ptrHandlerPwm, 220);
		delay_ms(750);
		setPwmDuty(ptrHandlerPwm, 164);
		delay_ms(350);
		setPwmDuty(ptrHandlerPwm, 108);
		delay_ms(350);
		setPwmDuty(ptrHandlerPwm, 164);
		delay_ms(350);
		setPwmDuty(ptrHandlerPwm, 125);
		delay_ms(350);
		setPwmDuty(ptrHandlerPwm, 90);
		delay_ms(2000);
	}
	partyMode = false;
}

/* Implementacion del Callback para el timer2 */
void BTimer2_Callback(void){
	// Se incrementan las variables que hacen el conteo en ms para el stateLed y para el sampling time del ADC
	counterStateLED++;
	counterAdcSampling++;
	// Si el conteo llega al valor de la variable stateLedPeriod se hace el blinky del stateLED
	if (counterStateLED >= stateLedPeriod){
		handlerStateLED.pGPIOx->ODR ^= GPIO_ODR_OD5;
		counterStateLED = 0;
	}
	// Se hace una conversión de los ejes del Joystick cada 70ms, solo si la conversión está activada
	if (counterAdcSampling >= 70 && startAdc){
		startContinuousConversion();
		counterAdcSampling = 0;
	}
}

/* Implementacion del Callback para el timer4 */
void BTimer4_Callback(void){
	// Se activa la variable de estado
	autoUpdateLcd = true;
	// Se intercalan los segmentos de la LCD que se van a refrescar
	LCD_segment = !LCD_segment;
}

/* Implementacion del Callback para el Usart2 */
void Usart1_RX_Callback(void){
	rxData = getRxData();
}

void Usart1_TX_Callback(void){
	__NOP();
}

void adcComplete_Callback(void){
	// Se guardan los datos de la conversión de el arreglo joystickAdcData
	joystickAdcData[dataPosition] = getADC();
	dataPosition++;
	// Si el arreglo se llena, es porque se terminó la conversión de todos los canales, entonces se activa la variable de estado que indica esto
	if (dataPosition >= ADC_SIGNAL_SIZE){
		dataPosition = 0;
		adcIsComplete = true;
	}
}

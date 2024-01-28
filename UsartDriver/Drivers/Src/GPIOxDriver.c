/*
 * GPIOxDriver.c
 *
 *  Created on: 2/04/2022
 *      Author: ezque
 */

/*
 *      Este archivo es la parte del programa donde escribimos adecuadamente el control para que sea
 *       lo más genérico posible, de forma que independiente del puerto GPIO y el PIN seleccionados,
 *       el programa se ejecute y configure correctamente
 */

#include "GPIOxDriver.h"



/** Para cualquier periférico hay varios pasos que siempre se deben seguir en un orden estricto para poder
 *  que el sistema permita configurar el periférico X.Lo primero y más importante es activar la señal del
 *  reloj principal hacia ese elemento específico relacionado con el periférico RCC, a esto llamaremos
 *  simplemente "activar el periférico o activar la señal de reloj del periférico"
 * */

void GPIO_Config (GPIO_Handler_t *pGPIOHandler){
	// variable para hacer to do paso a paso
	uint32_t auxConfig = 0;
	uint32_t auxPosition = 0;
	 // 1) Activar el periférico
	// Verificamos para GPIDA
	if (pGPIOHandler->pGPIOx == GPIOA){
		// Escribimos 1 (SET) en la posicion correspondiente al GPIOA
		RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN);
	}
	// Verificamos para GPIOB
	else if(pGPIOHandler->pGPIOx== GPIOB){
		//Escribimos 1 (SET) en la posicion correspondiente al GPIOB
		RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOBEN);
	}
	//Verificamos para GPIOC
	else if (pGPIOHandler->pGPIOx== GPIOC){
		RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOCEN);
	}
	//Verificamos para GPIOD
	else if (pGPIOHandler->pGPIOx== GPIOD){
			RCC->AHB1ENR |= (RCC_AHB1ENR_GPIODEN);
	}
	//Verificamos para GPIOE
	else if (pGPIOHandler->pGPIOx== GPIOE){
			RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOEEN);
		}
	//Verificamos para GPIOH
	else if (pGPIOHandler->pGPIOx== GPIOH){
			RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOHEN);
		}
	//Después de activado, podemos comenzar a configurar.

	// 2) Configurando el resgistro GPIOx_MODER
	//Acá estamos leyendo la config, moviendo "PinNumber" veces hacia la izquierda ese valor (shift left)
	// y to do eso lo cargamos en la variables auxConfig
	auxConfig = (pGPIOHandler->GPIO_PinConfig.GPIO_PinMode << 2 * pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);

	//Antes de cargar el nuevo valor, limpiamos los bits específicos de ese registro (0b00)
	// para lo cual aplicamos una máscara y una operación bitwise AND
	pGPIOHandler->pGPIOx->MODER &= ~(0b11 << 2 * pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);

	//Cargamos a auxConfig en el registro MODER
	pGPIOHandler->pGPIOx->MODER |= auxConfig;

	//3) Configurando el registro GPIOx_OTYPER
	//De nuevo, leemos y movemos el valor un numero "PinNumber" de veces
	auxConfig = (pGPIOHandler->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);

	// Limpiamos antes de cargar
	pGPIOHandler->pGPIOx->OTYPER &= ~(SET << pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);
	// cargamos el resultado sobre el registro adecuado
	pGPIOHandler->pGPIOx->OTYPER |= auxConfig;

	 //4) Configurando ahora la velocidad
	auxConfig = (pGPIOHandler->GPIO_PinConfig.GPIO_PinSpeed << 2*pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);

	//Limpiando la posicion antes de cargar la nueva configuracion
	pGPIOHandler->pGPIOx->OSPEEDR &= ~(0b11 << 2 * pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);

	// cargamos el resultado sobre el registro adecuado
	pGPIOHandler->pGPIOx->OSPEEDR |= auxConfig;

	//5) Configurando si se desea pull-up,pull-down o flotante.
	auxConfig = (pGPIOHandler->GPIO_PinConfig.GPIO_PinPuPdControl << 2 * pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);

	// Limpiando la posicion antes de cargar la nueva configuracion
	pGPIOHandler->pGPIOx->PUPDR &= ~(0b11 << 2 * pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);

	// cargamos el resultado sobre el registro adecuado
	pGPIOHandler->pGPIOx->PUPDR |= auxConfig;

	// Esta es la parte para la configuracion de las funciones alternativas... se vera luego
	if(pGPIOHandler->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN){

		// Seleccionamos primero si se debe utilizar el registro bajo (AFRL) o el alto (AFRH)
		if(pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber < 8){
			//Estamos en el registro AFRL, que controla los pines del PIN_0 al PIN_7
			auxPosition = 4 * pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber;

			//limpiamos primero la posicion del registro que deseamos escribir a continuacion
			pGPIOHandler->pGPIOx->AFR[0] &= ~(0b1111 <<auxPosition);

			//Y escribimos el valor configurado en la posicion seleccionada
			pGPIOHandler->pGPIOx->AFR[0] |= (pGPIOHandler->GPIO_PinConfig.GPIO_PinAltFunMode << auxPosition);
		}
		else {
		// Estamos en el registro AFRH, que controla los pines del PIN_/ al PIN_15
			auxPosition = 4 *(pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber - 8);

		//Limpiamos primero la posicion del registro que deseamos escribir a continuacion
			pGPIOHandler->pGPIOx->AFR[1] &= ~(0b1111 << auxPosition);

		// Y escribimos el valor configurado en la posicion seleccionada
			pGPIOHandler->pGPIOx->AFR[1] |= (pGPIOHandler->GPIO_PinConfig.GPIO_PinAltFunMode << auxPosition);
		}
	}

} // Fin del GPIO_config


/**
 * Función utilizada para cambiar de estado el pin entregado en el handler, asignando el valor
 * entregado en la variable newState
 */

void GPIO_WritePin(GPIO_Handler_t *pPinHandler, uint8_t newState){
	//Limpiamos la posición que deseamos
	pPinHandler->pGPIOx->ODR &= ~(SET << pPinHandler->GPIO_PinConfig.GPIO_PinNumber);

	if (newState == SET){
		// Trabajando con la parte baja del registro
		pPinHandler->pGPIOx->BSRR |= (SET << pPinHandler->GPIO_PinConfig.GPIO_PinNumber);
	}
	else{
		// Trabajando con la parte alta del registro
		pPinHandler->pGPIOx->BSRR |= (SET << (pPinHandler->GPIO_PinConfig.GPIO_PinNumber + 16));
	}
}

/**
 * Función para leer el estado de un PIN especifico
 */
uint32_t GPIO_ReadPin(GPIO_Handler_t *pPinHandler){
	// Creamos una variable auxiliar la cuel luego retornaremos
	uint32_t pinValue = 0;

	//Cargamos el valor del registro IDR, desplazando a la derecha tantas veces como la ubicación del PIN específico
	pinValue = (pPinHandler->pGPIOx->IDR >> pPinHandler->GPIO_PinConfig.GPIO_PinNumber);
	pinValue &= 0b1;
	return pinValue;
}

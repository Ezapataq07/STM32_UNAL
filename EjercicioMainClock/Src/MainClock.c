/*
 * MainClock.c
 *
 *  Created on: Mar 24, 2022
 *      Author: ezque
 */


/*
 * 1. BASE:
 * 		AHB1: 0x40020000
 * 		RCC: 0x40023800
 * 		GPIOE: 0x40021000
 *
 * 2. RCC:
 * 		CR: 0x00
 * 		CFGR: 0x08
 *
 * 3.
 *
 */


#include <stdint.h>
#include <stdbool.h>
 /* 1) Posiciones de memoria base:
  * 	- AHB1: 0x40020000
  * 	- RCC: 0x40023800
  * 	- GPIOE: 0x40021000
  */
#define AHB1_BASE_ADDR  0x40020000UL
#define RCC_BASE_ADDR   (AHB1_BASE_ADDR + 0x3800UL)
#define GPIOA_BASE_ADDR (AHB1_BASE_ADDR + 0x0000UL)

  /* 2) Offset RCC
  * 	- RCC--> CR: 0x00
  * 	- RCC --> CFGR: 0x08
  */
#define RCC_CR_OFFSET   0x0UL
#define RCC_CFGR_OFFSET 0x08UL
  /* 3) Offsets GPIOx:
  * 	- RCC --> AHB1ENR
  *
  *
  */
#define RCC_AHB1ENR_OFFSET   0x30UL

#define GPIOx_MODER_OFFSET   0x00UL		// Offset for register "pin mode"
#define GPIOx_OTYPER_OFFSET  0x04UL		// Offset for register "Pin output type"
#define GPIOx_OSPEEDR_OFFSET 0x08UL		// Offset for register "Output speed"
#define GPIOx_AFRH_OFFSET    0x24UL		// Offset for register "Alternate function"

/* Función principal del programa. Es acá dodne se ejecuta to do */

int main (void){
	/* 4. Crear variables_ptr para cada uno de estos registros de periféricos y hacer un type-cast de cada
	 * una de las posiciones definidas en el punto 1, de forma que cada ptr quede "apuntando a la posición
	 * de memoria adecuada
	 */
	uint32_t *pRCC_CR_Reg		= (uint32_t*) (RCC_BASE_ADDR + RCC_CR_OFFSET);				// Apuntando a la posición RCC_CR
	uint32_t *pRCC_CFGR_Reg		= (uint32_t*) (RCC_BASE_ADDR + RCC_CFGR_OFFSET);			// Apuntando a la posición RCC_CFGR
	uint32_t *pRCC_AHB1ENR_Reg	= (uint32_t*) (RCC_BASE_ADDR + RCC_AHB1ENR_OFFSET);			// Apuntando a la posición RCC_AHB1ENR
	uint32_t *pGPIOA_MODER_Reg	= (uint32_t*) (GPIOA_BASE_ADDR + GPIOx_MODER_OFFSET);		// Apuntando a la posición GPIA_MODER
	uint32_t *GPIOA_OTYPER_Reg	= (uint32_t*) (GPIOA_BASE_ADDR + GPIOx_OTYPER_OFFSET);		// Apuntando a la posición GPIOx_OTYPER
	uint32_t *GPIOx_OSPEEDR_Reg	= (uint32_t*) (GPIOA_BASE_ADDR + GPIOx_OSPEEDR_OFFSET);		// Apuntando a la posición GPIOx_OSPEEDR
	uint32_t *GPIOA_AFRH_Reg	= (uint32_t*) (GPIOA_BASE_ADDR + GPIOx_AFRH_OFFSET);		// Apuntando a la posición GPIOA_AFRH

	/* 5. Configurar qué reloj se desea "observar" (HSI en la salida MCO1) */
	*pRCC_CR_Reg		|= (0x1UL << 0);	// Encendiendo el HSI (por defecto debe estar encendido)
	*pRCC_CFGR_Reg		|= (0x0UL << 0);	// System Clock Switch, seleccionando el HSI como reloj principal
	*pRCC_CFGR_Reg		&= ~(0x3UL << 21);	// Reiniciamos a cero estos bits -> MC01
	*pRCC_CFGR_Reg		|= (0x0UL << 21);	// Cargamos el valor deseado en el MC01
	*pRCC_CFGR_Reg		&= ~(0b111 << 24);	// Configuramos el preescaler con relación 1:1
	*pRCC_CFGR_Reg		|= (0b100 << 24);	// Configuramos el preescaler coon relación 1:2

	/* 6. Configurar el PINx que posee la salida MC01 como una de sus funciones Alternativas. */
	*pRCC_AHB1ENR_Reg	|= (0x1UL << 0);	//Activando la señal de reloj para el periférico GPIOA
	*pGPIOA_MODER_Reg	|= (0b10 << 16);	// Cargamos el valor 0b10 en los bits 16 y 17 -> Función alternativa
	*GPIOA_OTYPER_Reg	&= ~(0x1UL << 8);	// Cargamos el valor 0 al bit 8 (salida tipo Push-Pull)
	*GPIOx_OSPEEDR_Reg	|= (0b10 << 16);	// Cargamos el valor 0b10 en los bits 16 y 17 (Fast speed)
	*GPIOA_AFRH_Reg		&= ~(0b1111 << 0);	// Cargamos el valor 0b0000 en los pimeros 4 bits.

	/* 7. Agregar un ciclo infinito creado con un ciclo for() */
	for( ; ; ){

	}

	return 26;
}

/*
 * SysTickDriver.c
 *
 *  Created on: May 12, 2022
 *      Author: ezapataq
 *
 *
 *  Este driver controla el Timer que trae por defecto to.do procesador de ARM Cortx Mx, el cual hace parte del sistema independiente de la empresa
 *  fabricante del MCU.
 *
 *  PAra encontrar cual es su registro de configuración, debemos utilizar el manual genérico del procesador Cortex-M4, ya que es allí donde se encuentra
 *  la doumentación para este periférico.
 *
 *  En el archivo core_cm4.h, la estructura que define el periférico se llama SysTick_Type
 */

#include "SysTickDriver.h"

#define SYSTICK_LOAD_VALUE		16000  // Número de ciclos en 1us

uint64_t ticks;
uint32_t sysTicksStart = 0;
uint32_t sysTicksEnd   = 0;

/**/
void config_SysTickMs(void){
	// Reiniciamos el valor de la variable que cuenta tiempo
	ticks = 0;

	// Cargando el valor del limite de icrementos que representan 1ms
	SysTick->LOAD = SYSTICK_LOAD_VALUE;

	// Limpiamos el valor actual del SysTick
	SysTick->VAL = 0;

	// Configuramos el reloj interno como el reloj para el Timer
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;

	// Desactivamos la interrupciones globales
	__disable_irq();

	// Activamos la interrupción debida al conteo a cero del SysTick
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

	// Matriculamos la interrupción en el NVIC
	__NVIC_EnableIRQ(SysTick_IRQn);

	// Activamos el Timer
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	// Activamos las interrupciones globales
	__enable_irq();
}

uint64_t getTicksMs(void){
	return ticks;
}

/**/
void SysTick_Handler(void){
	//Verificamos que la interrupción se lanzó
	if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk){
		//Limpiamos la bandera
		SysTick->CTRL &= ~SysTick_CTRL_COUNTFLAG_Msk;
		//Incrementamos en 1 el contador
		ticks++;
	}
}

void delay_ms(uint32_t time){
	sysTicksStart = getTicksMs();
	sysTicksEnd = getTicksMs();
	while ((sysTicksEnd - sysTicksStart) < time){
		sysTicksEnd = getTicksMs();
	}
}



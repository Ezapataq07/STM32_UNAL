/*
 * BasicTimer.c
 *
 *  Created on: 21/04/2022
 *      Author: ezapataq
 */

#include "BasicTimer.h"

/* Variable que guarda la referencia del periférico que se esta utilizando*/
TIM_TypeDef	*ptrTimerUsed;

/*
 * Función que configura un Timer básico para que genere interrupcines de forma periódica
 */

void BTimer_Config(BTIMER_Handler_t *ptrTimerConfig){

	// Guardamos una referencia al periferico que estamos utilizando...
	ptrTimerUsed = ptrTimerConfig->ptrTIMx;

	/* 0. Desactivamos las interrupciones globales */
	__disable_irq();

	/* 1. Activar la señal de reloj para el periferico especifico */
	if (ptrTimerConfig->ptrTIMx == TIM2){
		// Activamos la señal del TIM2
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	}
	else if (ptrTimerConfig->ptrTIMx == TIM3){
		// Activamos la señal del TIM3
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	}

	/* 2. Configuramos el modo del timer (UP or DOWN) */
	if (ptrTimerConfig->timerConfig.Timer_mode == TIMER_MODE_UP){
		// Configuramos el timer en modo UP
		ptrTimerConfig->ptrTIMx->CR1 &= ~TIM_CR1_DIR;

		// Ponemos el contador (CNT) el valor del periodo
		ptrTimerConfig->ptrTIMx->CNT = 0;
	} else{
		// Configuramos el timer en modo DOWN
		ptrTimerConfig->ptrTIMx->CR1 |= TIM_CR1_DIR;

		// Ponemos el contador (CNT) el valor del periodo
		ptrTimerConfig->ptrTIMx->CNT = ptrTimerConfig->timerConfig.Timer_period -1;
	}

	/* 3. Configuración del Prescaler */
	ptrTimerConfig->ptrTIMx->PSC = ptrTimerConfig->timerConfig.Timer_speed -1;

	/* 4. Configuramos el periodo de las interrupciones */
	ptrTimerConfig->ptrTIMx->ARR = ptrTimerConfig->timerConfig.Timer_period -1;

	/* 5. Activamos al timer para que comience a incrementarse */
	ptrTimerConfig->ptrTIMx->CR1 |= TIM_CR1_CEN;

	/* 6. Activamos la interrupcion debida a un "update event" */
	ptrTimerConfig->ptrTIMx->DIER |= TIM_DIER_UIE;

	/* 7. Activamos la señal de la interrupcion en el NVIC */
	if (ptrTimerConfig->ptrTIMx == TIM2){
		// Activamos la IRQ del TIM2
		__NVIC_EnableIRQ(TIM2_IRQn);
		__NVIC_SetPriority(TIM2_IRQn, 3);
	}
	else if (ptrTimerConfig->ptrTIMx == TIM3){
		// Activamos la IRQ del TIM3
		__NVIC_EnableIRQ(TIM3_IRQn);
		__NVIC_SetPriority(TIM3_IRQn, 3);
	}


	/* 8. Activamos las interrupciones globales */
	__enable_irq();
}

__attribute__((weak)) void BTimer2_Callback(void){
	 __NOP();
}

__attribute__((weak)) void BTimer3_Callback(void){
	 __NOP();
}

/* Rutina de artencion a la interrupcion del TIM2 */
void TIM2_IRQHandler(void){
	TIM2->SR &= ~TIM_SR_UIF;
	BTimer2_Callback();

}

/* Rutina de artencion a la interrupcion del TIM3 */
void TIM3_IRQHandler(void){
	TIM3->SR &= ~TIM_SR_UIF;
	BTimer3_Callback();
}

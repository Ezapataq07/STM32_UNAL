/*
 * BasicTimer.c
 *
 *  Created on: 21/04/2022
 *      Author: ezapataq
 */

#include "BasicTimer.h"

/*
 * Función que configura un Timer básico para que genere interrupcines de forma periódica
 */

void BTimer_Config(BTIMER_Handler_t *ptrTimerConfig){
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
	}
	else if (ptrTimerConfig->ptrTIMx == TIM3){
		// Activamos la IRQ del TIM3
		__NVIC_EnableIRQ(TIM3_IRQn);
	}


	/* 8. Activamos las interrupciones globales */
	__enable_irq();
}

 __attribute__((weak)) void BTimer_Callback(void){
	 __NOP();
 }

/* Rutina de artencion a la interrupcion del TIM2 */
void TIM2_IRQHandler(void){
	TIM2->SR &= ~TIM_SR_UIF;
	BTimer_Callback();
}

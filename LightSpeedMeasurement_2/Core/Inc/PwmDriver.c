/*
 * PwmDriver.c
 *
 *  Created on: 19/05/2022
 *      Author: ezapataq
 */

#include "BasicTimer.h"
#include "PwmDriver.h"

void PWM_Config(PWM_Handler_t	*pPwmConfig){


	/* 1. Activar la señal de reloj para el periferico especifico */
		if (pPwmConfig->ptrTIMx == TIM2){
			// Activamos la señal del TIM2
			RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
		}
		else if (pPwmConfig->ptrTIMx == TIM3){
			// Activamos la señal del TIM3
			RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
		}
		else if (pPwmConfig->ptrTIMx == TIM4){
			// Activamos la señal del TIM4
			RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
		}

	/* Counter used as upcounter */
	pPwmConfig->ptrTIMx->CR1 &= ~TIM_CR1_DIR;

	/* Se reincia el contador a 0 */
	pPwmConfig->ptrTIMx->CNT = 0;

	/* Se configura el prescaler */
	pPwmConfig->ptrTIMx->PSC = pPwmConfig->pwmConfig.PWM_prescaler-1;

	/* Se configura el periodo en el ARR */
	pPwmConfig->ptrTIMx->ARR = pPwmConfig->pwmConfig.PWM_period-1;


	/* Se activa el contador */
	pPwmConfig->ptrTIMx->CR1 |= TIM_CR1_CEN;


	switch(pPwmConfig->pwmConfig.PWM_channel){
	case CHANNEL1:
	{
		/* Se configura el dutyCycle */
		pPwmConfig->ptrTIMx->CCR1 = pPwmConfig->pwmConfig.PWM_dutyCycle;
		/* Se configura el canal como OUTPUT */
		pPwmConfig->ptrTIMx->CCMR1 &= ~TIM_CCMR1_CC1S;
		/* Se activa el Preload */
		pPwmConfig->ptrTIMx->CCMR1 |= TIM_CCMR1_OC1PE;
		/* Se configura el modo Compare en PWM mode 1 */
		pPwmConfig->ptrTIMx->CCMR1 |= (0b110 << TIM_CCMR1_OC1M_Pos);
		/* Se activa el canal */
		pPwmConfig->ptrTIMx->CCER |= TIM_CCER_CC1E;
		break;
	}
	case CHANNEL2:
	{
		/* Se configura el dutyCycle */
		pPwmConfig->ptrTIMx->CCR2 = pPwmConfig->pwmConfig.PWM_dutyCycle;
		/* Se configura el canal como OUTPUT */
		pPwmConfig->ptrTIMx->CCMR1 &= ~TIM_CCMR1_CC2S;
		/* Se activa el Preload */
		pPwmConfig->ptrTIMx->CCMR1 |= TIM_CCMR1_OC2PE;
		/* Se configura el modo Compare en PWM mode 1 */
		pPwmConfig->ptrTIMx->CCMR1 |= (0b110 << TIM_CCMR1_OC2M_Pos);
		/* Se activa el canal */
		pPwmConfig->ptrTIMx->CCER |= TIM_CCER_CC2E;
		break;
	}
	case CHANNEL3:
	{
		/* Se configura el dutyCycle */
		pPwmConfig->ptrTIMx->CCR3 = pPwmConfig->pwmConfig.PWM_dutyCycle;
		/* Se configura el canal como OUTPUT */
		pPwmConfig->ptrTIMx->CCMR2 &= ~TIM_CCMR2_CC3S;
		/* Se activa el Preload */
		pPwmConfig->ptrTIMx->CCMR2 |= TIM_CCMR2_OC3PE;
		/* Se configura el modo Compare en PWM mode 1 */
		pPwmConfig->ptrTIMx->CCMR2 |= (0b110 << TIM_CCMR2_OC3M_Pos);
		/* Se activa el canal */
		pPwmConfig->ptrTIMx->CCER |= TIM_CCER_CC3E;
		break;
	}
	case CHANNEL4:
	{
		/* Se configura el dutyCycle */
		pPwmConfig->ptrTIMx->CCR4 = pPwmConfig->pwmConfig.PWM_dutyCycle;
		/* Se configura el canal como OUTPUT */
		pPwmConfig->ptrTIMx->CCMR2 &= ~TIM_CCMR2_CC4S;
		/* Se activa el Preload */
		pPwmConfig->ptrTIMx->CCMR2 |= TIM_CCMR2_OC4PE;
		/* Se configura el modo Compare en PWM mode 1 */
		pPwmConfig->ptrTIMx->CCMR2 |= (0b110 << TIM_CCMR2_OC4M_Pos);
		/* Se activa el canal */
		pPwmConfig->ptrTIMx->CCER |= TIM_CCER_CC4E;
		break;
	}
	default:
	{
		break;
	}
	}

}

void setPwmDuty(PWM_Handler_t *pPwmConfig, uint16_t newDuty){
	pPwmConfig->pwmConfig.PWM_dutyCycle = newDuty;
	switch(pPwmConfig->pwmConfig.PWM_channel){
		case CHANNEL1:
		{
			/* Se configura el dutyCycle */
			pPwmConfig->ptrTIMx->CCR1 = pPwmConfig->pwmConfig.PWM_dutyCycle;
			break;
		}
		case CHANNEL2:
		{
			/* Se configura el dutyCycle */
			pPwmConfig->ptrTIMx->CCR2 = pPwmConfig->pwmConfig.PWM_dutyCycle;
			break;
		}
		case CHANNEL3:
		{
			/* Se configura el dutyCycle */
			pPwmConfig->ptrTIMx->CCR3 = pPwmConfig->pwmConfig.PWM_dutyCycle;
			break;
		}
		case CHANNEL4:
		{
			/* Se configura el dutyCycle */
			pPwmConfig->ptrTIMx->CCR4 = pPwmConfig->pwmConfig.PWM_dutyCycle;
			break;
		}
		default:
		{
			break;
		}
	}
}

void stopPWM(PWM_Handler_t *ptrHandlerPWM){
	ptrHandlerPWM->ptrTIMx->CR1 &= ~TIM_CR1_CEN;
}

void startPWM(PWM_Handler_t *ptrHandlerPWM){
	ptrHandlerPWM->ptrTIMx->CR1 |= TIM_CR1_CEN;
}

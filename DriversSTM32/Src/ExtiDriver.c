
/*
 * ExtiDriver->c
 *
 *  Created on: May 12, 2022
 *      Author: ezapataq
 */

#include "ExtiDriver.h"
#include "GPIOxDriver.h"


GPIO_Handler_t 	handlerExtiPIN = {0};

void exti_Config(EXTI_Config_t	*extiConfig){

	/* Se activa la señal de reloj para SYSCFG*/
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	/* Configuramos el PINX como entrada digital */
	configExtiPin(extiConfig);


	/* Se conecta la entrada del PIN configurado al EXTI correspondiente */
	if (extiConfig->EXTIx <= EXTI3){
		SYSCFG->EXTICR[0] |= (extiConfig->pinPort << (extiConfig->EXTIx)*4);
	}
	else if ((extiConfig->EXTIx >= EXTI4 && extiConfig->EXTIx <= EXTI7)){
		SYSCFG->EXTICR[1] |= (extiConfig->pinPort << (extiConfig->EXTIx-4)*4);
	}
	else if (extiConfig->EXTIx >= EXTI8 && extiConfig->EXTIx <= EXTI11){
		SYSCFG->EXTICR[2] |= (extiConfig->pinPort << (extiConfig->EXTIx-8)*4);
	}
	else if (extiConfig->EXTIx >= EXTI12 && extiConfig->EXTIx <= EXTI15){
		SYSCFG->EXTICR[3] |= (extiConfig->pinPort << (extiConfig->EXTIx-12)*4);
	}

	/* Configurar el tipo de flanco según el PIN utilizado*/
	switch(extiConfig->triggerMode){
	case RISING_TRIGGER:
	{
		EXTI->RTSR |= (0b1 << extiConfig->EXTIx);
		break;
	}
	case FALLING_TRIGGER:
	{
		EXTI->FTSR |= (0b1 << extiConfig->EXTIx);
		break;
	}
	case FALLING_RISING_TRIGGER:
	{
		EXTI->RTSR |= (0b1 << extiConfig->EXTIx);
		EXTI->FTSR |= (0b1 << extiConfig->EXTIx);
		break;
	}
	default:
	{
		break;
	}
	}

	__disable_irq();
	/* Se activa la interrupción para el EXTI configurado */
	EXTI->IMR |= (0b1 << extiConfig->EXTIx);

	/* Se matricula la interrupción correspondiente en el NVIC */

	if (extiConfig->EXTIx == EXTI0){
		__NVIC_EnableIRQ(EXTI0_IRQn);
	}
	else if (extiConfig->EXTIx == EXTI1){
		__NVIC_EnableIRQ(EXTI1_IRQn);
	}
	else if (extiConfig->EXTIx == EXTI2){
		__NVIC_EnableIRQ(EXTI2_IRQn);
	}
	else if (extiConfig->EXTIx == EXTI3){
		__NVIC_EnableIRQ(EXTI3_IRQn);
	}
	else if (extiConfig->EXTIx == EXTI4){
		__NVIC_EnableIRQ(EXTI4_IRQn);
	}
	else if (extiConfig->EXTIx >= EXTI5 && extiConfig->EXTIx <= EXTI9){
		__NVIC_EnableIRQ(EXTI9_5_IRQn);
	}
	else if (extiConfig->EXTIx >= EXTI10 && extiConfig->EXTIx <= EXTI15){
		__NVIC_EnableIRQ(EXTI15_10_IRQn);
	}


	/* Se reactican las interrupciones globales */
	__enable_irq();


}

void EXTI0_IRQHandler(void){
	if (EXTI->PR & EXTI_PR_PR0){
		EXTI->PR |= EXTI_PR_PR0;
		Exti0_Callback();
	}
}

void EXTI1_IRQHandler(void){
	if (EXTI->PR & EXTI_PR_PR1){
		EXTI->PR |= EXTI_PR_PR1;
		Exti1_Callback();
	}
}

void EXTI2_IRQHandler(void){
	if (EXTI->PR & EXTI_PR_PR2){
		EXTI->PR |= EXTI_PR_PR2;
		Exti2_Callback();
	}
}

void EXTI3_IRQHandler(void){
	if (EXTI->PR & EXTI_PR_PR3){
		EXTI->PR |= EXTI_PR_PR3;
		Exti3_Callback();
	}
}

void EXTI4_IRQHandler(void){
	if (EXTI->PR & EXTI_PR_PR4){
		EXTI->PR |= EXTI_PR_PR4;
		Exti4_Callback();
	}
}

void EXTI9_5_IRQHandler(void){
	if (EXTI->PR & EXTI_PR_PR5){
		EXTI->PR |= EXTI_PR_PR5;
		Exti5_Callback();
	}
	else if (EXTI->PR & EXTI_PR_PR6){
		EXTI->PR |= EXTI_PR_PR6;
		Exti6_Callback();
	}
	else if (EXTI->PR & EXTI_PR_PR7){
		EXTI->PR |= EXTI_PR_PR7;
		Exti7_Callback();
	}
	else if (EXTI->PR & EXTI_PR_PR8){
		EXTI->PR |= EXTI_PR_PR8;
		Exti8_Callback();
	}
	else if (EXTI->PR & EXTI_PR_PR9){
		EXTI->PR |= EXTI_PR_PR9;
		Exti9_Callback();
	}
}

void EXTI15_10_IRQHandler(void){
	if (EXTI->PR & EXTI_PR_PR10){
		EXTI->PR |= EXTI_PR_PR10;
		Exti10_Callback();
	}
	else if (EXTI->PR & EXTI_PR_PR11){
		EXTI->PR |= EXTI_PR_PR11;
		Exti11_Callback();
	}
	else if (EXTI->PR & EXTI_PR_PR12){
		EXTI->PR |= EXTI_PR_PR12;
		Exti12_Callback();
	}
	else if (EXTI->PR & EXTI_PR_PR13){
		EXTI->PR |= EXTI_PR_PR13;
		Exti13_Callback();
	}
	else if (EXTI->PR & EXTI_PR_PR14){
		EXTI->PR |= EXTI_PR_PR14;
		Exti14_Callback();
	}
	else if (EXTI->PR & EXTI_PR_PR15){
		EXTI->PR |= EXTI_PR_PR15;
		Exti15_Callback();
	}
}


__attribute__ ((weak)) void Exti0_Callback(void){
	__NOP();
}
__attribute__ ((weak)) void Exti1_Callback(void){
	__NOP();
}
__attribute__ ((weak)) void Exti2_Callback(void){
	__NOP();
}
__attribute__ ((weak)) void Exti3_Callback(void){
	__NOP();
}
__attribute__ ((weak)) void Exti4_Callback(void){
	__NOP();
}
__attribute__ ((weak)) void Exti5_Callback(void){
	__NOP();
}
__attribute__ ((weak)) void Exti6_Callback(void){
	__NOP();
}
__attribute__ ((weak)) void Exti7_Callback(void){
	__NOP();
}

__attribute__ ((weak)) void Exti8_Callback(void){
	__NOP();
}
__attribute__ ((weak)) void Exti9_Callback(void){
	__NOP();
}
__attribute__ ((weak)) void Exti10_Callback(void){
	__NOP();
}
__attribute__ ((weak)) void Exti11_Callback(void){
	__NOP();
}
__attribute__ ((weak)) void Exti12_Callback(void){
	__NOP();
}
__attribute__ ((weak)) void Exti13_Callback(void){
	__NOP();
}
__attribute__ ((weak)) void Exti14_Callback(void){
	__NOP();
}
__attribute__ ((weak)) void Exti15_Callback(void){
	__NOP();
}

void configExtiPin(EXTI_Config_t *extiConfig){
	switch (extiConfig->pinPort){
	case PA:
	{
		handlerExtiPIN.pGPIOx = GPIOA;
		break;
	}
	case PB:
	{
		handlerExtiPIN.pGPIOx = GPIOB;
		break;
	}
	case PC:
	{
		handlerExtiPIN.pGPIOx = GPIOC;
		break;
	}
	case PD:
	{
		handlerExtiPIN.pGPIOx = GPIOD;
		break;
	}
	case PE:
	{
		handlerExtiPIN.pGPIOx = GPIOE;
		break;
	}
	case PH:
	{
		handlerExtiPIN.pGPIOx = GPIOH;
		break;
	}
	default:
	{
		break;
	}
	}

	handlerExtiPIN.GPIO_PinConfig.GPIO_PinNumber 		= extiConfig->EXTIx;
	handlerExtiPIN.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_IN;
	handlerExtiPIN.GPIO_PinConfig.GPIO_PinPuPdControl	= extiConfig->pinPUPD_Mode;
	GPIO_Config(&handlerExtiPIN);
	extiConfig->handlerEXTIPin = handlerExtiPIN;
}

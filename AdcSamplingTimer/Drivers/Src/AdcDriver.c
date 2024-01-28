/*
 * AdcDriver.c
 *
 *  Created on: 28/04/2022
 *      Author: ezapataq
 */

#include "AdcDriver.h"
#include "GPIOxDriver.h"

GPIO_Handler_t 	handlerAdcPin 	= {0};
uint16_t		adcRawData 		= 0;

void adc_Config(ADC_Config_t *adcConfig){
	/* 1. Configuramos el PinX para que cumpla la función de canal análogo deseado */
	configAnalogPin(adcConfig->channel);

	/* 2. Activamos la señal de reloj para el periférico ADC1 (bus APB2) */
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	// Limpiamos los registros antes de comenzar a configurarlos
	ADC1->CR1 = 0;
	ADC1->CR2 = 0;

	/* Comenzamos la configuración del ADC1 */
	/* 3. Resolución del ADC */
	switch(adcConfig->resolution){
	case ADC_RESOLUTION_12_BIT:
	{
		ADC1->CR1 &= ~ADC_CR1_RES_0;
		ADC1->CR1 &= ~ADC_CR1_RES_1;
		break;
	}
	case ADC_RESOLUTION_10_BIT:
	{
		ADC1->CR1 |= ADC_CR1_RES_0;
		ADC1->CR1 &= ~ADC_CR1_RES_1;
		break;
	}
	case ADC_RESOLUTION_8_BIT:
	{
		ADC1->CR1 &= ~ADC_CR1_RES_0;
		ADC1->CR1 |= ADC_CR1_RES_1;
		break;
	}
	case ADC_RESOLUTION_6_BIT:
	{
		ADC1->CR1 |= ADC_CR1_RES_0;
		ADC1->CR1 |= ADC_CR1_RES_1;
		break;
	}
	default:
	{
		break;
	}
	}

	/* 4. Configuramos el modo Scan como desactivado */
	ADC1->CR1 &= ~ADC_CR1_SCAN;

	/* 5. Configuramos la alineación de los datos (derecha o izquierda) */

	if(adcConfig->dataAlignment == ADC_ALIGNMENT_RIGHT){
		//Alineación a la derecha (esta es la forma "natural")
		ADC1->CR2 &= ~ADC_CR2_ALIGN;
	}
	else {
		// Alineación a la izquierda (para algunos cálculos matemáticos)
		ADC1->CR2 |= ADC_CR2_ALIGN;
	}

	/* 6. Desactivamos el "continuos mode" */
	ADC1->CR2 &= ~ADC_CR2_CONT;

	/* 7. Acá se debería configurar el sampling */
	if (adcConfig->channel < ADC_CHANNEL_10){
		ADC1->SMPR2 |= (adcConfig->samplingPeriod << (3*(adcConfig->channel)));
	}
	else{
		ADC1->SMPR1 |= (adcConfig->samplingPeriod << (3*(adcConfig->channel - 9)));
	}

	/* 8. Configuramos la secuencia y cuantos elemenos hay en la secuencia */
	// Al hacerlo to.do 0, estamos seleccionando solo 1 elemento en el conteo de la secuencia
	ADC1->SQR1 = 0;

	// Asignamos el canal de la conversión a la primera posición en la secuencia
	ADC1->SQR3 |= (adcConfig->channel << 0);

	/* 9. Configuramos el preescaler del ADC en 2:1 (el más rápido que se puede tener) */
	ADC->CCR = ADC_CCR_ADCPRE_0;

	/* 10. Desactivamos las interrupciones globales */
	__disable_irq();

	/* 11. Activamos la interrupción debida a la finalización de una conversión EOC */
	ADC1->CR1 |= ADC_CR1_EOCIE;

	/* 11.a. Matriculamos la interrupción en el NVIC */
	__NVIC_EnableIRQ(ADC_IRQn);
	__NVIC_SetPriority(ADC_IRQn, 4);

	/* 12. Activamos el módulo ADC */
	ADC1->CR2 |= ADC_CR2_ADON;

	/* 13. Activamos las interrupciones globales */
	__enable_irq();
}

/* */
void startSingleConversion(void){
	/* Iniciamos un ciclo de conversión ADC */
	ADC1->CR2 |= ADC_CR2_SWSTART;
}

void startContinuousConversion(void){
	ADC1->CR2 |= ADC_CR2_CONT;
	/* Iniciamos un ciclo de conversión ADC */
	ADC1->CR2 |= ADC_CR2_SWSTART;
}

void stopContinuousConversion(void){
	ADC1->CR2 &= ~ADC_CR2_CONT;
}

/* Función que me retorna el último dato adquirido por la ADC */
uint16_t getADC(void){
	return adcRawData;
}

/* Esta es la ISR de la interrupción por conversión ADC */
void ADC_IRQHandler(void){
	// Evaluamos que se dio la interupción por conversión ADC
	if (ADC1->SR & ADC_SR_EOC){
		// Leemos el resultado de la conversión ADC y lo cargamos en un valor auxiliar
		adcRawData = ADC1->DR;

		// Hacemos el llamado a la función que se ejecutará en el main
		adcComplete_Callback();
	}
}

/* Función débil, que debe ser sobreescrita en el main */
__attribute__ ((weak)) void adcComplete_Callback(void){
	__NOP();
}

/* con esta función configuramos que pin deseamos que funcione como ADC */
void configAnalogPin(uint8_t adcChannel){

	// Con este switch seleccionamos el canal y lo configuramos como análogo
	switch (adcChannel){

	case ADC_CHANNEL_0:
	{
		// Es el Pin PA0
		handlerAdcPin.pGPIOx						= GPIOA;
		handlerAdcPin.GPIO_PinConfig.GPIO_PinNumber = PIN_0;
		break;
	}
	case ADC_CHANNEL_1:
	{
		//Es el pin PA1
		handlerAdcPin.pGPIOx						= GPIOA;
		handlerAdcPin.GPIO_PinConfig.GPIO_PinNumber = PIN_1;
		break;
	}
	case ADC_CHANNEL_2:
	{
		//Es el pin PA2
		handlerAdcPin.pGPIOx						= GPIOA;
		handlerAdcPin.GPIO_PinConfig.GPIO_PinNumber = PIN_2;
		break;
	}
	case ADC_CHANNEL_3:
	{
		//Es el pin PA3
		handlerAdcPin.pGPIOx						= GPIOA;
		handlerAdcPin.GPIO_PinConfig.GPIO_PinNumber = PIN_3;
		break;
	}
	case ADC_CHANNEL_4:
	{
		//Es el pin PA4
		handlerAdcPin.pGPIOx						= GPIOA;
		handlerAdcPin.GPIO_PinConfig.GPIO_PinNumber = PIN_4;
		break;
	}
	case ADC_CHANNEL_5:
	{
		//Es el pin PA5
		handlerAdcPin.pGPIOx						= GPIOA;
		handlerAdcPin.GPIO_PinConfig.GPIO_PinNumber = PIN_5;
		break;
	}
	case ADC_CHANNEL_6:
	{
		//Es el pin PA6
		handlerAdcPin.pGPIOx						= GPIOA;
		handlerAdcPin.GPIO_PinConfig.GPIO_PinNumber = PIN_6;
		break;
	}
	case ADC_CHANNEL_7:
	{
		//Es el pin PA7
		handlerAdcPin.pGPIOx						= GPIOA;
		handlerAdcPin.GPIO_PinConfig.GPIO_PinNumber = PIN_7;
		break;
	}
	case ADC_CHANNEL_8:
	{
		//Es el pin PB0
		handlerAdcPin.pGPIOx						= GPIOB;
		handlerAdcPin.GPIO_PinConfig.GPIO_PinNumber = PIN_0;
		break;
	}
	case ADC_CHANNEL_9:
	{
		//Es el pin PB1
		handlerAdcPin.pGPIOx						= GPIOB;
		handlerAdcPin.GPIO_PinConfig.GPIO_PinNumber = PIN_1;
		break;
	}
	case ADC_CHANNEL_10:
	{
		//Es el pin PC0
		handlerAdcPin.pGPIOx						= GPIOC;
		handlerAdcPin.GPIO_PinConfig.GPIO_PinNumber = PIN_0;
		break;
	}
	case ADC_CHANNEL_11:
	{
		//Es el pin PC1
		handlerAdcPin.pGPIOx						= GPIOC;
		handlerAdcPin.GPIO_PinConfig.GPIO_PinNumber = PIN_1;
		break;
	}
	case ADC_CHANNEL_12:
	{
		//Es el pin PC2
		handlerAdcPin.pGPIOx						= GPIOC;
		handlerAdcPin.GPIO_PinConfig.GPIO_PinNumber = PIN_2;
		break;
	}
	case ADC_CHANNEL_13:
	{
		//Es el pin PC3
		handlerAdcPin.pGPIOx						= GPIOC;
		handlerAdcPin.GPIO_PinConfig.GPIO_PinNumber = PIN_3;
		break;
	}
	case ADC_CHANNEL_14:
	{
		//Es el pin PC4
		handlerAdcPin.pGPIOx						= GPIOC;
		handlerAdcPin.GPIO_PinConfig.GPIO_PinNumber = PIN_4;
		break;
	}
	case ADC_CHANNEL_15:
	{
		//Es el pin PC5
		handlerAdcPin.pGPIOx						= GPIOC;
		handlerAdcPin.GPIO_PinConfig.GPIO_PinNumber = PIN_5;
		break;
	}
	default:
	{
		break;
	}
	}

	handlerAdcPin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ANALOG;
	GPIO_Config(&handlerAdcPin);

}

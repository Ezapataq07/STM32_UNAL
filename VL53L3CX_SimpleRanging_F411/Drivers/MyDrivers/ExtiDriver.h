/*
 * ExtiDriver.h
 *
 *  Created on: May 12, 2022
 *      Author: ezapataq
 */

#ifndef EXTIDRIVER_H_
#define EXTIDRIVER_H_

#include "stm32f4xx.h"
#include "GPIOxDriver.h"

#define EXTI0		0
#define EXTI1		1
#define EXTI2		2
#define EXTI3		3
#define EXTI4		4
#define EXTI5		5
#define EXTI6		6
#define EXTI7		7
#define EXTI8		8
#define EXTI9		9
#define EXTI10		10
#define EXTI11		11
#define EXTI12		12
#define EXTI13		13
#define EXTI14		14
#define EXTI15		15

#define PA			0b0000
#define PB			0b0001
#define PC			0b0010
#define PD			0b0011
#define PE			0b0100
#define PH			0b0111

#define RISING_TRIGGER			0
#define FALLING_TRIGGER 		1
#define FALLING_RISING_TRIGGER 	2

typedef struct
{
	uint8_t 		EXTIx;
	uint8_t			pinPort;
	uint8_t			pinPUPD_Mode;
	uint8_t			triggerMode;
	GPIO_Handler_t 	handlerEXTIPin;
}EXTI_Config_t;



void exti_Config(EXTI_Config_t	*extiConfig);
void configExtiPin(EXTI_Config_t *extiConfig);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

void Exti0_Callback(void);
void Exti1_Callback(void);
void Exti2_Callback(void);
void Exti3_Callback(void);
void Exti4_Callback(void);
void Exti5_Callback(void);
void Exti6_Callback(void);
void Exti7_Callback(void);
void Exti8_Callback(void);
void Exti9_Callback(void);
void Exti10_Callback(void);
void Exti11_Callback(void);
void Exti12_Callback(void);
void Exti13_Callback(void);
void Exti14_Callback(void);
void Exti15_Callback(void);

#endif /* EXTIDRIVER_H_ */

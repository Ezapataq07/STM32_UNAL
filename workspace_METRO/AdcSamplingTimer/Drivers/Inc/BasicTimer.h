/*
 * BasicTimer.h
 *
 *  Created on: 21/04/2022
 *      Author: ezapataq
 */

#ifndef INC_BASICTIMER_H_
#define INC_BASICTIMER_H_

#include "stm32f4xx.h"

#define TIMER_MODE_UP		1
#define TIMER_MODE_DOWN		0

#define TIMER_INCR_SPEED_1ms	16000
#define TIMER_INCR_SPEED_100us	1600
#define TIMER_INCR_SPEED_10us	160
#define TIMER_INCR_SPEED_1us	16

typedef struct
{
	uint8_t 	Timer_mode;			// Selecciona si va Up or Douwn
	uint16_t 	Timer_speed;		// Configuración de que tan rápido aumenta el timer
	uint32_t	Timer_period;		// Cada cuanto se genera una interrpción
	uint8_t		Timer_interrupt;
}BTIMER_Config_t;


typedef struct
{
	TIM_TypeDef *ptrTIMx;
	BTIMER_Config_t timerConfig;
}BTIMER_Handler_t;


/* Prototipo de las funciones - son las funciones públicas */

void BTimer_Config(BTIMER_Handler_t *ptrTimerConfig);
void startTimer(BTIMER_Handler_t *ptrTimerConfig);
void stopTimer(BTIMER_Handler_t *ptrTimerConfig);
void BTimer2_Callback(void);
void BTimer3_Callback(void);
void BTimer4_Callback(void);



#endif /* INC_BASICTIMER_H_ */

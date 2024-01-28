/*
 * PLL_Driver.c
 *
 *  Created on: 15/06/2022
 *      Author: ezapataq
 */



#include <stm32f4xx.h>
#include "PLL_Driver.h"

void PLL_Config(void){



	/* Se configura el MCO1 para observar la señal en un PIN */
	RCC->CFGR |= (0b11 << RCC_CFGR_MCO2_Pos);
	RCC->CFGR |= (0b000 << RCC_CFGR_MCO2PRE_Pos);


	/* Configuración del PLL */
	RCC->PLLCFGR |= (0b100 << RCC_PLLCFGR_PLLQ_Pos);
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC;
	RCC->PLLCFGR |= (8 << RCC_PLLCFGR_PLLM_Pos);
	RCC->PLLCFGR |= (64 << RCC_PLLCFGR_PLLN_Pos);
	RCC->PLLCFGR |= (0b01 << RCC_PLLCFGR_PLLP_Pos);
	//RCC->PLLCFGR |= (0b10 << RCC_PLLCFGR_PLLP_Pos);

	/* Seleccionamos el PLL como reloj principal en el System Clock Switch */
	RCC->CFGR |= (0b10 << RCC_CFGR_SW_Pos);

	/* Se enciende el HSI */
	RCC->CR |= RCC_CR_HSION;
	while (!(RCC->CR & RCC_CR_HSIRDY)){	}

	/* Se enciende el PLL */
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY)){	}
}

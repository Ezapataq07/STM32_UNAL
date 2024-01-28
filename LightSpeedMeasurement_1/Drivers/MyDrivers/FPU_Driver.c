/*
 * FPU_Driver.c
 *
 *  Created on: 6/06/2022
 *      Author: ezapataq
 */

//#include "core_cm4.h"
#include "stm32f4xx.h"
#include "core_cm4.h"

#include "FPU_Driver.h"

void FPU_Config(void){
	/* Se activa el FPU dandole Full Access al CPACR */
	SCB->CPACR |= (0xF << 20);

}

/*
 * SysTickDriver.h
 *
 *  Created on: May 12, 2022
 *      Author: ezapataq
 */

#ifndef SYSTICKDRIVER_H_
#define SYSTICKDRIVER_H_

//#include "core_cm4.h"
#include "stm32f4xx.h"
#include "core_cm4.h"

void config_SysTickMs(void);
uint64_t getTicksMs(void);
void delay_ms(uint32_t time);


#endif /* SYSTICKDRIVER_H_ */

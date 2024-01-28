/*
 * IntroDebuggerMain.c
 *
 *  Created on: Mar 17, 2022
 *      Author: ezque
 */
void dummy(void);

unsigned char animales;
unsigned char bicicletas;
unsigned char auxData;

#include <stdio.h>

int main(void){

	animales = 12U;
	bicicletas = 45;
	auxData = animales + bicicletas;
	dummy();
	return 0;

}

void dummy(void){
	animales++;
}

/*
 * Calculadora.c
 *
 *  Created on: Mar 10, 2022
 *      Author: ezque
 */

#include "Calculadora.h"

//Puedo hacer definicion del prototipo para las funciones desde aqui, de manera que sea privada

void sumar(void){
	int sumando1 = 15;
	int sumando2 = 38;
	int resultado = 45;

	resultado = sumando1 + sumando2;
	resultado = resultado + 1;
	multiplicar();
}


int multiplicar (void){

	int factor1 = 20;
	int factor2 = 17;
	int resultado = 1;

	resultado = factor1*factor2;

	return resultado;
}


/*
 * Taller3Main.c
 *
 *  Created on: Mar 25, 2022
 *      Author: ezque
 */

#define true 	1
#define false	0

#define NOP() __asm("NOP")

long potencia(int base, int exponente){
    long r;
    if (exponente>0){
        r = base * potencia(base, exponente-1);
        return r;
    } else {
        return 1;
    }
}

int main(void){
	// Ejemplo 1

//	unsigned char age = 0;
//	unsigned char elegible;
//
//	if (age < 18){
//		elegible = false;
//	} else {
//		elegible = true;
//	}

	//Ejemplo 2

//	unsigned char x, y, z, max;
//	x = 90;
//	y = 52;
//	z = 45;
//
//	if (x > y && x > z){
//		max = x;
//	}else if (z > y && z > x){
//		max = z;
//	}else{
//		max = y;
//	}


	// Ejemplo 4
//	unsigned char hora, minutos, segundos;
//	hora = 12;
//	minutos = 59;
//	segundos = 0;
//
//
//	if ((minutos >= 59) & (hora == 23)){
//		hora = 0;
//		minutos = 0;
//	} else if (minutos >= 59){
//		hora += 1;
//		minutos = 0;
//	}
//	if ((segundos >= 59) & (minutos == 0)){
//		segundos = 0;
//	} else if (segundos >= 59) {
//		minutos += 1;
//		segundos = 0;
//	} else {
//		segundos += 1;
//	}


	//Ejemplo For

//	unsigned char i, x;
//	x = 0;
//
//	for (i = 2; i <= 100; i+=2){
//		x += i;
//	}

//	unsigned short hora = 0, minuto = 0, segundo = 0;
//
//	while (1){
//
//			for (minuto = 0; minuto <= 59 ; minuto += 1){
//				for (segundo = 0; segundo <= 59 ; segundo += 1){
//					NOP();
//				}
//			}
//			hora += 1;
//		}



//
	unsigned char mask = 0b1, bin = 0b11010010, dec = 0, isOne = 0;
//
//	for (mask; mask <= 0b10000000; mask <<= 1){
//		dec = dec + (mask & bin);
//		NOP();
//		if (mask == 0b10000000){
//			break;
//		}
//	}

	for (int i=0; i<8; i++){
		dec += (bin & potencia(2,i));
	}


	return 0;
}





/**
 * GuessWhoMain.c
 *
 *  Integrantes: - Luisa Fernanda Orozco López
 *  			 - Emanuel Zapata Querubín
 *
 */

unsigned short facesSetComplete1;
unsigned short facesSetComplete2;

void initSystem(void);
unsigned short getPosGirls(unsigned short facesSet);
unsigned short getPosMustages(unsigned short facesSet);
unsigned short getPosMGlasses1(unsigned short facesSet1);
unsigned short getPosFGlasses1(unsigned short facesSet1);
unsigned short getPosMGlasses2(unsigned short facesSet2);
unsigned short getPosFGlasses2(unsigned short facesSet2);
unsigned short maleFaces (unsigned short facesSet1, unsigned short facesSet2);
unsigned short femaleFaces (unsigned short facesSet1, unsigned short facesSet2);
unsigned short mixFaces (unsigned short facesSet1, unsigned short facesSet2);
unsigned int totalSet (unsigned short facesSet1, unsigned short facesSet2);
signed char uniqueNumber (void);
signed char uniqueNumber2 (void);

#define NOP() __asm("NOP")

int main(void){
	/*
	 * 1) Dado a que el lenguaje de máquinas es con números binarios, se tiene que 1KB = 1024B, con esto se tendría un número de bits equivalente a una potencia de 2,
	 * así:
	 *
	 * 	a) 16KB = 16384B
	 * 	b) 32KB = 32768B
	 * 	c) 64MB = 67108864B
	 * 	d) 6.4GB = 6871947673.6B
	 *
	 * 2) El entero más grande que puede representarse con 16bits es 2^(16)-1 = 65535. En el caso de números con signo el mayor sería 32767 y el menor sería -32768.
	 *
	 * 3)
	 * 	a) 0xCAFE = 0b1100101011111110 = 51966
	 * 	b) 0xACDC = 0b1010110011011100 = 44252
	 * 	c) 0xDED0 = 0b1101111011010000 = 57040
	 * 	d) 0xF0CA = 0b1111000011001010 = 61642
	 *
	 * 4)
	 *			0	0	0	0	0	0	0	0
	 *			b	b	b	b	b	b	b	b
	 *
	 * 		0b	1	0	0	0	1	1	0	0
	 * 		0b	1	1	0	0	1	0	0	1
	 * 		0b	1	1	1	1	0	0	0	1
	 * 		0b	1	1	0	1	0	0	0	1
	 * 		0b	1	1	1	0	0	0	1	0
	 * 		0b	1	1	1	0	1	1	0	1
	 * 		0b	1	1	1	0	1	0	0	0
	 * 		0b	1	0	0	0	0	1	0	0
	 *
	 * 5) +51 = 0b00110011, +27 = 0b00011011
	 * 	a) -51 = 0b11001101; -27 = 0b11100101
	 * 	b)
	 * 		i) (+27) + (-51) = 0b11101000
	 * 		ii) (-27) + (+51) = 0b00011000
	 * 		iii) (-27) + (-51) = 0b10110010
	 *
	 */

	initSystem();

	int bang=1000000;
	bang=!bang;
	bang=!bang;
	bang=!bang;
/*
 * El operador "bang!!" es un operador lógico, por tanto retorna valores de 0 o 1; en este caso,
 * cualquier número diferente de 0 tendrá como resultado 0 al aplicarle dicho operador, y para
 * el 0 retorna 1. Así, cuando se aplica la operación NOT a una variable que contiene un
 * número mucho más grande que 1, se obtiene un 0 como resultado. True/False
 */

	unsigned short posGirls = getPosGirls(facesSetComplete1);	// La variable posGirls toma el valor que retorna la función getPosGirls aplicada a facesSetComplete1
	NOP();
	unsigned short posMustages = getPosMustages(facesSetComplete1);	// La variable posMustages toma el valor que retorna la función getPosMustages aplicada a
																	// facesSetComplete1
	NOP();
	unsigned short posMGlasses1 = getPosMGlasses1(facesSetComplete1);	// La variable posMGlasses1 toma el valor que retorna la función getPosMGlasses1 aplicada a
																		// facesSetComplete1
	unsigned short posFGlasses1 = getPosFGlasses1(facesSetComplete1);	// La variable posFGlasses1 toma el valor que retorna la función getPosFGlasses1 aplicada a
																		// facesSetComplete1

	unsigned short posMGlasses2 = getPosMGlasses2(facesSetComplete2);	// La variable posMGlasses2 toma el valor que retorna la función getPosMGlasses2 aplicada a
																		// facesSetComplete2
	unsigned short posFGlasses2 = getPosFGlasses2(facesSetComplete2);	// La variable posFGlasses2 toma el valor que retorna la función getPosFGlasses2 aplicada a
																		// facesSetComplete2
	NOP();
	unsigned short posMaleFaces = maleFaces (facesSetComplete1, facesSetComplete2);		// La variable posMaleFaces toma el valor que retorna la función maleFaces
																						// aplicada a ambos conjuntos de imágenes
	unsigned short posFemaleFaces = femaleFaces (facesSetComplete1, facesSetComplete2);	// La variable posFemaleFaces toma el valor que retorna la función femaleFaces
																						// aplicada a ambos conjuntos de imágenes
	unsigned short posMixFaces = mixFaces (facesSetComplete1, facesSetComplete2);		// La variable posMixFaces toma el valor que retorna la función mixFaces
																						// aplicada a ambos conjuntos de imágenes
	NOP();
	unsigned int facesSetTotal= totalSet(facesSetComplete1, facesSetComplete2); // La variable facesSetTotal toma el valor que retorna la función totalSet aplicada a
																				// ambos conjuntos de imágenes
	signed char negativeNumber = uniqueNumber(); 		// La variable negativeNumber toma el valor que retorna la función uniqueNumber

	signed char negativeNumber2 = uniqueNumber2();		// La variable negativeNumber2 toma el valor que retorna la función uniqueNumber2

	return 0;
}

void initSystem(void){
	facesSetComplete1 = 0b1111100100110001;		//0xF931
	facesSetComplete2 = 0b0010011110111000;		//0x27B8
}


unsigned short getPosGirls(unsigned short facesSet){
	/**
	 * La función getPosGirls retorna una variable de 16 bits sin signo con '1s' en la posición donde
	 * hay mujeres en el primer conjunto de imágenes
	 */
	unsigned short posGirls = ~facesSet;	// Se aplica la operación NOT bit a bit sobre la variable de entrada de la función
	return posGirls;						// Retorna la posición de las mujeres

}


unsigned short getPosMustages(unsigned short facesSet){
	/**
	 * La función getPosMustages retorna una variable de 16 bits sin signo con '1s' en la posición donde
	 * hay bigotes en el primer conjunto de imágenes
	 */
	unsigned short constant = 14;				// Se asigna la constante 14 a una variable
	unsigned short uno = constant/constant;		// Se divide la constante por sí misma para obtener el valor de 1, y esto se asigna a una varible
	unsigned short posMustages;					// Se define la varible posMustages

	posMustages = uno;							// Se le asigna la variable uno a posMustages
	posMustages = posMustages << uno;			// Se aplica la operación shift a la izquierda una vez a posMustages y se reasigna el resultado a la misma variable
	posMustages = posMustages << uno;			// Se aplica la operación shift a la izquierda una vez a posMustages y se reasigna el resultado a la misma variable
	posMustages = posMustages << uno;			// Se aplica la operación shift a la izquierda una vez a posMustages y se reasigna el resultado a la misma variable
	posMustages = posMustages << uno;			// Se aplica la operación shift a la izquierda una vez a posMustages y se reasigna el resultado a la misma variable
	posMustages = posMustages | uno;			// Se aplica el operador OR bit a bit entre uno y posMustages, para obtener el número 0b10001
	posMustages = posMustages << uno;			// Se aplica la operación shift a la izquierda una vez a posMustages y se reasigna el resultado a la misma variable
	posMustages = posMustages << uno;			// Se aplica la operación shift a la izquierda una vez a posMustages y se reasigna el resultado a la misma variable
	posMustages = posMustages << uno;			// Se aplica la operación shift a la izquierda una vez a posMustages y se reasigna el resultado a la misma variable
	posMustages = posMustages << uno;			// Se aplica la operación shift a la izquierda una vez a posMustages y se reasigna el resultado a la misma variable
	posMustages = posMustages | uno;			// Se aplica el operador OR bit a bit entre uno y posMustages, para obtener el número 0b100010001


	posMustages=posMustages & facesSet;			// Se aplica el operador AND bit a bit entre posMustages y facesSet, teniendo en cuenta que posMustages contiene las
												// posiciones de hombres con bigote, de manera que dicho operador hace 0 las posiciones de hombres sin bigote

	return posMustages;							// Se retorna la posicion de hombres con bigote en facesSet
}


unsigned short mask1 = 0b1110010000000000;	// Se crea una máscara con las posiciones de las personas que tienen gafas en el primer conjunto de imágenes

unsigned short getPosMGlasses1(unsigned short facesSet1){
	/**
	 * La función getPosMGlasses1 retorna una variable de 16 bits sin signo con "1s" en las posiciones de hombres con gafas en el primer conjunto de imágenes
	 */
	unsigned short posMGlasses1 = facesSet1 & mask1; // Se aplica el operador AND bit a bit entre facesSet1 y la máscara

	return posMGlasses1;							// Se retorna las posiciones de hombres con gafas
}

unsigned short getPosFGlasses1(unsigned short facesSet1){
	/**
	 * La función getPosFGlasses1 retorna una variable de 16 bits sin signo con "1s" en las posiciones de mujeres con gafas en el primer conjunto de imágenes
	 */
	unsigned short posFGlasses1 = (~facesSet1) & mask1;	// Se aplica el operador NOT a facesSet1 para obtener "1s" en las posiciones de las mujeres y luego se aplica
														// el operador AND bit a bit con la máscara

	return posFGlasses1;								// Se retorna la posicion de mujeres con gafas
}



unsigned short mask2 = 0b0101001000000000;	// Se crea una máscara con las posiciones de las personas que tienen gafas en el segundo conjunto de imágenes

unsigned short getPosMGlasses2(unsigned short facesSet2){
	/**
	 * La función getPosMGlasses2 retorna una variable de 16 bits sin signo con "1s" en las posiciones de hombres con gafas en el segundo conjunto de imágenes
	 */
	unsigned short posMGlasses2 = facesSet2 & mask2; // Se aplica el operador AND bit a bit entre facesSet2 y la máscara

	return posMGlasses2;							// Se retorna las posiciones de hombres con gafas
}

unsigned short getPosFGlasses2(unsigned short facesSet2){
	/**
	 * La función getPosFGlasses2 retorna una variable de 16 bits sin signo con "1s" en las posiciones de mujeres con gafas en el segundo conjunto de imágenes
	 */
	unsigned short posFGlasses2 = (~facesSet2) & mask2;	// Se aplica el operador NOT a facesSet2 para obtener "1s" en las posiciones de las mujeres y luego se aplica
														// el operador AND bit a bit con la máscara

	return posFGlasses2;								// Se retorna la posicion de mujeres con gafas
}



unsigned short maleFaces (unsigned short facesSet1, unsigned short facesSet2){
	/**
	 * La función maleFaces toma ambos conjuntos de imágenes y retorna una variable de 16 bits sin signo con "1s" en las posiciones donde en la misma posición hay
	 * una cara masculina
	 */
	unsigned short posMaleFaces = facesSet1 & facesSet2;	// Se aplica el operador AND bit a bit entre los conjuntos de imágenes

	return posMaleFaces;									// Se retorna las posiciones donde coinciden caras masculinas
}

unsigned short femaleFaces (unsigned short facesSet1, unsigned short facesSet2){
	/**
	 * La función femaleFaces toma ambos conjuntos de imágenes y retorna una variable de 16 bits sin signo con "1s" en las posiciones donde en la misma posición hay
	 * una cara femenina
	 */
	unsigned short posFemaleFaces = (~facesSet1) & (~facesSet2); 	// Se aplica el operador NOT bit a bit a cada conjunto de imágenes y luego entre los resultantes
																	// se aplica la operación AND bit a bit

	return posFemaleFaces;											// Se retorna las posiciones donde coinciden caras femeninas
}

unsigned short mixFaces (unsigned short facesSet1, unsigned short facesSet2){
	/**
	 * La función mixFaces toma ambos conjuntos de imágenes y retorna una variable de 16 bits sin signo con "1s" en las posiciones donde en la misma posición hay
	 * caras de sexos opuestos
	 */
	unsigned short posMixFaces = facesSet1 ^ facesSet2;		// Se aplica el operador XOR bit a bit entre los conjuntos de imágenes

	return posMixFaces;										// Se retorna las posiciones donde coinciden caras de sexos opuestos
}



unsigned int totalSet (unsigned short facesSet1, unsigned short facesSet2){
	/**
	 * La función totalSet retorna ambos conjuntos de imágenes unidos en una sola variable de 32bits sin signo, siendo facesSet1 el 'word' más significativo
	 * y facesSet2 el menos significativo
	 */
	unsigned int facesSetTotal = facesSet1; // Se define una variable de 32 bits sin signo y se inicializa con el valor de facesSet1
	facesSetTotal <<= 16;					// Se hace la operación de shift a la izquierda 16 veces y se reasigna a la misma variable
	facesSetTotal |= facesSet2;				// Se hace la operación OR bit a bit entre facesSetTotal  y faceSet2 y se reasigna el valor a la primer variable

	return facesSetTotal;

	/*
	 * El resultado es:
	 * Binario: 0b11111001001100010010011110111000
	 * HEX: 0xF93127B8
	 * DEC: 4180748216
	 */

}

signed char uniqueNumber (void){
	/**
	 * La función uniqueNumber retorna el negativo del único número entero que existe entre un cuadrado perfecto y un cubo perfecto, utilizando el un método equivalente
	 * al complemento A 2
	 */
	char constant1 = 0b00011010;		// Se define la constante 1 como el número 26 en su represetación binario
	char constant2 = constant1>>3;		// Se define la constante 2 desplazando 3 veces a la derecha la constante 1 (en realidad las constante utilizadas son 26 y 3)
	signed char negativeNumber;				// Se define una variable de 8 bits con signo

	constant1 = ~constant1;				// Se aplica el operador NOT bit a bit sobre la constante 1 y se reasigna a sí misma
	negativeNumber = constant1 ^ constant2;	// Se define el valor de negativeNumber con la operación XOR entre la constante 1 y 2

	return negativeNumber;				// Se retorna el número -26 en su representación binaria

}


signed char uniqueNumber2 (void){
	/**
	 * La función uniqueNumber retorna el negativo del único número entero que existe entre un cuadrado perfecto y un cubo perfecto
	 */
	char constante = 0b11111101;				// Se define e inicializa la constante a utilizar
	char uno = !(!constante);					// Se aplica el operador "bang!" dos veces sobre la constante para asignarlo a la variable "uno"
	signed char negativeNumber2;						// Se define la variable de retorno de 8 bits con signo
	char midvar;								// Se define una variable para cálculos intermedios

	midvar = constante >> uno;					// Se desplaza la constante una vez a la derecha y se le asigna a la variable midvar
	midvar = midvar & constante;				// Se aplica la operación AND bit a bit entre midvar y la constante y se reasigna a midvar
	midvar = midvar >> uno;						// Se desplaza la variable midvar una vez a la derecha y se reasigna a sí misma
	midvar = midvar & constante;				// Se aplica la operación AND bit a bit entre midvar y la constante y se reasigna a midvar
	midvar = midvar >> uno;						// Se desplaza la variable midvar una vez a la derecha y se reasigna a sí misma
	midvar = midvar & constante;				// Se aplica la operación AND bit a bit entre midvar y la constante y se reasigna a midvar

	negativeNumber2 = constante ^ midvar;		// Se aplica la operación XOR bit a bit entre la constante y midvar

	midvar = midvar >> uno;						// Se desplaza la variable midvar una vez a la derecha y se reasigna a sí misma
	midvar = midvar & constante;				// Se aplica la operación AND bit a bit entre midvar y la constante y se reasigna a midvar

	char tres;									// Se define la variable que contendrá el número tres
	tres = midvar >> uno;						// Se desplaza la variable midvar una vez a la derecha
	tres = tres >> uno;							// Se desplaza la variable midvar una vez a la derecha

	midvar = midvar >> uno;						// Se desplaza la variable midvar una vez a la derecha y se reasigna a sí misma
	midvar = midvar & constante;				// Se aplica la operación AND bit a bit entre midvar y la constante y se reasigna a midvar

	negativeNumber2 = negativeNumber2 ^ midvar;	// Se aplica la operación XNOR entre negativeNumber2 y midvar y se reasigna a la primera variable
	negativeNumber2 = negativeNumber2 ^ tres;	// Se aplica la operación XNOR entre negativeNumber2 y tres y se reasigna a la primera variable

	return negativeNumber2;						// Se retorna el número -26 en su representación binaria


}

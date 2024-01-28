/*
 * Taller6Main.c
 *
 *  Created on: Apr 22, 2022
 *      Author: ezapataq
 */


/*Prototipo de la funcion */
int restar(int a, int b);
void restarRef(int *a, int *b, int *resta);


int main(void){

	/* Funcion con paso por valor */
	int x = 5;
	int y = 9;
	int resta;

	resta=restar(x,y);

	/* Por referencia */
	int z = 6;
	int w = 5;
	int restaRef;

	restarRef(&z,&w,&restaRef);
}

int restar(int a, int b){
	int resta = a-b;

	return resta;
}

void restarRef(int *a, int *b, int *resta){
	*resta=*a-*b;
}

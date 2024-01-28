/*
 * Taller2Main.c
 *
 *  Created on: Mar 18, 2022
 *      Author: ezque
 */


#include <stdint.h>

int main(void){

	uint8_t num1, num2, num3, num4,  num5, num6, num7;
	num1 = 0b01010010;
	num2 = 0b01110011;
//
//	int bitwiseAND = num1 & num2;
//	int logicalAND = num1 && num2;
//
//	int bitwiseOR = num1 | num2;
//	int logicalOR = num1 || num2;
//
//	int bitwiseXOR = num1 ^ num2;
//
//	int bitwiseNOT = ~num1;
//	int logicalNOT = !num1;



//	unsigned char a = 1;
//	unsigned char b= 0;
//	unsigned char c = 0;

//	unsigned char x1 = a||(b&&c);
//	unsigned char x2 = (a||b)&&(a||c);
//
//	unsigned char distributiva = (x1==x2);

//	unsigned char AB_ = !(a&&b);
//	unsigned char A_MasB_ = (!a)||(!b);
//	unsigned char NAND = (AB_ == A_MasB_);
//
//	unsigned char AMasB_ = !(a||b);
//	unsigned char A_B_ = (!a)&&(!b);
//	unsigned char NOR = (AMasB_ == A_B_);




	num1 |= 0x90; // 0x90 en binario es 10010000 "SET"

	num3 = 0b1111111;
	//num3 &= 0x47; // 0x47 en binario es 1000111 -> "RESET"
	num3 &= ~ 0x38; // 0x38 en binario es 0111000



	/*
	 * ¿Es par?
	 */
//	unsigned char par = 100;
//	unsigned char impar = 101;
//	unsigned char imparMask = 0b1;
//
//	par &= imparMask;
//	impar &= imparMask;







	num7 = 2;

	uint8_t num7_1bit_iz = num7<<1;
	uint8_t num7_2bit_iz = num7<<2;
	uint8_t num7_3bit_iz = num7<<3;
	uint8_t num7_4bit_iz = num7<<4;


	unsigned short num8 = 1024;

	unsigned short  num8_1bit_der = num8>>1;
	unsigned short  num8_2bit_der = num8>>2;
	unsigned short  num8_3bit_der = num8>>3;
	unsigned short  num8_4bit_der = num8>>4;
	unsigned short  num8_5bit_der = num8>>5;
	unsigned short  num8_6bit_der = num8>>6;








}

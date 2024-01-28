/*
 * EjEstructuras.c
 *
 *  Created on: Apr 22, 2022
 *      Author: ezapataq
 */

#include <stdio.h>

typedef struct
{
	uint32_t	calculus;
	uint32_t	physics;
	uint32_t	electronics;
}Student_Grades_t;

typedef struct
{
	uint32_t			id;
	uint32_t			grade;
	Student_Grades_t	grades;
	uint8_t*			name;
}Student_Info_t;


void changeGrades(Student_Info_t *pStudentInfo, uint32_t notaCalc, uint32_t notaPhy, uint32_t notaElec){
	pStudentInfo->grades.calculus = notaCalc;
	pStudentInfo->grades.physics = notaPhy;
	pStudentInfo->grades.electronics = notaElec;
}

int main(void){
	Student_Info_t EmanuelInfo = {0};

	EmanuelInfo.id 		= 1007506265;
	EmanuelInfo.grade	= 10;
	changeGrades(&EmanuelInfo, 5, 4.7, 4.5);
	EmanuelInfo.name	= "Emanuel";


	return 0;

}

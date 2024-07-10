/*
 * MAX.h
 *
 *  Created on: 24 de jun de 2024
 *      Author: gustavo
 */

#include <msp430.h>

#ifndef MAX_H_
#define MAX_H_

#define MAX_ADR 0x57

char MAXVector[6];
char Bat[8];
float SPO2;
unsigned long RED1, RED0, IR1, IR0;
int MAXFlag;
volatile int contagem;
int HR;


void MAX_Send(char reg, char dado);

void MAX_Data(char reg);

void MAX_Config();

void LeituraMAX();

void Batimentos();

#endif /* MAX_H_ */

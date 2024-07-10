/*
 * Relogio.h
 *
 *  Created on: 24 de jun de 2024
 *      Author: gustavo
 */
 
 #include <msp430.h>
 #include <stdio.h>
 
extern char Serial_Str[17];


#ifndef RELOGIO_H_
#define RELOGIO_H_

int HORA;
int MIN;
int SEG;
char HORARIO[6];

void TimerA2_config();

void TakeTime();

void PrintHora();

#endif /* RELOGIO_H_ */

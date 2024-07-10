/*
 * MPU.h
 *
 *  Created on: 24 de jun de 2024
 *      Author: gustavo
 */

#include <msp430.h>

#ifndef MPU_H_
#define MPU_H_

#define MPU_ADR 0x68
char MpuVector[16];
volatile int ax,ay,az,gx,gy,gz;
char tremor[4];
float temp;
char temperatura[4];
char envia;

void MPU_Config();

void MPU_Data(char reg);

void MPU_Send(char reg, char dado);

void B0_config();

void leds_s1_config();

void LeituraMPU();

void Tremores();



#endif /* MPU_H_ */

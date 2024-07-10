/*
 * BLUETOOTH.h
 *
 *  Created on: 24 de jun de 2024
 *      Author: gustavo
 */
#include <msp430.h>

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

char Serial_Str[17];
int LeituraUart;

void USCI_A0_config(void);

void WriteSerial_str(char *str);

void WriteSerial_char(char character);

void READ(char caracter);

void CleanSerial();

#endif /* BLUETOOTH_H_ */

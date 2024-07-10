/*
 * BLUETOOTH.C
 *
 *  Created on: 24 de jun de 2024
 *      Author: gustavo
 */
#include "Bluetooth.h"

void USCI_A0_config(void){
    UCA0CTL1 = UCSWRST;
    UCA0CTL0 = 0;
    UCA0BRW = 3;
    UCA0MCTL = UCBRS_3;
    P3SEL |= BIT4 | BIT3;
    UCA0CTL1 = UCSSEL_1;
    UCA0IE = UCRXIE;
}


void WriteSerial_str(char *str){
    unsigned int i = 0;
    while (str[i] !=0){
        WriteSerial_char(str[i++]);
    }
}

void WriteSerial_char(char character){
    __delay_cycles(100);
    while ((UCA0IFG & UCTXIFG) == 0);
    UCA0TXBUF = character;
}


void READ(char caracter){
    unsigned int i = 0;
    while(Serial_Str[i] != 0 && i<16){
        i++;
    }
    Serial_Str[i++]=caracter;
    Serial_Str[16]=0;
    if (caracter == '\n' || caracter == '\r')
        LeituraUart=1;
}

void CleanSerial(){
    volatile int i;
    for(i=0;i<16;i++)
        Serial_Str[i] = 0;
}

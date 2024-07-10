/*
 * Lcd.c
 *
 *  Created on: 24 de jun de 2024
 *      Author: gustavo
 */
#include <Lcd.h>

char i2cSend(char address, char data) {
    UCB0I2CSA = address;
    UCB0CTL1 |= UCTR | UCTXSTT;
    while ((UCB0IFG & UCTXIFG) == 0);
    UCB0TXBUF = data;
    while ((UCB0CTL1 & UCTXSTT) != 0);
    UCB0CTL1 |= UCTXSTP;
    while ((UCB0CTL1 & UCTXSTP) != 0);
    if ((UCB0IFG & UCNACKIFG) != 0)
        return 1; // Erro
    return 0; // Sucesso
}


void LcdWriteByte(char dado, char RS){
    char highNibble = (dado & 0xF0) | (RS ? 0x01 : 0x00);
    char lowNibble = ((dado << 4) & 0xF0) | (RS ? 0x01 : 0x00);
    i2cSend(0x27, highNibble| BIT3);
   // __delay_cycles(100);
    i2cSend(0x27, highNibble| BIT3 | BIT2);
    //__delay_cycles(1000);
    i2cSend(0x27, highNibble | BIT3);
    //__delay_cycles(1000);
    i2cSend(0x27, lowNibble| BIT3);
    //__delay_cycles(100);
    i2cSend(0x27, lowNibble| BIT3 | BIT2);
    //__delay_cycles(1000);
    i2cSend(0x27, lowNibble | BIT3);
}

void LcdWriteStr(char *str){
    volatile int i = 0;
    while (str[i] != 0 && str[i] != 10){
        LcdWriteByte(str[i++], 1);
    }
}


void lcd_inic(void){
    UCB0I2CSA = 0x27;
    UCB0CTL1 |= UCTR    | UCTXSTT;
    while ((UCB0IFG & UCTXIFG) == 0);
    UCB0TXBUF = 0;
    while ((UCB0CTL1 & UCTXSTT) == UCTXSTT);
    if ((UCB0IFG & UCNACKIFG) == UCNACKIFG)
        while(1);

    LcdWriteByte(0, 0);
    LcdWriteByte(3, 0);
    LcdWriteByte(3, 0);
    LcdWriteByte(3, 0);
    LcdWriteByte(2, 0);
//configurar LCD
    LcdWriteByte(0x28, 0);
    LcdWriteByte(8, 0);
    LcdWriteByte(01, 0);
    LcdWriteByte(06, 0);
    LcdWriteByte(0x0F, 0);
}


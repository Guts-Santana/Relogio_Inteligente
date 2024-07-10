/*
 * MAX.c
 *
 *  Created on: 24 de jun de 2024
 *      Author: gustavo
 */

#include "MAX.h"

void MAX_Send(char reg, char dado){
    UCB0I2CSA = MAX_ADR;
    UCB0CTL1 |= UCTR | UCTXSTT;
    while ( (UCB0IFG & UCTXIFG) == 0);
    UCB0TXBUF = reg;
    while ( (UCB0CTL1 & UCTXSTT) == UCTXSTT);
    if ( (UCB0IFG & UCNACKIFG) == UCNACKIFG){
        P1OUT |= BIT0;
        while(1);
    }
    while ( (UCB0IFG & UCTXIFG) == 0);
    UCB0TXBUF = dado;
    while ( (UCB0IFG & UCTXIFG) == 0);
    UCB0CTL1 |= UCTXSTP;
    while ( (UCB0CTL1 & UCTXSTP) == UCTXSTP);
}

void MAX_Data(char reg){
    char i;
    UCB0I2CSA = MAX_ADR;
    UCB0CTL1 |= UCTR | UCTXSTT;
    while ( (UCB0IFG & UCTXIFG) == 0);
    UCB0TXBUF = reg;
    while ( (UCB0CTL1 & UCTXSTT) == UCTXSTT);
    UCB0CTL1 &= ~UCTR;
    UCB0CTL1 |= UCTXSTT;
    while ( (UCB0CTL1 & UCTXSTT) == UCTXSTT);
    for (i=0; i<5; i++){
        while ((UCB0IFG & UCRXIFG) == 0);
        MAXVector[i]=UCB0RXBUF;
    }
    UCB0CTL1 |= UCTXSTP;
    while ((UCB0IFG & UCRXIFG) == 0);
    MAXVector[i]=UCB0RXBUF;
    while ( (UCB0CTL1 & UCTXSTP) == UCTXSTP);
}

void MAX_Config(){
    MAX_Send(0x09, 0x40);
    __delay_cycles(1000);
    MAX_Send(0x08, 0x10);
    MAX_Send(0x09, 0x03);
    MAX_Send(0x0A, 0x27);
    MAX_Send(0x0C, 0x1F);
    MAX_Send(0x0D, 0x1F);
}

void LeituraMAX(){

    RED0 = RED1;
    MAX_Data(0x07);
    RED1 = ((unsigned long)MAXVector[0]<<16) + (MAXVector[1]<<8) + MAXVector[2];
    IR1 = ((unsigned long)MAXVector[3]<<16) + (MAXVector[4]<<8) + MAXVector[5];
}

void Batimentos(){
    int i;
    for(i=0;i<100;i++){
        LeituraMAX();
        if (RED1 > RED0 && RED1 > 0x1000)
            MAXFlag = 1;
        else if (RED1 < RED0 && MAXFlag == 1 && RED1 > 0x1000)
            HR++;
        else
            MAXFlag = 0;
    }
}

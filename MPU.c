/*
 * MPU.c
 *
 *  Created on: 24 de jun de 2024
 *      Author: gustavo
 */

#include "MPU.h"

void MPU_Config(){
    MPU_Send(0x6B, 1);
    __delay_cycles(10000);
    MPU_Send(0x1A, 6);
    MPU_Send(0x19, 9);
    MPU_Send(0x1B, 0);
    MPU_Send(0x1C, 0);
}


void MPU_Data(char reg){
    char i;
    UCB0I2CSA = MPU_ADR;
    UCB0CTL1 |= UCTR | UCTXSTT;
    while ( (UCB0IFG & UCTXIFG) == 0);
    UCB0TXBUF = reg;
    while ( (UCB0CTL1 & UCTXSTT) == UCTXSTT);
    UCB0CTL1 &= ~UCTR;
    UCB0CTL1 |= UCTXSTT;
    while ( (UCB0CTL1 & UCTXSTT) == UCTXSTT);
    for (i=0; i<13; i++){
        while ((UCB0IFG & UCRXIFG) == 0);
        MpuVector[i]=UCB0RXBUF;
    }
    UCB0CTL1 |= UCTXSTP;
    while ((UCB0IFG & UCRXIFG) == 0);
    MpuVector[i]=UCB0RXBUF;
    while ( (UCB0CTL1 & UCTXSTP) == UCTXSTP);
}


void MPU_Send(char reg, char dado){
    UCB0I2CSA = MPU_ADR;
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


void leds_s1_config(){
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
    P4DIR |= BIT7;
    P4OUT &= ~BIT7;
    P2DIR &= ~BIT1;
    P2REN |= BIT1;
    P2OUT |= BIT1;
}

void B0_config(){
    UCB0CTL1 = UCSWRST;
    UCB0CTL0 = UCSYNC | UCMODE_3 | UCMST;
    UCB0BRW = 11;
    UCB0CTL1 = UCSSEL_3;
    P3SEL |= BIT0 | BIT1;
    P3REN |= BIT1 | BIT0;
    P3OUT |= BIT1 | BIT0;
}

void LeituraMPU(){
    int tp;

    MPU_Data(0x3B); //Ler 14 regs
    ax=MpuVector[ 0]; ax=(ax<<8)+MpuVector[ 1]; //aceleração eixo x
    ay=MpuVector[ 2]; ay=(ay<<8)+MpuVector[ 3]; //aceleração eixo y
    az=MpuVector[ 4]; az=(az<<8)+MpuVector[ 5]; //aceleração eixo z
    tp=MpuVector[ 6]; tp=(tp<<8)+MpuVector[ 7]; //temperatura
    gx=MpuVector[ 8]; gx=(gx<<8)+MpuVector[ 9]; //giro eixo x
    gy=MpuVector[10]; gy=(gy<<8)+MpuVector[11]; //giro eixo y
    gz=MpuVector[12]; gz=(gz<<8)+MpuVector[13]; //giro eixo z

    temp = tp/340.0+36.53;
    ax/=16384;
    ay/=16384;
    az/=16384;
    gx/=131;
    gy/=131;
    gz/=131;
}

void Tremores(){
    if(gx > 10 || gy > 10 || gz > 10 ||
        gx < -10 || gy < -10 || gz < -10){
        tremor[0] = 'S';
        tremor[1] = 'I';
        tremor[2] = 'M';
        tremor[3] = 0;
        envia = 1;
    }
    else{
        tremor[0] = 'N';
        tremor[1] = 'A';
        tremor[2] = 'O';
        tremor[3] = 0;
        envia = 0;
    }
}

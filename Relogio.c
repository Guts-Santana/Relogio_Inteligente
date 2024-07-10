/*
 * Relogio.c
 *
 *  Created on: 25 de jun de 2024
 *      Author: gustavo
 */

#include "Relogio.h";

void TimerA2_config(){
    TA2CTL = TASSEL_1 | MC_1 | ID_3;
    TA2CCR0 = 4095;
    TA2CCTL0 = CCIE;
}

void TakeTime(){
    HORA=(Serial_Str[0]-'0')*10+Serial_Str[1]-'0';
    MIN =(Serial_Str[3]-'0')*10+Serial_Str[4]-'0';
}

void PrintHora(){
	if(HORA < 10 && MIN <10)
    	sprintf(HORARIO, "0%d:0%d", HORA, MIN);
    else if(HORA< 10 && MIN >=10)
    	sprintf(HORARIO,"0%d:%d", HORA, MIN);
    else if(HORA >= 10 && MIN < 10)
    	sprintf(HORARIO, "%d:0%d", HORA, MIN);
    else
    	sprintf(HORARIO, "%d:%d", HORA, MIN);
}

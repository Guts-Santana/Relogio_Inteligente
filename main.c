
#include <stdio.h>
#include "Bluetooth.h"
#include "Lcd.h"
#include "MPU.h"
#include "MAX.h"
#include "Relogio.h"

void RETORNA();
void PRINTLCD();

//0x68 MPU
//0x27 LCD
//0x57 MAX

//SCL 3.1
//SDA 3.0

//TXM 3.3
//RXM 3.4

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
	B0_config();
	__delay_cycles(1000);
	lcd_inic();
	MPU_Config();
	MAX_Config();
	USCI_A0_config();
	leds_s1_config();
	//MPU_Config();
	leds_s1_config();
	TimerA2_config();
	__enable_interrupt();
	CleanSerial();
	char Start[] = "Para comecar, digite o horario XX:XX\n";
	WriteSerial_str(Start);
	while(!LeituraUart);
	TakeTime();
	TimerA2_config();
	while(1);
	return 0;
}

#pragma vector = USCI_A0_VECTOR
__interrupt void usci_a0_int(void){
    UCA0IV;
    char c = UCA0RXBUF;
    READ(c);
}


#pragma vector=TIMER2_A0_VECTOR
__interrupt void Timer2_A0_ISR(void)
{
    TA2CCTL0 &= ~CCIFG;
    SEG++;
    char string[] = "DADOS";
    Batimentos();
    if(SEG%10==0){
        sprintf(Bat,"%d bpm", HR/2);
        HR = 0;
        LeituraMPU();
        sprintf(temperatura, "%dC", (int)temp);
        Tremores();
        __delay_cycles(100);
        WriteSerial_str(string);
        WriteSerial_char('\n');
        WriteSerial_char('\n');

        RETORNA();

        PRINTLCD();
    }
    if (SEG == 60){
       SEG = 0;
       MIN++;
       if (MIN == 60){
           MIN = 0;
           HORA++;
           if (HORA == 24)
               HORA = 0;

       }
       PRINTLCD();
   }
}

void RETORNA(){
    char string1[] = "Batimentos: ";
    char string2[] = "Temperatura Ambiente: ";
    char string3[] = "Há tremores: ";


    WriteSerial_str(string1);
    WriteSerial_str(Bat);
    WriteSerial_char('\n');

    WriteSerial_str(string2);
    WriteSerial_str(temperatura);
    WriteSerial_char('\n');

0    WriteSerial_str(string3);
    if (envia)
        WriteSerial_str("SIM");
    else
        WriteSerial_str("NAO");
    WriteSerial_char('\n');
    WriteSerial_char('\n');


}

void PRINTLCD(){

    LcdWriteByte(0x80, 0);
    PrintHora();
    LcdWriteStr(HORARIO);
    LcdWriteStr("     ");
    LcdWriteStr(Bat);
    LcdWriteByte(0xc0, 0);
    LcdWriteStr(temperatura);
    LcdWriteStr("         ");
    LcdWriteStr(tremor);

}

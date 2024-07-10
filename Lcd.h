/*
 * Lcd.h
 *
 *  Created on: 24 de jun de 2024
 *      Author: gustavo
 */
#include <msp430.h>

#ifndef LCD_H_
#define LCD_H_


char i2cSend(char address, char data);

void LcdWriteByte(char dado, char RS);

void LcdWriteStr(char *str);

void lcd_inic(void);



#endif /* LCD_H_ */

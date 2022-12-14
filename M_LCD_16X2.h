/* 
 * File:   M_LCD_16X2.h
 * Author: Juancho
 *
 * Created on 12 de abril de 2018, 22:48
 */

#ifndef M_LCD_16X2_H
#define	M_LCD_16X2_H

#include "delay.h"
#include "systemPIC32MX.h"

#define RS LATBbits.LATB2
#define E  LATBbits.LATB3

#define DIR_RS TRISBbits.TRISB2
#define DIR_E  TRISBbits.TRISB3


#define D0 LATBbits.LATB4
#define D1 LATBbits.LATB5
#define D2 LATBbits.LATB7
#define D3 LATBbits.LATB8

#define DIR_D0 TRISBbits.TRISB4
#define DIR_D1 TRISBbits.TRISB5
#define DIR_D2 TRISBbits.TRISB7
#define DIR_D3 TRISBbits.TRISB8


void LCD_init(void);
void lcd_cmd4(unsigned char cmd);
void lcd_cmd(unsigned char cmd);
void lcd_dato(unsigned char dato);
void lcd_puts(unsigned char *msg);
void lcd_putc(unsigned char caracter);
void lcd_xy(unsigned char x, unsigned char y);
void lcd_clrscr(void);
void batery(void);
void lcd_barra(unsigned int dato);
void lcd_dinicio(void);
#endif	/* M_LCD_16X2_H */


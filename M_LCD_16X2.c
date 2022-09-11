#include "M_LCD_16X2.h"

void lcd_init(void){
    DIR_RS=0;
    DIR_E=0;
    DIR_D0=0;
    DIR_D1=0;
    DIR_D2=0;
    DIR_D3=0;
    
    RS=0;
    E=0;
    D0=0;
    D1=0;
    D2=0;
    D3=0;
    delay_ms(15);
    
    lcd_cmd4(0x30);
    delay_ms(5);
    lcd_cmd4(0x30);
    delay_us(200);
    lcd_cmd4(0x30);
    delay_us(200);
    lcd_cmd4(0x20);
    lcd_cmd(0x28);
    lcd_cmd(0x0f);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
    delay_ms(2);
}

void lcd_cmd4(unsigned char cmd){
    RS=0;
    D0=(cmd>>4)&1;
    D1=(cmd>>5)&1;
    D2=(cmd>>6)&1;
    D3=(cmd>>7)&1;
    Nop();
    Nop();
    E=1;
    delay_us(1);
    E=0;
    delay_us(50);
}

void lcd_cmd(unsigned char cmd){
    RS=0;
    D0=(cmd>>4)&1;
    D1=(cmd>>5)&1;
    D2=(cmd>>6)&1;
    D3=(cmd>>7)&1;
    Nop();
    Nop();
    E=1;
    delay_us(1);
    E=0;
    Nop();
    Nop();
    D0=(cmd)&1;
    D1=(cmd>>1)&1;
    D2=(cmd>>2)&1;
    D3=(cmd>>3)&1;
    Nop();
    Nop();
    E=1;
    delay_us(1);
    E=0;
    delay_us(50);
}

void lcd_dato(unsigned char dato){
    RS=1;
    D0=(dato>>4)&1;
    D1=(dato>>5)&1;
    D2=(dato>>6)&1;
    D3=(dato>>7)&1;
    Nop();
    Nop();
    E=1;
    delay_us(1);
    E=0;
    Nop();
    Nop();
    D0=(dato)&1;
    D1=(dato>>1)&1;
    D2=(dato>>2)&1;
    D3=(dato>>3)&1;
    Nop();
    Nop();
    E=1;
    delay_us(1);
    E=0;
    delay_us(50);
    RS=0;
}

void lcd_puts(unsigned char *msg){
    while(*(msg)!='\0'){
        lcd_dato(*(msg++));
    }
}

void lcd_putc(unsigned char caracter){
    lcd_dato(caracter);
}

void lcd_xy(unsigned char x, unsigned char y){
    unsigned char tmp=0;
    tmp=x|0x80;
    if(y!=0){
        tmp|=0x40;
    }
    lcd_cmd(tmp);
}

void lcd_clrscr(void){
    lcd_cmd(0x01);
    delay_ms(2);
}

void batery(void){
    unsigned char caracter1[8]={0B00000,0B00000,0B00000,0B00000,0B00000,0B00000,0B00000,0B11111};
    unsigned char caracter2[8]={0B00000,0B00000,0B00000,0B00000,0B00000,0B00000,0B11111,0B11111};
    unsigned char caracter3[8]={0B00000,0B00000,0B00000,0B00000,0B00000,0B11111,0B11111,0B11111};
    unsigned char caracter4[8]={0B00000,0B00000,0B00000,0B00000,0B11111,0B11111,0B11111,0B11111};
    unsigned char caracter5[8]={0B00000,0B00000,0B00000,0B11111,0B11111,0B11111,0B11111,0B11111};
    unsigned char caracter6[8]={0B00000,0B00000,0B11111,0B11111,0B11111,0B11111,0B11111,0B11111};
    unsigned char caracter7[8]={0B00000,0B11111,0B11111,0B11111,0B11111,0B11111,0B11111,0B11111};
    unsigned char caracter8[8]={0B00000,0B01010,0B01010,0B00000,0B10001,0B10001,0B01110,0B00000};
    lcd_cmd(0x40);
    lcd_dato(caracter1[0]);
    lcd_dato(caracter1[1]);
    lcd_dato(caracter1[2]);
    lcd_dato(caracter1[3]);
    lcd_dato(caracter1[4]);
    lcd_dato(caracter1[5]);
    lcd_dato(caracter1[6]);
    lcd_dato(caracter1[7]);
    lcd_cmd(0x48);
    lcd_dato(caracter2[0]);
    lcd_dato(caracter2[1]);
    lcd_dato(caracter2[2]);
    lcd_dato(caracter2[3]);
    lcd_dato(caracter2[4]);
    lcd_dato(caracter2[5]);
    lcd_dato(caracter2[6]);
    lcd_dato(caracter2[7]);
    lcd_cmd(0x50);
    lcd_dato(caracter3[0]);
    lcd_dato(caracter3[1]);
    lcd_dato(caracter3[2]);
    lcd_dato(caracter3[3]);
    lcd_dato(caracter3[4]);
    lcd_dato(caracter3[5]);
    lcd_dato(caracter3[6]);
    lcd_dato(caracter3[7]);
    lcd_cmd(0x58);
    lcd_dato(caracter4[0]);
    lcd_dato(caracter4[1]);
    lcd_dato(caracter4[2]);
    lcd_dato(caracter4[3]);
    lcd_dato(caracter4[4]);
    lcd_dato(caracter4[5]);
    lcd_dato(caracter4[6]);
    lcd_dato(caracter4[7]);
    lcd_cmd(0x60);
    lcd_dato(caracter5[0]);
    lcd_dato(caracter5[1]);
    lcd_dato(caracter5[2]);
    lcd_dato(caracter5[3]);
    lcd_dato(caracter5[4]);
    lcd_dato(caracter5[5]);
    lcd_dato(caracter5[6]);
    lcd_dato(caracter5[7]);
    lcd_cmd(0x68);
    lcd_dato(caracter6[0]);
    lcd_dato(caracter6[1]);
    lcd_dato(caracter6[2]);
    lcd_dato(caracter6[3]);
    lcd_dato(caracter6[4]);
    lcd_dato(caracter6[5]);
    lcd_dato(caracter6[6]);
    lcd_dato(caracter6[7]);
    lcd_cmd(0x70);
    lcd_dato(caracter7[0]);
    lcd_dato(caracter7[1]);
    lcd_dato(caracter7[2]);
    lcd_dato(caracter7[3]);
    lcd_dato(caracter7[4]);
    lcd_dato(caracter7[5]);
    lcd_dato(caracter7[6]);
    lcd_dato(caracter7[7]);
    lcd_cmd(0x78);
    lcd_dato(caracter8[0]);
    lcd_dato(caracter8[1]);
    lcd_dato(caracter8[2]);
    lcd_dato(caracter8[3]);
    lcd_dato(caracter8[4]);
    lcd_dato(caracter8[5]);
    lcd_dato(caracter8[6]);
    lcd_dato(caracter8[7]);    
}

void lcd_barra(unsigned int dato){
    if(dato>=12){
        batery();
        lcd_xy(5,1);
        lcd_dato(0);
    }
    if(dato>=24){
        batery();
        lcd_xy(5,1);
        lcd_dato(0);
        lcd_dato(1);
    }
    if(dato>=36){
        batery();
        lcd_xy(5,1);
        lcd_dato(0);
        lcd_dato(1);
        lcd_dato(2);
    }
    if(dato>=48){
        batery();
        lcd_xy(5,1);
        lcd_dato(0);
        lcd_dato(1);
        lcd_dato(2);
        lcd_dato(3);
    }
    if(dato>=60){
        batery();
        lcd_xy(5,1);
        lcd_dato(0);
        lcd_dato(1);
        lcd_dato(2);
        lcd_dato(3);
        lcd_dato(4);
    }
    if(dato>=72){
        batery();
        lcd_xy(5,1);
        lcd_dato(0);
        lcd_dato(1);
        lcd_dato(2);
        lcd_dato(3);
        lcd_dato(4);
        lcd_dato(5);
    }
    if(dato>=84){
        batery();
        lcd_xy(5,1);
        lcd_dato(0);
        lcd_dato(1);
        lcd_dato(2);
        lcd_dato(3);
        lcd_dato(4);
        lcd_dato(5);
        lcd_dato(6);
    }
    if(dato>=96){
        batery();
        lcd_xy(12,1);
        lcd_dato(0xFF);
    }
}

void lcd_dinicio(void){
    lcd_xy(5,0);                //Hubica la posicion
    lcd_puts(((unsigned char *)"DIMMER\0"));    //Escribe en la posicion
    batery();
    lcd_xy(14,1);
    lcd_dato(7);
    lcd_xy(0,1);
    lcd_puts(((unsigned char *)"INGRESE UN VALOR\0"));
}
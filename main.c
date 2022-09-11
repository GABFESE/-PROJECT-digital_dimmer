#include <stdio.h>
#include "systemPIC32MX.h"
#include "delay.h"
#include "M_LCD_16X2.h"
#include "M_Timers.h"
#include "Teclado_4X4.h"
#include <string.h>
#define DISPARO(valor) LATBbits.LATB15=valor;

typedef struct{
    unsigned Teclado:1,Deteccion:1;
}soft_flags;

const unsigned char Key_deco[16]={1,2,3,10,4,5,6,11,7,8,9,12,13,0,14,15};
unsigned char msg[20],Tecla=0,vect[10];
volatile unsigned char tecla_key=0;
volatile soft_flags banderas;
volatile unsigned int intencidad=0,cnt1=0,cnt2=0;

void __ISR(_EXTERNAL_1_VECTOR,IPL7SOFT) Deteccion(void){
    //delay_us(180);          // delay_us(180);
    cnt2=0;                 //Reinicia el contador
    DISPARO(0);  
    //banderas.Deteccion=1;   //Sube la bandera
    IFS0bits.INT1IF=0;      //Baja la bandera de persistencia de la interrupcion
}

void __ISR(_TIMER_2_VECTOR,IPL6SOFT) Timer(void){
    if(cnt2<=100){    
        cnt2++;
    }                     //Incrementa el contador
    else{
        cnt2=0;
    }
    
    if(cnt2>100-intencidad){    //Compara el contador con el duty
        DISPARO(1);             //Activa el disparo
    }
    else{
        DISPARO(0);  
    }
    IFS0bits.T2IF=0;            //Baja la bandera de persistencia del Timer
}

void __ISR(_CHANGE_NOTICE_VECTOR,IPL5SOFT) Change_Notice(void){
    if(IFS1bits.CNAIF==1 || IFS1bits.CNBIF==1){
        delay_us(500);
        if(key_press()){
           banderas.Teclado=key_read(&tecla_key);      
        }  
        Key_Read_Port();
        IFS1bits.CNAIF=0;
        IFS1bits.CNBIF=0;
    }
}

int main(void){
    ANSELA=0;                   //Puerto A como digitales
    ANSELB=0;                   //Puerto B como digitales
    banderas.Teclado=0;         //Inicia la bandera del teclado en 0  
    BMXCONbits.BMXWSDRM=0;
    TRISBbits.TRISB15=0;        //Pin RB15 salida 
    TRISBbits.TRISB14=1;        //Pin RB14 entrada
    INT1R=1;                    //interrupcion en el pin RPB14 = 0001
    TRISA=0;
    LATA=0;
    LATB=0;                     //0 como salidas para puerto B
    DISPARO(0); 
    
    teclado_init();             //Inicia la funcion del teclado
    lcd_init();                 //Inicia la funcion de LCD
    lcd_dinicio();              //Inicia la funcion datos de inicio
    
    __builtin_disable_interrupts();        
    Timer2_config(TMR2_PRESCALA_256,13-1);  // 83us
    Timer2_cntrl(1);                        //Habilita el contador
    
    INTCONbits.MVEC=1;  
    IPC2bits.T2IP=6;        //4,5
    IPC2bits.T2IS=1;
    IFS0bits.T2IF=0;
    IEC0bits.T2IE=1;
    
    IPC8bits.CNIP=5;        //6,4
    IPC8bits.CNIS=1;
    IFS1bits.CNBIF=0;
    IEC1bits.CNBIE=1;
    
    INTCONbits.INT1EP=1;    //Polaridad de la deteccion del flanco = 1 = subida
    IPC1bits.INT1IP=7;      //prioridad 5,6
    IPC1bits.INT1IS=1;      //Sub prioridad
    IFS0bits.INT1IF=0;      //Bandera
    IEC0bits.INT1IE=1;      //Enable
    __builtin_enable_interrupts();

    while(1){
        if(banderas.Teclado==1){
            banderas.Teclado=0;
            Tecla=Key_deco[tecla_key];
            if(Tecla>=0 && Tecla<=9){
                vect[cnt1]=Tecla+48;
                cnt1++;
            }
            else if(Tecla==15 & cnt1!=0){
                lcd_xy(0,1);
                lcd_puts("                \0");
                vect[cnt1]='\0';
                cnt1=0;
                intencidad=atoi(vect);
                if(intencidad<=100){
                    lcd_xy(1,1);
                    sprintf(msg,"%d\0",intencidad);
                    lcd_puts(msg);
                    lcd_barra(intencidad);
                    batery();
                    lcd_xy(14,1);
                    lcd_dato(7);    
                }
                else{
                    lcd_xy(0,1);
                    lcd_puts(((unsigned char *)"ACCION INVALIDA\0"));
                    intencidad=100;
                }
            }
            else if(Tecla==10 | Tecla==11){
                if(Tecla==10 & intencidad<=99){
                    intencidad++;
                }
                if(Tecla==11 & intencidad>=1){
                    intencidad--;
                }
                lcd_xy(0,1);
                lcd_puts("                \0");
                lcd_xy(1,1);
                sprintf(msg,"%d\0",intencidad);
                lcd_puts(msg);
                lcd_barra(intencidad);
                batery();
                lcd_xy(14,1);
                lcd_dato(7);
            }
        }           
    }       
}
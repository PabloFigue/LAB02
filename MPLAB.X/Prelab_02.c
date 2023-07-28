/*
 * File:   main.c
 * Author: Pablo
 * Ejemplo de uso de la LCD 16x2 en modo 4 bits
 * Se utiliz� y se adaptaron las librer�as de Ligo George 
 * de la p�gina www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
 * Created on 31 de enero de 2020, 11:20 AM
 */

#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include "LCD.h"
#include "ADC_Library.h"
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pic16f887.h>

#define _XTAL_FREQ 8000000
#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RB5
#define D6 RD6
#define D7 RD7

//**************************
//Prototipos de funcion
//**************************
void setup(void);

char palabra;

void __interrupt() isr(void){
       
    if (PIR1bits.ADIF){ // Interrupción del ADC
        PORTC = ADRESH;
        PIR1bits.ADIF = 0; //Se limpia la bandera de Interrupción del ADC
    }
    return;
}

void main(void) {
  unsigned int a;
  setup();    //Configuración inicial
  Lcd_Init();
  adc_init(0);
  while(1)
  {
    adc_read();
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Valor Pot1:");
    Lcd_Set_Cursor(2,1);
    palabra = Lcd_set_value(ADRESH);
    Lcd_Write_String(palabra);
    __delay_ms(2);
  }
    return;
}

void setup(void){
    TRISC = 0;
    PORTC = 0;    
    TRISD = 0;
    
    //OSCILADOR
    OSCCONbits.IRCF = 0b111;    // 8MHz
    OSCCONbits.SCS = 1;         // Utilización del oscilador Interno
    
    //INTERRUPCIÓN GLOBAL
    INTCONbits.GIE = 1;         // Activación Interrupción Global

   
    return;
}

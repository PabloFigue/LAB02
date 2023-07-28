/*
 * File:   LAB_02.c
 * Author: Pablo
 * Implementación de la LCD 16x2 en modo 8 bits
 * Created on 25 de julio de 2023
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

//#include "LCD.h"
#include "LCD_ALL.h"
#include "ADC_Library.h"
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pic16f887.h>

#define _XTAL_FREQ 8000000
#define RS PORTEbits.RE0
#define EN PORTEbits.RE1
#define D0 PORTBbits.RB0
#define D1 PORTBbits.RB1
#define D2 PORTBbits.RB2
#define D3 PORTBbits.RB3
#define D4 PORTBbits.RB4
#define D5 PORTBbits.RB5
#define D6 PORTBbits.RB6 
#define D7 PORTBbits.RB7

//**************************
//Prototipos de funcion
//**************************
void setup(void);

int palabra;

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
  LcdALL_Init();    //Inicializar la LCD
  adc_init(0);      //Inicializar el ADC en el canal 0
  while(1)
  {
    adc_read(); //Verificar la lectura del ADC
    LcdALL_Clear();     //limpiar la pantalla
    LcdALL_Set_Cursor(1,1);     //Setear el cursor en la primera linea.
    LcdALL_Write_String("Valor Pot1:");     //Escribir los títulos.
    LcdALL_Set_Cursor(2,1); //Setear el cursor en la segunda linea.
    palabra = LcdALL_map(ADRESH, 0, 255, 0, 500);   //mapear el valor del potenciometro para mostrar de 0 a 5 volts.
    LcdALL_set_value(palabra);  //Escribir en la pantalla el valor del potenciometro.
    __delay_ms(2);
  }
    return;
}

void setup(void){
    //configuración incial de los puertos.
    ANSEL = 0;
    ANSELH = 0;
    TRISC = 0;
    PORTC = 0;    
    TRISD = 0;
    TRISE = 0;
    
    //OSCILADOR
    OSCCONbits.IRCF = 0b111;    // 8MHz
    OSCCONbits.SCS = 1;         // Utilización del oscilador Interno
    
    //INTERRUPCIÓN GLOBAL
    INTCONbits.GIE = 1;         // Activación Interrupción Global

   
    return;
}

/* 
 * File:   POSTLAB_02.c
 * Author: Pablo Figueroa
 * Aplicación: Control de LCD para mostrar el valor de un potenciometro y comunicación serial
 *
 * Created on 25 de julio de 2023, 5:01 p.m.
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

//Librerias a utilizar
#include "USART_Library.h"
#include "LCD_ALL.h"
#include "ADC_Library.h"
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pic16f887.h>

//Definicion de los puertos del LCD
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

//**************************
// Variables GLobales
//**************************
int mapeado;
int tempo;
int cont;

//*************************
//Vector de Interrupcion
//*************************
void __interrupt() isr(void){
       
    if (PIR1bits.ADIF){ // Interrupción del ADC
        //PORTD = ADRESH;
        PIR1bits.ADIF = 0; //Se limpia la bandera de Interrupción del ADC
    }
    if(RCIF == 1){      // Interrupcion Recepcion de Datos UART
        PORTD = RCREG;
        if (RCREG == 48){   //Si el caracter recibido es igual a 0
        UART_write_string("Voltaje Potenciometro:");    //Escribir un string en pantalla
        UART_set_value(mapeado);    //el mismo valor mapeado escribirlo en pantalla
        }
        cont = UART_read_char();    //verificar si el caracter es + o -
        PIR1bits.RCIF = 0; // Borrar el indicador
    }
    return;
}

void main(void) {
  unsigned int a;
  setup();    //Configuración inicial
  LcdALL_Init();    //Inicializar la LCD
  adc_init(0);      //Configurar el ADC en el canal 0
  UART_RX_config(9600); //Configurar transmision y recepcion de datos por comunicacion serial a 9600 baudios.

  while(1)
  {
    adc_read();     //Verificar la lectura del ADC
    LcdALL_Set_Cursor(1,1);     //Setear el cursor en la primera linea
    LcdALL_Write_String("Pot1:  CPU:"); //Escribir los títulos en la primera linea
    LcdALL_Set_Cursor(2,1); //Setear el cursor en la segunda linea.
    mapeado = LcdALL_map(ADRESH, 0, 255, 0, 500);  //Mapear el valor para obtener el voltaje del potenciometro de 0 a 500
    LcdALL_set_value(mapeado);  //Mostrar en la LCD el valor del potenciometro
    LcdALL_Write_String("   "); //Escribir en pantalla un espacio
    LcdALLb_set_value(cont);    //Mostrar en pantalla el valor del contador
    __delay_ms(2);
  }
    return;
}

void setup(void){
    //Inicializacion de los puertos.
    ANSEL = 0;
    ANSELH = 0;
    //TRISC = 0;
    //PORTC = 0;   
    TRISA = 0;
    PORTA = 0;
    TRISD = 0;
    TRISE = 0;
    PORTD = 0;
    
    //OSCILADOR
    OSCCONbits.IRCF = 0b111;    // 8MHz
    OSCCONbits.SCS = 1;         // Utilización del oscilador Interno
    
    //INTERRUPCIÓN GLOBAL
    INTCONbits.GIE = 1;         // Activación Interrupción Global
    PIE1bits.RCIE = 1;          // Interrupcion RX
    PIR1bits.RCIF = 0;          // limpiar bandera
    INTCONbits.PEIE = 1; // habilitar interrupciones perifericas
   
    return;
}

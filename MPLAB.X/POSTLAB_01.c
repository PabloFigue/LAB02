/* 
 * File:   POSTLAB_01.c
 * Author: pablo
 *
 * Created on 18 de julio de 2023, 11:48 p.m.
 */

//Bits de configuración
#pragma config FOSC = INTRC_NOCLKOUT // Bits de selección del oscilador (Oscilador INTOSCIO: función de E/S en el pin RA6/OSC2/CLKOUT, función de E/S en el pin RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Bit de habilitación del perro guardián (Perro guardián deshabilitado, se puede habilitar mediante el bit SWDTEN del registro WDTCON)
#pragma config PWRTE = OFF      // Bit de habilitación del temporizador de encendido (Temporizador de encendido deshabilitado)
#pragma config MCLRE = OFF      // Bit de selección de la función del pin RE3/MCLR (La función del pin RE3/MCLR es una entrada digital, MCLR está conectado internamente a VDD)
#pragma config CP = OFF         // Bit de protección del código (Protección de código de memoria de programa deshabilitada)
#pragma config CPD = OFF        // Bit de protección de datos (Protección de código de memoria de datos deshabilitada)
#pragma config BOREN = OFF      // Bits de selección del restablecimiento por bajo voltaje (Restablecimiento por bajo voltaje deshabilitado)
#pragma config IESO = OFF       // Bit de selección de conmutación interna/externa (Modo de conmutación interna/externa deshabilitado)
#pragma config FCMEN = OFF      // Bit de habilitación del monitor de reloj a prueba de fallas (Monitor de reloj a prueba de fallas deshabilitado)
#pragma config LVP = OFF        // Bit de habilitación de la programación de voltaje bajo (El pin RB3 tiene E/S digital, se debe utilizar HV en MCLR para la programación)

// CONFIG2
#pragma config BOR4V = BOR40V   // Bit de selección de restablecimiento por bajo voltaje (Restablecimiento por bajo voltaje ajustado a 4.0V)
#pragma config WRT = OFF        // Bits de habilitación de la escritura automática en la memoria de programa Flash (Protección de escritura desactivada)


//**************************
//Librerias
//**************************

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pic16f887.h>
#include "INTERRUPT_Library.h"
#include "ADC_Library.h"
#include "TMR_Library.h"
#include "FourDISP_Library.h"

//**************************
//Prototipos de funcion
//**************************
void setup(void);
//**************************
//Variables Globles 
//**************************
#define _XTAL_FREQ 8000000
//**************************
//Vector de Interrupción
//**************************

void __interrupt() isr(void){
    
    if(T0IF)    //tmr0
    { 
        //PORTD ++;
        change_disp();
        //__delay_ms(1000);
        TMR0_Reset();
        INTCONbits.T0IF = 0;
    }
    
    if (PIR1bits.ADIF){ // Interrupción del ADC
        set_value(ADRESH); 
        //PORTC = ADRESH;
        PIR1bits.ADIF = 0; //Se limpia la bandera de Interrupción del ADC
    }
    
    if (INTCONbits.RBIF){//Interrupción del PORTB
        if (PORTBbits.RB0 == 0) {
            PORTD++;
            while (PORTBbits.RB0 == 0) {    //While antirebote
                ;
            }
        }if (PORTBbits.RB1 == 0) {
            PORTD--;
            while (PORTBbits.RB1 == 0) {    //While antirebote
                ;
            }
        }
        INTCONbits.RBIF = 0; 

    }
    return;
    
}



//**************************
//Funcion principal
//**************************
void main() {
    setup();    //Configuración inicial
    adc_init(1);    //Configuracion del ADC en el canal 1
    TMR0_Init(10, 256); //Configuracion a 10ms y prescaler 256 en el TMR0
    
    while(1){
        adc_read();
        if (ADRESH >= PORTD){   //Se verifica si el ADRESH es mayor al contador
            TRISAbits.TRISA7 = 0;
            PORTAbits.RA7 = 1;
        }else {
            TRISAbits.TRISA7 = 0;
            PORTAbits.RA7 = 0;
        }
    }
}

//**************************
//Funciones  
//**************************
void setup(void){
    
//configuracion de entradas y salidas
    ANSELH = 0; // Configuración entradas analogicas del PUERTO B
    ANSEL = 0;  // Configuración entradas Analogicas/Digiales del Puerto A y E
    
    //CONFIGURACIÓN INICIAL: todos los puertos como salidas.
    TRISA = 0; 
    TRISB = 0;  
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;
    
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    
        
    ioc_init(0);
    ioc_init(1);
    
    //OSCILADOR
    OSCCONbits.IRCF = 0b111;    // 8MHz
    OSCCONbits.SCS = 1;         // Utilización del oscilador Interno
    
    //INTERRUPCIÓN GLOBAL
    INTCONbits.GIE = 1;         // Activación Interrupción Global

   
    return;
}

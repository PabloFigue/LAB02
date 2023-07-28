/* 
 * Libreria de Configuracion del ADC
 * Author: pablo figueroa
 *
 * Created on 18 de julio de 2023, 
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pic16f887.h>
#define _XTAL_FREQ 8000000

int adc_init(int channel){
//Configuración de las interrupciones para el ADC
PIR1bits.ADIF = 0;   // limpiar la bandera de interrupcion del ADC
PIE1bits.ADIE = 1;   // habilitar interrupciones de ADC
INTCONbits.PEIE = 1; // habilitar interrupciones perifericas   

switch (channel) {
    case 0:
        channel = 0b00000001;
        ANSEL = channel;
        TRISA = channel;
        ADCON0bits.CHS = 0b0000;
        break;
    case 1:
        channel = 0b00000010;
        ANSEL = channel;
        TRISA = channel;
        ADCON0bits.CHS = 0b0001;
        break;
    case 2:
        channel = 0b00000100;
        ANSEL = channel;
        TRISA = channel;
        ADCON0bits.CHS = 0b0010;
        break;
    case 3:
        channel = 0b00001000;
        ANSEL = channel;
        TRISA = channel;
        ADCON0bits.CHS = 0b0011;
        break;
    case 4:
        channel = 0b00010000;
        ANSEL = channel;
        TRISA = 0b00100000;
        ADCON0bits.CHS = 0b0100;
        break;
    case 5:
        channel = 0b00100000;
        ANSEL = channel;
        TRISE = 0b001;
        ADCON0bits.CHS = 0b0101;
        break;
    case 6:
        channel = 0b01000000;
        ANSEL = channel;
        TRISE = 0b010;
        ADCON0bits.CHS = 0b0110;
        break;
    case 7:
        channel = 0b10000000;
        ANSEL = channel;
        TRISE = 0b100;
        ADCON0bits.CHS = 0b0111;
        break;
    default:
        ANSEL = 0b00000000;
        // Handle invalid channel value here, if needed.
        break;
}
    //Configuracion ADC

    ADCON0bits.ADCS = 0b10;     //Conversion Clock
    ADCON1bits.ADFM = 0;    //justificado a la izquierda
    ADCON1bits.VCFG0 = 0;   //Vdd
    ADCON1bits.VCFG1 = 0;   //Vss
    ADCON0bits.ADON = 1;    //ADC enable
    ADIF =  0;
    __delay_ms(5);
}

int adc_read(){
    if (ADCON0bits.GO == 0){//Revisión si no está funcionando el ADC
        ADCON0bits.GO = 1; //iniciar la conversion del ADC0.
        __delay_ms(2);
    }    
    }
    
int adc_change_channel(int channel){
switch (channel) {
    case 0:
        channel = 0b00000001;
        ANSEL = channel;
        TRISA = channel;
        ADCON0bits.CHS = 0b0000;
        break;
    case 1:
        channel = 0b00000010;
        ANSEL = channel;
        TRISA = channel;
        ADCON0bits.CHS = 0b0001;
        break;
    case 2:
        channel = 0b00000100;
        ANSEL = channel;
        TRISA = channel;
        ADCON0bits.CHS = 0b0010;
        break;
    case 3:
        channel = 0b00001000;
        ANSEL = channel;
        TRISA = channel;
        ADCON0bits.CHS = 0b0011;
        break;
    case 4:
        channel = 0b00010000;
        ANSEL = channel;
        TRISA = 0b00100000;
        ADCON0bits.CHS = 0b0100;
        break;
    case 5:
        channel = 0b00100000;
        ANSEL = channel;
        TRISE = 0b001;
        ADCON0bits.CHS = 0b0101;
        break;
    case 6:
        channel = 0b01000000;
        ANSEL = channel;
        TRISE = 0b010;
        ADCON0bits.CHS = 0b0110;
        break;
    case 7:
        channel = 0b10000000;
        ANSEL = channel;
        TRISE = 0b100;
        ADCON0bits.CHS = 0b0111;
        break;
    default:
        ANSEL = 0b00000000;
        // Handle invalid channel value here, if needed.
        break;
    }   
}
int adc_get_channel(){
    return ADCON0bits.CHS;
}
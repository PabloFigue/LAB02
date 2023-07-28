/* 
 * Libreria de Configuracion de las interrupciones de los Timer
 * Author: pablo figueroa
 *
 * Created on 18 de julio de 2023, 
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pic16f887.h>

int TMR0_Value;

void TMR0_Init(int periodo_ms, int prescaler){
    int frecuencia = 4000000;
    //Formula para calcular el valor de TMR0 a partir del periodo deseado.
    TMR0_Value = (int)(256-((periodo_ms/1000)*frecuencia/(prescaler*4))); 
    
    //Configuracion de la interrupcion del TMR0
    INTCONbits.T0IF = 0; // Limpiar la bandera de interrupcion del TMR0
    INTCONbits.T0IE = 1; // Habilitacion de la interrupcion del TMR0
    //configuración tmr0
    OPTION_REGbits.T0CS = 0;        //Selector del CLOCK del TMR0
    OPTION_REGbits.PSA = 0;         //Selector del Prescaler para TMR0
    OPTION_REGbits.PS = prescaler;  //Prescaler 
    TMR0 = TMR0_Value;             //Inicialización del Conteo TMR0
}

void TMR0_Reset(){
    TMR0 = TMR0_Value;
}

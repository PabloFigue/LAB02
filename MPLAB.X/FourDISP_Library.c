/* 
 * Libreria de Configuracion para multiplexar displays
 * Author: pablo figueroa
 *
 * Created on 18 de julio de 2023, 
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pic16f887.h>

int unidades, decenas, centenas, miles, value_disp;

void set_value(int byte_value){
    miles = (byte_value/100);
    centenas = ((byte_value / 100)%10);       // Calcular las centenas 
    decenas = ((byte_value/10)%10);    // Calcular las decenas 
    unidades = (byte_value%10);         // Calcular las unidades 
}

void change_disp(){
    if (PORTE == 0b000){
        PORTE = 0b001;
        value_disp = centenas;
    }else if (PORTE == 0b001){
        PORTE = 0b010;
        value_disp = decenas;
    }else if (PORTE == 0b010){
        PORTE = 0b100;
        value_disp = unidades;
    }else {
        PORTE = 0b000;
    }
    if (value_disp == 0){
        value_disp = 0b00111111;
    }else if (value_disp == 1){
        value_disp = 0b00000110;
    }else if (value_disp == 2){
        value_disp = 0b01011011;
    }else if (value_disp == 3){
        value_disp = 0b01001111;
    }else if (value_disp == 4){
        value_disp = 0b01100110;
    }else if (value_disp == 5){
        value_disp = 0b01101101;
    }else if (value_disp == 6){
        value_disp = 0b01111101;
    }else if (value_disp == 7){
        value_disp = 0b00000111;
    }else if (value_disp == 8){
        value_disp = 0b01111111;
    }else if (value_disp == 9){
        value_disp = 0b01101111;
    }else{
        value_disp = 0b00111111;
    }
    PORTC = value_disp;
}
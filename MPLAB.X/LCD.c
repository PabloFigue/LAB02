/* 
 * File: LCD.c  
 * Se utiliz� y se adaptaron las librer�as de Ligo George 
 * de la p�gina www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
 * Revision history: 
 */

//LCD Functions Developed by electroSome

#include "LCD.h"

void Lcd_Port(char a) {
    if (a & 1)
        D4 = 1;
    else
        D4 = 0;

    if (a & 2)
        D5 = 1;
    else
        D5 = 0;

    if (a & 4)
        D6 = 1;
    else
        D6 = 0;

    if (a & 8)
        D7 = 1;
    else
        D7 = 0;
}

void Lcd_Cmd(char a) {
    RS = 0; // => RS = 0 // Dato en el puerto lo va interpretar como comando
    Lcd_Port(a);
    EN = 1; // => E = 1
    __delay_ms(4);
    EN = 0; // => E = 0
}

void Lcd_Clear(void) {
    Lcd_Cmd(0);
    Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b) {
    char temp, z, y;
    if (a == 1) {
        temp = 0x80 + b - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        Lcd_Cmd(z);
        Lcd_Cmd(y);
    } else if (a == 2) {
        temp = 0xC0 + b - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        Lcd_Cmd(z);
        Lcd_Cmd(y);
    }
}

void Lcd_Init(void) {
    Lcd_Port(0x00);
    __delay_ms(20);
    Lcd_Cmd(0x03);
    __delay_ms(5);
    Lcd_Cmd(0x03);
    __delay_ms(11);
    Lcd_Cmd(0x03);
    /////////////////////////////////////////////////////
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x08);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x0C);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x06);
}

void Lcd_Write_Char(char a) {
    char temp, y;
    temp = a & 0x0F;
    y = a & 0xF0;
    RS = 1; // => RS = 1
    Lcd_Port(y >> 4); //Data transfer
    EN = 1;
    __delay_us(40);
    EN = 0;
    Lcd_Port(temp);
    EN = 1;
    __delay_us(40);
    EN = 0;
}

void Lcd_Write_String(char *a) {
    int i;
    for (i = 0; a[i] != '\0'; i++)
        Lcd_Write_Char(a[i]);
}

void Lcd_Shift_Right(void) {
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x0C);
}

void Lcd_Shift_Left(void) {
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x08);
}

char Lcd_set_value(int byte_value){
    char string[3];
    int miles = (byte_value/100);
    int centenas = ((byte_value / 100)%10);       // Calcular las centenas 
    int decenas = ((byte_value/10)%10);    // Calcular las decenas 
    int unidades = (byte_value%10);         // Calcular las unidades 
    
    int tempo;
    
    for (int i = 0; i <= 2; i++){
        if (i==0){
            tempo=centenas;
        }else if (i==1){
            tempo=decenas;
        }else if (i==2){
            tempo=unidades;
        }
        
        if (tempo == 0){
            string[i] = '0';
        }else if (tempo == 1){
            string[i] = '1';
        }else if (tempo == 2){
            string[i] = '2';
        }else if (tempo == 3){
            string[i] = '3';
        }else if (tempo == 4){
            string[i] = '4';
        }else if (tempo == 5){
            string[i] = '5';
        }else if (tempo == 6){
            string[i] = '6';
        }else if (tempo == 7){
            string[i] = '7';
        }else if (tempo == 8){
            string[i] = '8';
        }else if (tempo == 9){
            string[i] = '9';
        }else{
            string[i] = '0';
        }
    }
    return string;
}

int Lcd_map(int valor, int rango_min, int rango_max, int nuevo_min, int nuevo_max){
    int nuevo_valor = nuevo_min + (valor - rango_min)*(nuevo_max - nuevo_min)/(rango_max - rango_min);
    return nuevo_valor;
}
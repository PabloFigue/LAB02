/* 
 * File: LCD_ALL.h
 * Librería para controlar un LCD en modo de 8 bits.
 */

#ifndef LCD_ALL_H
#define LCD_ALL_H

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 8000000
#endif

#include <xc.h>

// Definiciones de pines de control y datos del LCD
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

void LcdALL_Port(char a);
void LcdALL_Cmd(char a);
void LcdALL_Clear(void);
void LcdALL_Set_Cursor(char a, char b);
void LcdALL_Init(void);
void LcdALL_Write_Char(char a);
void LcdALL_Write_String(char *a);
void LcdALL_Shift_Right(void);
void LcdALL_Shift_Left(void);
char LcdALL_set_value(int byte_value);
char LcdALLb_set_value(int byte_value);
float LcdALL_map(float valor, float rango_min, float rango_max, float nuevo_min, float nuevo_max);

#endif /* LCD_ALL_H */
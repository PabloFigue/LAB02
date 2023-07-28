/* 
 * File:   TMR_Library.h
 * Author: pablo
 *
 * Created on 19 de julio de 2023, 12:15 a.m.
 */

#ifndef TMR_LIBRARY_H
#define	TMR_LIBRARY_H

#ifdef	__cplusplus
extern "C" {
#endif

void TMR0_Init(int periodo_ms, int prescaler);
void TMR0_Reset();

#ifdef	__cplusplus
}
#endif

#endif	/* TMR_LIBRARY_H */


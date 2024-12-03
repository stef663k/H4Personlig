/*
 * UART.h
 * Created: 25-02-2015 20:8:13
 * Version: 1.0
 * Author: alkj
 */ 
#ifndef __UART_H__
#define __UART_H__

#include <stdio.h>
//#include "Arduino.h"

#define F_CPU 16000000UL

#define BAUD 9600UL

#define UART_NORMAL_MODE
#ifdef UART_NORMAL_MODE
#define MyUBRR (unsigned int)(F_CPU/(16*BAUD) -1)   // normal mode
#else
#define MyUBRR (unsigned int)(F_CPU/(8*BAUD) -1)   // *2 mode
#endif

// Man beh�ver ikke at bruge n�gleordet extern foran funktions erkl�ringer lavet i header
// filer. Man nogle foretr�kker det for at g�re opm�rksom p�, at vi ikke definerer selve
// funktionen i header filen, men blot laver en forward erkl�ring af denne, s�ledes
// at andre c filer end den c fil, hvor funktionerne er erkl�ret (i tilf�ldet her UART.c),
// kan n� disse.

extern void RS232Init( void);

extern int uart_getch(FILE*stream);

extern int uart_putch(char ch, FILE*stream);

extern void SetupOutputStreamToUart(void);

extern void SetupInputStreamToUart(void);

extern void Enable_UART_Receive_Interrupt();
extern void Disable_UART_Receive_Interupt();

extern void SetupFunctionCallbackPointer(Function_Pointer_With_One_Char_Parameter
                                         Function_To_Callback);

#define AVR8_UART_NUMBER       0

#endif // __UART_H__

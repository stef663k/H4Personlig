#ifndef UART_H_
#define UART_H_

#include <stdio.h>
#include <stdint.h>
#include "../ProjectDefines.h"


#define BAUD 9600UL

#define UART_NORMAL_MODE
#ifdef UART_NORMAL_MODE
#define MyUBRR (unsigned int)(F_CPU/(16*BAUD) - 1)
#else
#define MyUBRR (unsigned int)(F_CPU/(8*BAUD) - 1)
#endif

extern void RS232Init(void);
extern int uart_getch(FILE* stream);
extern int uart_putch(char ch, FILE* stream);
extern void Enable_UART_Receive_Interrupt();
extern void Disable_UART_Receive_Interrupt();
void setupFunctionCallPointer(Function_Pointer_With_One_Char_Parameters);
void UART_PrintChar(char c);
void UART_PrintString(const char* str);
void UART_PrintHex(uint8_t value);
void UART_PrintBinary(uint8_t value);
int UART_BufferGet(UART_Buffer* buf, char* data);
void UART_BufferPut(UART_Buffer* buf, char data);

 
void HandleUARTCommand(char command, uint8_t bitPosition);

#endif /* UART_H_ */

#include "UART.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "ProjectDefines.h"
#include "Main.h"
#define F_CPU 16000000UL
#define BAUD 9600UL
#define MyUBRR ((F_CPU / (16UL * BAUD)) - 1)


static FILE uart_output = FDEV_SETUP_STREAM(uart_putch, NULL, _FDEV_SETUP_WRITE);
static FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getch, _FDEV_SETUP_READ);

void RS232Init(void) {
	uint16_t ubrr = MyUBRR;
	UBRRL = (unsigned char)(ubrr & 0xff);
	UBRRH = (unsigned char)(ubrr >> 8);
	
	#ifdef UART_NORMAL_MODE
	UCSRA = 0x00;
	#else
	UCSRA = (1 << U2X);
	#endif

	UCSRB = (1 << RXEN) | (1 << TXEN);
	UCSRC = (1 << UCSZ1) | (1 << UCSZ0);

	stdout = &uart_output;
	stdin = &uart_input;
}

void Enable_UART_Receive_Interrupt() {
	UCSR0B |= (1 << RXCIE);
}

void Disable_UART_Receive_Interrupt() {
	UCSR0B &= ~(1 << RXCIE);
}

int uart_getch(FILE* stream) {
	while (!(UCSRA & (1 << RXC)));
	return UDR;
}

int uart_putch(char ch, FILE* stream) {
	while (!(UCSRA & (1 << UDRE)));
	UDR = ch;
	return 0;
}

ISR(USART_RX_vect) {
	char ReceivedByte = UDR;
	ReceiveNewTimeoutValue(&ReceivedByte);
}

void UART_PrintString(const char* str) {
	while (*str) {
		uart_putch(*str++, NULL);
	}
}

void UART_PrintChar(char c) {
	uart_putch(c, NULL);
}

void UART_PrintHex(uint8_t value) {
	const char hexDigits[] = "0123456789ABCDEF";
	uart_putch(hexDigits[value >> 4], stdout); // Send high nibble
	uart_putch(hexDigits[value & 0x0F], stdout); // Send low nibble
}

void UART_PrintBinary(uint8_t value) {
	char binaryStr[9];
	for(int i = 0; i < 8; i++){
		binaryStr[i] = (value & (1 << (7 - i))) ? '1' : '0';
	}
	binaryStr[8] = '\0';
	UART_PrintString(binaryStr);
	UART_PrintString("\n");
}


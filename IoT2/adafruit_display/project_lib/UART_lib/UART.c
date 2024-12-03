#include "UART.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "../../main.h"
#include "../ProjectDefines.h"
#include "../../main.h"

#define F_CPU 16000000UL
#define BAUD 9600UL
#define MyUBRR ((F_CPU / (16UL * BAUD)) - 1)
#define Upper_Lower_Bit_Position 5
#define Upper_Lower_Bit_Value (1 << Upper_Lower_Bit_Position)

UART_Buffer uart_rx_buffer = {.head = 0, .tail = 0};
volatile bool UART_BufferOverflow = false; 
static bool overflow_logged = false;


static FILE uart_output = FDEV_SETUP_STREAM(uart_putch, NULL, _FDEV_SETUP_WRITE);
static FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getch, _FDEV_SETUP_READ);
static Function_Pointer_With_One_Char_Parameters callback_function_pointer = NULL;

void setupFunctionCallPointer(Function_Pointer_With_One_Char_Parameters call_function_pointer) {
	callback_function_pointer = call_function_pointer;
}

void RS232Init(void) {
	uint16_t ubrr = MyUBRR;
	UBRR0H = (unsigned char)(ubrr >> 8);  
	UBRR0L = (unsigned char)(ubrr);      
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);  
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  
	stdout = &uart_output;  
	stdin = &uart_input;    
}


void Enable_UART_Receive_Interrupt() {
	UCSR1B |= (1 << RXCIE1);
}

void Disable_UART_Receive_Interrupt() {
	UCSR1B &= ~(1 << RXCIE1);
}

int uart_getch(FILE* stream) {
	while (!(UCSR0A & (1 << RXC0)));  
	return UDR0;  
}

int uart_putch(char ch, FILE* stream) {
	while (!(UCSR0A & (1 << UDRE0))); 
	UDR0 = ch;  
	return 0;
}


void UART_BufferPut(UART_Buffer *buffer, char data) {
	uint8_t nextHead = (buffer->head + 1) % UART_BUFFER_SIZE;

	printf("Put: Head=%d, Tail=%d, NextHead=%d\n", buffer->head, buffer->tail, nextHead);

	if (nextHead != buffer->tail) {  
		buffer->buffer[buffer->head] = data;
		buffer->head = nextHead;
		printf("Put: Data '%c' added to buffer\n", data);
		} else {
		if (!overflow_logged) {  
			printf("Buffer overflow!\n");
			UART_BufferOverflow = true;
			overflow_logged = true;    
		}
	}
}

int UART_BufferGet(UART_Buffer *buffer, char *data) {
	if (buffer->tail != buffer->head) {  
		*data = buffer->buffer[buffer->tail];
		buffer->tail = (buffer->tail + 1) % UART_BUFFER_SIZE;
		printf("Get: Data '%c' retrieved from buffer\n", *data);
		printf("Get: Head=%d, Tail=%d\n", buffer->head, buffer->tail);
		return 0;  
		} else {
		printf("Buffer is empty!\n");
		return -1;  
	}
}

int UART_BufferAvailable(UART_Buffer* buf) {
	int available = (buf->head >= buf->tail) ?
	(buf->head - buf->tail) :
	(UART_BUFFER_SIZE - buf->tail + buf->head);
	printf("Buffer available: %d\n", available);
	return available;
}

void UART_BufferClear(UART_Buffer* buf) {
	cli(); 
	buf->head = 0;
	buf->tail = 0;
	sei();  
	printf("Buffer cleared.\n");
}

bool UART_BufferIsFull(UART_Buffer* buf) {
	return ((buf->head + 1) % UART_BUFFER_SIZE) == buf->tail;
}

void UART_DebugBufferStatus(UART_Buffer* buf) {
	printf("Buffer status: Head=%d, Tail=%d, Available=%d\n", buf->head, buf->tail, UART_BufferAvailable(buf));
	PrintBufferContents(buf);  
}

void PrintBufferContents(UART_Buffer* buf) {
	printf("Buffer Contents: ");
	for (int i = 0; i < UART_BUFFER_SIZE; ++i) {
		printf("%c ", buf->buffer[i]);
	}
	printf("\nHead: %d, Tail: %d\n", buf->head, buf->tail);
}


ISR(USART0_RX_vect) {
	char ReceivedChar = UDR0;  // Read received character from USART0
	printf("ISR0 received: %c\n", ReceivedChar);  // Debug message
	UART_BufferPut(&uart_rx_buffer, ReceivedChar);
	if (callback_function_pointer != NULL) {
		callback_function_pointer(ReceivedChar);
	}
}


void UART_PrintString(const char* str) {
	while (*str) {
		uart_putch(*str++, NULL);
	}
}

void UART_PrintChar(char c) {
	uart_putch(c, NULL);
}

void UART_PrintInt(int value) {
	char buffer[12]; // Enough for a 32-bit signed integer
	sprintf(buffer, "%d", value);
	UART_PrintString(buffer);
	UART_PrintString("\n");
}

void UART_PrintHex(uint8_t value) {
	const char hexDigits[] = "0123456789ABCDEF";
	uart_putch(hexDigits[value >> 4], stdout); // Send high nibble
	uart_putch(hexDigits[value & 0x0F], stdout); // Send low nibble
}

void UART_PrintBinary(uint8_t value) {
	char binaryStr[9];
	for (int i = 0; i < 8; i++) {
		binaryStr[i] = (value & (1 << (7 - i))) ? '1' : '0';
	}
	binaryStr[8] = '\0';
	UART_PrintString(binaryStr);
	UART_PrintString("\n");
}

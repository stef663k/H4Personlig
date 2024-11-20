#include "UART.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../../main.h"
#include "../ProjectDefines.h"
#include "../../main.h"
#define F_CPU 16000000UL
#define BAUD 9600UL
#define MyUBRR ((F_CPU / (16UL * BAUD)) - 1)
#define Upper_Lower_Bit_Position 5
#define Upper_Lower_Bit_Value (1 << Upper_Lower_Bit_Position)

UART_Buffer uart_rx_buffer = {.head = 0, .tail = 0};

static FILE uart_output = FDEV_SETUP_STREAM(uart_putch, NULL, _FDEV_SETUP_WRITE);
static FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getch, _FDEV_SETUP_READ);
static Function_Pointer_With_One_Char_Parameters callback_function_pointer = NULL;

void setupFunctionCallPointer(Function_Pointer_With_One_Char_Parameters call_function_pointer){
	callback_function_pointer = call_function_pointer;
}

void RS232Init(void) {
	uint16_t ubrr = MyUBRR;
	UBRR1L = (unsigned char)(ubrr & 0xff);
	UBRR1H = (unsigned char)(ubrr >> 8);
	
	UCSR1A = 0x00;
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);
	UCSR1C = (1 << UCSZ1) | (1 << UCSZ0);

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
	while (!(UCSR1A & (1 << RXC1)));
	return UDR1;
}

int uart_putch(char ch, FILE* stream) {
	while (!(UCSR1A & (1 << UDRE1)));
	UDR1 = ch;
	return 0;
}
void UART_BufferPut(UART_Buffer* buf, char data) {
	uint8_t next = (buf->head + 1) % UART_BUFFER_SIZE;
	if (next != buf->tail) {
		buf->buffer[buf->head] = data;
		buf->head = next;
		#ifdef DEBUG
			printf("BufferPut: Stored '%c' at index %d\n", data, buf->head);
		#endif
	} 
	else {
		printf("BufferPut: Buffer is full, cannot store '%c'\n", data);
	}

}


int UART_BufferGet(UART_Buffer* buf, char* data) {
    if (buf->head == buf->tail) {
        printf("BufferGet: Buffer is empty!\n");
        return -1; 
    } else {
        *data = buf->buffer[buf->tail];  
        printf("BufferGet: Retrieved '%c' from index %d\n", *data, buf->tail);
        buf->tail = (buf->tail + 1) % UART_BUFFER_SIZE;  
        return 0;  
    }
}

int UART_BufferAvailable(UART_Buffer* buf) {
	return (buf->head >= buf->tail) ?
	(buf->head - buf->tail) :
	(UART_BUFFER_SIZE - buf->tail + buf->head);
}

void PrintBufferContents(UART_Buffer* buf) {
    printf("Buffer Contents: ");
    for (int i = 0; i < UART_BUFFER_SIZE; ++i) {
        printf("%c ", buf->buffer[i]);
    }
    printf("\nHead: %d, Tail: %d\n", buf->head, buf->tail);
}


ISR(USART_RX_vect) {
	char ReceivedByte = UDR1;
	ReceiveNewTimeoutValue(&ReceivedByte);
}

void ConvertReceivedChar(char *ReceivedChar)
{

	if ( ((*ReceivedChar >= 0x41) && (*ReceivedChar <= 0x5D)) ||
	((*ReceivedChar >= 0x61) && (*ReceivedChar <= 0x7D)))
	{
		*ReceivedChar = *ReceivedChar ^ Upper_Lower_Bit_Value;
	}

}



ISR(USART1_RX_vect)
{
	char ReceivedChar = UDR1;
	UART_BufferPut(&uart_rx_buffer, ReceivedChar);
	if(callback_function_pointer != NULL){
		callback_function_pointer(ReceivedChar);
	}
	//WriteReceivedCharacterFromUARTInDisplay(ReceivedChar);
	
	printf("RecivedChar: %c \n", ReceivedChar);
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


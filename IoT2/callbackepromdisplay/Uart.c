/*
 * Uart.c
 *
 * Created: 15-01-2018 09:44:48
 *  Author: ltpe
 */ 

 #include "UART.h"
 #include <stdio.h>
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include "ProjectDefines.h"
 #include "Main.h"

 static FILE uart_output = FDEV_SETUP_STREAM(uart_putch, NULL, _FDEV_SETUP_WRITE);
 static FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getch, _FDEV_SETUP_READ);


 void RS232Init(void)
 {
	 // Set baud rate
	 UBRRL = (unsigned char)(MyUBRR & 0xff);
	 UBRRH = (unsigned char)(MyUBRR>>8);
	 #ifdef UART_NORMAL_MODE
	 UCSRA = 0x00;
	 #else
	 UCSRA = 1<<U2X; // Set *2 mode
	 #endif
	 UCSRB = (1<<RXEN) | (1<<TXEN);  //0x18 , enable receive and transmit
	 UCSRC =  (1<<UCSZ1) | (1<<UCSZ0); // 8 data bit 1 stop bit
	 stdout = &uart_output;
	 stdin = &uart_input;
 }

 void Enable_UART_Receive_Interrupt()
 {
	 UCSRB |= (1 << RXCIE); // Enable the USART Recieve Complete interrupt (USART_RXC)
 }

 void Disable_UART_Receive_Interupt()
 {
	UCSRB &= ~(1 << RXCIE); // Disable the USART Recieve Complete interrupt (USART_RXC)
 }

 int uart_getch(FILE* stream)
 {
	 while( !(UCSRA & (1<<RXC)))  ; // do nothing but wait
	 return( UDR);
 }

 int uart_putch(char ch, FILE* stream)
 {
	 while( !(UCSRA & (1<<UDRE))) ;
	 UDR = ch;
	 return 0;
 }

 ISR(USR_Vect_Num)
 {
	 char ReceivedByte;
	 ReceivedByte = UDR;
	 //ConvertReceivedChar(&ReceivedByte);
	 ReceiveNewTimeoutValue(&ReceivedByte);
	 UDR = ReceivedByte; // Echo back the received byte to the computer
}
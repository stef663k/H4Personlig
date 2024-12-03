#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "bitwise_operations.h"
#include "UART.h"
#include "state_machine.h"
#include "ExternalInterrupt.h"

volatile uint16_t interruptCount = 0;
State currentState = Modtag_Adresse;
uint8_t address = 0x00;

int main(void) {
	RS232Init();
	Enable_UART_Receive_Interrupt();
	
	sei(); // Enable global interrupts
	AttachAndEnableExternalInterrupt(EXTERNAL_INTERRUPT_0, MyExternalInterruptHandler, FALLING_EDGE_GENERATE_INTERRUPT);
	
	// Set D2 (INT0) as input
	DDRD &= ~(1 << DDD2);
	
	// Set D13 as output
	DDRB |= (1 << DDRB1) | (1 << DDRB2) | (1 << DDRB3);
	
	while (1) {
		char receivedChar = uart_getch(NULL);
		char receivedByte = UDR1;
		PORTB ^= (1 << PORTB5);
		_delay_ms(1000);
		handle_state_machine(&currentState, receivedByte, &address);
	}

	return 0;
}

ISR(USART1_RX_vect) {
	if (UCSR1A & ((1 << FE1) | (1 << DOR1))) {
		UART_PrintString("UART Error: ");
		if (UCSR1A & (1 << FE1)) {
			UART_PrintString("Framing Error ");
		}
		if (UCSR1A & (1 << DOR1)) {
			UART_PrintString("Data Overrun ");
		}
		UART_PrintString("\n");
		
		UCSR1A |= (1 << FE1) | (1 << DOR1);
		} else {
		char receivedByte = UDR1;
		
		handle_state_machine(&currentState, receivedByte, &address);
	}
}
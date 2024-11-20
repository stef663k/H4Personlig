#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "bitwise_operations.h"
#include "UART.h"
#include "state_machine.h"

// Global variables
State currentState = Modtag_Adresse;
uint8_t address = 0x00;

uint16_t Add8BitNumbers(uint8_t Number1, uint8_t Number2) {
	return (Number1 + Number2);
}

void UART_PrintUCSR1A() {
	uint8_t ucsr1a_value = UCSR1A;
	UART_PrintString("UCSR1A value: ");
	UART_PrintHex(ucsr1a_value);
	UART_PrintString("\n");
}

int main(void) {
	RS232Init();
	Enable_UART_Receive_Interrupt();
	sei();  // Enable global interrupts

	while (1) {
		// Main loop remains empty as processing is handled in the interrupt
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
		} else {
		char receivedByte = UDR1;
		handle_state_machine(&currentState, receivedByte, &address);
	}
}

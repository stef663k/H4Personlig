#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ExternalInterrupt.h"
#include "ProjectDefines.h"
#include "UART.h"


int main(void) {
	RS232Init();
	Timer1_Init();
	
	DDRB |= (1 << LED_PINBUT);
	PORTB |= (1 << LED_PINBUT);
	
	DDRD &= ~(1 << BUTTON_PIN);
	PORTD |= (1 << BUTTON_PIN);

	EICRA = (1 << ISC01) | (1 << ISC00);  
	EIMSK = (1 << INT0);
	

	sei();  

	while (1) {
		processInterrupts();
	}

	return 0;
}
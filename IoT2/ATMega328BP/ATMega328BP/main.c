//#include <util/delay.h>
//#include <avr/interrupt.h>
//#include <avr/io.h>
//#include "bitwise_operations.h"
//#include "UART.h"
//
//uint16_t Add8BitNumbers(uint8_t Number1, uint8_t Number2) {
	//return (Number1 + Number2);
//}
//
//int main(void) {
	//RS232Init();
	//_delay_ms(100);
//
	//uint8_t Var1 = 0xF8;
	//uint8_t Var2 = 0x01;
//
//
	//sei();
//
	//simulateBitSetting(Var1);
//
	//UART_PrintString("Hello UART!\n");
//
	//while (1) {
//
	//}
//
	//return 0; 
//}
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "bitwise_operations.h"
#include "UART.h"
#include "state_machine.h"


uint16_t Add8BitNumbers(uint8_t Number1, uint8_t Number2) {
	return (Number1 + Number2);
}

int main(void) {
	RS232Init();
	_delay_ms(100);
	
	sei();
	Enable_UART_Receive_Interrupt();
	
	State currentState = Modtag_Adresse;
	uint8_t address = 0x00;

	while (1) {
		if(UCSR0A  & (1 << RXC0)){
			char recviedChar = uart_getch(NULL);
			handle_state_machine(&currentState, recviedChar, &address);
		}
	}

	return 0;
}

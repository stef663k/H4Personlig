#include "bitwise_operations.h"
#include "UART.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
	Modtag_Adresse,
	Modtag_Bit_Position_I_Adresse,
	Modtag_Bit_Position_Vaerdi
} State;

void handle_state_machine(State *currentState, char recivedChar, uint8_t *address) {
	static char hexBuffer[3] = {0};
	static uint8_t hexIndex = 0;
	
	UART_PrintString("Recieved Char: ");
	UART_PrintHex((uint8_t)recivedChar);
	UART_PrintString("\n");

	switch (*currentState) {
		case Modtag_Adresse:
		if (recivedChar == ':') {
			*address = (uint8_t)strtol(hexBuffer, NULL, 16);
			
			UART_PrintString("Received address: 0x");
			UART_PrintHex(*address); // Print the address in hexadecimal
			UART_PrintString("\n");

			// Reset for the next address
			hexIndex = 0;
			hexBuffer[0] = '\0';
			*currentState = Modtag_Bit_Position_I_Adresse;
		}
		else if (isxdigit(recivedChar) && hexIndex < 2) {
			hexBuffer[hexIndex++] = recivedChar;
			hexBuffer[hexIndex] = '\0';
		}
		break;

		case Modtag_Bit_Position_I_Adresse:
		UART_PrintString("Enter bit position for address: 0x");
		UART_PrintHex(*address);
		UART_PrintString("\n");

		*currentState = Modtag_Bit_Position_Vaerdi;
		break;

		case Modtag_Bit_Position_Vaerdi:
		UART_PrintString("Enter bit value (0 or 1) for position\n");
		
		*currentState = Modtag_Adresse;  // Reset to wait for the next address
		break;

		default:
		UART_PrintString("Unknown state\n");
		break;
	}
}

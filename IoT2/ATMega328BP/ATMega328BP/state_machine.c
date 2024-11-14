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
	static char hexBuffer[3] = {0};  // Buffer for two hex characters and null terminator
	static uint8_t hexIndex = 0;

	UART_PrintString("Received Char: ");
	UART_PrintHex((uint8_t)recivedChar);
	UART_PrintString("\n");

	UART_PrintString("Current State: ");
	switch (*currentState) {
		case Modtag_Adresse:
		UART_PrintString("Modtag_Adresse\n");
		break;
		case Modtag_Bit_Position_I_Adresse:
		UART_PrintString("Modtag_Bit_Position_I_Adresse\n");
		break;
		case Modtag_Bit_Position_Vaerdi:
		UART_PrintString("Modtag_Bit_Position_Vaerdi\n");
		break;
		default:
		UART_PrintString("Unknown State\n");
		break;
	}

	switch (*currentState) {
		case Modtag_Adresse:
		if (recivedChar == ':') {
			// Convert the buffer to the address and print it
			*address = (uint8_t)strtol(hexBuffer, NULL, 16);

			UART_PrintString("Received address: 0x");
			UART_PrintHex(*address);
			UART_PrintString("\n");

			// Reset buffer for next address
			hexIndex = 0;
			hexBuffer[0] = '\0';

			// Transition to the next state
			*currentState = Modtag_Bit_Position_I_Adresse;
			} else if (isxdigit(recivedChar) && hexIndex < 2) {
			// Fill the hexBuffer with received characters
			hexBuffer[hexIndex++] = recivedChar;
			hexBuffer[hexIndex] = '\0';  // Ensure null termination
			} else {
			UART_PrintString("Unexpected character received: ");
			UART_PrintChar(recivedChar);
			UART_PrintString("\n");
		}
		break;

		case Modtag_Bit_Position_I_Adresse:
		if (isxdigit(recivedChar)) {
			uint8_t bitPosition = recivedChar - '0'; 
			UART_PrintString("Enter bit position for address: 0x");
			UART_PrintHex(bitPosition);
			UART_PrintString("\n");

			*currentState = Modtag_Bit_Position_Vaerdi;
			} else {
			UART_PrintString("Invalid bit position, please enter a valid position (0-9)\n");
		}
		break;

		case Modtag_Bit_Position_Vaerdi:
		if (recivedChar == '0' || recivedChar == '1') {
			UART_PrintString("Valid bit value received\n");

			*currentState = Modtag_Adresse;
			} else {
			UART_PrintString("Invalid bit value, please enter 0 or 1\n");
		}
		break;

		default:
		UART_PrintString("Unknown state\n");
		break;
	}
}


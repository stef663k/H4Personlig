#include "bitwise_operations.h"
#include "UART.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ExternalInterrupt.h"

typedef enum {
	Modtag_Adresse,
	Modtag_Bit_Position_I_Adresse,
	Modtag_Bit_Position_Vaerdi
} State;

void handle_state_machine(State *currentState, char recivedChar, uint8_t *address) {
	static char hexBuffer[3] = {0};  
	static uint8_t hexIndex = 0;
	static uint8_t bitPosition = 0;

	UART_PrintString("Received Char (Hex): ");
	UART_PrintHex((uint8_t)recivedChar);  
	UART_PrintString(" ASCII Value: ");
	UART_PrintInt((uint8_t)recivedChar);  
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
			*address = (uint8_t)strtol(hexBuffer, NULL, 16);

			UART_PrintString("Received address: 0x");
			UART_PrintHex(*address);
			UART_PrintString("\n");

			hexIndex = 0;
			hexBuffer[0] = '\0';

			UART_PrintString("Transitioning to Modtag_Bit_Position_I_Adresse\n");
			*currentState = Modtag_Bit_Position_I_Adresse;
			} else if (isxdigit(recivedChar) && hexIndex < 2) {
			hexBuffer[hexIndex++] = recivedChar;
			hexBuffer[hexIndex] = '\0';  
			} else {
			UART_PrintString("Unexpected character received: ");
			UART_PrintChar(recivedChar);
			UART_PrintString("\n");

			hexIndex = 0;
			hexBuffer[0] = '\0';
		}
		break;

		case Modtag_Bit_Position_I_Adresse:
		if (recivedChar >= '0' && recivedChar <= '7') {
			bitPosition = recivedChar - '0';  
			UART_PrintString("Enter bit position for address: 0x");
			UART_PrintHex(bitPosition);
			UART_PrintString("\n");

			*currentState = Modtag_Bit_Position_Vaerdi;
			} else {
			UART_PrintString("Invalid bit position, please enter a valid position (0-7)\n");
			*currentState = Modtag_Adresse;
		}
		break;

		case Modtag_Bit_Position_Vaerdi:
		if (recivedChar == '\n' || recivedChar == '\r' || recivedChar == ':') {
			UART_PrintString("Ignoring unwanted character: ");
			UART_PrintChar(recivedChar); 
			UART_PrintString("\n");
			return;  
		}

		UART_PrintString("Received Char for Bit Value: ");
		UART_PrintChar(recivedChar); 
		UART_PrintString("\n");

		if (recivedChar == '0' || recivedChar == '1') {
			uint8_t bitMask = (1 << bitPosition);
			if (recivedChar == '1') {
				*address |= bitMask;  
				} else {
				*address &= ~bitMask;  
			}

			UART_PrintString("Updated address: 0x");
			UART_PrintHex(*address);
			UART_PrintString("\n");

			*currentState = Modtag_Adresse;
			} else {
			UART_PrintString("Invalid bit value, please enter 0 or 1\n");

			*currentState = Modtag_Bit_Position_I_Adresse;
		}
		break;

		default:
		UART_PrintString("Unknown state\n");
		break;
	}
}



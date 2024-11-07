#include "bitwise_operations.h"
#include "UART.h"

uint8_t setBit(uint8_t value, uint8_t position) {
	return value | (1 << position);
}

uint8_t clearBit(uint8_t value, uint8_t position) {
	return value & ~(1 << position);
}


void simulateBitSetting(uint8_t initialValue) {
	UART_PrintString("Initial Value: 0x");
	UART_PrintHex(initialValue);
	UART_PrintString(" (binary: ");

	for (int i = 7; i >= 0; i--) {
		UART_PrintString((initialValue >> i) & 1 ? "1" : "0");
	}
	UART_PrintString(")\n");

	for (uint8_t i = 0; i < 8; i++) {
		uint8_t updatedValue = setBit(initialValue, i);

		UART_PrintString("Setting bit position ");
		
		char posStr[2] = { '0' + i, '\0' };
		UART_PrintString(posStr);

		UART_PrintString(": 0x");
		UART_PrintHex(updatedValue);
		UART_PrintString(" (binary: ");

		for (int j = 7; j >= 0; j--) {
			UART_PrintString((updatedValue >> j) & 1 ? "1" : "0");
		}
		UART_PrintString(")\n");
	}
}




void HandleUARTCommand(char command, uint8_t bitPositions) {
	static uint8_t registerValue = 0x00;

	if (command == 'S') {
		// Set the specified bits
		for (uint8_t i = 0; i < 8; i++) {
			if (bitPositions & (1 << i)) {
				registerValue = setBit(registerValue, i);
			}
		}
		UART_PrintString("Bits set: ");
		} else if (command == 'C') {
		// Clear the specified bits
		for (uint8_t i = 0; i < 8; i++) {
			if (bitPositions & (1 << i)) {
				registerValue = clearBit(registerValue, i);
			}
		}
		UART_PrintString("Bits cleared: ");
		} else {
		UART_PrintString("Invalid command.\n");
		return;
	}

	UART_PrintString("Register value: 0x");
	UART_PrintHex(registerValue);
	UART_PrintString(" (binary: ");
	for (int i = 7; i >= 0; i--) {
		UART_PrintString((registerValue >> i) & 1 ? "1" : "0");
	}
	UART_PrintString(")\n");
}
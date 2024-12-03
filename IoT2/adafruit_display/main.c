#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "project_lib/ProjectDefines.h"
#include "project_lib/diplay_lib/ssd1306.h"
#include <stdbool.h>

static volatile uint8_t DisplayLineCounter = 0;
static volatile uint8_t I2C_Address = SSD1306_ADDR;
static char recievedString[MAX_STRING_LENGHT] = { '0' };
static uint8_t stringIndex = 0;

// UART buffer
extern UART_Buffer uart_rx_buffer;

void RecieveCharacterFromUart(char ReceivedCharacter) {
	// Push character to buffer in ISR
	if (UART_BufferPut(&uart_rx_buffer, ReceivedCharacter) == 0) {
		// Successfully inserted character into buffer
	}
}

void WriteReceivedCharacterFromUARTInDisplay() {
	// Update display with the string
	SSD1306_ClearScreen();
	SSD1306_SetPosition(0, 0);
	SSD1306_DrawString(recievedString, NORMAL);
	SSD1306_UpdateScreen(I2C_Address);

	if (SSD1306_UpdateScreen(I2C_Address) == SSD1306_ERROR) {
		printf("Error updating display.\n");
		} else {
		printf("Display updated successfully.\n");
	}
}

void ProcessRecievedCharacters() {
	char recievedCharacter;

	//printf("Buffer available: %d\n", UART_BufferAvailable(&uart_rx_buffer));  // Debug buffer state

	if (UART_BufferAvailable(&uart_rx_buffer) > 0) {
		while (UART_BufferGet(&uart_rx_buffer, &recievedCharacter) == 0) {
			printf("Received character: %c\n", recievedCharacter);
			printf("String length: %d\n", stringIndex);  // Debug string length

			if (recievedCharacter == '\n' || stringIndex >= MAX_STRING_LENGHT - 1) {
				recievedString[stringIndex] = '\0';  // Null-terminate string
				printf("Final string: %s\n", recievedString);
				printf("String length before display: %d\n", stringIndex);

				WriteReceivedCharacterFromUARTInDisplay();  // Update display

				stringIndex = 0;
				DisplayLineCounter = (DisplayLineCounter + 1) % 8;
				SSD1306_ClearScreen();
				SSD1306_SetPosition(0, DisplayLineCounter);
				} else {
				recievedString[stringIndex++] = recievedCharacter;
			}
		}
	}
}


int main(void) {
	RS232Init();
	setupFunctionCallPointer(&RecieveCharacterFromUart);
	Enable_UART_Receive_Interrupt();
	
	SSD1306_Init(I2C_Address);
	SSD1306_ClearScreen();
	SSD1306_SetPosition(0, 0);
	SSD1306_DrawString("Test Message", NORMAL);
	SSD1306_UpdateScreen(I2C_Address);


	sei();  // Enable global interrupts

	uart_rx_buffer.head = 0;
	uart_rx_buffer.tail = 0;

	while (1) {
		ProcessRecievedCharacters();  // Process received UART characters
	}
}

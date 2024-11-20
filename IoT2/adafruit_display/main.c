/*
 * AdaFruit_Display_C.c
 *
 * Created: 23-06-2023 00:18:42
 * Author : ltpe
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "project_lib/ProjectDefines.h"
#include "project_lib/diplay_lib/ssd1306.h"
#include <stdbool.h>


static volatile char ReceivedCharacterFromUART;
static volatile bool CharacterReceivedFromUART = false;
static volatile uint8_t DisplayLineCounter = 0;
static volatile uint8_t I2C_Address = SSD1306_ADDR;
static char recievedString[MAX_STRING_LENGHT] = { '0' };
static uint8_t stringIndex = 0;



void RecieveCharacterFromUart(char ReceivedCharacter)
{
	ReceivedCharacterFromUART = ReceivedCharacter;
	CharacterReceivedFromUART = true;
}
void WriteReceivedCharacterFromUARTInDisplay(char ReceivedCharacterFromUART) {
	printf("ReceivedCharacterFromUART: %c\n", ReceivedCharacterFromUART);

	if (stringIndex < MAX_STRING_LENGHT - 1) {
		recievedString[stringIndex] = ReceivedCharacterFromUART;
		stringIndex++;
		recievedString[stringIndex] = '\0'; 
		printf("String updated to: %s\n", recievedString); 
		} else {
		printf("String index overflow! Resetting.\n");
		stringIndex = 0;
	}

	printf("Preparing to update display...\n");

	SSD1306_ClearScreen();

	SSD1306_SetPosition(0, 0);

	SSD1306_DrawString(recievedString, NORMAL);

	if (SSD1306_UpdateScreen(I2C_Address) == SSD1306_ERROR) {
		printf("Error updating display.\n");
		} else {
		printf("Display updated successfully.\n");
	}

	printf("Writing to display: %s\n", recievedString);
	printf("DisplayLineCounter: %d\n", DisplayLineCounter);
}


void ProcessRecievedCharacters() {
    char recievedCharacter;

    uint8_t available = UART_BufferAvailable(&uart_rx_buffer);
    printf("ProcessReceivedCharacters: UART_BufferAvailable = %d\n", available);

    if (available > 0) {
        uint8_t status = UART_BufferGet(&uart_rx_buffer, &recievedCharacter);

        if (status == 0) {
            printf("Successfully received character: %c\n", recievedCharacter);
            WriteReceivedCharacterFromUARTInDisplay(recievedCharacter);
        } else {
            printf("Error reading from buffer, status: %d\n", status);
        }
    } else {
        printf("Buffer is empty, not processing.\n");
    }

    PrintBufferContents(&uart_rx_buffer);
}




int main(void)
{
	RS232Init();
	
	setupFunctionCallPointer(&RecieveCharacterFromUart);
	uint8_t I2C_Address = SSD1306_ADDR;

	// init ssd1306
	SSD1306_Init(I2C_Address);

	// clear screen
	SSD1306_ClearScreen();
	
	SSD1306_SetPosition(7, 0);
	SSD1306_DrawString("Line 1", NORMAL);
	SSD1306_UpdateScreen(I2C_Address);
	
	SSD1306_SetPosition(7, 1);
	SSD1306_DrawString("Line 2", NORMAL);
	SSD1306_UpdateScreen(I2C_Address);
	
	SSD1306_SetPosition(7, 2);
	SSD1306_DrawString("Line 3", NORMAL);
	SSD1306_UpdateScreen(I2C_Address);
	
	SSD1306_SetPosition(7, 3);
	SSD1306_DrawString("Line 4", NORMAL);
	SSD1306_UpdateScreen(I2C_Address);
	
	SSD1306_SetPosition(7, 4);
	SSD1306_DrawString("Line 5", NORMAL);
	SSD1306_UpdateScreen(I2C_Address);
	
	SSD1306_SetPosition(7, 5);
	SSD1306_DrawString("Line 6", NORMAL);
	SSD1306_UpdateScreen(I2C_Address);
	
	SSD1306_SetPosition(7, 6);
	SSD1306_DrawString("Line 7", NORMAL);
	SSD1306_UpdateScreen(I2C_Address);
	
	SSD1306_SetPosition(7, 7);
	SSD1306_DrawString("Line 8", NORMAL);
	SSD1306_UpdateScreen(I2C_Address);
	

#if defined Normal_Code
	// draw string
	SSD1306_DrawString("SSD1306 OLED DRIVER");
	
	for (int Counter = 0; Counter < MAX_X - 1; Counter++)
	{
		SSD1306_DrawLine(Counter, Counter + 1, 4, 4);
		SSD1306_UpdateScreen(I2C_Address);
	}
	// draw line
	SSD1306_DrawLine(0, MAX_X, 4, 4);
	// set position
	SSD1306_SetPosition(7, 1);
	// draw string
	SSD1306_DrawString("SSD1306 OLED DRIVER", NORMAL);
	// draw line
	SSD1306_DrawLine(0, MAX_X, 18, 18);
	 set position
	SSD1306_SetPosition(20, 3);
	// draw string
	SSD1306_DrawString("Microchip Studio", NORMAL);
	// set position
	SSD1306_SetPosition(10, 5);
	// draw string
	SSD1306_DrawString("h4pd100124", NORMAL);
	// set position
	SSD1306_SetPosition(40, 7);
	// draw string
	SSD1306_DrawString("2023", NORMAL);
	// update
	SSD1306_UpdateScreen(I2C_Address);
#endif
	
	Enable_UART_Receive_Interrupt();
	
	sei();
	
	uart_rx_buffer.head = 0;
	uart_rx_buffer.tail = 0;
	
	while (1)
	{
		ProcessRecievedCharacters();
		//if (true == CharacterReceivedFromUART)
		//{
			//CharacterReceivedFromUART = false;
			//WriteReceivedCharacterFromUARTInDisplay(ReceivedCharacterFromUART);
		//}
	}
}


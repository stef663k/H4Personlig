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
#include "project_lib/display_lib/ssd1306.h"
#include <stdbool.h>


static volatile char ReceivedCharacterFromUART;
static volatile bool CharacterReceivedFromUART = false;
static volatile uint8_t DisplayLineCounter = 0;
static volatile uint8_t I2C_Address = SSD1306_ADDR;

void RecieveCharacterFromUart(char ReceivedCharacter)
{
	ReceivedCharacterFromUART = ReceivedCharacter;
	CharacterReceivedFromUART = true;
}
void WriteReceivedCharacterFromUARTInDisplay(char ReceivedCharacterFromUART)
{
	char ReceivedCharacterFromUARTString[2];
	SSD1306_SetPosition(0, DisplayLineCounter++);
	SSD1306_DrawString("character : ");
	sprintf(ReceivedCharacterFromUARTString, "%c", ReceivedCharacterFromUART);
	SSD1306_DrawString(ReceivedCharacterFromUARTString);
	SSD1306_UpdateScreen(I2C_Address);
	DisplayLineCounter = DisplayLineCounter % MAX_NUMBER_OF_LINES_IN_DISPLAY;
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
	SSD1306_DrawString("Line 1");
	SSD1306_UpdateScreen(I2C_Address);
	
	SSD1306_SetPosition(7, 1);
	SSD1306_DrawString("Line 2");
	SSD1306_UpdateScreen(I2C_Address);
	
	SSD1306_SetPosition(7, 2);
	SSD1306_DrawString("Line 3");
	SSD1306_UpdateScreen(I2C_Address);
	
	SSD1306_SetPosition(7, 3);
	SSD1306_DrawString("Line 4");
	SSD1306_UpdateScreen(I2C_Address);
	
	SSD1306_SetPosition(7, 4);
	SSD1306_DrawString("Line 5");
	SSD1306_UpdateScreen(I2C_Address);
	
	SSD1306_SetPosition(7, 5);
	SSD1306_DrawString("Line 6");
	SSD1306_UpdateScreen(I2C_Address);
	
	SSD1306_SetPosition(7, 6);
	SSD1306_DrawString("Line 7");
	SSD1306_UpdateScreen(I2C_Address);
	
	SSD1306_SetPosition(7, 7);
	SSD1306_DrawString("Line 8");
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
	SSD1306_DrawString("SSD1306 OLED DRIVER");
	// draw line
	SSD1306_DrawLine(0, MAX_X, 18, 18);
	// set position
	SSD1306_SetPosition(20, 3);
	// draw string
	SSD1306_DrawString("Microchip Studio");
	// set position
	SSD1306_SetPosition(10, 5);
	// draw string
	SSD1306_DrawString("h4pd100124");
	// set position
	SSD1306_SetPosition(40, 7);
	// draw string
	SSD1306_DrawString("2023");
	// update
	SSD1306_UpdateScreen(I2C_Address);
#endif
	
	Enable_UART_Receive_Interrupt();
	
	sei();
	
	while (1)
	{
		if (true == CharacterReceivedFromUART)
		{
			CharacterReceivedFromUART = false;
			WriteReceivedCharacterFromUARTInDisplay(ReceivedCharacterFromUART);
		}
	}
}


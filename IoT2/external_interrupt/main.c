/*
 * External_Interrupt.c
 *
 * Created: 23-11-2023 22:39:30
 * Author : ltpe
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "ProjectDefines.h"
#include "ExternalInterrupt.h"
#include "UART.h"

static volatile uint16_t NumberOfExternalInterruptsOnPin0 = 0;
static volatile uint16_t NumberOfExternalInterruptsOnPin0FromCallback = 0;
static volatile bool InterruptOnExternalPin0 = false;

void ExternalInterruptFunction_0(uint16_t NumberOfExternalInterruptsOnPin0FromCallbackHere)
{
	NumberOfExternalInterruptsOnPin0++;
	NumberOfExternalInterruptsOnPin0FromCallback = NumberOfExternalInterruptsOnPin0FromCallbackHere;
	InterruptOnExternalPin0 = true;
}

int main(void)
 {
	char OutputCharArray[6];
	 
	AttachAndEnableExternalInterrupt(EXTERNAL_INTERRUPT_0, ExternalInterruptFunction_0, FALLING_EDGE_GENERATE_INTERRUPT);
		
	RS232Init();
	Enable_UART_Receive_Interrupt();
	
	sei();
	
	printf("\nEmbedded styrer for vildt !!!\n");
    /* Replace with your application code */
    while (1) 
    {
		if (true == InterruptOnExternalPin0)
		{
			InterruptOnExternalPin0 = false;
			
			// Output info to UART
			printf("\nInterrupt on External Pin 0. \n");
			printf("Number of Interrupts on ExternalPin 0 : ");
			sprintf(OutputCharArray, "%05d", NumberOfExternalInterruptsOnPin0);
			printf(OutputCharArray);
			printf("\n");
		}
    }
}


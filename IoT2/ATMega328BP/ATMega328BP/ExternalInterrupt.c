#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "ExternalInterrupt.h"
#include "ProjectDefines.h"
#include "UART.h"

volatile uint16_t interruptCount;
volatile bool int0Triggered = false;
volatile uint16_t timerOverflowCount = 0;
volatile uint32_t timeElapsed = 0;
static volatile lastInterruptTime = 0;

static void NoCallbackIsPerformedOnExternalInterrupt(uint16_t NumberOfExternalInterruptsOnPin) {
	// Placeholder function
}

static volatile ExternalInterruptCallbackStruct ExternalInterruptCallbackStructArray[NUMBER_OF_EXTERNAL_INTRRUPTS] = {
	{NoCallbackIsPerformedOnExternalInterrupt, 0},
	{NoCallbackIsPerformedOnExternalInterrupt, 0},
	#if defined (_AVR_IOM2560_H_)
	{NoCallbackIsPerformedOnExternalInterrupt, 0},
	{NoCallbackIsPerformedOnExternalInterrupt, 0},
	{NoCallbackIsPerformedOnExternalInterrupt, 0},
	{NoCallbackIsPerformedOnExternalInterrupt, 0},
	{NoCallbackIsPerformedOnExternalInterrupt, 0},
	{NoCallbackIsPerformedOnExternalInterrupt, 0}
	#endif
};

void MyExternalInterruptHandler(uint16_t interruptCount) {
	UART_PrintString("External interrupt triggered!\n");
	UART_PrintInt(interruptCount);
	UART_PrintString("\n");
	UART_PrintInt(TCNT1);
}


void Timer1_Init(void) {
	TCCR1B |= (1 << CS11) | (1 << CS10);
	TCNT1 = 0;
	
	TIMSK1 |= (1 << TOIE1);
}

ISR(TIMER1_OVF_vect) {
	timerOverflowCount++;
	if (timerOverflowCount % 10 == 0) {
		UART_PrintString("Overflow count: ");
		UART_PrintInt(timerOverflowCount);
		UART_PrintString("\n");
	}
	
	timeElapsed++;
}


ISR(INT0_vect) {
	UART_PrintString("INT0 interrupt triggered");
	uint16_t currentTime = timeElapsed;
	
	if (currentTime - lastInterruptTime > 2) { 
		int0Triggered = true; 
		lastInterruptTime = currentTime;
	}
	EIFR |= (1 << TOIE1);
	
}

void processInterrupts(void) {
	if (int0Triggered && timeElapsed >= FIVE_SECOND_THRESHOLD) {
		UART_PrintString("Processing interrupt!\n");
		int0Triggered = false; 
		interruptCount++;
		MyExternalInterruptHandler(interruptCount);
		PORTB ^= (1 << LED_PINBUT); 
	}
}


//ISR(INT1_vect) {
	//static uint16_t lastInterruptTime = 0;
	//uint16_t currentTime = timerOverflowCount;
	//PORTB ^= (1 << PORTB1); 
	//
	//if (currentTime - lastInterruptTime > 10) {
		//UART_PrintString("Debounced INT1 TRIGGERED!\n");
		//ExternalInterruptCallbackStructArray[1].NumberOfExternalInterruptsOnPin++;
		//ExternalInterruptCallbackStructArray[1].ThisFunctionPointer(ExternalInterruptCallbackStructArray[1].NumberOfExternalInterruptsOnPin);
		//lastInterruptTime = currentTime;
	//}
//}


//#if defined (_AVR_IOM2560_H_)
//ISR(INT2_vect) {
	//ExternalInterruptCallbackStructArray[2].NumberOfExternalInterruptsOnPin++;
	//ExternalInterruptCallbackStructArray[2].ThisFunctionPointer(ExternalInterruptCallbackStructArray[2].NumberOfExternalInterruptsOnPin);
//}
//
//ISR(INT3_vect, ISR_BLOCK ISR_NAKED) {
	//ExternalInterruptCallbackStructArray[3].NumberOfExternalInterruptsOnPin++;
	//ExternalInterruptCallbackStructArray[3].ThisFunctionPointer(ExternalInterruptCallbackStructArray[3].NumberOfExternalInterruptsOnPin);
//}
//
//ISR(INT4_vect, ISR_BLOCK ISR_NAKED) {
	//ExternalInterruptCallbackStructArray[4].NumberOfExternalInterruptsOnPin++;
	//ExternalInterruptCallbackStructArray[4].ThisFunctionPointer(ExternalInterruptCallbackStructArray[4].NumberOfExternalInterruptsOnPin);
//}
//
//ISR(INT5_vect) {
	//ExternalInterruptCallbackStructArray[5].NumberOfExternalInterruptsOnPin++;
	//ExternalInterruptCallbackStructArray[5].ThisFunctionPointer(ExternalInterruptCallbackStructArray[5].NumberOfExternalInterruptsOnPin);
//}
//
//ISR(INT6_vect) {
	//ExternalInterruptCallbackStructArray[6].NumberOfExternalInterruptsOnPin++;
	//ExternalInterruptCallbackStructArray[6].ThisFunctionPointer(ExternalInterruptCallbackStructArray[6].NumberOfExternalInterruptsOnPin);
//}
//
//ISR(INT7_vect) {
	//ExternalInterruptCallbackStructArray[7].NumberOfExternalInterruptsOnPin++;
	//ExternalInterruptCallbackStructArray[7].ThisFunctionPointer(ExternalInterruptCallbackStructArray[7].NumberOfExternalInterruptsOnPin);
//}
//#endif
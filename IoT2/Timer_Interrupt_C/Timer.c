/*
 * Timer.c
 *
 * Created: 20-04-2022 14:54:21
 *  Author: ltpe
 */ 


 #include <avr/interrupt.h>
 #include "ProjectDefines.h"
 #include "Timer.h"
 #include "Timer0.h"
 

 static uint16_t Timer0OverflowValue;
 static uint16_t Timer0OverflowCounter = 0;
 
 static uint16_t Timer_PrescalerBitValues[][2] =
 {
	 {TimerPrescalerValue1,    0b001},
	 {TimerPrescalerValue8,    0b010},
	 {TimerPrescalerValue64,   0b011},
	 {TimerPrescalerValue256,  0b100},
	 {TimerPrescalerValue1024, 0b101}
 };

 uint8_t GetBitValuesForClockSelect(uint_fast16_t ClockPrescalerValue)
 {
	 uint8_t Counter = 0;

	 do
	 {
		 if (Timer_PrescalerBitValues[Counter][0] == ClockPrescalerValue)
		 {
			 return (Timer_PrescalerBitValues[Counter][1]);
		 }
	 } while (++Counter < sizeof(Timer_PrescalerBitValues) / sizeof(Timer_PrescalerBitValues[0]));

	 return (Timer_PrescalerBitValues[0][1]);
 }

 void Setup_Timer0_Overflow_Interrupt(uint16_t ValueToVariable)
 {
	 TCNT0 = 0x00;                     // Sæt 0 som Timer Counter start værdi.

	 TCCR0A = 0x00;                    // Brug Timer 0 som Standard op-Tæller.

	 TIFR0 = 0x00;					   // Clear TOV0 => Clear pending interrupts

	 TCCR0B |= GetBitValuesForClockSelect(Timer8BitPrescalerValue);

	 Timer0OverflowValue = ValueToVariable;
 }

 void Enable_Timer0_Overflow_Interrupt()
 {
	 TIMSK0 |= (1 << TOIE0);   // Enable timer0 overflow interrupt(TOIE0)
 }

 void Disable_Timer0_Overflow_Interrupt()
 {
	 TIMSK0 &= ~(1 << TOIE0);   // Disable timer0 overflow interrupt(TOIE0)
 }

 ISR(TIMER0_OVF_vect)
 {
	Timer0OverflowCounter++;
	if (Timer0OverflowCounter >= Timer0OverflowValue)
	{
		PORTB ^= (1 << RedLedBit);
		Timer0OverflowCounter = 0;
	}
	sei();
 }
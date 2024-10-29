/*
 * Timer.asm
 *
 *  Created: 01-01-2018 11:48:52
 *   Author: ltpe
 */ 


 /********************************************************************************************************
 Kode følger herefter i kodesegment
 *********************************************************************************************************/
		SpecifyCodeSegment

/********************************************************************************************************
  Funktionsnavn    : SetupTimer0OverflowInterrupt
  Beskrivelse      : Sætter Timer 0 Overflow interrupt op. 
  Input            : Ingen
  Output           : Ingen
  Registre anvendt : R17
  Kalder           : Ingen
 *********************************************************************************************************/
 SetupTimer0OverflowInterrupt:
		PushRegisterOnStack	r17                 
		; Push R17 register til stakken       

		ResetAllBitsInRegister		r17         
		; R17 = 0x00
		
		STORE_REGISTER_VALUE_IN_IO_OR_DATASPACE	TCCR0A, r17  
		; TCCR0A register = R17 = 0x00 => 
		; Brug Timer 0 som Standard op-tæller.

		STORE_REGISTER_VALUE_IN_IO_OR_DATASPACE	TCNT0, r17	  
		; TCNT0 register = R17 = 0x00 => 
		; Sæt 0 som Timer Counter start værdi.

		LOAD_REGISTER_VALUE_DIRECT	r17, (1<<CS02)|(1<<CS00)  
		; R17 = (1<<CS02)|(1<<CS00) 

		STORE_REGISTER_VALUE_IN_IO_OR_DATASPACE	TCCR0B, r17	  
		; TCCR0B register = R17 = (1<<CS02)|(1<<CS00) => 
		; Timer Clock = System Clock/1024 (16Mhz/1024 = 15.625 
		; "timer svingninger"/s)

		LOAD_REGISTER_VALUE_DIRECT	r17, (1<<TOV0)	
		; R17 = (1<<TOV0) 	

		STORE_REGISTER_VALUE_IN_IO_OR_DATASPACE	TIFR0, r17		
		; TIFR0 register = R17 = (1<<TOV0) => Clear TOV0 => 
		; Clear pending interrupts
		
		PopRegisterFromStack		r17         
		; Pop fra stakken på den adresse som Stack Pointeren peger på
		; og læg den "poppede" værdi i register R17

		ReturnFromFunction                      
		; Return fra funktion SetupTimer0OverflowInterrupt

/********************************************************************************************************
  Funktionsnavn    : EnableTimer0OverflowInterupt
  Beskrivelse      : Disable Timer 0 Overflow interrupt. 
  Input            : Ingen.
  Output           : Ingen
  Registre anvendt : R17
  Kalder           : Ingen
 *********************************************************************************************************/
EnableTimer0OverflowInterupt:
		PushRegisterOnStack	r17                
		; Push R17 register til stakken

		LOAD_REGISTER_VALUE_FROM_IO_OR_DATASPACE r17, TIMSK0 
		; R17 = indhold i register TIMSK0

		SetBitsInRegister		r17, (1<<TOIE0)
		; Sæt bit (1<<TOIE0) i R17

		STORE_REGISTER_VALUE_IN_IO_OR_DATASPACE	TIMSK0, r17	
		; TIMSK0 register = R17 => Enable TimerCounter0 Overflow Interrupt
	
		PopRegisterFromStack		r17        
		; Pop fra stakken på den adresse som Stack Pointeren peger på
		; og læg den "poppede" værdi i register R17

		ReturnFromFunction                     
		; Return fra funktion EnableTimer0OverflowInterupt

/********************************************************************************************************
  Funktionsnavn    : DisableTimer0OverflowInterupt
  Beskrivelse      : Disable Timer 0 Overflow interrupt. 
  Input            : Ingen.
  Output           : Ingen
  Registre anvendt : R17
  Kalder           : Ingen
 *********************************************************************************************************/
DisableTimer0OverflowInterupt:
		PushRegisterOnStack	r17               
		; Push R17 register til stakken

		LOAD_REGISTER_VALUE_FROM_IO_OR_DATASPACE r17, TIMSK0 
		; R17 = indhold i register TIMSK0

		ResetBitsInRegister		r17, (1<<TOIE0)               
		; Clear bit (1<<TOIE0) i R17

		STORE_REGISTER_VALUE_IN_IO_OR_DATASPACE	TIMSK0, r17 
		; TIMSK0 register = R17 => Disable TimerCounter0 Overflow Interrupt

		PopRegisterFromStack		r17       
		; Pop fra stakken på den adresse som Stack Pointeren peger på
		; og læg den "poppede" værdi i register R17

		ReturnFromFunction                    
		; Return fra funktion DisableTimer0OverflowInterupt

/*********************************************************************************************************
  Interrupt funktions definitioner følger herefter
*********************************************************************************************************/

/********************************************************************************************************
  Funktionsnavn    : TIMER0_OVERFLOW_INTERRUPT
  Anvendelse       : Behandler Timer0 Overflow Interrupt. 
  Input            : Ingen
  Output           : Ingen
  Registre anvendt : R16
					 R17
  Kalder           : TogglePin
*********************************************************************************************************/
 TIMER0_OVERFLOW_INTERRUPT:
		PushRegisterOnStack	r16             
		; Push R16 register til stakken

		PushRegisterOnStack	r17                 
		; Push R17 register til stakken

		PushRegisterOnStack	r18					
		; Push R18 register til stakken
		
		LOAD_REGISTER_VALUE_FROM_IO_OR_DATASPACE r18, SREG
		; R18 = SREG

		PushRegisterOnStack	r18					
		; Push R18 register (Staus Rgister) til stakken
		
		LOAD_REGISTER_VALUE_FROM_RAM_DATASPACE	r16, Timer0OverflowCounter          
		; R16 = værdien af variabel i RAM Timer0OverflowCounter  
		
		LOAD_REGISTER_VALUE_FROM_RAM_DATASPACE	r17, Timer0OverflowCounterStopValue 
		; R17 = værdien af variabel i RAM Timer0OverflowCounterStopValue  

		CompareValuesInRegisters		r16, r17                            
		; Sammenlign indhold i R16 med indhold i R17 
		
		BranchIfNotEqual	IncrementTimer0OverflowCounter      
		; Hvis indhold i R16 er forskellig fra indhold i R17
		; så hop til label IncrementTimer0OverflowCounter

		ResetAllBitsInRegister		r16             
		; R16 = 0x00
		
		STORE_REGISTER_VALUE_IN_RAM_DATASPACE	Timer0OverflowCounter, r16          
		; Sæt variabel i RAM Timer0OverflowCounter = R16 = 0x00

		LOAD_REGISTER_VALUE_FROM_IO_OR_DATASPACE r16, PortB
		; R16 = PortB
				
		LOAD_REGISTER_VALUE_DIRECT	r17, RedLedBitValue                 
		; R17 = værdien af konstant RedLedBitValue 
		; (defineret i ProjectDefines.inc)
		
		ExclusiveOrRegisters		r16, r17                           
		; Xor værdien af R16 med værdien af R17  

		STORE_REGISTER_VALUE_IN_IO_OR_DATASPACE	PortB, r16		                    
		; PORTB = R16

		RelativeJump		DoneTreatingTimer0_Overflow_Interrupt  
		; Hop til label DoneTreatingTimer0_Overflow_Interrupt

IncrementTimer0OverflowCounter:
		IncrementValueInRegister		r16                             
		; R16 = R16 + 1

		STORE_REGISTER_VALUE_IN_RAM_DATASPACE	Timer0OverflowCounter, r16         
		; Sæt variabel i RAM Timer0OverflowCounter = R16

DoneTreatingTimer0_Overflow_Interrupt:

		PopRegisterFromStack		r16
		; Pop fra stakken på den adresse som Stack Pointeren peger på
		; og læg den "poppede" værdi i register R16

		STORE_REGISTER_VALUE_IN_IO_OR_DATASPACE SREG, r16 
		; SREG = r16 => (Instruktionen her sikrer, at indholdet i SREG
		; er det samme, når interrupt funktionen forlades, som ved 
		; indgangen i interrupt funktionen.

		PopRegisterFromStack		r18
		; Pop fra stakken på den adresse som Stack Pointeren peger på
		; og læg den "poppede" værdi i register R18

		PopRegisterFromStack		r17            
		; Pop fra stakken på den adresse som Stack Pointeren peger på
		; og læg den "poppede" værdi i register R17

		PopRegisterFromStack		r16                             
		; Pop fra stakken på den adresse som Stack Pointeren peger på
		; og læg den "poppede" værdi i register R16

		ReturnFromInterruptFunction                                 
		; Return fra funktion TIMER0_OVERFLOW_INTERRUPT => GLobalt 
		; Interrupt Enable bit i SREG sættes.

Test0AdrInterrupt:

		ReturnFromInterruptFunction


Test1AdrInterrupt:

		ReturnFromInterruptFunction


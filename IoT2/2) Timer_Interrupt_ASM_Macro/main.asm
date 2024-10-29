;
; h3pd040120_Timer0_OverFlow_Interrupt_Asm.asm
;
; Created: 16-05-2020 00:36:28
; Author : ltpe
;


/********************************************************************************************************
 Include filer, der definerer projekt definitioner, erklæringer i EEprom (eseg) og erklæringer i RAM (desg)
 følger herefter. 
*********************************************************************************************************/
	.include	"ProjectDefines.inc"
	
	.include	"DirectiveDefines.inc"
	.include	"MacroDefines.inc"
	.include	"RAMDefines.inc"
	.include	"TimerDefines.inc"

/********************************************************************************************************
 Start på Kode (cseg). 
*********************************************************************************************************/
	SpecifyCodeSegment

/********************************************************************************************************
 Interruptvektorer i cseg. 
*********************************************************************************************************/
	PlaceOnAddress	RWW_START_ADDR
	RelativeJump	main

	PlaceOnAddress	INT0addr
	AbsoluteJump	Test0AdrInterrupt

	PlaceOnAddress	INT1addr
	RelativeJump	Test1AdrInterrupt

	PlaceOnAddress	OVF0addr  
	RelativeJump	TIMER0_OVERFLOW_INTERRUPT

/********************************************************************************************************
 Start på Program Kode (cseg). 
*********************************************************************************************************/
	PlaceOnAddress	INT_VECTORS_SIZE

	.include	"Timer.asm"

main:
	SetupStack

	LOAD_REGISTER_VALUE_DIRECT	R16, 0xFF				    
	; R16 = 0xFF 

	STORE_REGISTER_VALUE_IN_IO_OR_DATASPACE	DDRB, R16       
	; DDRB = 0xFF

	TurnAlleBitsInRegister		R16                         
	; R16 = 0x00

	STORE_REGISTER_VALUE_IN_IO_OR_DATASPACE	PORTB, R16		
	; PORTB = R16 = 0x00
	
	STORE_REGISTER_VALUE_IN_RAM_DATASPACE Timer0OverflowCounter, R16    
	; Sæt variabel i RAM Timer0OverflowCounter = R16 = 0x00

	LOAD_REGISTER_VALUE_DIRECT	R16, Timer0_1SecondInterruptValue     
	; R16 = Timer0_1SecondInterruptValue = 0x3D

	STORE_REGISTER_VALUE_IN_RAM_DATASPACE	Timer0OverflowCounterStopValue, R16  
	; Sæt variabel i RAM Timer0OverflowCounterStopValue = R16 = 0x3D
	
	RelativeCall		SetupTimer0OverflowInterrupt  
	; Kald funktion SetupTimer0OverflowInterrupt

	RelativeCall		EnableTimer0OverflowInterupt  
	; Kald funktion EnableTimer0OverflowInterupt

	EnableGlobaltInterrupt                            
	; Enable for Global Interrupt. Global Interrupt skal
	; være enabled, ellers er der ingen Interrupts 
	; overhovedet, der kan aktiveres !!!

loop:
	RelativeJump		loop                  
	; Vent her i en uendelig løkke. Programmet kører
	; udelukkende på TimerInterrupt. Funktionen 
	; TIMER0_OVERFLOW_INTERRUPT i filen Timer.asm



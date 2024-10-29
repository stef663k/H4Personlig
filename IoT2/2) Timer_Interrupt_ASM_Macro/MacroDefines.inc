/*
 * MacroDefines.inc
 *
 *  Created: 14-05-2019 12:46:03
 *   Author: ltpe
 */ 
 
/********************************************************************************************************
  Macronavn        : RelativeJump
  Beskrivelse      : Kalder funktionen på adressen specificeret som argument (2 bytes instruktion)
                     Jump within 64kB Segment.
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro RelativeJump
 	rjmp		 @0
.ENDMACRO

/********************************************************************************************************
  Macronavn        : AbsoluteJump
  Beskrivelse      : Kalder funktionen på adressen specificeret som argument (3 bytes instruktion)
                     Jump within 64kB Segment.
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro AbsoluteJump
 	jmp			 @0
.ENDMACRO

/********************************************************************************************************
  Macronavn        : RelativeCall
  Beskrivelse      : Kalder funktionen på adressen specificeret som argument (4 bytes instruktion)
                     12 bits displacement = 4kByte displacement.
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro RelativeCall
 	rcall	 @0
.ENDMACRO

/********************************************************************************************************
  Macronavn        : AbsoluteCall
  Beskrivelse      : Kalder funktionen på adressen specificeret som argument (4 bytes instruktion)
                     12 bits displacement = 4kByte displacement.
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro AbsoluteCall
 	rcall	 @0
.ENDMACRO

/********************************************************************************************************
  Macronavn        : TurnAlleBitsInRegister
  Beskrivelse      : Vender alle bits i det specificerede register (0 => 1 og 1 => 0)
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro TurnAlleBitsInRegister
 	com		 @0
.ENDMACRO

/********************************************************************************************************
  Macronavn        : ResetAllBitsInRegister
  Beskrivelse      : Sætter alle bits i det specificerede register til 0
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro ResetAllBitsInRegister
 	clr		 @0
.ENDMACRO

/********************************************************************************************************
  Macronavn        : SetAllBitsInRegister
  Beskrivelse      : Sætter alle bits i det specificerede register til 0
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro SetAllBitsInRegister
 	set		 @0
.ENDMACRO

/********************************************************************************************************
  Macronavn        : ResetBitsInRegister
  Beskrivelse      : Sætter alle specificerede bits i det specificerede register til 0
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro ResetBitsInRegister
 	sbr		 @0, @1
.ENDMACRO

/********************************************************************************************************
  Macronavn        : SetBitsInRegister
  Beskrivelse      : Sætter alle specificerede bits i det specificerede register til 1
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro SetBitsInRegister
 	sbr		 @0, @1
.ENDMACRO

/********************************************************************************************************
  Macronavn        : IncrementValueInRegister
  Beskrivelse      : Forøger værdien i det specificerede register med én
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro IncrementValueInRegister
 	inc		 @0
.ENDMACRO

/********************************************************************************************************
  Macronavn        : ExclusiveOrRegisters
  Beskrivelse      : Laver en Exclusive Or mellem alle bits i de 2 specificerede
	                 registre.
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro ExclusiveOrRegisters
 	eor		 @0, @1
.ENDMACRO

/********************************************************************************************************
  Macronavn        : CompareValuesInRegisters
  Beskrivelse      : Laver en sammenligning mellem værdierne i de 2 specificerede
	                 registre.
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro CompareValuesInRegisters
 	cp		 @0, @1
.ENDMACRO

/********************************************************************************************************
  Macronavn        : CompareValueInRegisterWithConstant
  Beskrivelse      : Laver en sammenligning mellem værdien i det specificerede
	                 register med en konstant.
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro CompareValueInRegisterWithConstant
 	cpi		 @0, @1
.ENDMACRO


/********************************************************************************************************
  Macronavn        : EnableGlobaltInterrupt
  Beskrivelse      : Enabler for det globale Interrupt i mikroen
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro EnableGlobaltInterrupt
 	sei
.ENDMACRO

/********************************************************************************************************
  Macronavn        : DisableGlobaltInterrupt
  Beskrivelse      : Disabler for det globale Interrupt i mikroen
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro DisableGlobaltInterrupt
 	cli
.ENDMACRO

/********************************************************************************************************
  Macronavn        : PushRegisterOnStack
  Beskrivelse      : Lægger indholdet i det angivne register op på stakken,
                     i den adresse som Stack Pointeren peger på.
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro PushRegisterOnStack
 	push	@0	
.ENDMACRO

/********************************************************************************************************
  Macronavn        : AddRegisters
  Beskrivelse      : Adderer indholdet af 2 registre. Resultatet gemmes i det første angivne
                     register
  Input            : Ingen
  Output           : Ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
.Macro AddRegisters
	add		@0, @1
.ENDMACRO

/********************************************************************************************************
  Macronavn        : PopRegisterFromStack
  Beskrivelse      : Lægger indholdet i den adresse som Stack Pointeren peger på 
                     ind i det angivne register.
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro PopRegisterFromStack
 	pop		@0	
.ENDMACRO

/********************************************************************************************************
  Macronavn        : ReturnFromFunction
  Beskrivelse      : Returnerer fra den kaldte funktion til adressen, hvorfra
					 funktionen blev kaldt. 
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro ReturnFromFunction
 	ret
.ENDMACRO

/********************************************************************************************************
  Macronavn        : ReturnFromInterruptFunction
  Beskrivelse      : Returnerer fra Interrupt funktionen til næste adresse efter
					 den adresse, hvor programmet blev interruptet.
					 Enable for Globalt Interrupt Flag.
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro ReturnFromInterruptFunction
 	reti
.ENDMACRO

/********************************************************************************************************
  Macronavn        : NoOperation
  Beskrivelse      : Udfører en Nop instruktion
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro NoOperation
 	nop
.ENDMACRO


/********************************************************************************************************
  Macronavn        : BranchIfNotEqual
  Beskrivelse      : Hop til den specificerede label/adresse, hvis Zero flaget i 
					 Status registret ikke er sat.
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro BranchIfNotEqual
 	brne	@0
.ENDMACRO


/********************************************************************************************************
  Macronavn        : BranchIfCarryCleared
  Beskrivelse      : Hop til den specificerede label/adresse, Carry zero flaget i 
					 Status registret ikke er sat.
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro BranchIfCarryCleared
 	brcc	@0
.ENDMACRO

/********************************************************************************************************
  Macronavn        : SetupStack
  Beskrivelse      : Sætter Stack Pointer op til øverste adresse i Intern RAM (Adresse : 0x04ff) 
  Input            : Ingen
  Output           : Ingen
  Registre anvendt : r16
  Kalder		   : Ingen
 *********************************************************************************************************/
.MACRO SetupStack
	LOAD_REGISTER_VALUE_DIRECT		r16, low(RAMEND)	; Sæt Stakpointer op til at pege på højeste RAM adresse. 
	STORE_REGISTER_VALUE_IN_IO_OR_DATASPACE		SPL, r16            ; Stakken gror nedad i hukomelsen.
	LOAD_REGISTER_VALUE_DIRECT		r16, high(RAMEND)
	STORE_REGISTER_VALUE_IN_IO_OR_DATASPACE		SPH, r16
.ENDMACRO

/********************************************************************************************************
  Macronavn        : STORE_REGISTER_VALUE_IN_DATASPACE
  Beskrivelse      : Gemmer register i Data memory område. 
  Input            : Ingen
  Output           : Ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
.MACRO STORE_REGISTER_VALUE_IN_DATASPACE 		;Arguments: Address, Register
	sts	@0, @1
.ENDMACRO

/********************************************************************************************************
  Macronavn        : STORE_REGISTER_VALUE_IN_IO
  Beskrivelse      : Gemmer register i IO adresse. 
  Input            : Ingen
  Output           : Ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
.MACRO STORE_REGISTER_VALUE_IN_IO 		;Arguments: Address, Register
	out	@0, @1
.ENDMACRO

/********************************************************************************************************
  Macronavn        : LOAD_REGISTER_VALUE_FROM_DATASPACE
  Beskrivelse      : Henter indhold fra Data memory adresse til register 
  Input            : Ingen
  Output           : Ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
.MACRO LOAD_REGISTER_VALUE_FROM_DATASPACE 		;Arguments: Address, Register
	lds	@0, @1
.ENDMACRO

/********************************************************************************************************
  Macronavn        : LOAD_REGISTER_VALUE_FROM_IO
  Beskrivelse      : Henter indhold fra IO adresse til register 
  Input            : Ingen
  Output           : Ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
.MACRO LOAD_REGISTER_VALUE_FROM_IO 		;Arguments: Address, Register
	in	@0, @1
.ENDMACRO

/********************************************************************************************************
  Macronavn        : STORE_REGISTER_VALUE_IN_IO_OR_DATASPACE
  Beskrivelse      : Gemmer register i IO eller Data memory område. Makroen tager selv høje for "problematikken"
                     omkring IO adresser (IN - OUT instruktioner) og Data Memory adresser (ST/STS/STD - LD/LDS/LDT 
					 instruktioner)
  Input            : Ingen
  Output           : Ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
.MACRO STORE_REGISTER_VALUE_IN_IO_OR_DATASPACE 		;Arguments: Address, Register
	.if	@0>=StopInOutPortAddress
		STORE_REGISTER_VALUE_IN_DATASPACE	@0, @1
	.else
		STORE_REGISTER_VALUE_IN_IO	@0, @1
	.endif
.ENDMACRO

/********************************************************************************************************
  Macronavn        : LOAD_REGISTER_VALUE_FROM_IO_OR_DATASPACE
  Beskrivelse      : Henter indhold i IO eller Data memory område til register. Makroen tager selv høje for "problematikken"
                     omkring IO adresser (IN - OUT instruktioner) og Data Memory adresser (ST/STS/STD - LD/LDS/LDT 
					 instruktioner)
  Input            : Ingen
  Output           : Ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .MACRO LOAD_REGISTER_VALUE_FROM_IO_OR_DATASPACE 		;Arguments: Register,  Address
	.if	@1>=StopInOutPortAddress
		LOAD_REGISTER_VALUE_FROM_DATASPACE	@0, @1
	.else
		LOAD_REGISTER_VALUE_FROM_IO			@0, @1
	.endif
.ENDMACRO

/********************************************************************************************************
  Macronavn        : STORE_REGISTER_VALUE_IN_RAM_DATASPACE
  Beskrivelse      : Gemmer register i IO eller Data memory område. Makroen tager selv høje for "problematikken"
                     omkring IO adresser (IN - OUT instruktioner) og Data Memory adresser (ST/STS/STD - LD/LDS/LDT 
					 instruktioner)
  Input            : Ingen
  Output           : Ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
.MACRO STORE_REGISTER_VALUE_IN_RAM_DATASPACE 		;Arguments: Address, Register
		STORE_REGISTER_VALUE_IN_DATASPACE	@0, @1
.ENDMACRO

/********************************************************************************************************
  Macronavn        : LOAD_REGISTER_VALUE_FROM_RAM_DATASPACE
  Beskrivelse      : Henter indhold i IO eller Data memory område til register. Makroen tager selv høje for "problematikken"
                     omkring IO adresser (IN - OUT instruktioner) og Data Memory adresser (ST/STS/STD - LD/LDS/LDT 
					 instruktioner)
  Input            : Ingen
  Output           : Ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
.MACRO LOAD_REGISTER_VALUE_FROM_RAM_DATASPACE 		;Arguments: Register,  Address
		LOAD_REGISTER_VALUE_FROM_DATASPACE	@0, @1
.ENDMACRO

/********************************************************************************************************
  Macronavn        : LOAD_REGISTER_VALUE_DIRECT
  Beskrivelse      : Gemmer Byte angivet som det andet argument ind i register angivet som det første argument.
  Input            : Ingen
  Output           : Ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
.MACRO LOAD_REGISTER_VALUE_DIRECT 		;Arguments: Register, DataByte,
	ldi	@0, @1
.ENDMACRO

/********************************************************************************************************
  Macronavn        : CONVERT_IO_ADDRESS_TO_DATA_ADDRESS
  Beskrivelse      : Laver en In - Out instruktions Adresse gemt i z registret om til en Data memory adresse 
					 og gemmer denne Data memory adresse tilbage i z registret
  Input            : Ingen
  Output           : Ingen
  Registre anvendt : r25
  Kalder		   : Ingen
 *********************************************************************************************************/
.Macro CONVERT_IO_ADDRESS_TO_DATA_ADDRESS
	CompareValueInRegisterWithConstant		zh, 0
	BranchIfNotEqual	done
	
	CompareValueInRegisterWithConstant		zl, StopInOutPortAddress
	BranchIfCarryCleared	done

	PushRegisterOnStack	r25
	LOAD_REGISTER_VALUE_DIRECT		r25, IO_DataMemoryOffsetValue
	AddRegisters		zl, r25
	PopRegisterFromStack	r25 
	
	done:
	    NoOperation
	
.ENDMACRO

/********************************************************************************************************
  Macronavn        : TransferDataMemoryAddressToZRegister
  Beskrivelse      : Gemmer en Data Memory adresse i z registret. 
  Input            : Ingen
  Output           : z registret som indeholder den angivne adresse
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro TransferDataMemoryAddressToZRegister
 	LOAD_REGISTER_VALUE_DIRECT		ZL,low(@0)		
	; Load low byte af addresse ind i ZL registret

	LOAD_REGISTER_VALUE_DIRECT		ZH,high(@0)		
	; Load high byte af addresse ind i ZH registret
.ENDMACRO

/********************************************************************************************************
  Macronavn        : TransferDataMemoryAddressToZRegisterAndConvert
  Beskrivelse      : Gemmer en Data Memory adresse i z registret. Makroen tager selv højde for, om den angivne
                     Data memory adresse, er en In - Out instruktions Adresse, der først skal konverteres om til
					 "rigtig" Data memory adresse.
  Input            : Ingen
  Output           : z registret som indeholder den angivne adresse (evt. konverteret fra IO adresse til Data memory
                     adresse).
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro TransferDataMemoryAddressToZRegisterAndConvert
 	LOAD_REGISTER_VALUE_DIRECT		ZL,low(@0)					
	; Load low byte af addresse ind i ZL registret

	LOAD_REGISTER_VALUE_DIRECT		ZH,high(@0)				
	; Load high byte af addresse ind i ZH registret

	CONVERT_IO_ADDRESS_TO_DATA_ADDRESS
.ENDMACRO

/********************************************************************************************************
  Macronavn        : TransferEEpromAddressToZRegister
  Beskrivelse      : Gemmer en EEprom adresse i z registret. 
  Input            : Ingen
  Output           : z registret som indeholder den angivne EEprom adresse
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro TransferEEpromAddressToZRegister
 	LOAD_REGISTER_VALUE_DIRECT		ZL,low(@0)		
	; Load low byte af EEprom addresse ind i ZL registret

	LOAD_REGISTER_VALUE_DIRECT		ZH,high(@0)	
	; Load high byte af EEprom addresse ind i ZH registret
.ENDMACRO

/********************************************************************************************************
  Macronavn        : TransferFlashPromAddressToZRegister
  Beskrivelse      : Gemmer en Flash Prom adresse i z registret. 
  Input            : Ingen
  Output           : z registret som indeholder den angivne Flash Prom adresse
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro TransferFlashPromAddressToZRegister
 	LOAD_REGISTER_VALUE_DIRECT		ZL,low(2*@0)	
	; Load low byte af Flash Prom addresse ind i ZL registret

	LOAD_REGISTER_VALUE_DIRECT		ZH,high(2*@0)		
	; Load high byte af Flash Prom addresse ind i ZH registret
.ENDMACRO

/********************************************************************************************************
  Macronavn        : PushZRegisters
  Beskrivelse      : Pusher ZL og ZH registrerne på stakken 
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro PushZRegisters
 	PushRegisterOnStack	ZL
	PushRegisterOnStack	ZH
.ENDMACRO

/********************************************************************************************************
  Macronavn        : PopZRegisters
  Beskrivelse      : Popper ZL og ZH registrerne fra stakken 
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro PopZRegisters
 	PopRegisterFromStack 	ZH
	PopRegisterFromStack 	ZL
.ENDMACRO

/********************************************************************************************************
  Macronavn        : IncrementZRegisters
  Beskrivelse      : Lægger argument til ZL register og tager højde for Carry. Er Carry sat, 
                     vil der blive adderet 1 til ZH register 
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro IncrementZRegisters
 	AddRegisters	ZL, @0
	BranchIfCarryCleared	DontIncrementZHRegister
	IncrementValueInRegister	ZH
DontIncrementZHRegister:	
.ENDMACRO


/********************************************************************************************************
 Slut på Macro definitioner. 
*********************************************************************************************************/


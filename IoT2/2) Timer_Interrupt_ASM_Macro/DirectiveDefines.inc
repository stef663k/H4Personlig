/*
 * DirectiveDefines.inc
 *
 *  Created: 07-12-2023 14:18:10
 *   Author: ltpe
 */ 

 /********************************************************************************************************
  Macronavn        : SpecifyCodeSegment
  Beskrivelse      : Specificer at kode/variabler herefter skal placeres i Code
                     segmentet => FlashProm.
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro SpecifyCodeSegment
 	.cseg
.ENDMACRO

/********************************************************************************************************
  Macronavn        : SpecifyDataSegment
  Beskrivelse      : Specificer at variabler erklæret herefter skal placeres i 
                     Data segmentet => Intern RAM eller ekstern RAM
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro SpecifyDataSegment
 	.dseg
.ENDMACRO

/********************************************************************************************************
  Macronavn        : SpecifyEEpromSegment
  Beskrivelse      : Specificer at variabler erklæret herefter skal placeres i 
                     EEprom segmentet => placeret i EEprom
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro SpecifyEEpromSegment
 	.eseg
.ENDMACRO

/********************************************************************************************************
  Macronavn        : PlaceOnAddress
  Beskrivelse      : Specificer at koden/variablerne herefter bliver placeret 
                     på den angivne adresse i det angivne segment =>
					 .cseg, .dseg eller .eseg 
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 .Macro PlaceOnAddress
 	.org	@0
.ENDMACRO

/********************************************************************************************************
  Macronavn        : SpecifyByteValues
  Beskrivelse      : Specificer at variablen her er en Byte (8 bit) variabel. 
					 Argumentet specificerer antal bytes til variablen.
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 /*.Macro SpecifyByteValues
 	.BYTE	@0
.ENDMACRO*/


/********************************************************************************************************
  Macronavn        : IncludeFile
  Beskrivelse      : Inkluder den specificerede fil.
  Input            : Ingen
  Output           : ingen
  Registre anvendt : Ingen
  Kalder		   : Ingen
 *********************************************************************************************************/
 /*.Macro IncludeFile
 	.Include	@0
.ENDMACRO*/

/********************************************************************************************************
 Slut på Directive definitioner. 
*********************************************************************************************************/

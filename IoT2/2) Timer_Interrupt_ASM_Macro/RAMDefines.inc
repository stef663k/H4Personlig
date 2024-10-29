/*
 * RAMDefines.inc
 *
 *  Created: 01-01-2018 12:48:51
 *   Author: ltpe
 */ 

 /********************************************************************************************************
 Intern Ram definitioner følger herefter.
*********************************************************************************************************/
		SpecifyDataSegment
				
		PlaceOnAddress	SRAM_START
		
		Timer0OverflowCounter: .BYTE	     	1	; Counter til at tælle antal Timer0 Overfæow Interrupts
		Timer0OverflowCounterStopValue: .BYTE	1	; Stop Counter værdi for antal Timer0 Overfæow Interrupts	
					
/********************************************************************************************************
 Slut på Intern Ram definitioner. 
*********************************************************************************************************/

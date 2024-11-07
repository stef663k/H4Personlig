/*
 * h3pd040120_Pointer.c
 *
 * Created: 04-05-2020 22:30:40
 * Author : ltpe
 */ 

#include <avr/io.h>
#include <string.h>
#include "uart.h"

void Change_Numbers_Without_Pointers(uint8_t Number1Func, uint8_t Number2Func)
{
	uint8_t TempNumber;
	
	TempNumber = Number1Func;
	Number1Func = Number2Func;
	Number2Func = TempNumber;
}

void Change_Numbers_With_Pointers(uint8_t* Number1Func, uint8_t* Number2Func)
{
	uint8_t TempNumber;
	
	TempNumber = *Number1Func;
	*Number1Func = *Number2Func;
	*Number2Func = TempNumber;
}

int main(void)
{
	uint8_t Number1 = 10;
	uint8_t Number2 = 20;
	
	uint8_t *pUint8_t;
	
	RS232Init();
	//printf("Number 1 er : %d og Number 2 er : %d\n", Number1, Number2);
	
	Change_Numbers_Without_Pointers(Number1, Number2);
	//printf("Number 1 er : %d og Number 2 er : %d\n", Number1, Number2);
	
	Change_Numbers_With_Pointers(&Number1, &Number2);
	//printf("Number 1 er : %d og Number 2 er : %d\n", Number1, Number2);
	//
	uint16_t ReceivedNumber = 0x24;
	uint8_t ContentOnAdress = 0xFF;
	
	//pUint8_t = (uint8_t *)0x24;
	//*pUint8_t = 0xFF;
	//pUint8_t = (uint8_t *)0x25;
	//*pUint8_t = 0xFF;
	
	pUint8_t = (uint8_t *)ReceivedNumber;
	*pUint8_t = ContentOnAdress;
	ReceivedNumber++;
	pUint8_t = (uint8_t *)ReceivedNumber;
	*pUint8_t = ContentOnAdress;
	
	// Uden brug af pointere herunder !!!! => Meget lang og træls kode.
	//if (ReceivedNumber == 0x24)
	//{
		//DDRB = ContentOnAdress;
	//}
	//if (ReceivedNumber == 0x25)
	//{
		//PORTB = ContentOnAdress;
	//}
	
		
    /* Replace with your application code */
    while (1) 
    {
    }
}


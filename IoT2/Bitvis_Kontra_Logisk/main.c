/*
 * Bitvis_Kontra_Logisk.c
 *
 * Created: 09-01-2018 15:34:55
 * Author : ltpe
 */ 

#include <avr/io.h>
#include "bitwise_operations.h"
#include "UART.h"

uint16_t Add8BitNumbers(uint8_t Number1, uint8_t Number2)
{
	return (Number1 + Number2);
}

int main(void)
{
	
	uint8_t Var1 = 0xF8;
	uint8_t Var2 = 0x01;

	uint8_t Var3;
	uint8_t Var4;
	uint8_t Var5;
	uint8_t Var6;

	uint16_t AddResult;
	
	UART_Init(9600);
	uint16_t initialValue = Var1;
	simulateBitSetting(initialValue);
	// Sandhedstabel for OR
	// 0     0     0
	// 0     1     1
	// 1     0     1
	// 1     1     1
	
	// Sandhedstabel for AND
	// 0     0     0
	// 0     1     0
	// 1     0     0
	// 1     1     1

	Var3 = Var1 || Var2;
	// Logisk OR. Hvis enten Var1 eller Var2 er forskellig fra 0, vil
	// Var3 blive lig med 1. Hvis b�de Var1 og Var2 er lig med 0, vil
	// Var3 blive lig med 0. Var3 kan s�ledes kun f� v�rdien 0 eller 1 !!! 

	// For m�ske at g�re ovenn�vnte lidt mere klart, kan man ogs� skrive 
	// det p� m�den vist herunder. Paranteserne i udtrykket er kun 
	// medtaget for overskuelighedens skyld og er ikke n�dvendige. 
	Var3 = (Var1 != 0) || (Var2 != 0);	

	Var4 = Var1 |  Var2;
	// Bitvis OR. Hver bit position i Var1 udf�rer en OR operation p� den 
	// samme bit position i Var2. Var4 vil s�ledes kunne f� alle v�rdier mellem 
	// 0 og 255 (0x00 - 0xFF).
	
	Var5 = Var1 && Var2;
	// Logisk AND. Hvis b�de Var1 og Var2 er forskellig fra 0, vil
	// Var5 blive lig med 1. Hvis enten Var1 eller Var2 er lig med 0, vil
	// Var5 blive lig med 0. Var5 kan s�ledes kun f� v�rdien 0 eller 1 !!!

	Var6 = Var1 & Var2;
	// Bitvis AND. Hver bit position i Var1 udf�rer en AND operation p� den
	// samme bit position i Var2. Var6 vil s�ledes kunne f� alle v�rdier mellem
	// 0 og 255 (0x00 - 0xFF)

	AddResult = Add8BitNumbers(0xaa, 0xbb);

	DDRB = 0xFF;

	PORTB = (1 << PB4) || (1 << PB2);
	// Forkert m�de at s�tte PORT B op p�. Port B vil altid f� v�rdien 1. Det vil sige Port B
	// bit position 0 vil blive sat. Og det var ikke vores mening !!!

	PORTB = (1 << PB4) | (1 << PB2);
	// Rigtig m�de at s�tte PORT B op p�. Port B vil nu f� v�rdien 0x14. Og det var det, vi gerne 
	// ville. S�tte bit 2 og bit 4 i Port B og resette alle andre bit i Port B.

	PORTB |= (1 << PB0);
	// Efter den initielle ops�tning af Port B �nsker vi nu at s�tte bit 0 i Port B uden at r�re 
	// ved nogen af de andre bit i PORT B.

	PORTB = PORTB | (1 << PB0);
	// S�tningen i linje 76 kunne ogs� v�re skrevet som vist i linje 80 
	
	PORTB |= ( (1 << PB7) | (1 << PB6) );
	// Efter den initielle ops�tning af Port B �nsker vi nu at s�tte bit 7 og bit 6 i Port B uden at 
	// r�re ved nogen af de andre bit i PORT B.

	PORTB &= ~(1 << PB2);
	// Efter den initielle ops�tning af Port B �nsker vi nu at resette bit 2 i Port B uden at r�re
	// ved nogen af de andre bit i PORT B.

	PORTB &= ~( (1 << PB7) | (1 << PB6) );
	// Efter den initielle ops�tning af Port B �nsker vi nu at resette bit 7 og bit 6 i Port B uden 
	// at r�re ved nogen af de andre bit i PORT B.
	
	Var4 = (Var1 != 0) |  (Var2 != 0);
	// Kodelinjen herover er lidt fr�k. Her blander vi faktisk en bitvis or operator
	// med 2 logiske operatorer != 0. Derfor vil vores vores output (afh�ngig af v�rdierne
	// af Var1 og Var2 kun kunne f� v�rdien 0 eller 1.
	
	Var4 = (Var1 != 0) ||  (Var2 != 0);
	// Kodelinjen herover indeholder "kun" logiske operatorer. Derfor vil vores vores output (afh�ngig af v�rdierne
	// af Var1 og Var2 kun kunne f� v�rdien 0 eller 1.
	
	Var4 = (Var2 != 0) |  Var1;
	// Igen er vi lidt fr�kke og blander bitvise og logiske operatorer. Her vil vores output (afh�ngig
	// af v�rdierne af Var1 og Var2) kunne antage alle v�rdier mellem 0 og 255.
	
	Var4 = (Var1 != 0) | (Var2 != 0) | Var1;
	// Igen er vi lidt fr�kke og blander bitvise og logiske operatorer. Her vil vores output (afh�ngig
	// af v�rdierne af Var1 og Var2) kunne antage alle v�rdier mellem 0 og 255.
	
	Var4 = (Var1 != 0 || Var2 != 0) | Var1;
	// Igen er vi lidt fr�kke og blander bitvise og logiske operatorer. Her vil vores output (afh�ngig
	// af v�rdierne af Var1 og Var2) kunne antage alle v�rdier mellem 0 og 255.
	
	Var4 = (Var1 != 0) |  (Var2 != 0 | Var1);
	// Igen er vi lidt fr�kke og blander bitvise og logiske operatorer. Her vil vores output (afh�ngig
	// af v�rdierne af Var1 og Var2) kunne antage alle v�rdier mellem 0 og 255.
	
	Var4 = (Var1 != 0) ||  (Var2 != 0 | Var1);
	// Igen er vi lidt fr�kke og blander bitvise og logiske operatorer. Her vil vores output (afh�ngig
	// af v�rdierne af Var1 og Var2) kunne antage alle v�rdier mellem 0 og 255. 

    /* Replace with your application code */
    while (1) 
    {
    }
}


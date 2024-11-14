
#include <avr/io.h>
#include "../main.h"

#ifndef PROJECTDEFINES_H_
#define PROJECTDEFINES_H_


#define UART_NORMAL_MODE


//#if defined (_AVR_IOM168_H_) || defined (_AVR_IOM328P_H_)
//#define USR_Vect_Num USART_RX_vect
//
//#define UBRRL UBRR0L
//#define UBRRH UBRR0H
//#define UCSRA UCSR0A
//#define UCSRB UCSR0B
//#define UCSRC UCSR0C
//
//#define RXEN RXEN0
//#define TXEN TXEN0
//
//#define UCSZ0 UCSZ00
//#define UCSZ1 UCSZ01
//
//#define RXCIE RXCIE0
//
//#define RXC   RXC0
//#define UDRE  UDRE0
//
//#define UDR	  UDR0
//
//#define U2X   U2X0
//
//#endif

#if defined (_AVR_IOM2560_H_) || defined (_AVR_ATMEGA328PB_H_INCLUDED)
#define USR_Vect_Num USART1_RX_vect

#define UBRRL UBRR0L
#define UBRRH UBRR0H
#define UCSRA UCSR0A
#define UCSRB UCSR0B
#define UCSRC UCSR0C

#define RXEN RXEN0
#define TXEN TXEN0

#define UCSZ0 UCSZ00
#define UCSZ1 UCSZ01

#define RXCIE RXCIE0

#define RXC   RXC0
#define UDRE  UDRE0

#define UDR	  UDR0

#define U2X   U2X0

#define UBRRL UBRR1L
#define UBRRH UBRR1H
#define UCSRA UCSR1A
#define UCSRB UCSR1B
#define UCSRC UCSR1C

#define RXEN RXEN1
#define TXEN TXEN1

#define UCSZ0 UCSZ10
#define UCSZ1 UCSZ11

#define RXCIE RXCIE1

#define RXC   RXC1
#define UDRE  UDRE1

#define UDR	  UDR1

#define U2X   U2X1

#endif

#define GreenLedBit		1
#define YellowLedBit	2
#define RedLedBit		3


#define TimeoutBaseValueDefaultInMilliseconds 1000

#define MaxDigitsInTimeoutArray 5
#define TimeoutValueEndCharacter ':'
#define SizeOFArray(arr)  ( (sizeof(arr) > 0) ? (sizeof(arr)/sizeof(arr[0])) : (0) )

typedef enum
{
	RETURN_UPPER_LETTERS = 0,
	RETURN_LOWER_LETTERS,
	NO_LETTER_CHANGE,
	ILLEGAL_LETTER_STATE
} CharState;

#define Upper_Lower_Bit_Position 5
#define Upper_Lower_Bit_Value (1 << Upper_Lower_Bit_Position)

#define NumberBase 10
#define CharArrayEndCharacter '\0'
#define MAX_NUMBER_OF_LINES_IN_DISPLAY	8

typedef void (*Function_Pointer_With_No_Parameters)(void);
typedef void (*Function_Pointer_With_One_Uint16_t_Parameter)(uint16_t);
typedef void (*Function_Pointer_With_One_Uint32_t_Parameter)(uint32_t);
typedef void (*Function_Pointer_With_One_Char_Parameters)(char);

#endif /* PROJECTDEFINES_H_ */
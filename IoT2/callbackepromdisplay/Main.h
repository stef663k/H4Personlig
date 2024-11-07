/*
 * Main.h
 *
 * Created: 16-01-2018 13:03:52
 *  Author: ltpe
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#define Max_Number_Of_Characters_In_String 256

extern void ConvertReceivedChar(char *ReceivedChar);
extern void ReceiveNewTimeoutValue(char *ReceivedChar);

#endif /* MAIN_H_ */
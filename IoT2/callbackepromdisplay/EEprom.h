/*
 * EEprom.h
 *
 * Created: 26-04-2019 09:09:32
 *  Author: ltpe
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

typedef const uint8_t *EEpromConstBytePointer;
typedef const uint16_t *EEpromConstWordPointer;

typedef uint8_t *EEpromBytePointer;
typedef uint16_t *EEpromWordPointer;

extern uint8_t EEprom_Read_Byte(uint16_t EEProm_Address);
extern uint16_t EEprom_Read_Word(uint16_t EEProm_Address);
extern void EEprom_Write_Byte(uint16_t EEProm_Address, uint8_t EEprom_Value);
extern void EEprom_Write_Word(uint16_t EEProm_Address, uint16_t EEprom_Value);
extern void EEprom_Read_Block(char *Ram_Pointer, uint16_t EEProm_Address, uint8_t NumberOfBytes);
extern void EEprom_Read_String(char *Ram_Pointer, uint16_t EEProm_Address);

#endif /* EEPROM_H_ */
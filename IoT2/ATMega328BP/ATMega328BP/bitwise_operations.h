#ifndef BIT_OPERATIONS_H
#define BIT_OPERATIONS_H

#include <stdint.h>

uint8_t setBit(uint8_t value, uint8_t position);
uint8_t clearBit(uint8_t value, uint8_t position);
void simulateBitSetting(uint8_t initialValue);
void HandleUARTCommand(char command, uint8_t bitPositions);

#endif // BIT_OPERATIONS_H

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include <stdint.h>

typedef enum {
	Modtag_Adresse,
	Modtag_Bit_Position_I_Adresse,
	Modtag_Bit_Position_Vaerdi
}State;

void handle_state_machine(State *currentState, char recivedChar, uint8_t *address);

#endif /* STATE_MACHINE_H_ */
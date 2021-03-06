/* Kennen DeRenard, kdere004@ucr.edu
 * Lab Section: 023
 * Assignment: Custom Lab Project
 * Reset Button State Machine
 */

#include <avr/io.h>
#include "includes/globals.h"
#include "includes/reset_sm.h"

unsigned char reset = 0;

int RES_TickFct(int state) {
	unsigned char button = (tmpC & 0x10) >> 4;

	switch (state) {
		case RES_Start:
			state = RES_IDLE;
			break;
		case RES_IDLE:
			if (button == 0x01) {
				reset = 1;
				state = RES_WAIT;
			} else {
				state = RES_IDLE;
			}
			break;
		case RES_WAIT:
			if (button == 0x01) {
				reset = 0;
				state = RES_WAIT;
			} else {
				state = RES_IDLE;
			}
			break;
		default:
			break;
	}
	return state;
} 

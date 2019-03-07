/* Kennen DeRenard, kdere004@ucr.edu
 * Lab Section: 023
 * Assignment: Custom Lab Project
 * Switch Control State Machine
 */

#include <avr/io.h>
#include "includes/globals.h"
#include "includes/switches_sm.h"

unsigned char action = 0;

int SWIT_TickFct(int state) {
	unsigned char draw = (tmpC & 0x20) >> 5;
	unsigned char erase = (tmpC & 0x40) >> 6;

	switch (state) {
		case SWIT_Start:
			action = MOVE;
			state = SWIT_UPDATE;
			break;
		case SWIT_UPDATE:
			if (draw == 0x01 && erase == 0x00) {
				action = DRAW;
			} else if (draw == 0x00 && erase == 0x01) {
				action = ERASE;
			} else {
				action = MOVE;
			}
			break;
		default:
			break;
	}
	return state;
}
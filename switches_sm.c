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
	unsigned char draw = (PINC & 0x40) >> 6;
	unsigned char erase = (PINC & 0x20) >> 5;

	switch (state) {
		case SWIT_Start:
			action = MOVE;
			state = SWIT_UPDATE;
			break;
		case SWIT_UPDATE:
			if (draw && !erase) {
				action = DRAW;
			} else if (!draw && erase) {
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
/* Kennen DeRenard, kdere004@ucr.edu
 * Lab Section: 023
 * Assignment: Custom Lab Project
 * Joystick State Machine
 */

#include "includes/adc.h"
#include "includes/globals.h"
#include "includes/joystick_sm.h"

unsigned char globalX = 0;
unsigned char globalY = 0;
unsigned char localY = 0;
unsigned char lastGlobalX = 0;
unsigned char lastGlobalY = 0;

int JOY_TickFct(int state) {
	static unsigned char direction;	

	switch (state) {
		case JOY_Start:
			ADC_init();
			state = JOY_UPDATE;
			break;
		case JOY_UPDATE:
			lastGlobalX = globalX;
			lastGlobalY = globalY;
			direction = GetDirection();
			if (direction == UP) {
				if (localY > 0) {
					localY--;
				} else if (globalY > 0) {
					globalY--;
					localY = 7;
				}
			} else if (direction == DOWN) {
				if (localY < 7) {
					localY++;
				} else if (globalY < 5) {
					globalY++;
					localY = 0;
				}
			} else if (direction == LEFT) {
				if (globalX > 0) {
					globalX--;
				}
			} else if (direction == RIGHT) {
				if (globalX < 83) {
					globalX++;
				}
			}
			state = JOY_UPDATE;
			break;
		default:
			break;
	}
	return state;
}
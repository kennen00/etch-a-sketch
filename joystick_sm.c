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
			direction = GetDirection();
			if (direction == UP) {
				if (localY > 0) {
					localY--;
				} else if (globalY > 0) {
					lastGlobalY = globalY;
					globalY--;
					localY = 7;
				} else {
					lastGlobalY = globalY = 0;
				}
			} else if (direction == DOWN) {
				if (localY < 7) {
					localY++;
				} else if (globalY < 5) {
					lastGlobalY = globalY;
					globalY++;
					localY = 0;
				} else {
					lastGlobalY = globalY = 5;
				}
			} else if (direction == LEFT) {
				if (globalX > 0) {
					lastGlobalX = globalX;
					globalX--;
				} else {
					lastGlobalX = globalX = 0;
				}
			} else if (direction == RIGHT) {
				if (globalX < 83) {
					lastGlobalX = globalX;
					globalX++;
				} else {
					lastGlobalX = globalX = 83;
				}
			}
			state = JOY_UPDATE;
			break;
		default:
			break;
	}
	return state;
}
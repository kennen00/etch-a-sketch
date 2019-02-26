/* Kennen DeRenard, kdere004@ucr.edu
 * Lab Section: 023
 * Assignment: Custom Lab Project
 * LCD Display State Machine
 */

#include "includes/lcd.h"
#include "includes/globals.h"
#include "includes/display_sm.h"

int DISP_TickFct(int state) {
	static unsigned char screen[84][6] = {0};
	static unsigned char globalX = 0, globalY = 0, localY = 0;
	switch (state) {
		case DISP_Start:
			LCD_init();
			state = DISP_UPDATE;
			break;
		case DISP_UPDATE:
			LCD_set_XY(globalX, globalY);
			screen[globalX][globalY] = screen[globalX][globalY] | (1 << localY);
			LCD_write_byte(screen[globalX][globalY], 0);
			if (globalX < 83) {
				globalX++;
			} else {
				globalX = 0;
				if (localY < 7) {
					localY++;
				} else if (globalY < 5) {
					globalY++;
					localY = 0;
				} else {
					globalY = 0;
					localY = 0;
				}
			}
			state = DISP_UPDATE;
			break;
	}
	return state;
}
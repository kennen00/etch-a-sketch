/* Kennen DeRenard, kdere004@ucr.edu
 * Lab Section: 023
 * Assignment: Custom Lab Project
 * LCD Display State Machine
 */

#include <string.h>
#include "includes/lcd.h"
#include "includes/globals.h"
#include "includes/display_sm.h"
#include "includes/reset_sm.h"

int DISP_TickFct(int state) {	
	static unsigned char screen[84][6] = {0};
	switch (state) {
		case DISP_Start:
			LCD_init();
			state = DISP_UPDATE;
			break;
		case DISP_UPDATE:
			if (reset) {
				LCD_clear();
				memset(screen, 0, sizeof(screen));
			} else {
				LCD_set_XY(globalX, globalY);
				screen[globalX][globalY] = screen[globalX][globalY] | (1 << localY);
				LCD_write_byte(screen[globalX][globalY], 0);
			}
			state = DISP_UPDATE;
			break;
		default:
			break;
	}
	return state;
}
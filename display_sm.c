/* Kennen DeRenard, kdere004@ucr.edu
 * Lab Section: 023
 * Assignment: Custom Lab Project
 * LCD Display State Machine
 */

#include <string.h>
#include "includes/lcd.h"
#include "includes/globals.h"
#include "includes/display_sm.h"

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
				// Refresh entire screen here to fix output glitching issues
				for (unsigned char i = 0; i < 84; i++) {
					for (unsigned char j = 0; j < 6; j++) {
						LCD_set_XY(i, j);
						LCD_write_byte(screen[i][j], 0);
					}
				}
				LCD_set_XY(globalX, globalY);
				if (action == DRAW) {
	 				screen[globalX][globalY] |= (1 << localY);
			 		LCD_write_byte(screen[globalX][globalY], 0);
				} else if (action == ERASE) {
					LCD_write_byte(screen[globalX][globalY] | (1 << localY), 0);
	 				screen[globalX][globalY] &= ~(1 << localY);
					LCD_set_XY(globalX, globalY);
		 			LCD_write_byte(screen[globalX][globalY], 0);
				} else if (action == MOVE) {
					LCD_write_byte(screen[globalX][globalY] | (1 << localY), 0);
					LCD_set_XY(lastGlobalX, lastGlobalY);
					LCD_write_byte(screen[lastGlobalX][lastGlobalY], 0);
				}
			}
			state = DISP_UPDATE;
			break;
		default:
			break;
	}
	return state;
}
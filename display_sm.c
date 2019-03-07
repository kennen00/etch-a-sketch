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
	static unsigned char lastByte = 0;

	switch (state) {
		case DISP_Start:
			LCD_init();
			state = DISP_UPDATE;
			break;
		case DISP_UPDATE:
			if (reset) {
				LCD_clear();
				/*unsigned char i = 0, j = 0;
				for (i = 0; i < 84; i++) {
					for (j = 0; j < 6; j++) {
						screen[i][j] = 0;
						LCD_set_XY(i,j);
						LCD_write_byte(0,0);
					}
				}*/
				memset(screen, 0, sizeof(screen));
			} else {
	 			LCD_set_XY(globalX, globalY);
				if (action == MOVE) {
					LCD_set_XY(lastGlobalX, lastGlobalY);
					screen[lastGlobalX][lastGlobalY] = lastByte;
					LCD_write_byte(lastByte, 0);
					lastByte = screen[globalX][globalY];
					LCD_set_XY(globalX, globalY);
					screen[globalX][globalY] |= (1 << localY);
				} else if (action == DRAW) {
	 				screen[globalX][globalY] |= (1 << localY);
				} else if (action == ERASE) {
	 				screen[globalX][globalY] &= ~(1 << localY);
				}
	 			LCD_write_byte(screen[globalX][globalY], 0);
			}
			state = DISP_UPDATE;
			break;
		default:
			break;
	}
	return state;
}
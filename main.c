/* Kennen DeRenard, kdere004@ucr.edu
 * Lab Section: 023
 * Assignment: Custom Lab Project
 * Main driver file for the system
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <bit.h>
#include <timer.h>
#include <stdio.h>
#include "includes/scheduler.h"
#include "includes/display_sm.h"

// Implement scheduler code from PES.
int main()
{
	DDRC = 0xFF; PORTC = 0x00;

	unsigned long int DISP_calc = 25;

	unsigned long int tmpGCD = DISP_calc;

	unsigned long int GCD = tmpGCD;

	unsigned long int DISP_period = DISP_calc/GCD;

	static task task1;
	task *tasks[] = { &task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	task1.state = DISP_Start;
	task1.period = DISP_period;
	task1.elapsedTime = DISP_period;
	task1.TickFct = &DISP_TickFct;

	TimerSet(GCD);
	TimerOn();

	unsigned short i;
	while(1) {
		for ( i = 0; i < numTasks; i++ ) {
			if ( tasks[i]->elapsedTime == tasks[i]->period ) {
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}

	// Error: Program should not exit!
	return 0;
}
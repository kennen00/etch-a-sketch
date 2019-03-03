/* Kennen DeRenard, kdere004@ucr.edu
 * Lab Section: 023
 * Assignment: Custom Lab Project
 * Main driver file for the system
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <timer.h>
#include <stdio.h>
#include "includes/scheduler.h"
#include "includes/display_sm.h"
#include "includes/joystick_sm.h"
#include "includes/reset_sm.h"
#include "includes/switches_sm.h"

// Implement scheduler code from PES.
int main()
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0x0F; PORTC = 0x00;

	unsigned long int DISP_calc = 50;
	unsigned long int JOY_calc = 100;
	unsigned long int RES_calc = 50;
	unsigned long int SWIT_calc = 50;

	unsigned long int tmpGCD = findGCD(DISP_calc, JOY_calc);
	tmpGCD = findGCD(tmpGCD, RES_calc);
	tmpGCD = findGCD(tmpGCD, SWIT_calc);

	unsigned long int GCD = tmpGCD;

	unsigned long int DISP_period = DISP_calc/GCD;
	unsigned long int JOY_period = JOY_calc/GCD;
	unsigned long int RES_period = RES_calc/GCD;
	unsigned long int SWIT_period = SWIT_calc/GCD;

	static task task1, task2, task3, task4;
	task *tasks[] = { &task1, &task2, &task3, &task4};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	task1.state = DISP_Start;
	task1.period = DISP_period;
	task1.elapsedTime = DISP_period;
	task1.TickFct = &DISP_TickFct;

	task2.state = JOY_Start;
	task2.period = JOY_period;
	task2.elapsedTime = JOY_period;
	task2.TickFct = &JOY_TickFct;

	task3.state = RES_Start;
	task3.period = RES_period;
	task3.elapsedTime = RES_period;
	task3.TickFct = &RES_TickFct;

	task4.state = SWIT_Start;
	task4.period = SWIT_period;
	task4.elapsedTime = SWIT_period;
	task4.TickFct = &SWIT_TickFct;

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

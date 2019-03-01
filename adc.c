/* Kennen DeRenard, kdere004@ucr.edu
 * Lab Section: 023
 * Assignment: Custom Lab Project
 * ADC conversion for the joystick
 * ADC functions adapted from http://maxembedded.com/2011/06/the-adc-of-the-avr/
 */

 #include "includes/adc.h"
 #include <avr/io.h>

void ADC_init() {
	// AREF = AVcc
	ADMUX = (1<<REFS0);
	
	// ADC Enable and prescaler of 128
	// 16000000/128 = 125000
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t ADC_read(uint8_t ch)
{
	// select the corresponding channel 0~7
	// ANDing with �7? will always keep the value
	// of �ch� between 0 and 7
	ch &= 0b00000111;  // AND operation with 7
	ADMUX = (ADMUX & 0xF8)|ch; // clears the bottom 3 bits before ORing
	
	// start single convertion
	// write �1? to ADSC
	ADCSRA |= (1<<ADSC);
	
	// wait for conversion to complete
	// ADSC becomes �0? again
	// till then, run loop continuously
	while(ADCSRA & (1<<ADSC));
	
	return (ADC);
}

unsigned char GetDirection() {
	uint16_t middle = 512;

	uint16_t verticalVal = ADC_read(0);
	uint16_t horizontalVal = ADC_read(1);
	
	if (verticalVal > middle + 100) {
		return UP;
	} else if (verticalVal < middle - 100){
		return DOWN;
	} else if (horizontalVal > middle + 100) {
		return LEFT;
	} else if (horizontalVal < middle - 100) {
		return RIGHT;
	} else {
		return IDLE;
	}
}
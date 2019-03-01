#ifndef __ADC_H__
#define __ADC_H__

enum DIRECTION {IDLE, UP, DOWN, LEFT, RIGHT};

void ADC_init();
unsigned char GetDirection();

#endif
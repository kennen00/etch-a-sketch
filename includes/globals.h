#ifndef __GLOBALS_H__
#define __GLOBALS_H__

// Shared SM Variables
extern unsigned char globalX;
extern unsigned char globalY;
extern unsigned char localY;
extern unsigned char lastGlobalX;
extern unsigned char lastGlobalY;
extern unsigned char reset;
extern unsigned char action;

// Shared Enums
enum DIRECTION {IDLE, UP, DOWN, LEFT, RIGHT};
enum ACTION {MOVE, DRAW, ERASE};

#endif
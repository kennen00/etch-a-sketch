#ifndef __RESET_SM_H__
#define __RESET_SM_H__

enum RES_States {RES_Start, RES_IDLE, RES_WAIT};

extern int RES_TickFct(int state);

#endif
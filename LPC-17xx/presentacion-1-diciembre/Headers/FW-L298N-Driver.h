
#ifndef FW_L293N_DRIVER_H_
#define FW_L293N_DRIVER_H_

#include <RobotExplorador.h>


extern uint8_t Buffer_For_L293D;

void DriverPuenteH (void);


#define A_MAS	1,21
#define A_MENOS	1,22

#define B_MAS	0,30
#define B_MENOS	0,29

#define C_MAS	0,10
#define C_MENOS	0,11

#define D_MAS	2,7
#define D_MENOS	2,8

						//PINMODE
#define	PULLUP		0
#define REPEATER	1
#define NEITHER 	2
#define	PULLDOWN 	3
						//FIODIR
#define OUTPUT	1
#define INPUT	0

#endif /*FW_L293N_DRIVER_H_*/

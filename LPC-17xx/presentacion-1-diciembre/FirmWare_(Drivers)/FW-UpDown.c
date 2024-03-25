#include "RobotExplorador.h"
#include "FW-UpDown.h"
uint8_t flag_updown=0;

void InitUpDown(void)
{
	//Funcion GPIO

	SetPINSEL(UPDOWN,0);

	//Direccion entrada
	SetDIR(UPDOWN,0);
	SetPINMODE(UPDOWN,NEITHER);

}

void mercurio(void)
{
	flag_updown = GetPIN(UPDOWN,ALTO);
}




#include "PR-PWM.h"


void VariadordeVelocidad(Motor select, uint8_t velocidad)
{
	switch(select)
	{
	case MotorA:
		g_motorA_PWM = velocidad;
		break;

	case MotorB:
		g_motorB_PWM = velocidad;
		break;

	case MotorC:
		g_motorC_PWM = velocidad;
		break;

	case MotorD:
		g_motorD_PWM = velocidad;
		break;
	}

	//Vuelvo a cargar los match y reinicio los latch
	DutyCiclePWM();
}




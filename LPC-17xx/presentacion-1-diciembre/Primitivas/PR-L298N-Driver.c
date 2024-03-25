#include "PR-PWM.h"
#include "PR-L298N-Driver.h"
#include "FW-L298N-Driver.h"


	void Motores(PuenteH seleccion,uint8_t valor)
	{
		switch (seleccion)
		{
			case AdelanteA:
				if(valor)
					Buffer_For_L293D |= (1 << 0);
				else
					Buffer_For_L293D &= ~(1 << 0);
				break;

			case AtrasA:
				if(valor)
					Buffer_For_L293D |= (1 << 1);
				else
					Buffer_For_L293D &= ~(1 << 1);
				break;

			case AdelanteB:
				if(valor)
					Buffer_For_L293D |= (1 << 2);
				else
					Buffer_For_L293D &= ~(1 << 2);
				break;

			case AtrasB:
				if(valor)
					Buffer_For_L293D |= (1 << 3);
				else
					Buffer_For_L293D &= ~(1 << 3);
				break;

			case AdelanteC:
				if(valor)
					Buffer_For_L293D |= (1 << 4);
				else
					Buffer_For_L293D &= ~(1 << 4);
				break;

			case AtrasC:
				if(valor)
					Buffer_For_L293D |= (1 << 5);
				else
					Buffer_For_L293D &= ~(1 << 5);
				break;

			case AdelanteD:
				if(valor)
					Buffer_For_L293D |= (1 << 6);
				else
					Buffer_For_L293D &= ~(1 << 6);
				break;

			case AtrasD:
				if(valor)
					Buffer_For_L293D |= (1 << 7);
				else
					Buffer_For_L293D &= ~(1 << 7);
				break;
			}
	}








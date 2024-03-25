#ifndef PW_L293N_DRIVER_H_
#define PW_L293N_DRIVER_H_
#include "FW-L298N-Driver.h"

typedef enum {
	AdelanteA,AtrasA,AdelanteB,AtrasB,AdelanteC,AtrasC,AdelanteD,AtrasD
} PuenteH;


void Motores(PuenteH seleccion, uint8_t valor);



#endif /*PW_L293N_DRIVER_H_*/

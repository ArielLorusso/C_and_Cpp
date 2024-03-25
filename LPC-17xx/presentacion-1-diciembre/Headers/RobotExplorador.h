
#ifndef INFOTRONIC_H_
#define INFOTRONIC_H

#include "RegsLPC1769.h"
#include "Oscilador.h"
#include "PR-Inputs.h"
#include "PR-L298N-Driver.h"
#include "PR-PWM.h"
#include <PR-Serie.h>
#include "PR-L298N-Driver.h"
#include <PR-Serie.h>
#include <PR-Ultrasonido.h>
#include "PR-UpDown.h"


#define INPUT_DEBOUNCE	2

//Definicion de teclas del teclado 4x1 de la placa
#define KEYA 0,21
#define KEYB 0,22
#define KEYC 0,27
#define KEYD 0,28


#define PULL_DOWN		3
#define PULL_UP			2


void DriverPuenteH (void);

uint8_t Tecla( void );

//Macros para CONFIG.c y GPIO.c
#define	ALTO	1
#define	BAJO	0

#define  ON		1
#define  OFF 	0

#define  SI		1
#define  NO 	0

void Inputs_Debounce(void);
void Inicializar ( void );
void InitPLL ( void );
void InicSysTick ( void );
void InitGPIOs(void);



#endif /* INFOTRONIC_H_ */

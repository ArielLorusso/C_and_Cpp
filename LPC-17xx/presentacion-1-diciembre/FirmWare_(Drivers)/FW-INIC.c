
#include "RobotExplorador.h"
#include "FW-Ultrasonido.h"
#include "FW-Timers.h"
#include "FW-UpDown.h"

/********************************************************************************
	\fn  void Inicializar ( void )
	\brief Inicializacion de Hardware.
	\author & date: Informática II
 	\param void
	\return:	void
*/
void Inicializar(void)
{
	InitPLL();
	InicSysTick();
	InitPWM();
	InitGPIOs();
	InitUART1();
	Inic_Ultrasonido();
	InitTimer0();
	InitTimer3();
	InitUpDown();

}

/********************************************************************************
	\fn  void InicSysTick ( void )
	\brief Inicialización de Interrupcion Systick.
	\author & date: Informática II
 	\param void
	\return:	void
*/
void InicSysTick ( void )
{
//	STRELOAD = (( STCALIB / 4) - 1);	// Recarga cada 2.5 ms
	STRELOAD = 25*100-1;				// Recarga cara 25 us, adaptado para los ultrasonidos
	STCURR = 0;	// Cargando con cero limpio y provoco el disparo de una intrrupcion
	// Habilito el conteo
	// Habilito interrupcion
	// Utilizamos Pclk
	STCTRL |=  ( ( 1 << ENABLE ) | ( 1 << TICKINT ) | ( 1 << CLKSOURCE ) );
}


void InitGPIOs(void)
{

	SetPINSEL(A_MAS,0);
	SetPINSEL(A_MENOS,0);


	SetPINSEL(B_MAS,0);
	SetPINSEL(B_MENOS,0);

	SetPINSEL(C_MAS,0);
	SetPINSEL(C_MENOS,0);


	SetPINSEL(D_MAS,0);
	SetPINSEL(D_MENOS,0);

	SetDIR(A_MAS,1);
	SetDIR(A_MENOS,1);


	SetDIR(B_MAS,1);
	SetDIR(B_MENOS,1);

	SetDIR(C_MAS,1);
	SetDIR(C_MENOS,1);


	SetDIR(D_MAS,1);
	SetDIR(D_MENOS,1);


//Teclado 4x1

	//Funcion GPIO
	SetPINSEL(KEYA,0);
	SetPINSEL(KEYB,0);
	SetPINSEL(KEYC,0);
	SetPINSEL(KEYD,0);

	//Direccion entrada
	SetDIR(KEYA,0);
	SetDIR(KEYB,0);
	SetDIR(KEYC,0);
	SetDIR(KEYD,0);

	SetPINMODE(KEYA,NEITHER);
	SetPINMODE(KEYB,NEITHER);
	SetPINMODE(KEYC,NEITHER);
	SetPINMODE(KEYD,NEITHER);

}

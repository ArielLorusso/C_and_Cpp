#include <RobotExplorador.h>

uint8_t Buffer_For_L293D = 0;

void DriverPuenteH ( void )
{
//	uint8_t aux = 0;

//	Apago todas las salidas
	SetPIN(A_MAS,OFF);
	SetPIN(A_MENOS,OFF);

	SetPIN(B_MAS,OFF);
	SetPIN(B_MENOS,OFF);

	SetPIN(C_MAS,OFF);
	SetPIN(C_MENOS,OFF);

	SetPIN(D_MAS,OFF);
	SetPIN(D_MENOS,OFF);

//	Pongo en ALTO las salidas
//	Buffer_for_L293D = {A+,A-,B+,B-,C+,C-,D+,D-}
//	El bit más significativo pertenece a A_MAS

	SetPIN(A_MAS,	(Buffer_For_L293D << 0)& (0x1 ) );
	SetPIN(A_MENOS, (Buffer_For_L293D >> 1)& (0x1 ) );
	SetPIN(B_MAS,	(Buffer_For_L293D >> 2)& (0x1 ) );
	SetPIN(B_MENOS, (Buffer_For_L293D >> 3)& (0x1 ) );
	SetPIN(C_MAS,	(Buffer_For_L293D >> 4)& (0x1 ) );
	SetPIN(C_MENOS,	(Buffer_For_L293D >> 5)& (0x1 ) );
	SetPIN(D_MAS,	(Buffer_For_L293D >> 6)& (0x1 ) );
	SetPIN(D_MENOS,	(Buffer_For_L293D >> 7)& (0x1 ) );

	/*
	SetPIN(A_MAS,	0 );
	SetPIN(A_MENOS, 0 );
	SetPIN(B_MAS,	0 );
	SetPIN(B_MENOS, 0 );
	SetPIN(C_MAS,	0 );
	SetPIN(C_MENOS,	0 );
	SetPIN(D_MAS,	0 );
	SetPIN(D_MENOS,	0 );*/
}

// 	Tabla de conversion 4 teclas A 16 acciones
//	teclas			A	B	C	D		Accion
//********************************************************************
//	0				0	0	0	0		Parado
//	1				1	0	0	0		Izquierda adelante
//	2				0	1	0	0		Derecha adelante
// 	3				1	1	0	0		Adelante
// 	4				0	0	1	0		Izquierda atras
// 	5				1	0	1	0		Nada de momento
//	6				0	1	1	0		Giro horario
//	7				1	1	1	0		Nada de momento
//	8				0	0	0	1		Derecha atras
// 	9				1	0	0	1		Giro antihorario
//	10				0	1	0	1		Nada de momento
//	11				1	1	0	1		Nada de momento
//	12				0	0	1	1		Nada de momento
//	13				1	0	1	1		Nada de momento
//	14				0	1	1	1		Nada de momento
//	15				1	1	1	1		Nada de momento



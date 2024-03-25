/**
 	\file FW_serie.c
 	\brief Drivers de comunicacion serie
 	\details
 	\author Pablo Irrera Condines
 	\date 2013.05.08
*/

#include <FW-GPIO.h>
#include <PR-Serie.h>
#include "RegsLPC1769.h"

uint8_t txStart;

void InitUART1(void)
{
	//1.- Registro PCONP - bit 4 en 1 prende la UART1:
	PCONP |= 0x01<<4;
	//2.- Registro PCLKSEL0 - bits 8 y 9 en 0 seleccionan que el clk de la UART1 sea 25MHz:
	PCLKSEL0 &= ~(0x03<<8);
//	PCLKSEL0 &= ~(0x01<<8);		//Prueba: PCLK=CCLK (100MHz)
	//3.- Registro U1LCR - transmision de 8 bits, 1 bit de stop, sin paridad, sin break cond, DLAB = 1:
	U1LCR = 0x00000083;
	//4.- Registros U0DLL y U0DLM - 9600 baudios:
	U1DLM = 0;
	U1DLL = 0xA3;		//9600 Br si PCLK = 25MHz
//	U1DLL = 0x37;		//114000 si el PCLK = 100MHz
	//5.- Registros PINSEL - habilitan las funciones especiales de los pines:
	SetPINSEL(PORT0,15,PINSEL_FUNC1);
	SetPINSEL(PORT0,16,PINSEL_FUNC1);
	//6.- Registro U1LCR, pongo DLAB en 0:
	U1LCR = 0x03;
	//7. Habilito las interrupciones (En la UART -IER- y en el NVIC -ISER)
	U1IER = 0x03;
	ISER0 |= (1<<6);
}

void UART1_IRQHandler (void)
{
	uint8_t iir, dato;

	do
	{
		//IIR es reset por HW, una vez que lo lei se resetea.
		iir = U1IIR;

		if ( iir & 0x02 ) //THRE
		{
			if( !PopTx(&dato) )
				U1THR = dato;
			else
				txStart = 0;
		}
		if ( iir & 0x04 ) //Data ready
		{
			PushRx((uint8_t )U1RBR );
		}

	}
	while( ! ( iir & 0x01 ) );  // me fijo si cuando entre a la ISR habia otra
						     	// int. pendiente de atencion: b0=1 (ocurre unicamente si dentro del mismo
								// espacio temporal lleguan dos interrupciones a la vez)
}

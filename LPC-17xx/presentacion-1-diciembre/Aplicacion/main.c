
#ifdef __USE_CMSIS
#include "LPC17xx.h"

#endif
#include "RobotExplorador.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void Comportamiento(void);          ///mover Comportamiento.h
void Esquivar(int* num);			///mover Comportamiento.h
uint8_t flag25us;
uint8_t	flag0_2s;


//Caracteres de control de trama
#define FRAME_START '$'
#define FRAME_END '#'
//Estados
#define E_INICIO_TRAMA	0
#define E_DATO			1
#define E_CHECKSUM		2
#define E_FIN_TRAMA		3

//Tamaño del buffer de datos
//#define TAM_BUFFER		6				//5 datos y el fin de linea
#define TAM_BUFFER		19					//18 datos y el fin de linea 0 , sin incluir($#) (Recepcion)

#define TAM_BUFF_TX		48					//8 sensores, 6 caracteres por sensor: 6x8=48

/*
 * NOTA DE ANGEL SOBRE '$' y '#' EN EL BUFFER
 *
 * ¿Porque el tamaño del buffer contempla los caracteres de fin e inicio de trama?
 * Esos caracteres no forman parte de los datos, el buffer solo almacena datos.
 * Esos datos son almacenados una vez extraidos de la trama.
 * Por lo tanto, nunca guarda esos dos caracteres y no tiene sentido considerarlos.
 *
 */
/****************************************************************************************/
    //Variables globales

	//Variable para compartir los datos recibidos (actuales) con las otras aplicaciones.
	uint32_t buffer_recibido = 0;

	//Variable para los primeros dos chars recibidos
	uint8_t buffer_PH = 0;

	//Variables para los dos chars de cada valor de velocidad de PWM
	uint8_t buffer_PWM[4] = {0};

	//Lo declaro global para probar con putty: el original esta dentro de la MdERx y no puedo leerlo desde el main
	//Borrar este en la version definitiva
	char buffer[TAM_BUFFER];

/*
 * Flags para temporizacion del piloto.
 * actualizar_piloto es el flag que evalua el piloto para leer el nuevo comando del buffer. Es activado por Systick.
 * nuevo_comando es el flag que utiliza el Systick para evaluar si hay un nuevo comando recibido por la MdE RX. En caso negativo, reemplaza el ultimo comando por ceros, parando el auto.
 * flag_enviar es el que se activa en el systick, para que el piloto realice el envio de los contenidos de los buffers
 */

	uint8_t flag_actualizar_piloto = 0;
	uint8_t flag_nuevo_comando = 0;
	uint8_t flag_enviar = 0;

//Flag de sensor de mercurio
	extern uint8_t flag_updown;

	uint8_t flag_InvertirControl=NO;

	uint8_t	flag_comportamiento;
	uint8_t	flag_Transmisor;
//Fin de Variables globales
/****************************************************************************************/

void MaqEstadosRx(void);	// declaracion
void MaqEstadosRx2(void);	//Igual pero sin checksum, para pruebas
void Piloto(void);
void Transmisor(void);
void EnviarDistancia(uint8_t sensor);

extern uint8_t flag_start;	//Flag de activacion de los sensores US


int main(void)
{
	Buffer_For_L293D = 0;
	Inicializar();

	flag_start = 1;

	while(1)
	{
		MaqEstadosRx2();
		Piloto();											//	LLAMADA AL PILOTO


		if(flag25us)										// estaba adentro del sistick  1
		{
			DriverPuenteH();
			mercurio();
			flag25us = 0;
			MdeTiming();
			MdeSensores();
		}

		if(flag_Transmisor)									// estaba adentro del sistick  8000
		{
			Transmisor();
			flag_Transmisor = 0;
		}
		if(flag_comportamiento)								// estaba adentro del sistick 3001
		{
			Comportamiento();
			flag_comportamiento = 0;
		}
	}
	return 0 ;
}
/////////////////////////////////////////// Funciones de comportamiento
#define DIST_LIMITE 30
//extern uint32_t buffer_tiempo[];
uint8_t comportamiento;  //flag- varieble global
void Comportamiento (void)	// llamada constantemente en el while(1) del main
{
	comportamiento = 0;
	uint8_t sensor [4]; uint8_t i;									//variavles de lectura de ultrasonidos
	for(i=0;i<4;i++ )	{sensor[i] = Ranging(i);  }		//lectura de ultrasonidos == Ranging
	if ((sensor[0]==0) || (sensor[1]==0) || (sensor[2]==0) ||(sensor[3]==0)) {}
	else if( (sensor[0]<DIST_LIMITE) || (sensor[1]<DIST_LIMITE) || (sensor[2]<DIST_LIMITE) || (sensor[3]<DIST_LIMITE) )
	{
		if (sensor[2]<DIST_LIMITE){ comportamiento += 1;}	//sensor A == bit 0	// guardo cuales sobrepasan el limite en comportamiento en comportamiento
		if (sensor[3]<DIST_LIMITE){ comportamiento += 2;}	//sensor B == bit 1
		if (sensor[0]<DIST_LIMITE){ comportamiento += 4;}	//sensor C == bit 2
		if (sensor[1]<DIST_LIMITE){ comportamiento += 8;}	//sensor D == bit 3  // en MdeRecepcion: if(comportamiento)  Esquivar(comportamiento);
	}
	else {comportamiento = 0;}					 								 // limpio el flag-varieble para MdeRecepcion (evita orden directa)
}
void Esquivar( int* num )		// LLamada por MdeRecepcion
{												// Uso operaciones binarias al calcular las acciones para reducir la carga en el procesadoor
	uint8_t block = 0;
	block += ( ((comportamiento>>0) & 1)  << 7);	/// motor  A Adelante bloquado		Sensdor A cerca
	block += ( ((comportamiento>>0) & 1)  << 3);	//  motor  C Adelante bloquado

	block += ( ((comportamiento>>1) & 1)  << 5);	/// motor  B Adelante bloquado		Sensdor B
	block += ( ((comportamiento>>1) & 1)  << 1);	//  motor  D Adelante bloquado

	block += ( ((comportamiento>>2) & 1)  << 2);	/// motor  C atras bloquado			Sensdor C
	block += ( ((comportamiento>>2) & 1)  << 6);	//  motor  A atras bloquado

	block += ( ((comportamiento>>3) & 1)  << 0);	/// motor  D atras bloquado			Sensdor D
	block += ( ((comportamiento>>3) & 1)  << 4);	//  motor  C atras bloquado
	*num &= ~(block); // modifico el balor recivido en la Mde Recepcion  // borro las direcciones no permitidas
}
////////////////////////////////////////////////////////////
void MaqEstadosRx2(void){

	static uint8_t estado_rx = E_INICIO_TRAMA, index = 0;
//	static char buffer[TAM_BUFFER];

	//buffer auxiliar para separar los datos.
	char aux[2];

	uint8_t dato;
//	uint32_t aux;
	if(!PopRx(&dato))
	{
		switch(estado_rx)
		{
			case E_INICIO_TRAMA:
				if(dato == FRAME_START)
					estado_rx = E_DATO;
				break;
			case E_DATO:
				if(index == TAM_BUFFER - 2)
				{
					//Guarda el ultimo dato en el anteultimo lugar del string
					buffer[TAM_BUFFER - 2] = dato;
					buffer[TAM_BUFFER - 1] = '\0';
					index = 0;
					estado_rx = E_FIN_TRAMA;
				}
				else
				{
					buffer[index] = dato;
					index++;
				}
				break;
			case E_FIN_TRAMA:
				if(dato == FRAME_END)
				{
					buffer_recibido = atoi(buffer);

					aux[0] = buffer[0];
					aux[1] = buffer[1];
					aux[2] = buffer[2];
					aux[3] = '\0';
					int num =16* atoi(aux);
					aux[0] = buffer[3];
					aux[1] = buffer[4];
					aux[2] = buffer[5];
					aux[3] = '\0';
					num +=  atoi(aux);

					if(flag_InvertirControl==SI)
					{	InvertirControl(&num);}
					if (comportamiento)
					{	Esquivar(&num);}

					buffer_PH = num;

					//Guarda valores de velocidad para PWM0
					aux[0] = buffer[6];
					aux[1] = buffer[7];
					aux[2] = buffer[8];
					aux[3] = '\0';
					buffer_PWM[0] = atoi(aux);

					//Guarda valores de velocidad para PWM1
					aux[0] = buffer[9];
					aux[1] = buffer[10];
					aux[2] = buffer[11];
					aux[3] = '\0';
					buffer_PWM[1] = atoi(aux);

					//Guarda valores de velocidad para PWM2
					aux[0] = buffer[12];
					aux[1] = buffer[13];
					aux[2] = buffer[14];
					aux[3] = '\0';
					buffer_PWM[2] = atoi(aux);

					//Guarda valores de velocidad para PWM3
					aux[0] = buffer[15];
					aux[1] = buffer[16];
					aux[2] = buffer[17];
					aux[3] = '\0';
					buffer_PWM[3] = atoi(aux);
					flag_nuevo_comando = 1;
				}
				estado_rx = E_INICIO_TRAMA;
				break;
		}
	}
}

void Piloto(void){

	uint8_t i;

	if(flag_actualizar_piloto){

		//Establece valores para activar motores en el Puente H
		for(i=0; i<8; i++)
			Motores(i, ((buffer_PH >> i) & 0x01));
			//Establece velocidades en cada PWM

		for(i=0;i<4;i++)
    		VariadordeVelocidad(i,buffer_PWM[i]);

		flag_actualizar_piloto = 0;
		}

	return;
}

/*
 * Descripcion de la forma en que los datos son interpretados en el control remoto (Qt)
 *
 * El control remoto interpreta un string de la forma:
 *
 * [TIPO][POS_VERTICAL][POS_HORIZONTAL][VALOR]
 *
 * TIPO:
 * 		'V': velocidad
 * 		'D': distancias
 * POSICION_VERTICAL:
 * 		'u': up
 * 		'd': down
 * POSICION HORIZONTAL:
 * 		'l': left
 * 		'r': right
 * VALOR:
 * 		Dato numerico, valor medido.
 * 		El control remoto recibe caracteres ascii numericos: '0' '1' '2' '3' '4' '5' '6' '7' '8' '9'
 *
 * Ejemplo:
 * 		"Dul120"	-->		Significa que el dato es del sensor de distancia, identificado como "arriba.izquierda" y que su valor medido es "120"
 */

void Transmisor(void){

	static uint8_t contador = 4;

	if(flag_enviar){
		flag_enviar = 0;

		contador--;
		if(contador==3)
			EnviarDistancia(0);
		if(contador==2)
			EnviarDistancia(1);
		if(contador==1)
			EnviarDistancia(2);
		if(!contador){
			EnviarDistancia(3);
			contador = 4;
		}
	}

}

/*
 * Calibrar: averiguar que sensor corresponde a cada juego de chars (Ddl, Ddr, etc...)
 */

/*
 * Realiza el armado de la trama y el envio del dato del sensor pasado como parametro: 0, 1, 2 y 3
 */
void EnviarDistancia(uint8_t sensor){
	char aux1[4];									//Buffer para guardar dato entero cometido a char
	char aux2[8];									//Buffer para el string concatenado

	aux2[0] = '$';
	aux2[4] = '\0';

	switch(sensor){
		case 0:					//sensor C
			aux2[1] = 'D';
			aux2[2] = 'd';
			aux2[3] = 'l';
			break;
		case 1:					// sensor D
			aux2[1] = 'D';
			aux2[2] = 'd';
			aux2[3] = 'r';
			break;
		case 2:					// sensor A
			aux2[1] = 'D';
			aux2[2] = 'u';
			aux2[3] = 'l';
			break;
		case 3:					// sensor B
			aux2[1] = 'D';
			aux2[2] = 'u';
			aux2[3] = 'r';
			break;
	}

	itoa(Ranging(sensor),aux1,10);				//Convierte el int en string

	switch(strlen(aux1)){						//Rellena con ceros cuando el string no es de 3 chars (el int no era de 3 digitos)
		case 1:
			aux1[2] = aux1[0];
			aux1[0] = '0';
			aux1[1] = '0';
			break;
		case 2:
			aux1[2] = aux1[1];
			aux1[1] = aux1[0];
			aux1[0] = '0';
			break;
		case 3:
			break;
	}
	aux1[3] = '\0';

	strcat(aux2,(const char *)aux1);			//Une Los caracteres de digitos con los caracteres que identifican el sensor
	aux2[7] = '#';								//Termina la trama con numeral

	EnviarString(aux2);							//Envia la trama


}

void SysTick_Handler(void)
{
	static uint32_t tick1seg = 40000;
	static uint32_t tick2seg = 80000;
	static uint32_t tick_comando = 13600;
//	static uint32_t tick_envio = 50000;
	static uint32_t tick_envio = 14400;
	static uint32_t tick_comportamiento = 7200;
/***********************************************************************************************/
//Funciones cada 25 eg
	flag25us = 1;

	tick_comportamiento--;
	if(!tick_comportamiento)
	{
		tick_comportamiento = 7200;
		flag_comportamiento = 1;
	}

/***********************************************************************************************/
	tick_comando--;
	if(!tick_comando)
	{
		tick_comando = 13600;
		if(flag_nuevo_comando){
			flag_nuevo_comando = 0;
			flag_actualizar_piloto = 1;
		}
		else{
			//Pone buffers de comandos en 0
			flag_actualizar_piloto = 1;
			buffer_PH = 0;
			buffer_PWM[0] = 0;
			buffer_PWM[1] = 0;
			buffer_PWM[2] = 0;
			buffer_PWM[3] = 0;
		}
		flag_Transmisor = 1;
	}

	tick_envio--;
	if(!tick_envio){
		tick_envio = 14400;
		flag_enviar = 1;
	}

/***********************************************************************************************/
//Funciones cada 1 seg

	if(flag_updown)
		tick1seg--;

	if(!tick1seg && flag_updown)	//se mantuvo 1 seg dado vuelta
	{
		tick1seg = 40000;
		flag_InvertirControl = SI;
	}
	else if(tick1seg && !flag_updown)	//No llego a 1 seg
	{
	//	tick1seg = 40000;
		flag_InvertirControl = NO;
	}

/***********************************************************************************************/
//Funciones cada 2 seg



}


/* 	Tabla de conversion 4 teclas A 16 acciones
 *	teclas			A	B	C	D		Accion
 *********************************************************************
 *	0				0	0	0	0		Parado
 *	1				1	0	0	0		Izquierda adelante
 *	2				0	1	0	0		Derecha adelante
 * 	3				1	1	0	0		Adelante
 * 	4				0	0	1	0		Izquierda atras
 * 	5				1	0	1	0		Nada de momento
 *	6				0	1	1	0		Giro horario
 *	7				1	1	1	0		Nada de momento
 *	8				0	0	0	1		Derecha atras
 * 	9				1	0	0	1		Giro antihorario
 *	10				0	1	0	1		Nada de momento
 *	11				1	1	0	1		Nada de momento
 *	12				0	0	1	1		Nada de momento
 *	13				1	0	1	1		Nada de momento
 *	14				0	1	1	1		Nada de momento
 *	15				1	1	1	1		Nada de momento
 ********************************************************************
 *	PuenteH[A+,A-,A_PWM,B+,B-,B_PWM,C+,C-,C_PWM,D+,D-,D_PWM]
 *	PuenteH{0 ,1 ,2    ,3 ,4 ,5    ,6 ,7 ,8    ,9 ,10,11}
*/

/*
 *	Buffer_for_L293D = {A+,A-,B+,B-,C+,C-,D+,D-}
 *	Buffer_PW[A_PWM, B_PWM, C_PWM, D_PWM]
 *uint8_t Buffer_For_L293D          BUFER DEL PUENTE H
*/

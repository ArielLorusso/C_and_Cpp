#include "FW-Timers.h"
#include "FW-GPIO.h"

extern uint8_t flag_trigger;
extern uint8_t flag_limite;
extern uint8_t flag_escuchando;

extern uint8_t echostart;
extern uint8_t echoend;

//Flag para el caso en que usamos la captura en echo detectando ambos flancos
//Lo usamos para determinar si habia entrado antes
uint8_t flag_echo_activo = 0;

void InitTimer0(void){
	PCONP |= (1<<1);		//Power para perifericos
	PCLKSEL0 |= (1<<2);		//Seleccion de la fuente de clock (divisores del clock del micro)
	T0PR = 9;				//Prescaler
	T0CTCR = 0x00000000;	//Seleccionde funcion del timer: timer o contador
	ISER0 |= (1<<1);		//Habilita interrupcion de periferico
	T0TCR = 0x00000002;		//Control del contador: apaga y resetea
}
void InitTimer1(void){
	PCONP |= (1<<2);
	PCLKSEL0 |= (1<<4);
	T1PR = 9;
	T1CTCR = 0x00000000;
	ISER0 |= (1<<2);
	T1TCR = 0x00000002;
}
void InitTimer2(void){
	PCONP |= (1<<22);
	PCLKSEL1 |= (1<<12);
	T2PR = 9;
	T2CTCR = 0x00000000;
	ISER0 |= (1<<3);
	T2TCR = 0x00000002;
}
void InitTimer3(void){
	PCONP |= (1<<23);
	PCLKSEL1 |= (1<<14);
	T3PR = 9;
	T3CTCR = 0x00000000;
	ISER0 |= (1<<4);
	T3TCR = 0x00000002;
}

void T0C0Init(void){
	SetPINSEL(PORT1,26,3);
}
void T0C1Init(void){
	SetPINSEL(PORT1,27,3);
}
void T1C0Init(void){
	SetPINSEL(PORT1,18,3);
}
void T1C1Init(void){
	SetPINSEL(PORT1,19,3);
}
void T2C0Init(void){
	SetPINSEL(PORT0,4,3);
}
void T2C1Init(void){
	SetPINSEL(PORT0,5,3);
}
void T3C0Init(void){
	SetPINSEL(PORT0,23,3);
}
void T3C1Init(void){
	SetPINSEL(PORT0,24,3);
}

void T0On(void){
	T0TCR = 0x00000001;
}
void T1On(void){
	T1TCR = 0x00000001;
}
void T2On(void){
	T2TCR = 0x00000001;
}
void T3On(void){
	T3TCR = 0x00000001;
}
void T0Off(void){
	T0TCR = 0x00000002;
}
void T1Off(void){
	T1TCR = 0x00000002;
}
void T2Off(void){
	T2TCR = 0x00000002;
}
void T3Off(void){
	T3TCR = 0x00000002;
}

void T0Reset(void){
	T0TCR = 0x00000002;
	T0TCR = 0x00000001;
}
void T1Reset(void){
	T1TCR = 0x00000002;
	T1TCR = 0x00000001;
}
void T2Reset(void){
	T2TCR = 0x00000002;
	T2TCR = 0x00000001;
}
void T3Reset(void){
	T3TCR = 0x00000002;
	T3TCR = 0x00000001;
}

void T0M0Config(uint32_t useg){
	T0MR0 = useg*100/((T0PR+1)*DIV0);
	T0MCR &= ~(0x00000007);
	T0MCR |= 0x00000003;				//Match0, interrumpe y resetea la cuenta del timer
}
void T0M1Config(uint32_t useg){
	T0MR1 = useg*100/((T0PR+1)*DIV0);
	T0MCR &= ~(0x00000038);
	T0MCR |= 0x00000018;
}
void T0M2Config(uint32_t useg){
	T0MR2 = useg*100/((T0PR+1)*DIV0);
	T0MCR &= ~(0x000001C0);
	T0MCR = 0x000000C0;
}
void T0M3Config(uint32_t useg){
	T0MR3 = useg*100/((T0PR+1)*DIV0);
	T0MCR &= ~(0x00000E00);
	T0MCR = 0x00000600;
}
void T1M0Config(uint32_t useg){
	T1MR0 = useg*100/((T1PR+1)*DIV1);
	T1MCR &= ~(0x00000007);
	T1MCR |= 0x00000003;
}
void T1M1Config(uint32_t useg){
	T1MR1 = useg*100/((T1PR+1)*DIV1);
	T1MCR &= ~(0x00000038);
	T1MCR |= 0x00000018;
}
void T1M2Config(uint32_t useg){
	T1MR2 = useg*100/((T1PR+1)*DIV1);
	T1MCR &= ~(0x000001C0);
	T1MCR = 0x000000C0;
}
void T1M3Config(uint32_t useg){
	T1MR3 = useg*100/((T1PR+1)*DIV1);
	T1MCR &= ~(0x00000E00);
	T1MCR = 0x00000600;
}
void T2M0Config(uint32_t useg){
	T2MR0 = useg*100/((T2PR+1)*DIV2);
	T2MCR &= ~(0x00000007);
	T2MCR |= 0x00000003;
}
void T2M1Config(uint32_t useg){
	T2MR1 = useg*100/((T2PR+1)*DIV2);
	T2MCR &= ~(0x00000038);
	T2MCR |= 0x00000018;
}
void T2M2Config(uint32_t useg){
	T2MR2 = useg*100/((T2PR+1)*DIV2);
	T2MCR &= ~(0x000001C0);
	T2MCR = 0x000000C0;
}
void T2M3Config(uint32_t useg){
	T2MR3 = useg*100/((T2PR+1)*DIV2);
	T2MCR &= ~(0x00000E00);
	T2MCR = 0x00000600;
}
void T3M0Config(uint32_t useg){
	T3MR0 = useg*100/((T3PR+1)*DIV3);
	T3MCR &= ~(0x00000007);
	T3MCR |= 0x00000003;
}
void T3M1Config(uint32_t useg){
	T3MR1 = useg*100/((T3PR+1)*DIV3);
	T3MCR &= ~(0x00000038);
	T3MCR |= 0x00000018;
}
void T3M2Config(uint32_t useg){
	T3MR2 = useg*100/((T3PR+1)*DIV3);
	T3MCR &= ~(0x000001C0);
	T3MCR = 0x000000C0;
}
void T3M3Config(uint32_t useg){
	T3MR3 = useg*100/((T3PR+1)*DIV3);
	T3MCR &= ~(0x00000E00);
	T3MCR = 0x00000600;
}

void T0M0Off(void){
	T0MCR &= ~(0x00000007);
}
void T0M1Off(void){
	T0MCR &= ~(0x00000038);
}
void T0M2Off(void){
	T0MCR &= ~(0x000001C0);
}
void T0M3Off(void){
	T0MCR &= ~(0x00000E00);
}
void T1M0Off(void){
	T1MCR &= ~(0x00000007);
}
void T1M1Off(void){
	T1MCR &= ~(0x00000038);
}
void T1M2Off(void){
	T1MCR &= ~(0x000001C0);
}
void T1M3Off(void){
	T1MCR &= ~(0x00000E00);
}
void T2M0Off(void){
	T2MCR &= ~(0x00000007);
}
void T2M1Off(void){
	T2MCR &= ~(0x00000038);
}
void T2M2Off(void){
	T2MCR &= ~(0x000001C0);
}
void T2M3Off(void){
	T2MCR &= ~(0x00000E00);
}
void T3M0Off(void){
	T3MCR &= ~(0x00000007);
}
void T3M1Off(void){
	T3MCR &= ~(0x00000038);
}
void T3M2Off(void){
	T3MCR &= ~(0x000001C0);
}
void T3M3Off(void){
	T3MCR &= ~(0x00000E00);
}

void T0C0Config(void){
	T0CCR &= ~(0x00000007);
	T0CCR |= 0x00000007;	//Captura0 por ambos e interrumpe
}
void T0C1Config(void){
	T0CCR &= ~(0x00000038);
	T0CCR |= 0x00000038;		//Captura1 por ambos flancos e interrumpe
}
void T1C0Config(void){
	T1CCR &= ~(0x00000007);
	T1CCR |= 0x00000007;	//Captura0 por ambos flancos e interrumpe
}
void T1C1Config(void){
	T1CCR &= ~(0x00000038);
	T1CCR |= 0x00000038;		//Captura1 por ambos flancos e interrumpe
}
void T2C0Config(void){
	T2CCR &= ~(0x00000007);
	T2CCR |= 0x00000007;	//Captura0 por ambos flancos e interrumpe
}
void T2C1Config(void){
	T2CCR &= ~(0x00000038);
	T2CCR |= 0x00000038;		//Captura1 por ambos flancos e interrumpe
}
void T3C0Config(void){
	T3CCR &= ~(0x00000007);
	T3CCR |= 0x00000007;	//Captura0 por ambos flancos e interrumpe
}
void T3C1Config(void){
	T3CCR &= ~(0x00000038);
	T3CCR |= 0x00000038;		//Captura1 por ambos flancos e interrumpe
}
void T0C0Off(void){
	T0CCR &= ~(0x00000007);
}
void T0C1Off(void){
	T0CCR &= ~(0x00000038);
}
void T1C0Off(void){
	T1CCR &= ~(0x00000007);
}
void T1C1Off(void){
	T1CCR &= ~(0x00000038);
}
void T2C0Off(void){
	T2CCR &= ~(0x00000007);
}
void T2C1Off(void){
	T2CCR &= ~(0x00000038);
}
void T3C0Off(void){
	T3CCR &= ~(0x00000007);
}
void T3C1Off(void){
	T3CCR &= ~(0x00000038);
}

void TIMER0_IRQHandler (void)
{
	//Evaluacion de interrupcion por match
	if((T0IR & 0x00000001))		// Si interrumpio match0
	{
			T0IR |= 0x00000001; 	// Borro flag de match0

			//¿Apago el M0 en la interrupcion?
			T0MCR &= ~(0x00000007);

			if(flag_escuchando)
				flag_limite = 1;

			else
				flag_trigger = 1;
	}

}
void TIMER1_IRQHandler (void)
{
	//Evaluacion de interrupcion por match
	if((T1IR & 0x00000001))		// Si interrumpio match0
	{
			T1IR |= 0x00000001; 	// Borro flag de match0

	}

	//Evaluacion de interrupcion por captura
	if( ( T1IR & 0x00000010 ) )		// Si interrumpio captura0
	{
			T1IR |= 0x00000010; 	// Borro flag de captura0


	}

}
void TIMER2_IRQHandler (void)
{
	//Evaluacion de interrupcion por match
	if( ( T2IR & 0x00000001 ) )		// Si interrumpio match0
	{
			T2IR |= 0x00000001; 	// Borro flag de match0

	}

	//Evaluacion de interrupcion por captura
	if( ( T2IR & 0x00000010 ) )		// Si interrumpio captura0
	{
			T2IR |= 0x00000010; 	// Borro flag de captura0

	}
}
void TIMER3_IRQHandler (void)
{
	//Evaluacion de interrupcion por match
	if( ( T3IR & 0x00000001 ) )		// Si interrumpio match0
	{
			T3IR |= 0x00000001; 	// Borro flag de match0

	}

	//Evaluacion de interrupcion por captura
	if( ( T3IR & 0x00000010 ) )		// Si interrumpio captura0
	{
			T3IR |= 0x00000010; 	// Borro flag de captura0

			if(!flag_echo_activo){
				flag_echo_activo = 1;
				echostart = 1;
			}
			else{
				flag_echo_activo = 0;
				echoend = 1;

			//¿Apago el M0 en la interrupcion?
				T0MCR &= ~(0x00000007);
			}

	}
}

/*
 * Ecuacion de medida de tiempo
 * t[uSeg] = (PR+1)*TC*1000000/PCLK
 *
 *Mas general, considerando divisor de clock, DIV
 * TC = t[uSeg]*100000000/((PR+1)*1000000*DIV)
 */

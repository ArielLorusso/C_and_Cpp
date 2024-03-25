#include <RobotExplorador.h>
#include "FW-PWM.h"


uint8_t g_motorA_PWM;
uint8_t g_motorB_PWM;
uint8_t g_motorC_PWM;
uint8_t g_motorD_PWM;

void InitPWM (void)
{
	/*
	The PWM is configured using the following registers:
1. Power: In the PCONP register (Table 46), set bit PCPWM1.
Remark: On reset, the PWM is enabled (PCPWM1 = 1).
2. Peripheral clock: In the PCLKSEL0 register (Table 40), select PCLK_PWM1.
3. Pins: Select PWM pins through the PINSEL registers. Select pin modes for port pins
with PWM1 functions through the PINMODE registers (Section 8.5).
4. Interrupts: See registers PWM1MCR (Table 449) and PWM1CCR (Table 450) for
match and capture events. Interrupts are enabled in the NVIC using the appropriate
Interrupt Set Enable register.
	 */

	uint32_t aux;

	// poner un 1 en el bit 6 del registro PCONP esto enciende el PCPWM1
	PCONP |= (1 << 6);

	//Reloj del periferico: En el registro PCLKSEL0 seleccionar PCLK_PWM osea CCLK*1
	PCLKSEL0 |= (1 << 12);

	//Pongo las variables del duty cycle en 0, osea que estoy frenando.

	g_motorA_PWM = g_motorB_PWM = g_motorC_PWM = g_motorD_PWM = 0;

	//Inicializo los pines

	SetPINSEL(PWM1_1, OUTPUT);
	SetPINSEL(PWM1_2, OUTPUT);
	SetPINSEL(PWM1_3, OUTPUT);
	SetPINSEL(PWM1_4, OUTPUT);

	//Pongo todas las salidas en cero

	SetPIN(PWM1_1, OFF);
	SetPIN(PWM1_2, OFF);
	SetPIN(PWM1_3, OFF);
	SetPIN(PWM1_4, OFF);

	//Habilito los Match
	IR = 0x00010F;
	//Habilito el PWM Timer Counter
	TCR = 0x00;
	//Habilito el modo PWM del PWM Timer Counter
	CTCR = 0x00;
	//Counter Timer Mode
	MCR = 0x00;
	CCR = 0x00;
	PCR = 0x00;
	LER = 0x00;

	if( (PWM_PRESCALE_NS%1000) < 500 )
			aux = PWM_PRESCALE_NS/1000;
		else
			aux = PWM_PRESCALE_NS/1000 + 1;

		//PR = (aux*25000000/1000000) - 1;
		PR = (10) - 1;
	//Configuracion match 0,1,2,3,4
	MCR |= 1<<1;		//reset match 0
	MR0	= PWM_MAX_DUTY_STEP;
	MR1 = g_motorA_PWM;
	MR2 = g_motorB_PWM;
	MR3 = g_motorC_PWM;
	MR4 = g_motorD_PWM;

	LER = (0x01F<<0);

	//Pongo en 0 desde el bit 2 al 4 para single edge en los canales PWM del 1 al 4 como salida
	PCR	&= ~(0x07<<2);
	//pongo en 1 desde el bit 9 al 12 para habilitar los canales de PWM del 1 al 4 como salida
	PCR	|= (0x0F<<9);

	TCR |= ( 1 << CounterReset);
	TCR = 0x09;			//se habilitan contador y PWM
}


void DutyCiclePWM(void) //ajusta los match & ...
{

	MR1 = g_motorA_PWM;
	MR2 = g_motorB_PWM;
	MR3 = g_motorC_PWM;
	MR4 = g_motorD_PWM;

	LER = 0x1E;		//habilito latch de match 1,2,3 y 4

}

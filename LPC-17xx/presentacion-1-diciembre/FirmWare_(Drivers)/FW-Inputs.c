/*
 * FW_Inputs.c
 *
 *  Created on: 29/04/2015
 *      Author: pmic
 */

#include <RobotExplorador.h>



uint32_t g_inputs = 0;				//estado de las entradas
uint32_t g_inputsChanges = 0;		//flags de cambios en entradas, se setea al haber un cambio en una entrada

void Inputs_Debounce(void)
{
	static uint8_t debounceCounter[4] = {0};
	uint8_t changes = 0;
	uint8_t i;

//Modifico un campo de bit que se completa con GetPIN

	changes |= (GetPIN(KEYA,ALTO) << 0);
	changes |= (GetPIN(KEYB,ALTO) << 1);
	changes |= (GetPIN(KEYC,ALTO) << 2);
	changes |= (GetPIN(KEYD,ALTO) << 3);
//
	i=0;
//	changes |= (GetPIN(INPUT_4_PORT, INPUT_4_PIN) << 4);
//	changes |= (GetPIN(INPUT_5_PORT, INPUT_5_PIN) << 5);
//	changes |= (GetPIN(INPUT_6_PORT, INPUT_6_PIN) << 6);
//	changes |= (GetPIN(INPUT_7_PORT, INPUT_7_PIN) << 7);

	changes ^= g_inputs;		//le aplico una mascara xor con 0 y se vuelve a guardar en changes

	if(changes)		//me fijo que changes sea distinto de cero
	{
		for(i=0; i<4; i++)
		{
			if((changes >> i) & 0x01)	//Esto compara bit a bit si changes tiene cargados 1
			{
				debounceCounter[i]++;
				if(debounceCounter[i] == INPUT_DEBOUNCE)
				{

					g_inputs ^= 1 << i;
					g_inputsChanges |= 1 << i;
					debounceCounter[i] = 0;
				}
			}
		}
	}
	else
	{
		for(i=0; i<4; i++)
		{
			debounceCounter[i] = 0;
		}
	}
}

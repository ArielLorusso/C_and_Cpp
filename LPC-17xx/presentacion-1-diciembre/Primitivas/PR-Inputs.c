/*
 * PR_Inputs.c
 *
 *  Created on: 29/06/2015
 *      Author: pmic
 */

#include <RobotExplorador.h>
extern uint32_t g_inputsChanges;
extern uint32_t g_inputs;
uint32_t Inputs_GetValue(uint8_t input)
{
	return (g_inputs >> input) & 0x01;		//Compara y devuelve el valor de la posicion de g_input que se le indique en input
}

uint32_t Inputs_GetChanges(void)
{
	uint32_t retVal = g_inputsChanges;		//retorna el g_inputsChanges y lo reinicia
	g_inputsChanges = 0;
	return retVal;
}

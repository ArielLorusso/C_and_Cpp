/*
 * PR_Inputs.h
 *
 */

#ifndef PR_INPUTS_H_
#define PR_INPUTS_H_

#include "RegsLPC1769.h"

#define BotonA 		0
#define BotonB 		1
#define BotonC 		2
#define BotonD 		3

uint32_t Inputs_GetValue(uint8_t input);
uint32_t Inputs_GetChanges(void);


#endif /* PR_INPUTS_H_ */

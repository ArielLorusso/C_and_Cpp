/*
 * FW_Serie.h
 *
 *  Created on: 09/07/2013
 *      Author: Pablo
 */

#ifndef FW_SERIE_H_
#define FW_SERIE_H_

#include "RegsLPC1769.h"

#define START_TX()	(PopTx((uint8_t*)&U1THR))

void InitUART1(void);

extern uint8_t txStart;

#endif /* FW_SERIE_H_ */

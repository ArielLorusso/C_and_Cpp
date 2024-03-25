#ifndef FW_TIMERS_H_
#define FW_TIMERS_H_
#include "Regslpc1769.h"

/*
 * Inicializaciones
 */
void InitTimer0(void);
void InitTimer1(void);
void InitTimer2(void);
void InitTimer3(void);

void T0C0Init(void);
void T0C1Init(void);
void T1C0Init(void);
void T1C1Init(void);
void T2C0Init(void);
void T2C1Init(void);
void T3C0Init(void);
void T3C1Init(void);

/*
 * Uso general
 * 1)Inicializar los timers a utilizar
 * 2)Inicializar capturas aparte, las que se vayan a utilizar
 * 3)No usar Timer On para iniciar la cuenta, porque no resetea. Usar Reset.
 */

/*
 * Uso de Match
 * Puntos anteriores y
 * 1)Llamar a Config del match que querramos usar. Pasarle el tiempo en usegs
 * 2)Llamar a la funcion Reset (porque resetea e inicia. No llamar On, porque no resetea. Solo llamar On si queremos retomar una cuenta)
 * 3)Al finalizar el trabajo del Match, llamar a Match Off para que no siga interrumpiendo
 * 4)Si ya no se usa, apagar el timer con timer off.
 */

/*
 * Uso de Capture
 * Puntos iniciales, generales.
 * 1)Llamar al capture config de la captura que querramos.
 * 2)Llamar al reset del timer. No al On, por los motivos ya mencionados
 * 3)Al finalizar, apagar la funcion de capture para que no siga interrumpiendo
 * 4)Si ya no se usa, llamar el timer off para apagar la cuenta del timer
 */

/*
 * Definicion de los divisores de clock, para establecer PCLK
 * Por ahora solo se usan en la configuracion de los matchs.
 * Mas adelante utilizar tambien para inicializar los timers, al usar PCLKSEL
 *
 * Pueden valer 1, 2, 4 u 8
 * En PCLKSEL
 *	00 -> 4
 *	01 -> 1
 *	10 -> 2
 *	11 -> 8
 */
#define DIV0 1
#define DIV1 1
#define DIV2 1
#define DIV3 1

void T0On(void);
void T1On(void);
void T2On(void);
void T3On(void);

void T0Off(void);
void T1Off(void);
void T2Off(void);
void T3Off(void);

void T0Reset(void);
void T1Reset(void);
void T2Reset(void);
void T3Reset(void);

/*
 * Configura MATCH
 * Tener en cuenta que al llamarla, configura el timer
 * para que interrumpa y resetee al llegar al valor
 * usegs pasado como parametro
 *
 * Se pueden llamar sucesivamente y dejar varios Match configurados a la vez
 *
 *MEJORAS
 * Mas adelante, mejorarlas con estas tres cualidades:
 * 	.Pasarle como parametro si queremos que resetee o no.
 * 	.Pasarle si lo que queremos se habilita o se apaga (ON, OFF solo del MATCH, no del TIMER)
 * 	.Unificar todas en una sola funcion, a la que le
 * 		pasamos timer y match a configurar.
 */
void T0M0Config(uint32_t useg);
void T0M1Config(uint32_t useg);
void T0M2Config(uint32_t useg);
void T0M3Config(uint32_t useg);
void T1M0Config(uint32_t useg);
void T1M1Config(uint32_t useg);
void T1M2Config(uint32_t useg);
void T1M3Config(uint32_t useg);
void T2M0Config(uint32_t useg);
void T2M1Config(uint32_t useg);
void T2M2Config(uint32_t useg);
void T2M3Config(uint32_t useg);
void T3M0Config(uint32_t useg);
void T3M1Config(uint32_t useg);
void T3M2Config(uint32_t useg);
void T3M3Config(uint32_t useg);

/*
 * Apaga la funcionalidad de MATCH del Timer
 * La funcion config, asi como esta, configura match y lo activa
 * Esta funcion lo desactiva.
 *
 * Mas adelante, ambas cosas deben quedar en una sola funcion
 */
void T0M0Off(void);
void T0M1Off(void);
void T0M2Off(void);
void T0M3Off(void);
void T1M0Off(void);
void T1M1Off(void);
void T1M2Off(void);
void T1M3Off(void);
void T2M0Off(void);
void T2M1Off(void);
void T2M2Off(void);
void T2M3Off(void);
void T3M0Off(void);
void T3M1Off(void);
void T3M2Off(void);
void T3M3Off(void);

/*
 * Configura captura. Por default: ambos flancos, con interrupcion
 *
 * MEJORAS:
 *  .Pasarle flanco
 *  .Unificar todas en una, pasando el timer y la captura
 */
void T0C0Config(void);
void T0C1Config(void);
void T1C0Config(void);
void T1C1Config(void);
void T2C0Config(void);
void T2C1Config(void);
void T3C0Config(void);
void T3C1Config(void);

/*
 * Apaga funcionalidad de captura en ese timer, pero no apaga el conteo de timer
 */
void T0C0Off(void);
void T0C1Off(void);
void T1C0Off(void);
void T1C1Off(void);
void T2C0Off(void);
void T2C1Off(void);
void T3C0Off(void);
void T3C1Off(void);

#endif /* PR_TIMERS_H_*/

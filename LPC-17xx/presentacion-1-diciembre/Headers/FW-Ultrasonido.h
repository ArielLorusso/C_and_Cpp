#ifndef FW_ULTRASONIC_H_
#define FW_ULTRASONIC_H_
#include <FW-Timers.h>

/*
 * Pines de Trigger
 * Los pines de Trigger iran hardcodeados, por el sistema empleado para la rotacion de sensores
 * Usamos el Trigger del sensor 0 como referencia y a ese pin le sumamos el sensor actual (0, 1, 2 y 3)
 * Los triggers son:
 * 0: P0.0
 * 1: P0.1
 * 2: P0.2
 * 3: P0.3
 */

/*
 * Limite de echo, para las distancias a medir
 * Minimo: 2 cm
 * Maximo: 400 cm
 *
 * Usamos el limite de 400 cm
 * Tiempo de duracion en usegs: 23200 usegs
 *
 */
#define ECHO_LIMIT 23200

/*
 * Duracion del trigger
 *
 * Puede durar cualquier tiempo mayor a 10 usegs
 * Lo usamos como variable de ajuste para que el ciclo completo dure alrededor de 60 msegs
 *
 */

//Para un solo sensor: 50000
//Para los 4: 20000
#define TRIGGER_TIME 20000

typedef enum {
	STANDBYT, TRIGGERING, ESCUCHANDO, RECIBIENDO
}estados_t;

typedef enum{
	STANDBYS, S0, S1, S2, S3
}estados_s;

void Inic_Ultrasonido(void);
void MdeTiming(void);
void MdeSensores(void);

#endif /* PR_ULTRASONIC_H_*/

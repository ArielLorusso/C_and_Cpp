#include <PR-Ultrasonido.h>

extern uint32_t buffer_tiempo[];

uint32_t Ranging(uint8_t sensor){

	uint32_t duracion = 0;
	duracion = buffer_tiempo[sensor];
//	buffer_tiempo[sensor] = 0;

	return duracion/58;

}

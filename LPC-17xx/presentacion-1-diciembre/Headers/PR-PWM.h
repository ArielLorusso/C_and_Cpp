
#ifndef PR_PWM_H_
#define PR_PWM_H_
#include <RobotExplorador.h>
#include "FW-PWM.h"

extern uint8_t g_motorA_PWM;
extern uint8_t g_motorB_PWM;
extern uint8_t g_motorC_PWM;
extern uint8_t g_motorD_PWM;

typedef enum {
	MotorA,MotorB,MotorC,MotorD
} Motor;

#define FRECUENCIA_MAX 255

void VariadordeVelocidad(Motor select, uint8_t velocidad);

#endif /* PR_PWM_H_ */

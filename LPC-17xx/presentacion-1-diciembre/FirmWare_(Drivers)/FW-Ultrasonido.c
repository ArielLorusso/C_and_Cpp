#include <FW-GPIO.h>
#include <FW-Ultrasonido.h>
#include <RobotExplorador.h>

//Buffer donde el driver guarda la medicion de tiempo de cada sensor, en microsegundos
uint32_t buffer_tiempo[4] = {0};

/*
 * Variable para indicar el sensor actual
 * Puede valer 0, 1, 2, 3
 * Es alterada por MdeSensores (ciclo 0->1->2->3->0) y leida por MdeTiming
 */

uint8_t sensor = 0;

/*
 * Flags de timers, en orden:
 * Flag para activar la MdeSensores (desde el usuario o algun sensor del sistema)
 * Flag para activar la MdeTiming (desde la MdeSensores)
 * Flag para marcar el paso de 10 microsegundos (del pulso del trigger)
 * Flag que marca el paso del tiempo limite presstablecido para esperar el fin del pulso.
 * Flag para inidicarle al handler de interrupcion el estado actual; estonos permite usar el mismo match en dos casos distintos.
 * Flag para indicar a la MdeSensores que se cargo el buffer de tiempo y que hay que pasar al siguiente sensor
 *
 */

uint8_t flag_start = 0;
uint8_t flag_timing = 0;
uint8_t flag_trigger = 0;
uint8_t flag_limite = 0;
uint8_t flag_escuchando = 0;
uint8_t flag_buffer = 0;

//Flags echo
uint8_t echostart = 0;
uint8_t echoend = 0;

/*
 * Uso de TIMERS:
 * Para el tiempo del pulso de trigger: T0M0
 * Para el limite de tiempo de espera del echo: reconfiguro T0M0
 * Para el echo: T3C0 en flanco ascendente y reconfiguro a descendente
 * Para la cuenta de tiempo del echo (calculo): T3, el mismo que el de captura
 */

void Inic_Ultrasonido(void){
//Inicializa pines de trigger como GPIO y setea direccion de salida
	SetPINSEL(PORT0,0,0);
	SetDIR(PORT0,0,GPIO_OUTPUT);
	SetPINSEL(PORT0,1,0);
	SetDIR(PORT0,1,GPIO_OUTPUT);
	SetPINSEL(PORT0,2,0);
	SetDIR(PORT0,2,GPIO_OUTPUT);
	SetPINSEL(PORT0,3,0);
	SetDIR(PORT0,3,GPIO_OUTPUT);

//Inicializacion del pin de captura
	T3C0Init();

	return;
}

void MdeTiming(void){

	static uint32_t cuenta_echo = 0;
	static estados_t estado = STANDBYT;

	switch(estado){
		case STANDBYT:
			if(flag_timing){
				estado = TRIGGERING;
				//Activa PIN TRIGGER
				SetPIN(0,0+sensor,ON);
				//Activa timer de duracion del trigger
				T0M0Config(TRIGGER_TIME);
				T0Reset();
				//Baja el flag_trigger
				flag_timing = 0;
			}

			break;
		case TRIGGERING:
			if(flag_trigger){
				estado = ESCUCHANDO;

				//Configura captura para detectar el pulso en echo
				//Ambos flancos (primer version, cambiar en funcion)
				T3C0Config();
				//Inicia el contador para calcular el tiempo
				T3Reset();

				//Desactiva PIN TRIGGER
				SetPIN(0,0+sensor,OFF);
				//Desactiva timer de trigger
				T0M0Off();
				T0Off();
				//Baja el flag_trigger
				flag_trigger = 0;

			}
			break;
		case ESCUCHANDO:
			if(echostart){
				estado = RECIBIENDO;
				//Guarda cuenta actual del timer de calculo
				cuenta_echo = T3TC;
				//Dispara timer limite
				T0M0Config(ECHO_LIMIT);
				T0Reset();
				//Activa un flag para el handler del timer
				flag_escuchando = 1;
				//Baja el flag echostart
				echostart = 0;
			}
			break;
		case RECIBIENDO:
			if(echoend || flag_limite){
				estado = STANDBYT;
				//Desactiva el timer limite
				T0M0Off();
				T0Off();
				//Guarda cuenta actual y establece la diferencia con la anterior
				cuenta_echo = T3TC - cuenta_echo;
				//Desactiva timer de calculo
				T3Off();
				//Baja configuracion de captura
				T3C0Off();
				//Calcula tiempo en base a cuentas y guarda tiempo en buffer
				buffer_tiempo[sensor] = (T3PR+1)*cuenta_echo/100;		//PCLK = CCLK, segun inicializacion
				//Baja el flag echo
				echoend = 0;

				if(flag_limite)
					//Establece un tiempo de ERROR
					buffer_tiempo[sensor] = 0;
					//Hardcodeado... CORREGIR

				//Baja flag_limite
				flag_limite = 0;
				//Baja el flag_escuchando
				flag_escuchando = 0;
				//Activa el flag que indica que se cargo el buffer
				flag_buffer = 1;

			}
			break;
	}

}

void MdeSensores(void){

	//Cuatro estados: S0, S1, S2, S3 y STANDBYS
	//Rotacion de sensores mediante la variable sensor

	static estados_s estado = STANDBYS;

	switch(estado){
	case STANDBYS:
		if(flag_start){
			//Baja el flag de start
			flag_start = 0;
			//Cambia de estado
			estado = S0;
			//Establece el sensor actual
			sensor = 0;
			//Activa la maquina de timing
			flag_timing = 1;
		}

		break;
	case S0:
		if(flag_buffer){
			//Baja el flag de buffer
			flag_buffer = 0;
			//Cambia de estado
			estado = S1;
			//Establece el sensor actual
			sensor = 1;
			//Activa la maquina de timing
			flag_timing = 1;
		}
		break;
	case S1:
		if(flag_buffer){
			//Baja el flag de buffer
			flag_buffer = 0;
			//Cambia de estado
			estado = S2;
			//Establece el sensor actual
			sensor = 2;
			//Activa la maquina de timing
			flag_timing = 1;
		}
		break;
	case S2:
		if(flag_buffer){
			//Baja el flag de buffer
			flag_buffer = 0;
			//Cambia de estado
			estado = S3;
			//Establece el sensor actual
			sensor = 3;
			//Activa la maquina de timing
			flag_timing = 1;
		}
		break;
	case S3:
		if(flag_buffer){
			//Baja el flag de buffer
			flag_buffer = 0;
			//Cambia de estado
			estado = STANDBYS;

			//SOLO PARA ESTE CASO, BORRAR DESPUES
			flag_start = 1;
		}
		break;

	}

}

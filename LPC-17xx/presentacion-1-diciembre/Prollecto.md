# Indice
# Desarrollo general de la idea

Los vehículos a control remoto tienen muchísimas aplicaciones, tan 
variadas que se pueden citar como ejemplos la recreacion, la 
exploracion, la investigacion y la guerra.
Sobre estos dispositivos pueden mencionarse algunas ventajas importantes:
*	Manejo remoto.
*	Acceso a lugares dificiles o imposibles para las personas, por volumen, peso o forma.
*	Acceso a lugares imposibles para las personas por cuestiones de riesgo
altas temperaturas, insalubridad del aire, presion, etc.

Teniendo en cuenta estas ventajas, la utilizacion de un vehiculo a 
control remoto da la posibilidad de explorar lugares lejanos, o sectores 
denegados de una construccion por diversos motivos y la manipulacion de 
objetos peligrosos. Algunos ejemplos concretos de aplicacion son:
*	La exploracion espacial.
*	La exploracion de antiguas ruinas que presentan conductos 
pequeños, ofreciendo la posibilidad de ingresar a otros sectores las 
mismas sin necesidad de alterar la estructura.
*	Drones de guerra (entro otros usos, como el cine para realizar 
tomas aereas, o en la televizacion del futbol).
*	Aviones y autos de modelismo, tambien usados para competicion.

En particular, nuestro proyecto consiste en un auto a control remoto, 
que tiene varias de las aplicaciones y ventajas antes mencionadas.
El objetivo principal es mostrar como mediante un dispositivo de este 
tipo, es decir un auto a control remoto, se pueden implementar algunas 
de esas capacidades: comunicacion remota y estable, en lugares o 
terrenos de dificil acceso superando obstaculos, resitencia a choques o 
vuelcos de cierto impacto, "inteligencia" (para reconocer y actuar en 
funcion del entorno) etc.

#	Introduccion al proyecto

El proyecto consiste en un auto a control remoto, con capacidad de 
dirección con precisión, ademas de la detección y eventual superacion de 
obstáculos. Está pensado, en principio, para recorrer trayectorias no 
muy lejanas al punto de control.

El control remoto será una interfaz de usuario programada en QT 
corriendo en una PC; el enlace será a través WiFi.

En cuanto a la forma del auto, hay que destacar que las dimensiones de 
las ruedas en comparación del chasis serán tales que le permitirán 
chocar contra ciertos obstáculos impactando con las ruedas, en vez de 
recibir el golpe en el chasis con los inconvenientes que eso traería.
Incluso puede llegar a darse vuelta (girar 180 grados al escalar un 
plano inclinado, por ejemplo) y detectar su posición, permitiendo 
corregir los controles para que dicho cambio de posición sea invisible 
para el usuario.

La velocidad será censada en las ruedas y mostradas al usuario en el 
tablero de control.

#	Descripcion detallada

## Bloque de control: 
	Está compuesto por la PC portátil, que corre una interfaz gráfica de usuario 
	programada en QT y se linkea al auto a través de Wifi, 
	utilizando un protocolo implementado con comunicación serie.

## Bloque vehículo: 
	El auto propiamente dicho. Contiene la mecánica del auto y la electrónica, 
	el micro, sensores, motores y el módulo Wifi que permite la comunicación 
	con el bloque de control.

## Especificaciones:
	Los motores de DC serán usados tanto para el movimiento adelante y atrás del auto, 
	como para controlar la dirección. Implementamos el control de los mismos con PWM.

	Los sensores US detectaran obstáculos (paredes u objetos ) a cierta distancia configurable,
	dando la posibilidad de detener el vehículo o programarle una rutina automática
	que permita evitar dichos obstáculos y continuar con el viaje con una corrección de la trayectoria.
	
	Para el manejo de los sensores haremos uso de los Timers, en modo match y captura.
	El sensor de velocidad opera como un cuenta vueltas en una de las ruedas del auto (
	sensor con disco perforado) que hace uso de un timer/counter para contar las vueltas y calcular la velocidad.
	El módulo Wifi comunica el stick con la PC en comunicación serie, usando una UART del LPC1769.

# Descripción del hardware

Módulo Wifi ESP8266:		con comunicación SERIE

LPC1769:			micro
	4 Motores: 			con salida por 4 GPIO + PWM
	4 Fotointerruptores:		mediante interrupción
	2 Fin de carrera:			controlados por 2 GPIO
	4 Ultrasonido:			controlados por timer
	Sensor UP/DOWN:		interruptor accionado por gravedad
	Leds azul y rojo:			con salida por 2 GPIO
	****


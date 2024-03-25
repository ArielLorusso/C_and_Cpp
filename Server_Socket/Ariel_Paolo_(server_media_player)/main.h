
#ifndef MAIN_H_
#define MAIN_H_

// stardard c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// fmod

#include "head/fmod.h"
#include "head/fmod_errors.h"
#include "head/wincompat.h"

// servidor

#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

#define PORT 3490	    /* El puerto donde se conectará, servidor */
#define BACKLOG 10	    /* Tamaño de la cola de conexiones recibidas */
#define MAXDATASIZE 100 /* máxima cantidad de bytes que puede recibir en una transacción*/

typedef struct cancion  //estructura de cancion
{
    char nombre[50];
    char autor [50];
    char direccion[100];
}Cancion;

typedef struct nodo 	//estructura nodo
{
    Cancion* cancion;
    struct nodo* PREV;
    struct nodo* NEXT;
}Nodo;


// servidor

int	conectar 	(int, char **);

int	Open_conection 	(struct sockaddr_in *); /* Función que crea la conexión*/

int	Aceptar_pedidos (int);	/* Función que acepta una conexión entrante*/

// fmod

void ERRCHECK (FMOD_RESULT result);

void pausar(FMOD_CHANNEL     **channel);

FMOD_RESULT F_CALLBACK 	myopen	(const char *name, int unicode, unsigned int *filesize, void **handle, void **userdata);

FMOD_RESULT F_CALLBACK 	myclose	(void *handle, void *userdata);

FMOD_RESULT F_CALLBACK 	myread	(void *handle, void *buffer, unsigned int sizebytes, unsigned int *bytesread, void *userdata);

FMOD_RESULT F_CALLBACK 	myseek	(void *handle, unsigned int pos, void *userdata);

// Listas

void 	menu ( Nodo **cabeza, Nodo **cola);

void 	crear_nodo(Nodo** cabeza, Nodo** cola);

Cancion* ingresar_cancion(Cancion* alguien);

void Borrar_cancion (Nodo** cabeza,Nodo** cola);

void Imprimir_lista(Nodo* cabeza);

void ordenar_name(Nodo** cabeza);

void ordenar_autor(Nodo** cabeza);

int contador_nodos(Nodo* cabeza);

void borrar_todo(Nodo* cola, Nodo** cabeza);

char* dir_cancion (Nodo* cabeza,int);

void limpiar_stdin();

#endif

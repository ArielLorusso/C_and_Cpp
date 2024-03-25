#ifndef	PARCIAL_H_
#define PARCIAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo
{
  char *apellido;
  char *nombres;
  char *legajo;
  int   calificacion;
  struct nodo *siguiente;
  struct nodo *anterior;
}alumnos;

void limpiarstdin ();

void menu ();

void nuevo_alumno (alumnos** nuevo);

void listar (alumnos *);

void ingresar (alumnos** );

void ordenar(alumnos *);

void borrar (alumnos *);

int contar (alumnos *);

void salir (alumnos *);

#endif
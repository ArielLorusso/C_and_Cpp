/*	Finalidad del programa: 	Utilisar listas para guardar nodos que contengan 
					
	
*/
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
//# include <>//# define

/*union tamaño
{
  short int numero; // %dh
  char      letra;
}*/

typedef struct pedidos
{
   char  nombre[40];
   char  colegio[40];
   char  prenda[40];
   short int talle;
   float    precio;
   struct pedidos* next;
   struct pedidos* prev;
}venta;

void menu();

void ingresar 	(venta** );
void listar 	(venta* );
void borrar 	(venta** );
void contar 	(venta* );
void ordenar	(venta** );
void vaciar	(venta** );

void limpiar ();
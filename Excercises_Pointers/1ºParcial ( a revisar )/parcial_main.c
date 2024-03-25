
#include "parcial.h"

// (gcc parcial_func.c parcial_main.c -I ~/Documentos/info1/ariel.lorusso/1ºParcial -g -oparcial)



void ingresar (alumnos **lista)
{
  alumnos *ingreso = (alumnos*)malloc(sizeof(alumnos));
  nuevo_alumno(&ingreso); 
   if (*lista == NULL)
   {
     *lista = ingreso;
   }

  else
  {
    (*lista)->anterior  = ingreso;
    ingreso->siguiente = (*lista);
    (*lista) = ingreso;
  }
  printf("	Ingreso de %s terminado\n",(*lista) -> apellido);
}


void menu ()
{ 
  alumnos *lista = NULL;
  short int numero = 0;
 
  while (numero != 7)
  {
  puts("____________________________________________________________________________________\n\n  Ingrese un numero correspondiente a la opcion del menù:");
  puts("	1  Ingresar");
  puts("	2  Listar");
  puts("	3  Borrar");
  puts("	4  Ordenar");
  puts("	5  Contar");
  puts("	6  Calcular");
  puts("	7  Salir");
  
    scanf("%hd",&numero);
    switch (numero)
    {
      case 1:puts("ingreso opcion 1");ingresar (&lista);break;
      case 2:puts("ingreso opcion 2");listar (lista);break;
      case 3:puts("ingreso opcion 3");borrar (lista);break;
      case 4:puts("ingreso opcion 4");ordenar (lista);break;
      case 5:puts("ingreso opcion 5");int num = contar(lista);printf("	La cantidad de alumnos es %d",num);break;
      case 6:puts("ingreso opcion 6");break;
      case 7:puts("ingreso opcion 7");break; /*salir ();*/;
      default: {puts("  Ingrese un numero valido (1,2,3,4,5,6)");}
    }
  }
}

int main ()
{
  menu();
  return 0;
}

#include "parcial.h"
 
 
void limpiarstdin ()
{
  int c;
  while ((c=getchar())!='\n' && c != EOF );
}

 void nuevo_alumno (alumnos** nuevo)
{
//   limpiarstdin();
//   printf("  Ingresar apellido\n");
//   scanf ("%s",(*nuevo)->apellido); fflush(stdin);
//   limpiarstdin();
//   puts("  Ingresar nombres");
//      fgets((*nuevo)->nombres,20,stdin);
//   puts("  Ingresar el legajo en formato: nn-nnnnnn-n 10 < n >= 0");
//     scanf ("%s", (*nuevo)->legajo); fflush(stdin);
//   puts("  Ingresar calificación");
//   scanf("%d",&((*nuevo)->calificacion) );
//   (*nuevo)->anterior=NULL;
//   (*nuevo)->siguiente=NULL;
  limpiarstdin();
  int c,i=0;
  printf("  Ingresar apellido\n");
  scanf ("%s",(*nuevo)->apellido); fflush(stdin);
  limpiarstdin();
  puts("  Ingresar nombres");
     while ((c=getchar())!='\n' && c != EOF )
     {
       ((*nuevo)->nombres)[i]=c;
       i++;
     }
     ((*nuevo)->nombres)[i]='\0';
  puts("  Ingresar el legajo en formato: nn-nnnnnn-n 10 < n >= 0");
    scanf ("%s", (*nuevo)->legajo); fflush(stdin);
  puts("  Ingresar calificación");
  scanf("%d",&((*nuevo)->calificacion) );
  (*nuevo)->anterior=NULL;
  (*nuevo)->siguiente=NULL;
}


void listar (alumnos *lista)
{
  alumnos *aux;
  aux = lista;
  do
  {
    if (aux != NULL){
    puts("	_______________ ____________________");
    printf("	Apellido	%s\n	Nombres		%s\n	Legajo		%s\n	Calificación	%d \n",aux->apellido,aux->nombres,aux->legajo,aux->calificacion);
    aux = aux->siguiente;}
     else {puts("	 ┌-----------------------------┐  > <\n	 | la lista se encuentra vacia |   ▬\n	 └-----------------------------┘\n░▒▓█");     
    }
  }while (aux != NULL);
}


void borrar(alumnos *lista)
{
  alumnos *aux=lista;
  int caso;
  puts("	1 Borrar basandose en el      →	apellido\n	2 Borrar basandose en los     →	Nombres\n	3 Borrar basandose en el      →	legajo\n	4 Borrar basandose en la      →	calificación\n ");
  scanf("%d",&caso);
  switch (caso)
  {/*salir ();*/;
    case 1:{
	    puts("\n	Ingrese el apellido del alumno a borrar");
	    char buscaR[20];
	    scanf("%s",buscaR);
	     if (aux != NULL)do
	      {
		if (! strcmp( (aux->apellido),buscaR) )
		{
		  puts("	_______________ ____________________");
		  printf("	Borrando....\n	Apellido	%s\n	Nombres		%s\n	Legajo		%s\n	Calificación	%d \n",aux->apellido,aux->nombres,aux->legajo,aux->calificacion);
		  aux->anterior->siguiente = aux->siguiente;
		  aux->siguiente->anterior = aux->anterior;
		  free(aux);	  
		}
		else { aux = (aux->siguiente); }
	      }while (aux->siguiente != NULL);
	   };break;
    default:{puts("  Ingrese un numero valido (1,2,3,4)");}
  }
}

void ordenar (alumnos *lista)
{
  printf("algo");
}

int contar (alumnos *lista)
{
  int i=0;alumnos* aux;
  aux = lista;
  if (aux != NULL)
  {
    while (aux != NULL);
    {
      aux = aux->siguiente;
      i++;
    }
  }  
  else
  {puts("	 ┌-----------------------------┐  > <\n	 | la lista se encuentra vacia |   ▬\n	 └-----------------------------┘\n░▒▓█");}
  return i;
}

//int calcular (alumnos *lista)


/*void salir (alumno *lista)
{j
  
}*/
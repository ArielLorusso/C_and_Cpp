/*Escribir una función que simule una mano de truco para la cantidad de jugadores indicada en su
argumento (2, 3, 4 o 6 jugadores). Solo se pide repartir las cartas.*/
#include <stdio.h>
#include <time.h>

void main ()
{
  int cont,palo,jug=1;
  srand(time(NULL));
  
  while(jug<4)
  {
    printf("\n\n  Jugador numero: %d ",jug);
    cont=1;
    
    while(cont<4)
    {
      printf("\n    Carta %d es: %d	",cont,1+rand()%12);
      printf("de");
      palo= 1+rand()%4;
      switch (palo)
      {
	case 1: printf(" Oro");   break;
	case 2: printf(" Espada");break;
	case 3: printf(" Basto"); break;
	case 4: printf(" Copa");  break;
      }
  
    cont++;
    }
    
  printf("\n\n");
  jug++;
  }
  
  
}

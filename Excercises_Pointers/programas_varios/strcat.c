#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void main ()
{
  const char* dos = "casa",*tres = "cama",*cuatro = "pistoru",*cinco ="gomugomuno",*seis = "caaa";
  char uno[50]="casa",* com;
  
  puts(" Holamundo");
  
  com = strcat(uno,dos);
  printf("\nprimera = %s",com);
  
  com = strcat(uno,tres);
  printf("\nsegunda = %s",com);
  
  com = strcat(uno,cuatro);
  printf("\ntercera = %s",com);
  
  com = strcat(uno,cinco);
  printf("\n cuarta = %s",com);
  
  com = strcat(uno,seis);
  printf("\nquinta = %s",com);
  
 // strcat(dos,tres);
  //printf("\nsexta = %s",dos);
}

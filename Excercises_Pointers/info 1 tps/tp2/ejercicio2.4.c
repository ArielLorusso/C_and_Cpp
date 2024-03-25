/* Programa que:
 * 	pide el ingreso d; 1 valor reale
 * 	calcula el factorial de dicho numero
 * 	imprime en pantalla el proceso
	*/
#include <stdio.h>

int main (void)

{
  printf("\n\n Ingrese una serir de  numeros enteros y positivos .\n La serie se dara por finalisada al ingresar un 0 \n");
  int save=0,x=1,y=1;
  scanf("%d",&x);
  while(x>0&&y>0)
  {
    scanf("%d",&y);
    if(y<=x)
    {	
      save++;
    }
    x=y;  
  }
  save--;
  if(x<0||y<0) printf("\n ingresaste un numero negativo\n\n");
  else
  if(save==0)  printf("\n La serie esta ordenada\n\n");
  if(save==1)  printf("\n la serie esta desordenada 1 vez\n\n");
  if(save >1)  printf("\n la serie esta desordenada %d veces\n\n",save);
}

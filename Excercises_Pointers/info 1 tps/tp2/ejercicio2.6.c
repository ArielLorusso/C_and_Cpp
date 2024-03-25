/*El valor aproximado del numero de Euler, e , se puede obtener con la siguiente
formula: e = 1 + 1/1! + 1/2! + 1/3! + 1/4! + 1/5! + ...
Escribir un programa que calcule el valor aproximado de e mediante un ciclo
repetitivo que termine cuando la diferencia entre dos aproximaciones sucesivas
difiera en menos de 10-9.*/

#include <stdio.h>

int main (void)

{
  printf("\n\n Este programa calcula el numero e acercandose a este mediante sucesivas repeticiones \n");
  printf(" Cuando la deferencia entre la ultima aproximacion y la anterior a esta sea 10^-9\n se mostrara el resultado.\n");
  
  int ser,numAct=50;  
  double save=0,prod[numAct],i=1;

  for(ser=1;i>0.000000001;ser++) 		//
  {  

    for(numAct=ser;numAct>0;numAct--) 		//carga prod[] = los valores naturales por debajo de ser
      {
	prod[numAct] = numAct;
      }  
  
    
    for(numAct=ser;numAct>1;numAct--)		//calcula save = valor de serie = 1/prod[numAct]*1/prod[numAct-n] (hasta n = [numAct-1] 
      {
	prod[numAct-1] = (prod[numAct-1])*(prod[numAct]);
      }
    
  save = 1/prod[numAct]+ save;
  i=1/prod[numAct];
  printf("\n	%.20lf	suma = 1/%d!",i,ser);
  printf("\n	%.20lf	Resultado\n",save);
  //imprime los procedimientos de calculo
  
  }
 
  save++;

  printf("\n  %d	     	                Cantidad de veces que se cumplio la serie \n",ser); 
  printf("  %.25lf	Resultado\n",save);
  printf("  %.25lf	Ultima suma a la suceccion\n\n",i); 
  //imprime todos los resultados
  
  return 0; 
}
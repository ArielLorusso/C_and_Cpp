/** Programa que:
 * 	pide el ingreso de 10 temperaturas
 * 	hace el promedio de lastemperaturas y lo imprime
 * 	ordena la secuencia de temperaturas
 * 	imprime la menor y la mayor temperaturas
 * 	comprueva cuantas temperaturas estubieron en el intervalo [20 ; 45]
 * 	imprime em pantalla cuantas temperaturas cumplieron esa condicion	*/

#include <stdio.h>

int main (void)

{
  int temp [9],eva,cont,save;
  float tempTotal; 
  printf ("\nIngrese diez valores de temperatura en el formato: \n N-N-N-N-N-N-N-N-N-N ");
  printf ("Donde N simboliza el valor de temperatura enteras\n\n");
  ///indica al usuario la informacion que deve ingresar
  
  scanf("%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-",&temp[0],&temp[1],&temp[2],&temp[3],&temp[4],&temp[5],&temp[6],&temp[7],&temp[8],&temp[9]);
  ///asignacion de numeros a las variables
  
  tempTotal = (temp[0]+temp[1]+temp[2]+temp[3]+temp[4]+temp[5]+temp[6]+temp[7]+temp[8]+temp[9]);
  tempTotal = (tempTotal / 10);
  ///asignacion de valor a tempTotal = promedio
  
  printf ("\n La temeratura promedio es %f \n ",tempTotal);
  /// imprime en pantalla el resultado
  
  for (cont=0;cont<=8;cont++) 
  ///ordena todos los numeros de menor a mayor  pomiendo al mas grande al final 9 veces
    {
      for (eva=0;eva<9;eva++) 
      /// ordenamiento en el cual la mayor temperatura se mueve hacia adelante y la menor queda 1 espacio atras
      {
	if (temp[eva] > temp[eva+1]) 
	/// si el valor evaluedo es mayor que el siguiente invertir los valores
	{
	  save      = temp[eva];
	  temp[eva]   = temp[eva+1];
	  temp[eva+1] = save;
	}      
      }
    }
  
  printf("\n La mayor de las temperatruras fue %d \n La menor de las temperatruras fue %d \n ",temp[9],temp[0]);
  
  save = 0;
  ///limpio save para usarlo de contador
    
  for (cont=0;cont<10;cont++)
  ///cuanta cantidad de veces la remperatura estuvo entre 20 y 45 
  {
    if (temp[cont]<=45 && temp[cont]>=20)
      save ++;
  }
  
  printf("\n La temperatura estuvo entre 45 y 20 (incluidos) %d \n\n" ,save);
  if (save != 1)  
  ///evaluacion para no comunicarse de una manera inadecuada :)
  {
    printf("veces");
  }
  else printf("vez");
  
  
  return 0;
}

/// para compilar ingresar en la consola: gcc -g -Wall -o ejercicio2.1 ejercicio2.1.c 
/* Programa que:
 * 	pide el ingreso de 1 valor reale
 * 	calcula el factorial de dicho numero
 * 	imprime en pantalla el proceso
	*/

#include <stdio.h>


int main (void)

{
  int numA,result,save;
  
  printf("\n\n Ingrese un numero entero positivo y menor que 13.\n A continuacion se calculara el factorial\n");
  scanf("%d",&numA);
  printf("\n");
  
  if (numA<0)
  {
    printf(" El numero no es positivo por lo tanto no se puede calcular el factorial\n\n");
  }
  
  else if (numA>12)
  {
    printf(" El numero es demasiado grande por lo tanto no se puede calcular el factorial\n\n");
  }
  else
  {  
    unsigned int prod[numA];
    save = numA;
    
    printf("Calculando:\n          serie de numeros:");
    for(numA<13;numA>0;numA--)
    {
      prod[numA] = numA;
      printf("  %d",numA);
    }
    
    numA = save;
    printf("\n          operando numeros:");
  
    for(numA<13;numA>1;numA--)
    {
      prod[numA-1] = (prod[numA-1])*(prod[numA]);
      printf(" %u",prod[numA]);
    }
    
    printf("\n\n El resultado es  %u\n\n",prod[numA]);
  }  
  
  return 0; 
}

// para compilar ingresar en la consola: gcc -o ejercicio2.3 ejercicio2.3.c
//ingresan dos valores reales y el signo - + mult div se deveran presentar por pantalla los datos ingresados 
/* Programa que:
 * 	pide el ingreso de 2 valores reales
 * 	pide el ingreso de operacion a realizar
 * 	presenta en pantalla los datos ingresados la operacion y el resultado
 * 	evalua si el ingreso de la operacion es valido
 * 	presenta en pantalla el resultado de la evaluacion
 * 	
 * 	imprime em pantalla cuantas temperaturas cumplieron esa condicion	*/

#include <stdio.h>


int main (void)

{
  float numA,numB,result;
  char operacion;
  
  printf("\n\n Ingrese un numero real el caracter " " una operacion caracter " " y un segundo numero ");
  printf("\n Por ejemplo: 1111 * 1.111 \n Los caracteres validos de operacion son '+' '-' '&' '/' \n\n");
  scanf("%f %c %f",&numA,&operacion,&numB);
  
  
    printf("\n\nEl primer  numero ingresado fue %f \n El segundo numero ingresado fue %f \n El resultado de la operacion es ",numA,numB);
  
    switch (operacion)
    {
      case '+': result = (numA + numB); printf("%f",result);
      break;
      case '-': result = (numA - numB); printf("%f",result);
      break;
      case '*': result = (numA * numB); printf("%f",result);
      break;
      case '/': 
	if (numB!=0)
	{ 
	  result = (numA / numB); printf("%f",result);
	}
	else printf("No se puede dividir por cero");
      break;
      default: printf("ingrese un caracter de operacion correcto");
    }
    
  printf("\n\n");
  
  
  return 0;
}

// para compilar ingresar en la consola: gcc -g -Wall -o ejercicio2.1 ejercicio2.1.c 

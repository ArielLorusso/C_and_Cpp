/**Ejercicio 3.3.
a) Defina un tipo de dato "tipodato" a partir del tipo nativo "float" (usando typedef)
b) Defina un tipo enumerativo "tescala" que contenga los símbolos CELSIUS y FAHRENHEIT.
c) Escriba una función que reciba un valor de temperatura en precisión doble, y la escala de
temperaturas de destino, y realice la conversión del valor.*/

#include <stdio.h>
typedef enum
{
  CELCIUS,
  FARENHEIT
}tescala;

void main()
{
  typedef float tipodato;
  printf("\n\n Programa de convercion de temperaturas entre celsius y farenheit: \n\n Ingrese C o F (correspondientes al sistema de temperatura) y el valor de temprratura ");
  printf("\n La temperatura se convertira al otro sistema\n ");
  tipodato p;
  char sis;
  scanf("%c",&sis);
  scanf("%f",&p);
  switch (sis)
  {
    case 'C':  p = (1.8 * p  +  32); sis ='F' ;break;
    case 'F':  p = ((p - 32) / 1.8); sis ='C' ;break;
    default : printf("\n Ha ingresado erroneament el sistema de temperatura");
  }
  printf("\n Son %f  ° %c\n\n",p,sis);

}

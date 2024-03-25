///Escriba una función que reciba dos argumentos enteros x e y, y devuelva xy.
#include <stdio.h>

void main ()
{
  double base,save;
  int exponente;
  printf("\n\n Programa que resuelve una potencia\n\n Ingrese la base de la potencia decimal con punto):	");
  scanf("%lf",&base);
  save=base;
  printf(" Ahora ingrese el exponente entero al cual se elevara:	");
  scanf("%d",&exponente);
  
  if (exponente>0)
  {
    while(exponente>1)
    {
      base = save*base;
      exponente--;
    }
    printf("\n El resultado es %f\n\n",base);
  }
  
  else if (exponente<0)
  {
    while(exponente<1)
    {
      base = base/save;
      exponente++;
    }
    
    printf("\n El resultado es %.20lf\n\n",base);
  }
  
  else printf("\n El resultado es 1\n\n");
}
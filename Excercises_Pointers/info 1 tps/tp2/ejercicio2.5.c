/*programa que: 
 * 	recibe pares de valores X e Y, querepresentan las coordenadas rectangulares
 * 	convierta en coordenadas polares(modilo,angulo)
 * 	imprime en pamtalla el resultado */

#include <stdio.h>
#include <math.h>



int main (void)
{
  float x,y,Mod,Ang;
  
  printf("\n\n Ingresar un par de numeros en formato (xx.x,yy.y)\n Donde x e y son los digitos en coordenadas rectangulares de un vector\n\n");
  printf(" ");
  scanf("(%f,%f)",&x,&y);
  
  Mod = sqrt(x*x+y*y);
  Ang = atan(y/x);
  printf("\n (%f,%f°)Radianesr\n",Mod,Ang);
  
  Ang = (Ang*180/(atan(1)*4));
  printf(" (%f,%f°)Grados\n\n",Mod,Ang);
  
  return 0;
}

// para compilar: g++ -L /usr/lib -o bejercicio2.5 ejercicio2.5.c
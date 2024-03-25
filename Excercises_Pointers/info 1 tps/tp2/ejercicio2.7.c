/* Ejercicio 2.7.
Un tirador realiza 20 disparos a un blanco cuyo centro coincide con el origen de
coordenadas. Leyendo la abscisa y la ordenada de cada impacto, deberá
calcularse el puntaje obtenido. El blanco tiene cuatro zonas que, de acuerdo a la
distancia del impacto al origen (R), son:
ZONA		DENOMINACIÓN	PUNTAJE
0 <=R <=1 	centro 		10
1 < R <= 5 	medio 		5
5 < R <= 10 	externo 	1
    R > 10 	falla 		0 	*/

#include <stdio.h>
#include <math.h>



void main ()
{
  int a,B=0;
  float x[19],y[19],Mod[19];
  
  printf("\n\n Ingresar un par de numeros en formato (x,y) \n Donde x e y representan:\n ");
  printf("La absisa y la ordenada de la distancia a la que el tiro estuvo de dar en el blaco\n ");
  printf("	Deve ingresar 20 veces ");

  x[0]=10;x[1]=10;x[2]=10;x[3]=10;x[4]=10;x[5]=10;x[6]=10;x[7]=10;x[8]=10;x[9]=10;x[10]=10;x[11]=10;x[12]=10;x[13]=10;x[14]=10;x[15]=10;x[16]=10;x[17]=10;x[18]=10;x[19]=10;
  y[0]=10;y[1]=10;y[2]=10;y[3]=10;y[4]=10;y[5]=10;y[6]=10;y[7]=10;y[8]=10;y[9]=10;y[10]=10;y[11]=10;y[12]=10;y[13]=10;y[14]=10;y[15]=10;y[16]=10;y[17]=10;y[18]=10;y[19]=10;
  //inicializo todos los valores en un valor que no sume puntos si no se lo cambia por otro para no sumar puntos extra en el caso de que no se ingrese valor
  
  scanf("(%f,%f)(%f,%f)(%f,%f)(%f,%f)(%f,%f)(%f,%f)(%f,%f)(%f,%f)(%f,%f)(%f,%f)",&x[0],&y[0],&x[1],&y[1],&x[2],&y[2],&x[3],&y[3],&x[4],&y[4],&x[5],&y[5],&x[6],&y[6],&x[7],&y[7],&x[8],&y[8],&x[9],&y[9]);
  scanf("(%f,%f)(%f,%f)(%f,%f)(%f,%f)(%f,%f)(%f,%f)(%f,%f)(%f,%f)(%f,%f)(%f,%f)",&x[10],&y[10],&x[11],&y[11],&x[12],&y[12],&x[13],&y[13],&x[14],&y[14],&x[15],&y[15],&x[16],&y[16],&x[17],&y[17],&x[18],&y[18],&x[19],&y[19]);
  
  for(a=0;a<=19;a++)
  {
    Mod[a] = sqrt(x[a]*x[a]+y[a]*y[a]);
    
   if   	(Mod[a] >= 0 && Mod[a] <=  1)	Mod[a] = 10;
   else if	(Mod[a] >  1 && Mod[a] <=  5)	Mod[a] = 5;
   else if	(Mod[a] >  5 && Mod[a] <=  10)	Mod[a] = 1;
   else if	(Mod[a] > 10 )	Mod[a] = 0;	   
   printf("%f\n",Mod[a]);   
   
  }

  for(a=0;a<=19;a++)
  {
    B = Mod[a] + B;
    printf("%d\n",B);
  }
  
  return 0;
}

//  g++ -L /usr/lib -o bejercicio2.7 ejercicio2.7.c
//   bug en el ultimo valor de los arreglos x e y siempre arroja el valor 1 deberia ser 0

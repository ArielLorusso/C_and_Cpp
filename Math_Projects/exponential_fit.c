/*  FALTA PODER INGRESAR FUNCIONES QUE CRUSEN EL EJE X
    CONST +   Esc * 2 ^ (X * Exp)
    SIGN (P1.Y) = SIGN (P2.Y) */

#include <stdio.h>
#include <math.h>

int MaxIter = 30;    // Limite para evitar bucle infinito

typedef  struct     //  Esructura que define un punto cartesiano
{
  double X;
  double Y;
}Point;

int ExpAjust (Point P1, Point P2, Point* Result ,float MaxError,int Iter);

int main(void) 
{
  float MaxError;      int Iter = 0;
  Point P1, P2, Result;
 
  P1.X = -1;   P1.Y = 4;   //  Punto 1   de exponencial 
  P2.X = 2;    P2.Y = 6;   //  Punto 2   de exponencial
  Result.X=1; Result.Y=1;   // Partida de aproximacion
  printf("P1=(%.2f, %.3f)      P2=(%.2f, %.3f) \n\n",P1.X,P1.Y,P2.X,P2.Y);

  ExpAjust (P1 , P2 ,& Result , 1.000000000001, Iter);
  printf("\n\n MAIN\t %.56f * 2^(%.56f x)", Result.X , Result.Y);

  return 0;
} 


/*  Result es la partida de donde se emieza a aproximar 
(si se desconose poner (1,1)) aqui se ira calculando el resultado   */
int ExpAjust (Point P1, Point P2, Point* Result ,float MaxError,int Iter) 
{
  double  Esc , Exp, EscError , ExpError;
  
  printf("Iter %d\t\t\t\t %.3f * 2^(%.3f X)\n",Iter, Result->X , Result->Y);

  EscError = P1.Y /   ( Result->X *  pow (2 , P1.X * Result->Y));
  Esc =  EscError * Result->X ;
  printf("EscERR %.9f", EscError);  
  /*Fator error Escalar
   Que tan fuera de escala esta  Esc * 2 ^ (X * Exp)
   EscError = cuanto falta multiplicar                */

  Exp  =  log2 (P2.Y/(Esc)) / P2.X ;
  ExpError = Exp / Result->Y;
  printf("  ExpErr %.9f    ", ExpError);
  /* Fator error exponencial  
     Cuanl es el cociente entre 
          valor actual(Exp)      y el previo (Result.Y) 
     Cuanto falle en la escala de  Y1   */

  
  Result->X = Esc;
  Result->Y = Exp;
  printf("\t %.4f * 2^(%.4f X)\t\n", Result->X , Result->Y);

  
  
  Iter++;
  if (((EscError > MaxError) || (EscError < 1/MaxError)) && Iter < MaxIter)
  { ExpAjust (P1 , P2 , Result , MaxError,Iter); } 
  else { return 1 ; }
}

//  corrijo el primer punto con escala y el segundo con exponente
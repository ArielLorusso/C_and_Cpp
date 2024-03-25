#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
  int Subdiv;
  float Min, Max;
  float *X;
  float *Y;
} Funct;

Funct  LinealFunct (float Min, float Max, int Subdiv);
void   PrintFunct  (Funct In);
Funct  DeriveFunct (Funct In);

Funct  SinFunct           (Funct In); 

Funct  IntegrateFunctOLD  (Funct In);  // Simplest Better end Fitting
Funct  IntegrateFunctOLD2 (Funct In);
Funct  IntegrateFunctNEW  (Funct In);  //          Better Start Fitting
Funct  IntegrateFunctPERF (Funct In);  // Bad ?
Funct  IntegrateFunctBEST (Funct In);  // Cost but best

int main ( void )
{
    Funct F1,F2;
    float Min,Max;
    int Subdiv;
  
    printf("Funcion Lineal...\n Cota inferior:");
    scanf("%f",& Min);
    printf("Cota superior:");
    scanf("%f",& Max);
    printf("subdivicion:");
    scanf("%d",& Subdiv);

    /*printf("\n\n\n   Lineal :\n");
    PrintFunct( F1 = LinealFunct (Min, Max, Subdiv));
///
    printf("\n\n\n   Derivada :\n");
    PrintFunct( F2 = DeriveFunct(F1));
    free (F2.X);free (F2.Y);
  */F1 = LinealFunct (Min, Max, Subdiv);
  
 //   printf("\n\n\n  Integral VIEJA:\n");
 //   PrintFunct( F2 = IntegrateFunctOLD (F1));
 //   printf("\n\n\n  Integral NUEVA:\n");
 //   PrintFunct( F2 =  IntegrateFunctNEW  (F1));  
      printf("\n\n\n  Integral MEZCLA:\n");
      PrintFunct( F2 =  IntegrateFunctPERF (F1));  
 //   printf("\n\n\n  Integral MEJOR:\n");
  //  PrintFunct( F2 =  IntegrateFunctBEST (F1)); 
/*
    printf("\n\n\n   Sin Lineal :\n");   
    PrintFunct( F1 = SinFunct ( LinealFunct (Min, Max, Subdiv)));
    printf("\n\n\n   Derivada :\n");
    PrintFunct( F2 = DeriveFunct(F1));
    free (F2.X);free (F2.Y);
    printf("\n\n\n  Integral :\n");
    PrintFunct( F2 = IntegrateFunct (F1));
*/
    printf("\n\n  PROGRAM ENDED");  while(1)
    return 0;
}

/*
    int  fi = (Max-Min)*Subdiv*10;                                                // integer will be multiple of 10 if Max-Min is a valid value
    if ( (fi) % 10 ) { printf(" The chosen Max value does n ",f*i,fi %10);}       // True (invalid Max value)*/
///////////////////////////////////////////////////////////////////////  OK
Funct  LinealFunct (float Min, float Max, int Subdiv)
{
  float Inc = (Max - Min) / (Subdiv - 1);
  float *X = (float *) malloc (Subdiv * sizeof (int));
  float *Y = (float *) malloc (Subdiv * sizeof (int));

  // int  SubdivTest = (Max-Min)*Subdiv*10;
  // if ( (SubdivTest) % 10 ) {  printf("True (Bad) Unhable to fit Naturals"); }
  for (int i = 0; i < Subdiv; i++)
    {
        X[i] = Min + (i * Inc);
        Y[i] = X[i];
    }
  Funct Out;
  Out.Subdiv = Subdiv;
  Out.Max = Max;
  Out.Min = Min;
  Out.X = X;
  Out.Y = Y;
  printf("\n   Exit LinealFunct :\n");
  return Out;
}

///////////////////////////////////////////////////////////////////////  OK
Funct  SinFunct (Funct In)
{
  float *X = (float *) malloc (In.Subdiv * sizeof (int));
  float *Y = (float *) malloc (In.Subdiv * sizeof (int));

  for (int i = 0; i < In.Subdiv; i++)
    {
        X[i] =     In.X[i] ;
        Y[i] = sin(In.Y[i]);
    }
  Funct Out;
  Out.Subdiv = In.Subdiv;
  Out.Max = In.Max;
  Out.Min = In.Min;
  Out.X = X;
  Out.Y = Y;
  printf("\n   exit SinFunct :\n");
  return Out;
}

///////////////////////////////////////////////////////////////////////  OK
void PrintFunct (Funct In)
{
    char buffer [10];

    printf("    X    --}>>\n");
    for (int i=0; i<In.Subdiv ;i++)
    {
        sprintf (  buffer, "%.3f",In.X[i] );   //  FORMAT FOR STUPID EXCEL
            for (int j=0; j<10 ;j++)   {if (buffer[j]=='.')   { buffer[j]=','; }      }
        printf  ("%s\n",   buffer);
    }

    printf("    Y    --}>>\n");
    for (int i=0; i<In.Subdiv ;i++) 
    {
        sprintf ( buffer, "%.3f",In.Y[i] );
            for (int j=0; j<10 ;j++)   {if (buffer[j]=='.')   { buffer[j]=','; }      }
        printf  ("%s\n", buffer);
    }
    
}

///////////////////////////////////////////////////////////////////////   OK
Funct DeriveFunct (Funct In)
{
    Funct Out;
    
    Out.Max = In.Max;
    Out.Min = In.Min;
    Out.Subdiv = In.Subdiv;
    
    Out.X = (float *) malloc (Out.Subdiv*sizeof(float));
    Out.Y = (float *) malloc (Out.Subdiv*sizeof(float));
    
    
    int i = 0;
        Out.X[i] =  In.X[i];
        Out.Y[i] = (In.Y[i + 1] - In.Y[i])  / (In.X[i+1]-In.X[i]);
    for (i = 1; i <  (In.Subdiv - 1); i++)
    {
        Out.X[i] = In.X[i];
        Out.Y[i] = (In.Y[i + 1] - In.Y[i - 1]) / (In.X[i+1]-In.X[i-1]);
    }
    i = In.Subdiv - 1;
        Out.X[i] =  In.X[i];
        Out.Y[i] = (In.Y[i] - In.Y[i - 1]) / (In.X[i ] - In.X[i-1]);

  return Out;
}
///////////////////////////////////////////////////////////////////////  NOT OK
Funct IntegrateFunctNEW (Funct In)
{
    float Inc = (In.Max - In.Min) / (In.Subdiv - 1);
    float *X = (float *) malloc ((In.Subdiv) * sizeof (int));
    float *Y = (float *) malloc ((In.Subdiv) * sizeof (int));
    
    for (int i = 0; i < In.Subdiv; i++)
    {
        X[i] = In.X[i];
        Y[i] = 0;
        for (int j = 1; i >= j; j++)                        //j = 0;   ( Metodo Viejo )
	    {
	        Y[i] += (In.Y[i - j] +In.Y[i - j -1]) * Inc/2;    // Y[i] += In.Y[i - j] * Inc;   // Inc es la base de cada rectangulo a los cuales aplicamos la sumatoria
	    }                                                     // ( Metodo Viejo )
    }
  Funct Out;
  Out.Max = In.Max;
  Out.Min = In.Min;
  Out.Subdiv = In.Subdiv;
  Out.X = X;
  Out.Y = Y;

  return Out;
}

///////////////////////////////////////////////////////////////////////  NOT OK
Funct IntegrateFunctOLD (Funct In)
{
    float Inc = (In.Max - In.Min) / (In.Subdiv - 1);
    float *X = (float *) malloc ((In.Subdiv) * sizeof (int));
    float *Y = (float *) malloc ((In.Subdiv) * sizeof (int));
    
    for (int i = 0; i < In.Subdiv; i++)
    {
        X[i] = In.X[i];
        Y[i] = 0;
        for (int j = 0; i >= j; j++)      //
	    {
	        Y[i] += In.Y[i - j] * Inc;      // Y[i] += (In.Y[i - j] +In.Y[i - j -1]) * Inc/2;  // Inc es la base de cada rectangulo a los cuales aplicamos la sumatoria
	    }                                   // 
    }
  Funct Out;
  Out.Max = In.Max;
  Out.Min = In.Min;
  Out.Subdiv = In.Subdiv;
  Out.X = X;
  Out.Y = Y;

  return Out;
}

Funct IntegrateFunctOLD2 (Funct In)
{
    float Inc = (In.Max - In.Min) / (In.Subdiv - 1);
    float *X = (float *) malloc ((In.Subdiv) * sizeof (int));
    float *Y = (float *) malloc ((In.Subdiv) * sizeof (int));
    
    for (int i = 0; i < In.Subdiv; i++)
    {
        X[i] = In.X[i];
        Y[i] = 0;
        for (int j = 1; i >= j; j++)      //
	      {
	        Y[i] += In.Y[i - j] * Inc;      // Y[i] += (In.Y[i - j] +In.Y[i - j -1]) * Inc/2;  // Inc es la base de cada rectangulo a los cuales aplicamos la sumatoria
	      }                                   // 
    }
  Funct Out;
  Out.Max = In.Max;
  Out.Min = In.Min;
  Out.Subdiv = In.Subdiv;
  Out.X = X;
  Out.Y = Y;

  return Out;
}

Funct IntegrateFunctPERF (Funct In)
{
    Funct F_Old , F_New; 
    F_Old = IntegrateFunctOLD (In) ;
    F_New = IntegrateFunctOLD2 (In) ;

    float Inc = (In.Max - In.Min) / (In.Subdiv - 1);
    float *X = (float *) malloc ((In.Subdiv) * sizeof (int));
    float *Y = (float *) malloc ((In.Subdiv) * sizeof (int));
    
    for (int i = 0; i < In.Subdiv; i++)
    {
        X[i] = In.X[i];
	    Y[i] = (F_Old.Y[i] + F_New.Y[i]) /2 ;  // Promedio                                   
    }
    for (int j = 0; j <= In.Subdiv; j++)      //Corrige la CTE de la Integral
    {   
        Y[j] -= F_Old.Y[0]/2;  
    }  // AC1ado
    // free(F_Old.Y); free(F_Old.X); free(F_New.Y); free(F_New.Y);
  Funct Out;
  Out.Max = In.Max;
  Out.Min = In.Min;
  Out.Subdiv = In.Subdiv;
  Out.X = X;
  Out.Y = Y;

  return Out;
}


// float IntegrateBarrow  Funct (float Min, float Max, Funct In)  {}
// float IntegrateBarrow  Funct (float Min, float Max, Funct In)  {}
/*
Funct
AddFunct (Funct F1, Funct F2)
{
  if (F1.Subdiv != F2.Subdiv)
    {
      prinf ("Error: Try using matching subdivition functions")
	// if (F1.Subdiv % F2.Subdiv = 0) { CurrSubdiv = F1.Subdiv / F2.Subdiv;}
	// if (F2.Subdiv % F1.Subdiv = 0) { CurrSubdiv = F1.Subdiv / F2.Subdiv;}
	// else { reurn ;}
    }

  else
    {
      int CurrMax, CurrMin;
      if (F1.Max < F1.Max)
	{
	  CurrMax = F1.Max;
	}			// Use lowest range intervale
      else
	{
	  CurrMax = F2.Max;
	}
      if (F1.Min > F1.Min)
	{
	  CurrMax = F1.Max;
	}
      else
	{
	  CurrMax = F2.Max;
	}
      int VecLen = (Curr.Max - Curr.Min) * F1.Subdiv;

      float *X = (int *) malloc ((VecLen) * sizeof (int));
      float *Y = (int *) malloc ((VecLen) * sizeof (int));
      for (int i = 0; i < VecLen; i++)
	{
	  X[i] = Min + (i / Subdiv);
	  Y[i] = F1.Y[i] + F2.Y[i] l;
	}
    }
  Funct Out;
  Out.Max = curr.Max;
  Out.Min = curr.Min;
  Out.Subdiv = F1.Subdiv;
  Out.X = X;
  Out.Y = Y;

  return Out;
}

//  MultiplyFunc ()  (F1(X)*F2(X)
Funct
AddFunct (Funct F1, Funct F2)
{
  if (F1.Subdiv != F2.Subdiv)
    {
      prinf ("Error: Try using matching subdivition functions")
	// if (F1.Subdiv % F2.Subdiv = 0) { CurrSubdiv = F1.Subdiv / F2.Subdiv;}
	// if (F2.Subdiv % F1.Subdiv = 0) { CurrSubdiv = F1.Subdiv / F2.Subdiv;}
	// else { reurn ;}
    }

  else
    {
      int CurrMax, CurrMin;
      if (F1.Max < F1.Max)
	{
	  CurrMax = F1.Max;
	}			// Use lowest range intervale
      else
	{
	  CurrMax = F2.Max;
	}
      if (F1.Min > F1.Min)
	{
	  CurrMax = F1.Max;
	}
      else
	{
	  CurrMax = F2.Max;
	}
      int VecLen = (Curr.Max - Curr.Min) * F1.Subdiv;

      float *X = (int *) malloc ((VecLen) * sizeof (int));
      float *Y = (int *) malloc ((VecLen) * sizeof (int));
      for (int i = 0; i < VecLen; i++)
	{
	  X[i] = Min + (i / Subdiv);
	  Y[i] = F1.Y[i] * F2.Y[i] l;
	}
    }
  Funct Out;
  Out.Max = curr.Max;
  Out.Min = curr.Min;
  Out.Subdiv = F1.Subdiv;
  Out.X = X;
  Out.Y = Y;

  return Out;
}

//  DivideFunc
Funct
AddFunct (Funct F1, Funct F2)	// F1:Numerad  F2:denom
{
  if (F1.Subdiv != F2.Subdiv)
    {
      prinf ("Error: Try using matching subdivition functions")
	// if (F1.Subdiv % F2.Subdiv = 0) { CurrSubdiv = F1.Subdiv / F2.Subdiv;}
	// if (F2.Subdiv % F1.Subdiv = 0) { CurrSubdiv = F1.Subdiv / F2.Subdiv;}
	// else { reurn ;}
    }

  else
    {
      int CurrMax, CurrMin;
      if (F1.Max < F1.Max)
	{
	  CurrMax = F1.Max;
	}			// Use lowest range intervale
      else
	{
	  CurrMax = F2.Max;
	}
      if (F1.Min > F1.Min)
	{
	  CurrMax = F1.Max;
	}
      else
	{
	  CurrMax = F2.Max;
	}
      int VecLen = (Curr.Max - Curr.Min) * F1.Subdiv;

      float *X = (int *) malloc ((VecLen) * sizeof (int));
      float *Y = (int *) malloc ((VecLen) * sizeof (int));
      for (int i = 0; i < VecLen; i++)
	{
	  X[i] = Min + (i / Subdiv);
	  Y[i] = F1.Y[i] / F2.Y[i] l;
	}
    }
  Funct Out;
  Out.Max = curr.Max;
  Out.Min = curr.Min;
  Out.Subdiv = F1.Subdiv;
  Out.X = X;
  Out.Y = Y;

  return Out;
}

//  ScaleFunc ()     (N *F1(X))
Funct
IntegrateFunct (int N, Funct In)
{
  int VecLen = (In.Max - In.Min) * In.Subdiv;
  float *X = (int *) malloc ((VecLen) * sizeof (int));	//  CREAR NUEVA FUNC ?    si
  float *Y = (int *) malloc ((VecLen) * sizeof (int));
  for (int i = 0; i < VecLen; i++)
    {
      X[i] = Min + (i / Subdiv);
      Y[i] = N * In.Y[i];
    }
  Funct Out;
  Out.Max = In.Max;
  Out.Min = In.Min;
  Out.Subdiv = In.Subdiv;
  Out.X = X;
  Out.Y = Y;

  return Out;
}

//  CompressFunc ()  (F1(N * X))
Func
CompressFunc (Float N, Func * In)
{
  In->Max = In->Max / N
    In->Min = In->Min / N
    In->Subdiv = int VecLen = (In.Max - In.Min) * In.Subdiv;
  for (int i = 0; i < VecLen; i++)
    {
      X[i] = Min + (i / Subdiv);
    }
}*/


//  AbsFunc ()       (|F1(x)|)
//  florFun ()       (float(int(F1(X))))
//  
//  Sin
//  Cos
//  X^2
//  X^N

//  ConstFunc  ()     
//  ConcatFunc (F1&F2) [Min1, MID=Max1)=[Min2  ,Max2]

//  FuncToVect ()

//Pol  TaylorSeries Func
//Func  TailorInverse Pol
//  linealResample  
//  f(X,Y)

//  BinomialDist
//  BinomialSimul
//  Probabliti    (Range Max, Range Mi n)


//  Boolean Algebra     TruthTableToCircuit
//  MdeToShiftReg       



#include "stdio.h"
#include "stdlib.h"
#include "time.h"
///         Contador de largo
/*//     while(& Muestras[i] != NULL) {i++;}   printf("\n\nTamano: %d\n",i);
*/

        /////  FUNCIONES
int*   GeneradorVectorRand   (int tamano,   int rango);
int*   GeneradorVectorLineal (int tamano,   int rango);
void   ImprimirVector        (int* Vector,  int tamano);
int*   FloToIntVector        (int tamano,float* Vector);
float* IntToFloVector        (int tamano,  int* Vector);
float* SumaVectores          (float* vector_1 ,float* vector_2 ,int tamano);

        ///// FILTROS
float* MediaMovilOrdenN      (int rango, int *Muestras ,int tamano, int N);
float* MediaMovilOrdenNLarge (int rango, int *Muestras ,int tamano, int N);


        ///// ESTADISTICA
int*  GeneradorHistograma   (int rango, int *Muestras   ,int tamano);
float Media                 (int rango, int *Muestras   ,int tamano);
float Esperanza             (int rango, int *Histograma ,int CantMuestras);
float Varianza              (int rango, int *Histograma ,int CantMuestras, float media );

/////////////////////////////////////////////////////////////////////////////////////
int  main (void)
{
    int*  Vector_1 = NULL;
    int*  Vector_2 = NULL;
    float*  Vector_3  = NULL;
    int*  Histograma_1= NULL;
    float Esperanza_1 = 0;
    float Media_1     = 0;
    float Varianza_1  = 0;

    int CantMuestras =  0, Rango = 0 ,N = 3;
    printf("Ingrese cantidad de muestras:\n");
    scanf ("%d",&CantMuestras);

    printf("Ingrese cantidad de el rango:\n");
    scanf ("%d",&Rango);

    if(CantMuestras==0 || Rango==0)
        printf("Error. El Rango o La cantidad de muestras es nulo");

    Vector_1     = GeneradorVectorRand       (CantMuestras,   Rango);
    Vector_2     = GeneradorVectorLineal     (CantMuestras,   Rango);

    Vector_3     = SumaVectores              (IntToFloVector(CantMuestras, Vector_1)    ,IntToFloVector(CantMuestras, Vector_2 ),CantMuestras);
    Histograma_1 = GeneradorHistograma       (Rango, Vector_1, CantMuestras);

    printf("Ingrese cantidad de MediaMovil:\n");
    scanf ("%d",&N);
    Vector_3        = MediaMovilOrdenN  (Rango, Vector_2      ,CantMuestras, N);

    Esperanza_1     = Esperanza         (Rango, Histograma_1  ,CantMuestras);
    Media_1         = Media             (Rango, Vector_1      ,CantMuestras);
    Varianza_1      = Varianza          (Rango, Histograma_1  ,CantMuestras, Media_1);

    free(Vector_1);
    free(Vector_2);
    free(Histograma_1);
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////   FUNCIONES    /////////////////////////////////////////////////////////
int*    GeneradorVectorRand (int tamano,int rango)
{
    int *vector = malloc(tamano * sizeof(int));
    int i;

    srand((unsigned)time(NULL));             // genero semilla aleatoria
    printf("Vector Random generado:");
    for(i=0;i<tamano;i++)                              // Recorro el vector
    {
        vector[i] = (rand() % rango);              // genero    valores random limitados de 0 al rango
        printf(",%d",vector[i]);                          // imprimo valores random
    }
        printf("\n");
    return vector;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
int*    GeneradorVectorLineal (int tamano,int rango)
{
    int *vector = malloc(tamano * sizeof(int));
    int i;

    srand((unsigned)time(NULL));                    //genero semilla aleatoria
    printf("Vector Lineal generado:");
    for(i=0;i<tamano;i++)
    {
        vector[i] = (i % rango);
        printf(",%d",vector[i]);
    }
        printf("\n");
    return vector;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void    ImprimirVector (int* Vector,int tamano)
{
    printf("Vector :");
    for(int i=0; i<tamano ;i++)
    {
        printf(",%d",Vector[i]);
    }
        printf("\n");
    return;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
int*    FloToIntVector       (int tamano,float* Vector)
{
    int *Vector_2 = malloc(tamano * sizeof(int));
    printf("\n\nConversion INT Result:");
    for(int i=0; i<tamano ;i++)
    {
        Vector_2[i] = Vector[i];
        printf("  %d",Vector_2[i]);
    }
    printf("\n");
    return  Vector_2;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
float*  IntToFloVector       (int tamano,int* Vector)
{
    float *Vector_2 = malloc(tamano * sizeof(int));
    printf("\n\nConversion FLOAT Result:");
    for(int i=0; i<tamano ;i++)
    {
        Vector_2[i] = Vector[i];
        printf(" ,%.1f",Vector_2[i]);
    }
    return  Vector_2;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
float*  SumaVectores ( float* vector_1 ,float* vector_2 ,int tamano)
{
    int i;
    float * vector_3 =  (float*) malloc(tamano*sizeof(float));
    printf("\nLa suma del los vectores resulta: ",vector_3[i]);
    for(i=0;i<tamano;i++)
    {
        vector_3[i]  =  vector_1[i]  +  vector_2[i];
        printf(", %.2f",vector_3[i]);
    }
    printf("\n");
    return vector_3;
}



/////////////////////////////////   FILTROS      ////////////////////////////////////////////////
float*  MediaMovilOrdenN (int rango, int *Muestras ,int tamano, int N)
{
    if (N<1){printf("Warning small N ");}
    //else{
    float *SuaveN = malloc((tamano-N+1) * sizeof(int));
    int i,j,ij;
    printf("Suavisado:");
    for(i=0;i<tamano-N+1;i++)
    {
        SuaveN[i]=0;
        for(j=0;j<N;j++)
        {
            ij =i+j;
            SuaveN[i] = SuaveN[i] + Muestras[(ij)];
        }
        if (N>1)
            {SuaveN[i] = SuaveN[i] /N;}
        printf(";%.2f",SuaveN[i]);
    }
    printf("\n");
}
/////////////////////////////////////////////////////////////////////////////////////////////////
float*  MediaMovilOrdenNLarge (int rango, int *Muestras ,int tamano, int N)
{
    if (N<1){printf("Warning small N ");}
    //else{
    float *SuaveN = malloc(tamano * sizeof(int));
    int i,j,ij;
    printf("Suavisado:");
    for(i=0;i<tamano;i++)
    {
        SuaveN[i]=0;
        if((i+N) < tamano)
        {
            for(j=0;j<N;j++)
            {
                ij =i+j;
                SuaveN[i] = SuaveN[i] + Muestras[(ij)];
            }
            if (N>1){SuaveN[i] = SuaveN[i] /N;}
        }
        if((i+N) >= tamano)
        {
            for(j=0;(j+i) < tamano;j++)
            {
               ij = i+j;
               SuaveN[i] = SuaveN[i] + Muestras[(ij)];
            }
            SuaveN[i] = SuaveN[i] /j;
        }
        printf(";%.3f",SuaveN[i]);
    }//}
    printf("\n");
}
//  CONVOLUCION


////////////////////////////////   ESTADISTICA   ///////////////////////////////////////////////////////////
int*    GeneradorHistograma(int rango, int *Muestras,int tamano)
{
    int *Histograma = malloc(rango * sizeof(int));
    //int tamano = sizeof(*Muestras)/* / sizeof(int)*/;
    int i;

     for(i=0;i<rango;i++)
    {
        Histograma[i]=0;
    }

    for(i=0;i<tamano;i++)
    {
        Histograma[Muestras[i]] = (Histograma[Muestras[i]]) + 1;

    }

    printf("Histograma generado:\n");
    for(i=0;i<rango;i++)
    {
        printf("Cantidad de %ds: %d\n",i, Histograma[i]);

    }
     printf("\n");

     return Histograma;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
float   Esperanza(int rango, int *Histograma,int CantMuestras)
{
    float esperanza=0;
    int i;


    for(i=0;i<rango;i++)
    {
        esperanza += (i * Histograma[i]);

    }
    esperanza = esperanza / CantMuestras;
    printf("La Esperanza es:%f\n", esperanza);

     return esperanza;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
float   Media    (int rango, int *Muestras ,int tamano)
{
    int i;
    float Media = 0;

    for(i=0;i<tamano;i++)
    {
        Media += Muestras[i];
    }

    Media = Media/tamano;

    printf("Media: %f\n",Media);

    return Media;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
float   Varianza (int rango, int *Histograma, int CantMuestras, float media )
//Varianza = E( X^2)- E(X)^2 )
{
    float mediaCuadrada = media*media;
    float Varianza=0;
    int i;


    for(i=0;i<rango;i++)
    {
        Varianza += (i * Histograma[i]*Histograma[i]);//  Esperanza del  cuadrado

    }
    Varianza = Varianza / CantMuestras;
    Varianza = Varianza - mediaCuadrada;
    printf("La Varianza es:%f\n", Varianza);

     return Varianza;

}

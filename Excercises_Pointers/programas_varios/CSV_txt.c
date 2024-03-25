#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
/*
    strlen() es para saber la longitud de una cadena de caracteres. Ej: longitud=strlen(cadena);
    strcpy() es para copiar una cadena.Ej: strcpy (copiacadena,cadenaoriginal)
    strcmp() es para comparar cadenas, resultado=0 si son iguales, resultado=numero son diferentes . Ej strcmp(cadenauno,cadena2)
    strcat() es para concatenar(unir) cadenas.Ej:texto="hola"=>strcat (texto,"pepe")=>texto="holapepe"
    strrev() es para invertir cadenas
*/

void separa_csv (const char*, char***, int*);
int main ()
    {
    int filas = 10, columnas = 40, i = 0;
    const char *frase;
    char *campos[40];
    char ***P;
    P = &campos;
    int numCampos = 0;
    frase = (char *)malloc(40*sizeof(char));
    printf ("Ingrese una cadena de caracteres con palabras o frases separadas por coma\n");
    gets (frase);
    separa_csv(frase,P,&numCampos);
    system ("pause");
    return 0;
    }

void separa_csv (const char *s, char ***campos, int *numCampos)
    {
    int i = 0, a = 0, b = 0, aux = 0;char saux[40];
    *numCampos = 1;
    /*Limpieza de campos*/
    for (a==0;a<10;a++)
            campos[a] = "";
    a = 0;
    /* Asignación de frases para cada campo */
    for (i==0;s[i]!='\0';i++)
      {
      if (s[i]==',')
	{
	saux[b]='\0';
	aux = aux + 1;
	*numCampos = *numCampos + 1;
	printf ("Campo n%d: ",aux);
	campos[a] = saux;
	printf ("%s\n",campos[a]);
	a++;
        b = 0;
	}
      else
	{
	saux[b] = s[i];
	b++;
	}
      }
    saux[b]='\0';
    printf ("Campo n%d: ",aux+1);
    campos[a] = saux;
    printf ("%s\n",campos[a]);
    printf ("\nCantidad de campos leidos: %d\n",*numCampos);
    }   
    

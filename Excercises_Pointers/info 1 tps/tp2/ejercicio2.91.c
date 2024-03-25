/*jercicio 2.9.
Escribir un programa que tome números decimales y los muestre en pantalla en
binario, octal y hexadecimal. El programa termina cuando se ingresa el número 0.*/

#include <stdio.h>
#include <stdlib.h>

int binario (int,int**);
int octal   (int,int**);
int hexadecimal (int,char**);

void main()
{
   printf("\n\n Programa de convercion a binario octal y hexadecimal \n Puede introducir numeros enteros no superiores a 8 digitod \n Al introducir un 0 termina el programa ");
  int x=1;
  int* digitos;int* digitos2;char* digitos3;
 while (x!=0) 
 {
   printf(" \n escriba un numero entero:\n");
   scanf("%d",&x);
   printf("\n Ha ingresado el numreo: %d\n\n",x);
 
   binario 	(x,&digitos);  	//Empieza a calcular mediante la funcion binario
   octal   	(x,&digitos2);	//Empieza a calcular mediante la funcion octal
   hexadecimal 	(x,&digitos3);	//Empieza a calcular mediante la funcion hexadecimal
   printf("binario ");
 } 
}


int binario (int x, int** bin)
{
 int cont=0,save;long dig;
 printf(" Calculando digitos..");
									      //empieza a calcular el BINARIO
  for(dig=1; x>=dig ;cont++)						//calcula la cantidad de digitos que tendra el binario comparando
  {									//el numero con sucesivos exponenciales de 2
    printf(" %ld _",dig);
    dig = 2*dig ;
  }
  if (x==1)								//imprime la cantidad de digitos que tendra el bnario
  {
    printf("\n el numero es de %d digito\n\n",cont);
  }
  else printf("\n\n el binario de %d sera de %d digitos\n\n",x,cont);
  
  save = cont;								//guarda el contador en save
  (*bin) = (int*) malloc(sizeof(int)*(cont--));
   
  while(x > 0)   							//guarda los balores del binario en forma decendente decresiendo 
  {									//el contador
    *bin[cont] = x%2;
    printf(" Resto de dividirlo por dos = %d\n",*bin[cont]);
    x = x/2;
    printf(" resultado: %d\n",x);
    cont--;
  }

  printf("\n");
  printf(" en binario se expresa ");
  for(cont=0;cont<save;cont++)						//impeime las variables guardadas mientras las aumenta y compara con el 
  {									//valor guardado en save
    printf("%d",*bin[cont]);
    
  }
  printf("\n\n%d",x);
}


int octal (int x, int** bin)
{
 int cont=0,save;long dig;
  printf(" Calculando digitos..");
										      //Empieza a calcular el OCTAL
  for(dig=1; x>=dig ;cont++)						//calcula la cantidad de digitos que tendra el octal comparando
  {									//el numero con sucesivos exponenciales de 2
    printf(" %ld _",dig);
    dig = 8*dig ;
  }
  if (x==1)								//imprime la cantidad de digitos que tendra el bnario
  {
    printf("\n el numero es de %d digito\n\n",cont);
  }
  else printf("\n\n el octal de %d sera de %d digitos\n\n",x,cont);
  
  save = cont;								//guarda el contador en save
  (*bin) = (int*) malloc(sizeof(int)*(cont--));
   
  while(x > 0)   							//guarda los balores del octal en forma decendente decresiendo 
  {									//el contador
    *bin[cont] = x%8;
    printf(" Resto de dividirlo por ocho = %d\n",*bin[cont]);
    x = x/8;
    printf(" resultado: %d\n",x);
    cont--;
  }

  printf("\n");
  printf(" en octal se expresa "); 
  
   for(cont=0;cont<save;cont++)						//impeime las variables guardadas mientras las aumenta y compara con el 
  {									//valor guardado en save
    printf("%d",*bin[cont]);
    
  }
  printf("\n\n%d",x);
}


int hexadecimal (int x,char**bin)
{
 int cont=0,save,save1=0;long dig;
  printf(" Calculando digitos..");
										      //Empieza a calcular el HEXADECIMAL
  for(dig=1; x>=dig ;cont++)						//calcula la cantidad de digitos que tendra el hexadecimal comparando
  {									//el numero con sucesivos exponenciales de 2
    printf(" %ld _",dig);
    dig = 16*dig ;
  }
  if (x==1)								//imprime la cantidad de digitos que tendra el hexadecimal
  {
    printf("\n el numero es de %d digito\n\n",cont);
  }
  else printf("\n\n el hexadecimal de %d sera de %d digitos\n\n",x,cont);
  
  save = cont;								//guarda el contador en save
  *bin = (char*) malloc (sizeof(char) *(cont--) );
   
  while(x > 0)   							//guarda los balores del hexadecimal en forma decendente decresiendo 
  {									//el contador
    save1 = x%16;							//uso save 1 para evaluar el residuo de la divicion
    switch (save1) 							// cambia numeros mayores a 9 por letras
    {
      case 10:*bin[cont]='a';break;
      case 11:*bin[cont]='b';break;
      case 12:*bin[cont]='c';break;
      case 13:*bin[cont]='d';break;
      case 14:*bin[cont]='e';break;
      case 15:*bin[cont]='f';break;
    }
    printf(" Resto de dividirlo por dieciseis = %c\n",*bin[cont]);
    x = x/16;
    printf(" resultado: %d\n",x);
    cont--;
  }

  printf("\n");
  printf(" en hexadecimal se expresa ");
  for(cont=0;cont<save;cont++)						//impeime las variables guardadas mientras las aumenta y compara con el 
  {									//valor guardado en save
    printf("%c",*bin[cont]);
    
  }
  printf("\n\n");
}

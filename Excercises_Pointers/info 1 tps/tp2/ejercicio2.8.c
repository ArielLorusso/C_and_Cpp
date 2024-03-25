/*Ejercicio 2.8.
Escribir un programa que invierta los dígitos de un número positivo entero.
(Sugerencia: usar operadores modulo, %, y división, /, para ir obteniendo los
dígitos uno a uno). El valor se ingresa por teclado.*/

#include <stdio.h>

void main ()
{
  int x,save,save1,save2,save3,dig=1;				
  //save guarda x save1 guarda 10^dig save2 guarda dig save3 guarda dig antes de que se use para guardar digitos
  
  printf("\n\n Programa que invierte un numero \n Ingrese un numero positivo y entero no mayor a 9 cifras: ");
  scanf("%d",&x);
  printf("\n Ingreso el numero: %d\n",x);
  
  if (x>=1) //guarda todos los digitos del numero
  {
    save = x;  							//save guarda el valor del numero
    
    while(x>=10)						//al cuontar los digitos se modifica x
    {
      x = x/10;
      dig++;
    }   
    printf (" El numero era de %d cifras\n",dig);
    save3=dig;
    int Save[dig-1];  						//creamos un save por cada digito
    
      while(dig>=1)
     {
       save1=1;
       x=save;							//devolvemos el valor a x    
       save2=dig;							//guardamos dig     
       while(dig>1) 						//usamos dig para calcular 10^dig
	 {
	   save1 = 10*save1;					//save1 = 10^dig = 
	   dig--;						//dig se modifica al ser usado  de contador
	 }   
       dig=save2;							//devolvemos el valor de dig
      
       x = x/save1;						//x = x / 10^dig = primer digito de x (por ser variable int)
       printf ("\n El primer digito numero del numero es %d\n",x);
       Save[dig-1]=x;						//guardo en el untimo save el primer digito
       x = save-(save1*x);					//guardo en x = save(numero) - (10^dig * x=ultimo digito)  
       printf (" al sacarselo el numero es %d",x);
       dig--;
       save=x;
     } 
    printf("\n");
    
    for(dig=1;dig<=save3;dig++)
    {
      printf("%d",Save[dig-1]);
    }
     printf("\n\n");
  }
  else
  { 
    printf(" El numero que ingreso es negativo\n\n");
  }
}

//bug muestra un sero y si intento evitalo haciendo un ciclo menos aparecen nimeros negativos y cosas raras
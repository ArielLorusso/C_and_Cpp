int main ()
{
  int fun;char* m,n;int i;
  printf("\n\n	Ingrese el numero de funcion a utilizar");
  scanf("%d",&fun);
  printf("\n	Iniciando funcion del ejercicio4.%d.c",fun);
  switch (fun)
  {
    case 1:
    {
      scanf("%ms\n",&m);
      m=string_reverse (m);
      printf("%s",m);
    }
    break;
    case 2:
    {
      scanf("%ms\n",&m);
      m=string_reverse (m);
      printf("%s",m);
    }
    break; 
    case 3:
    {
      scanf("%ms\n",&m);
      scanf("%ms\n",&n);
      i = my_strcmp(m,n);
      printf("%d",i);      
    }
    break; 
    case 4:
    {
      char* entrada;char condicion;cases pepe;
    
      printf("\n deve ingresar una cadena de caracteres seguido de : U o L \n (L pasa a minusculas U a mayusculas)");
      scanf("%ms\n",&entrada);//ms reserva de forma dinamica
      scanf("%c",&condicion);
  
      if (condicion=='U')
      {
	pepe = UPPERCASE;
      }
      if (condicion=='L')
      {
	pepe = LOWERCASE;
      }
      change_case(entrada,pepe);
      printf("%s",entrada);
      free(entrada);
    }
    break; 
    case 5:
    {
      printf("\n\n	Ingrese la primer palabra");scanf("%ms\n",&m);
      printf("\n	Ingrese la segunda");scanf("%ms\n",&n);
      my_strcpy(m,n)
      printf("\n\nprimera %s",m);
      printf("	segunda %s\n\n",n);
    } 
    break;
    case 6:
    {
      separa_csv
    } (const char *s, char **campos, int* numCampos)
    break;
  }
}
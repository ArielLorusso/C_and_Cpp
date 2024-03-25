#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct str
{
char * str;
struct str * prox;
struct str * ant;
} nodo;

void menu (nodo *head, int max_char)
{
  int num;
  printf("  Numero de caractrres maximos %d\n ", max_char);
  puts("");
  puts("	1. Ingresar datos");
  puts("	2. Ordenar datos");
  puts("	3. Presentar datos");
  puts("	4. Salir\n");
  
  scanf("%d",&num);
  switch (num)
  {
    case 1: {ingresarDatos(head, max_char);}
      break;
    case 2: {ordenarDatos();}
      break;
    case 3: {presentarDatos();}
      break;
    case 4: { salir(1);}
      break;
  }
}


void limpiarstdin ()
{
  int c;
  while ((c=getchar())!= "\n" && c!=EOF); //lee el residuo eof = end of file
}



void ingresarDatos(nodo *head,int max_char)
{
  puts("\n  Ingresardatos:");
  char *text = "algo";
  char *local= NUll;
  local = (char*)malloc (sizeof(char)*max_char);

  while(strcmp(text,""))
  {
    puts("\n while");
    limpiarstdin();
    scanf("%s",local);
    limpiarstdin();
    //insertarnodo(head,local);
    text = local;
  }
}

void insertarnodo(nodo *head,char *text)
{
  nodo *nuevo = (nodo*)malloc(sizeof(nodo));
  nuevo->str  = text;
  nuevo->prox = head;
  
  if(head != NULL)
    {
      (head)->ant = nuevo;
    }
  (head) = nuevo;
}

void ordenarDatos()
{
  puts("\n  Elija la opcion correspondiente:\n	1 ordenar de A hasta Z\n	2 ordenar de Z hasta A ");
}

void presentarDatos()
{
  
}

void salir()
{
  exit(0);
}

void main (int argc,int argv[])
{
  int max_char;
  
  nodo *head;
  head = NULL;
  if (argc!=2)
    {
      puts("	Debe ingresar un argumnto luego del programa indicando la cantidad de caracteres a guardar"); 
      exit (1);
    }
  max_char = atoi(argv[1]);
    puts("termina main");
    menu(head,max_char);
}

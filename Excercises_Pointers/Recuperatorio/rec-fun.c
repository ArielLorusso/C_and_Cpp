/*
  typedef struct pedidos
{
   char*    nombre;        char*   colegio;    char*  prenda;
   short int talle;        float    precio;
   struct pedidos* next;   struct pedidos* prev;
}venta; */
#include "recuperatorio.h"

void menu()
{
  int opcion;
  venta* list_head = NULL;
  
  while (opcion)
  {
    puts("\t Opciones: \n\n\t 0 = salir\n\t 1 = ingresar\n\t 2 = listar\n\t 3 = contar\n\t 4 = borrar\n\t 5 = ordenar\n\t 6 = vaciar");
    scanf("%d",&opcion);
  
    switch (opcion)		//se llama a la funcion correspondiente a la opcion
    {
 //     case 0: vaciar(&list_head);	//vacia la lista y luego sale del menu
      case 1: ingresar(&list_head);break;
      case 2: listar(list_head);break;
      case 3: contar(list_head);break;
      case 4: borrar(&list_head);break;
      case 5: ordenar(&list_head);break;       //precio nombre colegio
      case 6: vaciar(&list_head); 
    }
  } 
}

void ingresar (venta** list_head)
{
  venta* nueva_venta =(venta*)malloc(sizeof(venta));
  
  {  									//lleno los campos
  nueva_venta->next=NULL;
  nueva_venta->prev=NULL;
  puts("\t ingresar nombre");	//scanf("%s"  ,nueva_venta->nombre);
  limpiar();fgets(nueva_venta->nombre,40, stdin);nueva_venta->nombre[(strlen(nueva_venta->nombre))-1]='\0';
  
  puts("\t ingresar colegio");	//scanf("%s"  ,nueva_venta->colegio);	
  fgets(nueva_venta->colegio,40, stdin);nueva_venta->colegio[(strlen(nueva_venta->colegio))-1]='\0';
  
  puts("\t ingresar prenda");	//scanf("%s"  ,nueva_venta->prenda); 	
  fgets(nueva_venta->prenda,40, stdin);nueva_venta->prenda[(strlen(nueva_venta->prenda))-1]='\0';
  
  puts("\t ingresar talle");	scanf("%hd",&nueva_venta->talle);		
  puts("\t ingresar precio"); 	scanf("%f" ,&nueva_venta->precio);		
  
  printf("\n\t nombre:  %s ",nueva_venta->nombre);
  printf("\n\t colegio: %s ",nueva_venta->colegio);
  printf("\n\t prenda:  %s ",nueva_venta->prenda);
  printf("\n\t talle:   %hd",nueva_venta->talle);
  printf("\n\t precio:  %f ",nueva_venta->precio);
  }
  
  if ( (*list_head) == NULL )
  {
   (*list_head) = nueva_venta;
  }
  
  else
  {
    venta* aux = *list_head;
    
    while ( (aux->next) != NULL )//advertencia un ; joderia todo ell programa
    {
      aux = aux->next;
    }  
     aux->next = nueva_venta;
     nueva_venta->prev = aux;
  }
}

void listar (venta* list_head)
{
  venta* aux = list_head;
  
  if (list_head == NULL)
  {
     puts("\n\tLista vacia\n");
  }
  else do
  {  
    printf("\n\t nombre  %s ",aux->nombre);
    printf("\n\t colegio %s ",aux->colegio);
    printf("\n\t prenda  %s ",aux->prenda);
    printf("\n\t talle   %hd",aux->talle);
    printf("\n\t precio  %.2f \n\n",aux->precio);
    aux = aux->next;
  }while ( (aux) != NULL );
}

void borrar (venta** list_head)
{
  venta* aux = (*list_head);  char string [40];
 
  puts("\n\t Deve ingresar el nombre del cliente cuya venta borrar");
  limpiar();fgets(string,40, stdin);string[(strlen(string))-1]='\0';
  
  if (!strcmp((*list_head)->nombre,string))		//primero
  {
    (*list_head)=(*list_head)->next;
    (*list_head)->prev = NULL;
    free(aux);
  }
  
  else while (aux->next!=NULL)           		//central
  {
    aux=aux->next;
    if (!strcmp(aux->nombre,string) && aux->next != NULL )
    {
      aux->prev->next = aux->next;
      aux->next->prev = aux->prev;
      free(aux);
    }
  }
    if (!strcmp(aux->nombre,string) && aux->next == NULL )  	//ultimo
    {
      aux->prev->next = NULL;
      ; free(aux);
    }
}

void contar (venta* list_head)
{
  int a=1;
  if (list_head == NULL)
  {
    a=0;
  }
  while(list_head->next != NULL)
  {
    list_head = list_head->next;
    a++;
  }
  printf("\n\t son: %d nodos\n",a);
}

void ordenar(venta** list_head)
{
  int a=1,b,c=0; venta* aux = (*list_head);
  
  if (aux == NULL) //contamos los nodos
  {
    a=0; puts("\n\t No hay elementos que ordenar");
  }
  while(aux->next != NULL) //contar nodos a ordenar
  {
    aux = aux->next;
    a++;
  }
  
  aux = (*list_head);
  for (a=a;a>0 ;a--)  //ordenar nombres
  {
    for(b=a;b>0;b--)
    {
      c++; //contador de ordenamientos = (a-1)^2
      if(strcmp(aux->nombre,aux->next->nombre) && (aux->next->next != NULL) && (aux->prev != NULL) ) //medios
      {
	puts("\t a ordenar...");
	aux->next = aux->next->next;			//1ok
	aux->next->prev->prev = aux->prev;		//2ok
	aux->prev = aux->next->prev;			//3ok
	aux->next->prev->next = aux;			//4ok
	aux->next->prev = aux;
	aux->prev->prev->next = aux->prev;
	puts("\t Listo");
      }
      aux = aux->next;
      puts("\t Proximo");	
    }  
  }
  printf("\n\t Se necesitaron %d ordenamientos\n",c);
}

void vaciar(venta**list_head)
{ 
  venta* aux = (*list_head);  
    
  while(aux->next!=NULL )	//central
  {
    (*list_head)=aux->next;
    free(aux);
    aux=(*list_head);    
  }
  free(aux); 
}

void limpiar ()
{
  int c;
  while ( (c=getchar()) != EOF && c != '\n' );
}
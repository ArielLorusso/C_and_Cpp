#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void anadir (void);
void borrar (void);
void consultar (void);
void finalizar (void);

typedef struct list
     {
	long DNI;
	int edad;
	char nombre [25];
	struct list *psig;
     }tlista;

int main ()
    {
    int eleccion = 0;
    int DNIbuscado;
    char nombrebuscado [25];
    int edadbuscada;
    int aux = 0;
    int aux2;
    tlista *lista = NULL;
    tlista *p;
    
    while (1 == 1) //siempre
      {
    printf ("Bienvenido al ejercicio 1 de prática\n\n");
    printf ("1.Añadir elemento\n2.Borrar elemento\n3.Consultar elemento\n4.Finalizar\n");
    
    scanf ("%d",&eleccion); fflush (stdin);
    switch (eleccion)
        {
        
      case 1:
             printf ("elegiste 1 gato\n");
             //anadir();
             p=(tlista*)malloc(sizeof (tlista));
             scanf ("%ld",&p->DNI); fflush(stdin);
             scanf ("%s", p->nombre); fflush(stdin);
             scanf ("%d", &p->edad); fflush(stdin);
             if (aux == 0)
                {
                p->psig = NULL;
                lista = p;
                //printf("DNI: %ld\nNombre: %s\nEdad: %d\n",p->DNI,p->nombre,p->edad);
                aux ++;               
                }
             else
                {
                p->psig = lista;
                lista = p;
                }
             //////////////
             break;
        case 2:
             //es lo mismo que buscar, pero solo que cuando encontras el nodo a eliminar pones "free (p)" siendo p lo que apunta al nodo
             break;
        case 3:										//buscar
             printf ("elegiste 3 gato\n");
             //consultar();
             printf ("¿Búsqueda por DNI (1), nombre (2) o edad (3)?\n");
             scanf ("%d",&eleccion); fflush (stdin);
             
	     switch (eleccion)
                    {
                    case 1: 								//Dni
                         scanf ("%ld",&DNIbuscado); fflush (stdin);
                         p = lista;
                         while (p->DNI != DNIbuscado && p->psig != NULL) 
                            {
                            p = p->psig;
                            }
                         if (p->psig != NULL || p->DNI == DNIbuscado) 
                            {
                            printf ("Nombre: %s\nEdad: %d\n",p->nombre,p->edad);
                            }
                         if (p->psig == NULL && p->DNI != DNIbuscado)
                            {
                            printf ("DNI no encontrado\n");
                            }       
                         break;
                    case 2:								//nombre
                         scanf ("%s",&nombrebuscado); fflush (stdin);
                         p = lista;
                         aux2 = strcmp (p->nombre,nombrebuscado);
                         while (aux2 != 0 && p->psig != NULL) 
                            {
                            p = p->psig;
                            aux2 = strcmp (p->nombre,nombrebuscado);
                            }
                         if (p->psig != NULL || aux2 == 0) 
                            {
                            printf ("Edad: %d\nDNI: %ld\n",p->edad,p->DNI);
                            }
                         if (p->psig == NULL && aux2 != 0)
                            {
                            printf ("Nombre no encontrado\n");
                            }
                         break;
                    case 3:								//edad
                         scanf ("%d",&edadbuscada); fflush (stdin);
                         p = lista;
                         while (p->edad != edadbuscada && p->psig != NULL) 
                            {
                            p = p->psig;
                            }
                         if (p != NULL || p->DNI == DNIbuscado) 
                            {
                            printf ("Nombre: %s\nDNI: %ld\n",p->nombre,p->DNI);
                            }
                         if (p->psig == NULL && p->edad != edadbuscada)
                            {
                            printf ("Edad no encontrada\n");
                            }       
                         break;
                    }
             break;
        case 4:										
             printf ("elegiste 4 gato\n");
             //finalizar();
             p = lista;
             while (p != NULL) 
                   {
                   printf ("%ld %s %d\n",p->DNI, p->nombre, p->edad);
                   p = p->psig;
                   }
             system ("pause");
             return 0;
             break;
	case 5:
	  p=lista;
	   printf ("listado\n");
	  do
	  {
	    printf ("Nombre: %s Edad: %d DNI: %ld\n",p->nombre,p->edad,p->DNI);
	    p=p->psig;
	  }while(p->psig != NULL);
        default:
             printf ("elegi algo gato\n");
        }
      }  
    
    system ("pause");
    return 0;     
    }

void anadir()
     {
     
     }
void borrar()
     {
             
     }
void consultar ()
     {
               
     }
void finalizar ()
     {
               
     }

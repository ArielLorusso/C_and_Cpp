#include "main.h"


  // FUNCIONES DE FMOD
void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

void pausar(FMOD_CHANNEL     **channel)
{
	int paused;
	FMOD_Channel_GetPaused(*channel, &paused);
	FMOD_Channel_SetPaused(*channel, !paused);
}

FMOD_RESULT F_CALLBACK myopen(const char *name, int unicode, unsigned int *filesize, void **handle, void **userdata)
{
	if (name)
	{
		FILE *fp;

		fp = fopen(name, "rb");
		if (!fp)
		{
			return FMOD_ERR_FILE_NOTFOUND;
		}

		fseek(fp, 0, SEEK_END);
		*filesize = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		*userdata = (void *)0x12345678;
		*handle = fp;
	}

	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK myclose(void *handle, void *userdata)
{
	if (!handle)
	{
		return FMOD_ERR_INVALID_PARAM;
	}

	fclose((FILE *)handle);

	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK myread(void *handle, void *buffer, unsigned int sizebytes, unsigned int *bytesread, void *userdata)
{
	if (!handle)
	{
		return FMOD_ERR_INVALID_PARAM;
	}

	if (bytesread)
	{
		*bytesread = (int)fread(buffer, 1, sizebytes, (FILE *)handle);
		
		if (*bytesread < sizebytes)
		{
			return FMOD_ERR_FILE_EOF;
		}
	}

	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK myseek(void *handle, unsigned int pos, void *userdata)
{
	if (!handle)
	{
		return FMOD_ERR_INVALID_PARAM;
	}

	fseek((FILE *)handle, pos, SEEK_SET);

	return FMOD_OK;
}

  // FUNCIONES DE LISTAS
  
void limpiar_stdin()
{
  	int c;
	while((c=getchar()) != '\n' && c != EOF);
}


void crear_nodo(Nodo** cabeza,Nodo** cola)
{
	Cancion* tema=( Cancion*)malloc(sizeof(Cancion));
	
	if(*cabeza==NULL)
	{ 
		*cola=(Nodo*)malloc(sizeof(Nodo));
		
		(*cola)->NEXT = NULL;
		(*cola)->PREV = NULL;
		(*cola)->cancion = ( Cancion*)(ingresar_cancion(tema));
		*cabeza = *cola;
	}
	else
	{
		Nodo *nuevo = malloc( sizeof( Nodo ) );
		nuevo-> cancion = (Cancion*)(ingresar_cancion(tema));
		nuevo->NEXT = NULL; 
		nuevo->PREV = *cola;
		(*cola)->NEXT = nuevo; 
		*cola=nuevo;
		
	}
}

  
Cancion* ingresar_cancion(Cancion* tema)
{
    int caracter, i;
    i = 0;
    
	puts(  "╔══════════════════════════════════════════════════════════════════════════");  limpiar_stdin();
    printf("║ \tIngrese  ");putchar('"');printf("nombre_de_la_cancion.mp3");putchar('"');printf(" : ");

   while((caracter=getchar())!= EOF && caracter !='\n')
	{
		(tema->nombre)[i]= caracter;
		i++;
	}
    tema->nombre[i] = '\0'; 
	i = 0;
    

    printf("║ \tIngrese el Autor del Cancion: ");

   while((caracter=getchar())!= EOF && caracter !='\n')
	{
		(tema->autor)[i]= caracter;
		i++;
	}
    tema->autor[i] = '\0';
    i = 0;
   
  	printf("║ \tOBLIGATORIO\n║ \tIngrese la direccion y el nombre del archivo desde el directorio actual  \n║ \t");
   
	while((caracter=getchar())!= EOF && caracter !='\n')
	{
		(tema->direccion)[i]= caracter;
		i++;
	}
    tema->direccion[i] = '\0';
    i = 0;
    //scanf("%d",&i);

    puts("╚══════════════════════════════════════════════════════════════════════════");
    return tema;
}
 

void Imprimir_lista(Nodo* cabeza)
{
	if(cabeza!=NULL)
	{
		int registro=1;
		Nodo* aux = cabeza;
		puts("");
		
		do 
		{
			puts ( "╠════════════════════════════════════════════════════════════════");
			printf("║ Cancion N° %d\n",registro);
			printf("║ Nombre:     %s\n",aux->cancion->nombre);
			printf("║ Autor:      %s\n",aux->cancion->autor);
			printf("║ directorio: %s\n",aux->cancion->direccion);
			aux=aux->NEXT;
			registro++;
		} while(aux!=NULL);
		
		registro=0;
		free(aux);	
	}	
	else{
		puts("\n\t ╔══════════════════════════╗");
		puts(  "\t ║ No hay ningúna cancion   ║"); 
		puts(  "\t ╚══════════════════════════╝");
	}
}
   
   
int contador_nodos(Nodo* cabeza)
{
	
	int registros=0;
	Nodo* aux = cabeza;

	while(aux!=NULL)
	{
		aux=aux->NEXT;
		registros ++;
	}

	free(aux);
	return registros;
}
   
   
void borrar_todo(Nodo* cola, Nodo** cabeza)
{
	if( cola == NULL || *cabeza == NULL)
	{
		puts("\n\t╔════════════════════════════╗");
		puts(  "\t║ No hay ningún registro   : ║"); 
		puts(  "\t╚════════════════════════════╝");
	}
	
	else
	{
		Nodo *t;
		while(cola) 
		{
			t = cola;
			cola = cola->PREV;
			free(t->cancion);
			free(t);  
		}

		*cabeza=NULL;
		puts("\n\t╔═══════════════╗");
		puts(  "\t║ LISTA BORRADA ║");
		puts(  "\t╚═══════════════╝");
	}  
}	
	
    
void Borrar_cancion(Nodo** cabeza, Nodo** cola)
{
	if((*cabeza)!=NULL)
	{ 
		int i=1, borrar;
		Nodo* aux;
		aux = *cabeza;

		Imprimir_lista(*cabeza);

		puts("\n\t╔════════════════════════════════════════╗");
		puts(  "\t║ Ingrese el numero de cancion a borrar  ║"); 
		puts("  \t╚════════════════════════════════════════╝");
		printf("\t-> ");
		
		scanf("%d",&borrar);

		while(i<borrar)
		{
			if (aux->NEXT != NULL)
			{
				//printf("hola");
				aux=aux->NEXT;
				i++;
			}
			else{puts("\tElemento Inexistente\n\n");return;}
		}

		if((aux-> NEXT) != NULL && (aux->PREV) != NULL)	//Borrar por el medio
		{ 
			(aux->PREV)->NEXT = aux->NEXT;
			(aux->NEXT)->PREV = aux->PREV;  
		}

		else if(aux->PREV == NULL && aux->NEXT != NULL)		//Borrar cabeza
		{
			*cabeza = (*cabeza)->NEXT;
			(*cabeza)->PREV=NULL;  
		}
		else if(aux->PREV != NULL && aux->NEXT == NULL)		//Borar cola
		{
			*cola = (*cola)->PREV;
			(*cola)->NEXT = NULL;
		}
			
		else{borrar_todo(*cola, cabeza);return;}
		free(aux->cancion);
		free(aux);
	}
				
	else{
		puts("\n\t╔════════════════════════════╗");
		puts(  "\t║ No hay ningún registro !   ║"); 
		puts(  "\t╚════════════════════════════╝");
	}	
}

void ordenar_name(Nodo** cabeza)
{

	if( *cabeza !=NULL)
	{  
		Nodo* aux = *cabeza;
		Cancion* tema;
		int i,sort, nodos;
		
    
		for(nodos=(contador_nodos(*cabeza));nodos>0;nodos--)
		{
			for(i=0;i<(contador_nodos(*cabeza));i++)
			{ 
			
				if ((aux->NEXT)!=NULL)
				{
					sort=strcmp(aux->cancion->nombre , (aux->NEXT)->cancion->nombre);
					
					if (sort > 0)		// S1 > S2
					{
						tema = aux->cancion;
						aux->cancion = (aux->NEXT)->cancion;
						(aux->NEXT)->cancion = tema;
						aux=aux->NEXT;
					}
					else{
						aux = aux->NEXT;}
				} 
			}
			aux = *cabeza;
		}
	}
   	else{
		puts("\n\t╔════════════════════════════╗");
		puts(  "\t║ No hay ningún registro D': ║"); 
		puts(  "\t╚════════════════════════════╝");
	}  
    
}
  
  
void ordenar_autor(Nodo** cabeza)
{
	if( *cabeza !=NULL)
	{  
		Nodo* aux = *cabeza;
		Cancion* tema;
		int i,sort, nodos;

		for(nodos=(contador_nodos(*cabeza));nodos>0;nodos--)
		{
			for(i=0;i<(contador_nodos(*cabeza));i++)
			{ 
				if ((aux->NEXT)!=NULL)
				{
					sort=strcmp(aux->cancion->autor , (aux->NEXT)->cancion->autor);
						
					if (sort>0)		//S1 > S2
					{
						tema = aux->cancion;
						aux->cancion = (aux->NEXT)->cancion;
						(aux->NEXT)->cancion = tema;
						aux=aux->NEXT;
					}
					else { 
						aux=aux->NEXT; }
				} 
			}
		aux = *cabeza;
		}
	}
 	else{
		puts("\t╔════════════════════════════╗");
		puts("\t║ No hay ningún registro D': ║"); 
		puts("\t╚════════════════════════════╝");
	}   
}
  
  
char* dir_cancion (Nodo* cabeza, int rep)
{
    if( cabeza != NULL )
	{ 
		int i=1;
		Nodo* aux;
		aux = cabeza;

		while(i < rep)
		{
			if (aux->NEXT != NULL)
			{
				aux=aux->NEXT;
				i++;
			}
		}
		return (aux->cancion->direccion);
	}
      
    else{
		puts("\t╔════════════════════════════╗");
		puts("\t║ No hay ningúna cancion !   ║"); 
		puts("\t╚════════════════════════════╝");
	}
    return NULL;
}
  
void menu ( Nodo **cabeza, Nodo **cola)
{
    char opcion[1];
    
	do
	{
		//fflush(stdout);
		puts("\n\t╔═══════════════════════════════╗");
		printf("\t║ 0. Reproductor                ║\n");
		printf("\t║ 1. Ingresar cancion           ║\n");
		printf("\t║ 2. Borrar cancion             ║\n");
		printf("\t║ 3. Presentar registros        ║\n");
		printf("\t║ 4. Ordenar por autor          ║\n");
		printf("\t║ 5. Ordenar por nombre         ║\n");
		printf("\t║ 6. Cantidad de canciones      ║\n");
		printf("\t║ 7. Borrar todo                ║\n");
		printf("\t║ 8. Cerrar reproductor         ║\n");
			puts("\t╚═══════════════════════════════╝");
		printf("\t-> ");
		
		//fflush(stdin);
		scanf("%s",opcion);
      
		switch (opcion[0])
		{
			case '1': crear_nodo (cabeza,cola);break;
			
			case '2': Borrar_cancion (cabeza,cola); break;
			
			case '3': Imprimir_lista (*cabeza); break;
			
			case '4': ordenar_autor  (cabeza); break;
			
			case '5': ordenar_name   (cabeza); break;
			
			case '6': puts("\n\t╔════════════════════════════════════════════════════════════════════════");
					printf("\t║\tUsted guardo %d registros de canciones\n",(contador_nodos(*cabeza))); break;
			
			case '7': borrar_todo(*cola,cabeza); break;
			
			case '8': borrar_todo(*cola,cabeza); exit(0);
			
			default: puts("\n\t║  Ingrese una opción valida\n"); break;
		}
	}while(opcion[0] != '0');
    
}
 
 /**
 servidor-reproductor  controlado desde Arduino
 
 acciones: editar lista de canciones , subir y bajr volumen , siguiente , anterior , pausa
 
 protocolo: LAN TCP IPv4
 
 formatos: .mp3 .ogg .midi */ 
//===============================================================================================
/**
 \file  main.c
 \brief Main del proyecto de informatica 1 2013 UTN.
 
 Para compilar: make server
 
 '
 
 Funcionamiento:
 
    El programa pregunta al usuario si se desea conectar con el Arduino.
    de ser asi llama a las funciones Open_conection () y Aceptar_pedidos ().

    Luego utiliza una lista doblemente enlazada con informacion de las canciones
    conteniendo los nombres.
 
    Luego usa los nombres en la lista para pasarselos a FMOD_System_CreateStream ()
    para que cargue el sonido y luego se reprodusa en un canal stereo.
    
    Por ultimo si hay conexion con el arduino revisa el socket para cambiar de cancion. 
    De no ser asi solo se fija en la entrada del usuario.
    
 \par Ejemplo de llamada
 \code
   ./server
 \endcode
 \todo Verificar su funcionamiento en detalle.
 \bug
 \warning
 \author Paolo Fusaro y Ariel Lorusso (pcefusaro@gmail.com)
(ariellorusso@gmail.com)
 \date 28/2/2014
 \version 1.1.4
*/
#include "main.h"

/*
    TIPS:

    1. usar F_CALLBACK. NO castear forzosamente tu propia funcion a las llamadas de tipo fmod.
    2. retornar FMOD_ERR_FILE_NOTFOUND al abrir como es requerido (en caso de error).
    3. usar el retorno de numero de bytes leidos en read.
*/



int main(int argc, char *argv[])
{
///  variables:
  
    ///'       servidor
    char remoto [3];remoto [0]='\0';
    char message[] = "listo para recivbir .....";
    int sockfd, numbyte = 0 , sockdup;// /* File Descriptor del socket por el que el servidor "escuchará" conexiones*/
    struct sockaddr_in my_addr;	/* contendrá la dirección IP y el número de puerto local */
    char buf[MAXDATASIZE];
    
    ///'       fmod
    FMOD_SYSTEM      *system;		
    FMOD_SOUND       *sound; 		//*sound2 para multiples pistas simultaneas
    FMOD_CHANNEL     *channel = 0;	
    FMOD_RESULT       result;		
    int               key;		
    unsigned int      version;		
    
    int indice_temas = 1;
    float   volume = 1;
    ///'   lista
    Nodo* cabeza = NULL;
    Nodo* cola   = NULL;
  
/// conexion con arduino  (opcional)
    printf("\n\tDesea usar el arduino como control remoto del reproductor ?\ts/n:\n\t");scanf("%s",remoto);
    while (remoto[0] != 's' && remoto[0] != 'S' && remoto[0] != 'n' && remoto[0] != 'N')
    {  
        printf("\tseleccione s/n:");
        scanf("%s",remoto);
    }
    
    if (remoto[0] == 's' || remoto[0] == 'S' )
    {
        printf ("\n Esperando conexion con arduino\n");
        if ((sockfd = Open_conection (&my_addr)) == -1)
        {
            printf (" Falló la creación de la conexión\n"); 
        }
      
        sockdup = Aceptar_pedidos (sockfd);      
        //fcntl(sockdup, F_SETFL, O_NONBLOCK);
        
        if (write (sockdup, message , sizeof (message)) == -1)
        {
            printf (" Error en la conexion con Arduino\n");
        }
    }  
/// primer ingreso en menu 

    menu(&cabeza,&cola); 
   
 
/// Crear un Sistema objetivo a fmod e inisializar las functiones.
    
    result = FMOD_System_Create(&system);
    ERRCHECK(result);

    result = FMOD_System_GetVersion(system, &version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        return 0;
    }

    result = FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);
    ERRCHECK(result);

    result = FMOD_System_SetFileSystem(system, myopen, myclose, myread, myseek, 0, 0, 2048);
    ERRCHECK(result);

    result = FMOD_System_CreateStream(system, dir_cancion(cabeza,indice_temas), FMOD_HARDWARE | FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);
    ERRCHECK(result);

    

   
/// reproducir el sonido
    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, 0, &channel);
    ERRCHECK(result);

 
///     Main loop.
    do
    {
        ///'  ordenes desde el arduino (lectura de socket)
        if(remoto[0] == 's' || remoto[0] == 'S' )
        {
            //printf("\nPor leer\n");
            if ( (numbyte = read (sockdup,buf,MAXDATASIZE)) == -1)
            {
            perror("error de lectura en el socket");
            exit(1);
            }
            //printf("\nLeido !\n");
            buf[numbyte]='\0';


            switch (buf[0])
            {
                case 'A': puts("Arduino Conectado");break; 
                case 'x': puts("\n\tcerrando socket\n");close(sockdup);borrar_todo(cola,&cabeza);return 0;
                case 'n': goto next;break;
                case 'p': goto prev;break;
                case 'V': 
            //  while(buf[0]!= 'v')
            //  {
                numbyte = read (sockdup,buf,MAXDATASIZE);
                buf[numbyte]='\0';
                //if(buf[0]== 'v')break;
                volume = atoi(buf);
                if (volume >= 0)
                {
                    FMOD_Channel_SetVolume(channel, volume=((volume-79)/950) );break;
                } 
            //  }
                case 'P': pausar(&channel);break;
            }
        
        }   
         ///'    ordenes desde el servidor     (si el teclado es usado )
      
        if (kbhit()) // si el teclado es usado 
        {
            key = getch();
	   
            switch (key)
            {
                case ' ' :
                {
                    pausar(&channel);
		            break;
                }
                case 'v' :
                { 
                    FMOD_Channel_GetVolume(channel, &volume);
                    if (volume > 0)
                    {   volume -= 0.01f; }
                    FMOD_Channel_SetVolume(channel, volume);
                    break;
                }
                case 'V' :
                {
                    FMOD_Channel_GetVolume(channel, &volume);
                    if (volume < 1)
                    { volume += 0.01f; }
                    FMOD_Channel_SetVolume(channel, volume);
		    
                    break;
                }
                case 'n':
                {
                next:  
                    FMOD_Channel_GetVolume(channel, &volume);		// leer el volumen
                    indice_temas++;
                    if( indice_temas > contador_nodos(cabeza))
                    {   indice_temas = 1;   }
                    result = FMOD_Sound_Release(sound);  		// liberar la pista de sonido
                    result = FMOD_System_CreateStream(system,dir_cancion(cabeza,indice_temas) , FMOD_HARDWARE | FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);
                    ERRCHECK(result);                    		// cargar la cancion nueva
                    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, 0, &channel);
                    ERRCHECK(result);					            // reproducir
                    FMOD_Channel_SetVolume(channel, volume);		// setear el volumen
                    break;
                    
                }
                case 'p':
                {
                prev:
                    FMOD_Channel_GetVolume(channel, &volume);		// leer el volumen
                    result = FMOD_Sound_Release(sound);  		// liverar la pista de sonido
                    indice_temas--;                      		// avanzar el indice de temas
                    if( indice_temas < 1)				// si el tema supera el ultimo bolver al principio
                    {   indice_temas = contador_nodos(cabeza);}
                    result = FMOD_System_CreateStream(system, dir_cancion(cabeza,indice_temas), FMOD_HARDWARE | FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);
                    ERRCHECK(result);                  		// cargar la cancion nueva
                    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, 0, &channel);
                    ERRCHECK(result);					// reproducir
                    FMOD_Channel_SetVolume(channel, volume);		// setear el volumen
                    break;
                    
                }
                case 'l':
                {
                    menu(&cabeza,&cola);break; 
                }
            }
        }

        FMOD_System_Update(system);

        ///'      verificar la posocion de la cancion
	
        if (channel)
        {
            unsigned int ms;
            unsigned int lenms;
            int          playing;
            int          paused;

            FMOD_Channel_IsPlaying(channel, &playing);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
            {
                ERRCHECK(result);
            }

            result = FMOD_Channel_GetPaused(channel, &paused);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
            {
                ERRCHECK(result);
            }

            result = FMOD_Channel_GetPosition(channel, &ms, FMOD_TIMEUNIT_MS);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
            {
                ERRCHECK(result);
            }

            result = FMOD_Sound_GetLength(sound, &lenms, FMOD_TIMEUNIT_MS);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
            {
                ERRCHECK(result);
            }

            if (ms > (lenms-2000) ) 
            {
                goto next;
            }
	    
            if ( volume < 0 )
                { volume = 0;}
            printf("\rPresione n/p para next/prev, V/v para +/-Vol | Volumen: %.2f  Canción N°%d Tiempo %02d:%02d:%02d/%02d:%02d:%02d : %s",volume ,indice_temas, ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100, paused ? "Pausado      " : playing ? "Reproduciendo" : "Detenido");
            fflush(stdout);
        }

        Sleep(10);

    } while (key != 27);

    
    /// cerrar
    printf("\n\t Cerrando..\n\n");
  
    ///'      cerrar lista
    borrar_todo(cola,&cabeza);
    
    ///'      cerrar sonido
    result = FMOD_Sound_Release(sound);
    ERRCHECK(result);
    result = FMOD_System_Close(system);
    ERRCHECK(result);
    result = FMOD_System_Release(system);
    ERRCHECK(result);

    return 0;
}



#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
  
  /*Creando Variables*/
  int sock;
  struct sockaddr_in server;
  int mysock;
  char buff[1024];
  int rval;
  
  
  
  /*Creando socket*/
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock < 0)
  {
    perror("Fallo la creación del socket");
    exit(1);
  }
  
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(5000);
 
  /*llamando a bind*/
  if(bind(sock, (struct sockaddr *) &server, sizeof(server)))
  {
    perror("Fallo bind");
    exit(1);
  }
  
  /*Escuchando*/
  listen(sock, 5);

  /*Accepto*/
  do{
    mysock = accept(sock, (struct sockaddr *) 0, 0);
    if(mysock == -1)
    {
      perror("Fallo accept");
    }
    
    else
    {
      memset(buff, 0, sizeof(buff));
      if((rval = recv(mysock, buff, sizeof(buff), 0)) < 0)
	perror("Leyendo mensaje de error de torrente");
      
      else if(rval == 0){
	puts("Terminando Conección");
	close(mysock);}
      
      else{
	printf("MENSAJE: %s\n", buff);
	printf("Se enviaron %d caracteres\n", rval);
        close(mysock);}
    }  
  }while(rval != 0);
  
  return 0; 
}

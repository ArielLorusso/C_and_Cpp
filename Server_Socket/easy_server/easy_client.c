#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>

#define msg "OLA k ASE"

int main(int argc, char **argv)
{
  int sock;
  struct sockaddr_in server;
  struct hostent *hp;
  char buff[1024];
  
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock < 0)
  {
    perror("Fallo socket");
    exit(1);
  }
  
  server.sin_family = AF_INET;
  
  hp = gethostbyname( argv[1]);
  if(hp ==0)
  {
    perror("Fallo gethostbyname");
    exit(1);
  }
  
  
  memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
  server.sin_port = htons(5000);
  
  if(connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0)
  {
    perror("connect failed");
    exit(1);
  }
  
  
  if(argc > 2)
  {
    if(send(sock, argv[2], sizeof(argv[2]), 0) < 0)
      
    {
      perror("Fallo send");
      close(sock);
      exit(1);
    }  
  }
  
  else
  {
    if(send(sock, msg, sizeof(msg), 0) < 0)
    {
      perror("Fallo send");
      close(sock);
      exit(1);
    }
  }
  
 // printf("Sent %s\n", msg);
  close(sock);
  
  return 0;
}
#include<stdio.h>

typedef enum { UPPERCASE, LOWERCASE } cases;

void change_case (char * entrada, cases pepe)
{
  int i;
  if (pepe ==LOWERCASE)
  {
    for(i=0;entrada[i]!='\0';i++)
    {
	entrada[i]=entrada[i]+32;
    }
  }
  else if (pepe == UPPERCASE)
    {
     for(i=0;entrada[i]!='\0';i++)
      {
	entrada[i]=entrada[i]-32;
      } 
    }
  else printf ("\n error "); 
}

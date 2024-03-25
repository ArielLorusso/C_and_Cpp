
int my_strlen (const char * c) 
{
  int i; 
  for(i=0;c[i]!='\0';i++){}
  printf("\n La cantidad de letras es %d",i);
  return i;
}
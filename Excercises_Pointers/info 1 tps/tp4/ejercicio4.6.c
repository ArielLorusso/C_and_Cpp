void separa_csv (const char *s, char ***campos, int* numCampos)
{
  int i;
  numCampos=0;
  for (i=0;s[i]!='\0';i++)
  {
    if (s[i]=',') 
    {
      numCampos++;
    }
  }
  numCampos++;
  *campos = (char**)malloc(numCampos*(sizeof(char)));
  
  indiceInicio = 0;
  indicieFinal = 0;
  indiceCampo = 0;
  for (i=0;s[i]!='\0';i++)
  {
    if (s[i]=',') 
    {
      indiceFinal = i-1;
      (*campos)[indiceCampo] = (char*) malloc(sizeof(char)*(indiceFinal-indiceInicio));
      //Copiar caracteres
    }
    indiceInicio = i+2;
  }
}


void main ()
{
  gets(C);
  int cantPalabras=0;
  char strEntrada[] =" =erer,erer,erer,erereds,dfsdf";
  char** campos;
  separa_csv(strEntrada[],&campos,&cantPalabras)
}
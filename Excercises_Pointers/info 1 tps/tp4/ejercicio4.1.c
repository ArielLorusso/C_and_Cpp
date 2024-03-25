
void string_reverse (char *m)
{
  int i,j;char c; 
  for(i=0;m[i]!='\0';i++){}
  j=i-1;
  for(i=0;i<=(j+1)/2;i++)
  {
    c = m[i];
    m[i]=m[j]; 
    m[j]=c;
    j--;
  }
  return m;
}


int my_strcmp (const char *t, const char *s)
{
  int i,j,n=0;
  for(j=0;t[j]==s[j]&&t[j]!='\0'&&s[j]!='\0';j++){}
  
  if (t[j]<s[j]) 
  {
   n-- ;
  }
  if (t[j]>s[j]) 
  {
   n++ ;
  }
  return n;
}

#include <stdio.h>
#include <stdlib.h>

main()
{
  typedef struct bin
  {
    char bin_:1;
  }BIN;
  
  typedef union car
  {
    char a; 
    BIN Bin[7];
  }CAR;

  printf("sise of   bin:%lu\n",sizeof(BIN));
  printf("sise of   int:%lu\n",sizeof(int));
  printf("sise of  char:%lu\n",sizeof(char));
  
  CAR caracter;
  scanf("%c",&caracter.a);
  printf("%d",caracter.Bin[0].bin_);
  printf("%d",caracter.Bin[1].bin_);
  printf("%d",caracter.Bin[2].bin_);
  printf("%d",caracter.Bin[3].bin_);
  printf("%d",caracter.Bin[4].bin_);
  printf("%d",caracter.Bin[5].bin_);
  printf("%d",caracter.Bin[6].bin_);
  printf("%d",caracter.Bin[7].bin_);
}

#include <stdio.h>


void main(int argc, char* argv[]){
  int i;
  if(argc <= 1)
    printf("There is nothing to be inversed\n");
  else
    {
    for(i = argc - 1; i > 0; --i)
      printf("%s ",argv[i]);
    printf("\n");
    }
}

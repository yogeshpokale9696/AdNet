#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
  char buff[256];
  printf("Enter any string:");
  gets(buff);
  printf("\n");
  //fork system call  
    fork();
  
    printf("%s\n",buff);
    return 0;
}
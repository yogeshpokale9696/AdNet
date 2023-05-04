#include <stdio.h>
#include <unistd.h>

void main()
{
     pid_t p;

     printf("pid of main program:\t%d\n", getpid());
     
     p = fork();

     if (p == 0)
     {
          printf("\nHi this is child\n");
     }
     else if(p > 0)
     {
          printf("\nhlw this is parent:\n");
     }else
     {
          printf("failed");
     }
}

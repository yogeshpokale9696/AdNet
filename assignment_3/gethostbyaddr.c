#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

int main()
{
     struct in_addr ip_addr;
     char *ip = "127.0.0.1";  // Replace with actual IP address
     inet_aton(ip, &ip_addr); // Convert IP address string to binary format

     struct hostent *host = gethostbyaddr(&ip_addr, sizeof(ip_addr), AF_INET);
     if (host == NULL)
     {
          fprintf(stderr, "Error: %s\n", hstrerror(h_errno)); // Handle error
          exit(1);
     }

     printf("%s\n", host->h_name); // Print the host name
     return 0;
}

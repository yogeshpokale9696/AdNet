// server program for udp connection
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#define PORT 5000
#define MAXLINE 1000

// Driver code
int main()
{
char buffer[100];
char *message = "Server connected !";
int listenfd, len;
struct sockaddr_in servaddr, cliaddr;
bzero(&servaddr, sizeof(servaddr));
char client_addr[1024];

// Create a UDP Socket
listenfd = socket(AF_INET, SOCK_DGRAM, 0);
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(PORT);
servaddr.sin_family = AF_INET;

printf("Server is waiting\n");


// bind server address to socket descriptor
bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

//receive the datagram
len = sizeof(cliaddr);
int n = recvfrom(listenfd, buffer, sizeof(buffer),
0, (struct sockaddr*)&cliaddr,&len); //receive message from server
buffer[n] = '\0';
puts(buffer);

// send the response
sendto(listenfd, message, MAXLINE, 0,
(struct sockaddr*)&cliaddr, sizeof(cliaddr));

printf("\n Client port no. : %d",cliaddr.sin_port);
bzero(client_addr,1024);

inet_ntop(cliaddr.sin_family,(struct sockaddr *)&cliaddr.sin_addr,client_addr,sizeof(client_addr));
printf("\n Client address :%s",client_addr);


}
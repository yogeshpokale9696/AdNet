// server program for udp connection
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<ctype.h>
#define PORT 5000
#define MAXLINE 1000

// Driver code
int main()
{
char buffer[100],greet[50];
char *message = "Server connected !";
int listenfd, len;
struct sockaddr_in servaddr, cliaddr;
bzero(&servaddr, sizeof(servaddr));
char client_addr[1024];
uint32_t net_addr;

// Create a UDP Socket
listenfd = socket(AF_INET, SOCK_DGRAM, 0);
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(PORT);
servaddr.sin_family = AF_INET;

printf("[+] waiting for client........\n");
// bind server address to socket descriptor
bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

//receive the datagram
len = sizeof(cliaddr);
int n = recvfrom(listenfd, buffer, sizeof(buffer),
0, (struct sockaddr*)&cliaddr,&len); //receive message from server
buffer[n] = '\0';
puts(buffer);

recvfrom(listenfd, greet, sizeof(greet),
0, (struct sockaddr*)&cliaddr,&len); //receive message from server
/*for(int i=0;greet[i]!='\0';i++)
{
if(greet[i] >='A' && greet[i] <= 'Z')
{
greet[i]=greet[i]-32;
}
}*/
int i; char upperString[50]="";
while(greet[i]!='\0')
{
upperString[i] = greet[i]-32;
i++;
}
puts(upperString);



// send the response
sendto(listenfd, message, MAXLINE, 0,
(struct sockaddr*)&cliaddr, sizeof(cliaddr));


}
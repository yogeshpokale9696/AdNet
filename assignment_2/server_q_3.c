// server program for udp connection
#include <stdio.h>
#include<time.h>
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
	char buffer[100],greet[50];
	int dt[20];
	int nums[5],ans[5]; // for addition
	char *message = "Server connected !";
	int listenfd, len;
	struct sockaddr_in servaddr, cliaddr;
	bzero(&servaddr, sizeof(servaddr));
	char client_addr[1024];
	uint32_t net_addr;

	// Create a TCP Socket
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
	printf("Hello ");
	puts(greet);
		

	// send the response
	
	printf("\n Client port no. : %d \n",cliaddr.sin_port);
	bzero(client_addr,1024);
	



recvfrom(listenfd, nums, sizeof(dt),
			0, (struct sockaddr*)&cliaddr,&len); //receive message from server
	// printf("%d-%d",nums[0],nums[1]);
	ans[1]=nums[0]+nums[1];
	
	//printf("%d",ans[0]);
	sendto(listenfd, ans, MAXLINE, 0,
			(struct sockaddr*)&cliaddr, sizeof(cliaddr));

sendto(listenfd, message, MAXLINE, 0,
			(struct sockaddr*)&cliaddr, sizeof(cliaddr));

	recvfrom(listenfd, dt, sizeof(dt),
			0, (struct sockaddr*)&cliaddr,&len); //receive message from server
	

	printf("\nTime:-%d-%d-%d",dt[0],dt[1],dt[2]);
	
	printf("\nDate:-%d-%d-%d",dt[3],dt[4],dt[5]);


}

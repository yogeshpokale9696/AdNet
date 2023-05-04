// udp client driver program
#include <stdio.h>
#include<time.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>

#define PORT 5000
#define MAXLINE 1000

// Driver code
int main()
{
	char buffer[100];
	int nums[5];
	int ans[5];
	char *message = "Client Connected !";
	char username[50];
	int sockfd, n;
	struct sockaddr_in servaddr;
	
	time_t t;
	t = time(NULL);
	struct tm tm = *localtime(&t);
	int dt[20];
    dt[0] = tm.tm_hour; 	
	dt[1]=tm.tm_min;
	dt[2]=tm.tm_sec;
	dt[3]=tm.tm_mday;
	dt[4]=tm.tm_mon+1;
	dt[5]=tm.tm_year+1900;
	
	// clear servaddr
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;
	
	// create datagram socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	// connect to server
	if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		printf("\n Error : Connect Failed \n");
		exit(0);
	}

	// request to send datagram
	// no need to specify server address in sendto
	// connect stores the peers IP and port
	sendto(sockfd, message, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr));
	
	printf("\nEnter Your Name :- ");
	scanf("%s",&username);
	

	sendto(sockfd, username, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr));


printf("Enter two numbers to send numbers add in server side\n");		

	scanf("%d",&nums[0]);
	scanf("%d",&nums[1]);
	// to send numbers to server side
	sendto(sockfd, nums, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr));
	ans[1]=0;	
	
	//To recieve addtion from server side 

	recvfrom(sockfd, ans, sizeof(ans), 0, (struct sockaddr*)NULL, NULL);
	
	printf("addtion is :- %d \n",ans[1]);


	sendto(sockfd, dt, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr));
	
	// waiting for response
	recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL);
	puts(buffer);


	// close the descriptor
	close(sockfd);


}

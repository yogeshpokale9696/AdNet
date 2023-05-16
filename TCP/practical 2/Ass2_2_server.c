#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<sys/unistd.h>
#include <netinet/in.h>
#include<time.h>
#include<string.h>
int main()
{
	int socket_fd, retVal;
	int new_socket;
	char buff[1024];
	
	time_t ticks;
	struct sockaddr_in address, clientAddr;
	int socklen = sizeof(struct sockaddr_in);
	int clientlen = sizeof(struct sockaddr_in);
		
	// Create a Socket
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd < 0)
	{
		printf("not able to create socket\n");
		exit(0);
	}
	else
		printf("Socket created\n");
	
	// bind
	address.sin_family = AF_INET;
	address.sin_addr.s_addr= INADDR_ANY;
	address.sin_port = 55555;
	
	retVal = bind(socket_fd,(struct sockaddr *)&address,(socklen_t)socklen);
	if(retVal < 0)
	{
		printf("not able to bind the socket\n");
		exit(0);
	}
	
	
	// listen
	retVal = listen(socket_fd, 3);
	if(retVal < 0)
	{
		printf("not able to listen\n");
		exit(0);
	}
	else
		printf("Server is waiting for client\n");
	
	// accept
	new_socket = accept(socket_fd,(struct sockaddr *)&clientAddr,(socklen_t *)&clientlen);
	if(new_socket < 0)
	{
		printf("not able to establish the connection\n");
		exit(0);
	}
	printf("Connection Established with the client\n");
	time(&ticks);
	bzero(buff,1024);
	printf("date and time:%s",ctime(&ticks));
	snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
	send(new_socket,buff,sizeof(buff),0);

	//reciving data
	bzero(buff,1024);
	recv(new_socket,buff,sizeof(buff),0);
	printf("Client username: %s\n",buff);

	//sending data
	printf("write message for client:");
	bzero(buff,1024);
	fgets(buff,1024,stdin);
	send(new_socket,buff,sizeof(buff),0);
	close(new_socket);
	close(socket_fd);

	return 0;
}



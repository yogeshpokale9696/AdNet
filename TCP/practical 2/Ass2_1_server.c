#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<sys/unistd.h>
#include <netinet/in.h>

int main()
{
	int socket_fd, retVal;
	int new_socket;
	char buffer[1024] = {0};
	
	struct sockaddr_in address, clientAddr;
	int socklen = sizeof(struct sockaddr_in);
	int clientlen = sizeof(struct sockaddr_in);
		
	// Create a Socket
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd < 0)
	{
		printf("not able to create socket");
		exit(0);
	}
	else
		printf("\n Socket created");
	
	// bind
	address.sin_family = AF_INET;
	address.sin_addr.s_addr= INADDR_ANY;
	address.sin_port = 55555;
	
	retVal = bind(socket_fd,(struct sockaddr *)&address,(socklen_t)socklen);
	if(retVal < 0)
	{
		printf("\n not able to bind the socket");
		exit(0);
	}
	
	
	// listen
	retVal = listen(socket_fd, 3);
	if(retVal < 0)
	{
		printf("\n not able to listen");
		exit(0);
	}
	else
		printf("\n Server is waiting for client");
	
	// accept
	new_socket = accept(socket_fd,(struct sockaddr *)&clientAddr,(socklen_t *)&clientlen);
	if(new_socket < 0)
	{
		printf("\n not able to establish the connection");
		exit(0);
	}
	printf("\n Connection Established with the client");

    char msg[50];

    recv(new_socket,msg,sizeof(msg),0);
    printf("\nhello %s",msg);
	
	close(new_socket);
	close(socket_fd);
	return 0;
}



#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<sys/unistd.h>
#include <netinet/in.h>
#include<string.h>

int main()
{
	int socket_fd, retVal;
	char buffer[1024];
	
	struct sockaddr_in address;
	int socklen = sizeof(struct sockaddr_in);

	// Create a Socket
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd < 0)
	{
		printf("not able to create socket\n");
		exit(0);
	}
	else
		printf("Socket created\n");
	
	
	// connect to the server
	address.sin_family = AF_INET;
	address.sin_addr.s_addr= INADDR_ANY;
	address.sin_port = 55555;
	
	retVal = connect(socket_fd, (struct sockaddr *)&address, (socklen_t)socklen);
	
	if(retVal == -1)
	{
		printf("not able to connect the server\n");
		exit(0);
	}
	printf("Client connected with server\n");
	bzero(buffer,1024);
	recv(socket_fd,buffer,sizeof(buffer),0);
	printf("Server date and time: %s\n",buffer);

	//sending data
	printf("write message for server:");
	bzero(buffer,1024);
	fgets(buffer,1024,stdin);
	send(socket_fd,buffer,sizeof(buffer),0);
    
	//reciving data
	bzero(buffer,1024);
	recv(socket_fd,buffer,sizeof(buffer),0);
	printf("message from server: %s\n",buffer);	
	close(socket_fd);
	return 0;
}



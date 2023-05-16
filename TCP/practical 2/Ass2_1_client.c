#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<sys/unistd.h>
#include <netinet/in.h>

int main()
{
	int socket_fd, retVal;
    char msg[50];
	
	struct sockaddr_in address;
	int socklen = sizeof(struct sockaddr_in);

	// Create a Socket
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd < 0)
	{
		printf("not able to create socket");
		exit(0);
	}
	else
		printf("\n Socket created");
	
	
	// connect to the server
	address.sin_family = AF_INET;
	address.sin_addr.s_addr= INADDR_ANY;
	address.sin_port = 55555;
	
	retVal = connect(socket_fd, (struct sockaddr *)&address, (socklen_t)socklen);
	
	if(retVal == -1)
	{
		printf("not able to connect the server");
		exit(0);
	}
	printf("\n Client connected");

    printf("\n enter your name ");
    
    fgets(msg,50,stdin);
    //strcpy(msg,"good morning");
    send(socket_fd,msg,sizeof(msg),0);
		
	close(socket_fd);
	return 0;
}














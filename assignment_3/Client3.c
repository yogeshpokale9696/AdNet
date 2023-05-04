#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/unistd.h>
#include <netinet/in.h>
#include <string.h>

int main()
{
	int socket_fd, retVal;
	char buffer[1024];

	struct sockaddr_in address;
	int socklen = sizeof(struct sockaddr_in);

	// Create a Socket
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0)
	{
		printf("not able to create socket\n");
		exit(0);
	}
	else
		printf("Socket created\n");

	// connect to the server
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = 55555;

	retVal = connect(socket_fd, (struct sockaddr *)&address, (socklen_t)socklen);

	if (retVal == -1)
	{
		printf("not able to connect the server\n");
		exit(0);
	}
	printf("Connected with server\n");
	printf("\n");

	// sending data
	printf("Enter File name:");
	bzero(buffer, 1024);
	gets(buffer);

	send(socket_fd, buffer, sizeof(buffer), 0);
	printf("\n");

	// recieve message from server
	bzero(buffer, 1024);
	printf("Content in the file:\n");
	printf("\n");
	recv(socket_fd, buffer, sizeof(buffer), 0);
	printf("%s\n", buffer);

	close(socket_fd);
	return 0;
}

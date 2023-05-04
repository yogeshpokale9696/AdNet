#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
	int socket_fd, retVal, recv_f, sen_to;
	int new_socket;
	char buffer[1024];
	char client_addr[1024];
	char str[] = "exit";

	struct sockaddr_in address;
	struct sockaddr_in client;
	int socklen = sizeof(struct sockaddr_in);
	int clientlen = sizeof(struct sockaddr_in);

	// Create a Socket
	socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (socket_fd < 0)
	{
		printf("not able to create socket\n");
		exit(0);
	}
	else
		printf("Socket created\n");

	// bind
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = 55555;

	retVal = bind(socket_fd, (struct sockaddr *)&address, (socklen_t)socklen);
	if (retVal < 0)
	{
		printf("not able to bind the socket\n");
		exit(0);
	}
	printf("Binded succesfully\nwating for client !!\n");

	for (;;)
	{
		// reving data
		bzero(buffer, 1024);
		recv_f = recvfrom(socket_fd, buffer, 1024, 0, (struct sockaddr *)&client, (socklen_t *)&socklen);
		printf("\n");

		if (recv_f < 0)
		{
			printf("not recived anything\n");
			exit(0);
		}
		printf("recived message from client:");
		printf("%s\n", buffer);
		printf("\n");
		printf("write message for client:");
		bzero(buffer, 1024);
		gets(buffer);
		// printf("%s",buffer);
		int value = strcmp(buffer, str);
		if (value == 0)
		{
			printf("disconnected!!! \n");
			exit(0);
		}
		else
		{
			sen_to = sendto(socket_fd, buffer, strlen(buffer), 0, (struct sockaddr *)&client, (socklen_t)socklen);
			if (sen_to < 0)
			{
				printf("error !!!!");
				exit(0);
			}
		}
	}
}
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
int main()
{
	int socket_fd, retVal;
	int new_socket;
	char fname[1024];
	char buffer[1024];
	char client_addr[1024];
	FILE *fp;

	struct sockaddr_in address, clientAddr;
	int socklen = sizeof(struct sockaddr_in);
	int clientlen = sizeof(struct sockaddr_in);

	// Create a Socket
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
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

	// listen
	retVal = listen(socket_fd, 3);
	if (retVal < 0)
	{
		printf("not able to listen\n");
		exit(0);
	}
	else
		printf("Server is waiting for client\n");

	// accept

	new_socket = accept(socket_fd, (struct sockaddr *)&clientAddr, (socklen_t *)&clientlen);
	if (new_socket < 0)
	{
		printf("not able to establish the connection\n");
		exit(0);
	}
	printf("Connection Established with the client\n");
	printf("client port no:%d\n", clientAddr.sin_port);
	inet_ntop(clientAddr.sin_family, (struct sockaddr *)&clientAddr.sin_addr, client_addr, sizeof(client_addr));
	printf("client address:%s\n", client_addr);
	printf("\n");

	// receving data
	bzero(fname, 1024);
	recv(new_socket, fname, sizeof(fname), 0);
	printf("reading file: %s\n", fname);
	printf("\n");

	// sending data
	bzero(buffer, 1024);

	// opening the file and reding content
	fp = fopen(fname, "r+");
	if (fp == NULL)
	{
		send(new_socket, "\nFile not found\n", 15, 0);
		exit(0);
	}
	else
	{
		fseek(fp, 0, SEEK_SET);
		fread(buffer, sizeof(buffer), 1, fp);
		send(new_socket, buffer, sizeof(buffer), 0);
		fclose(fp);
	}

	close(new_socket);

	close(socket_fd);

	return 0;
}

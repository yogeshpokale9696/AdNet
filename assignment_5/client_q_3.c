#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<sys/unistd.h>
#include <netinet/in.h>
#include<string.h>

int main()
{
    int socket_fd, retVal,sen_to,recv_f;
    char buffer[256];
	char str[] = "exit";
	
	struct sockaddr_in address;
	struct sockaddr_in client;

	int socklen = sizeof(struct sockaddr_in);

	// Create a Socket
	socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(socket_fd < 0)
	{
		printf("not able to create socket");
		exit(0);
	}
	else
		printf("Socket created\n\n");

    address.sin_family = AF_INET;
	address.sin_addr.s_addr= INADDR_ANY;
	address.sin_port = 55555;
    
    for(;;){
    printf("Enter message for server:");
    bzero(buffer,256);
    gets(buffer);
    printf("\n");
    int value = strcmp(buffer,str);
    if(value == 0){
        printf("disconnected!!! \n");
		exit(0);
	}else{
      sen_to = sendto(socket_fd,buffer,strlen(buffer),0,(struct sockaddr *)&address,(socklen_t)socklen);
    if(sen_to < 0)
    {
        printf("error !!");
    }  
    }
    
    
    recv_f = recvfrom(socket_fd,buffer,256,0,(struct sockaddr *)&address,(socklen_t *)&socklen);
    if(recv_f < 0)
    {
        printf("not recived anything\n");
        exit(0);
    } 
	printf("recived message from server:");
	printf("%s\n",buffer);
    printf("\n");
    }   

}
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sockop.h"
#define BUFSIZE	1024
void handleRequest(int new_client_socket,int OrderCustomer){
    int MessageLength;
    char ReceiveMessage[BUFSIZE],SendMessage[BUFSIZE];
    printf("accept client order : %d \n",OrderCustomer);
    while(1){
        if ((MessageLength = read(new_client_socket, ReceiveMessage, BUFSIZE)) == -1)
            errexit("Error: read()\n");
        if (MessageLength == 0){
            printf("finish %d client\n",OrderCustomer);
            exit(0);
        }
    /* write message back to client */
        printf("from no. %d client message = %.*s\n",OrderCustomer,MessageLength,ReceiveMessage);
        MessageLength = sprintf(SendMessage, "from no. %d client message = %.*s\n",OrderCustomer,MessageLength,ReceiveMessage);
        if ((MessageLength = write(new_client_socket, SendMessage, MessageLength)) == -1)
            errexit("Error: write()\n");
    }
}

int main(int argc, char *argv[])
{
	int sockfd, new_client_socket, OrderCustomer = 0; /* socket descriptor */
	struct sockaddr_in addr_cln;
	socklen_t sLen = sizeof(addr_cln);
	int n;
	char SendMessage[BUFSIZE], ReceiveMessage[BUFSIZE];
	if (argc != 2)
		errexit("Usage: %s port\n", argv[0]);
	/* create socket and bind socket to port */
	sockfd = passivesock(argv[1], "tcp",10);
	while(1){
		/* wait for connection */
		new_client_socket = accept(sockfd, (struct sockaddr *) &addr_cln, &sLen);
		if (new_client_socket == -1)
			errexit("Error: accept()\n");
        OrderCustomer++;
        switch (fork()) {
            case -1:
                errexit("Can't create child process\n");
                close(new_client_socket);
                break;
            case 0:
                handleRequest(new_client_socket,OrderCustomer);
                exit(0);
            default:
                close(new_client_socket);
                break;
        }

	}
	/* close server socket */
	close(sockfd);
	return 0;
}

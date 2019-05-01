#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sockop.h"
#include <pthread.h>
#include <vector>
#define BUFSIZE	1024
using namespace std;
int OrderCustomer = 0;
struct ClientData{
    int OrderCustomer;
    int new_client_socket;
};
void *handleRequest(void *ClientDataPtr){
    struct ClientData new_client_socket =*(ClientData*)ClientDataPtr;
    int MessageLength;
    char ReceiveMessage[BUFSIZE],SendMessage[BUFSIZE];
    printf("accept client order : %d \n",new_client_socket.OrderCustomer);
    while(1){
        if ((MessageLength = read(new_client_socket.new_client_socket, ReceiveMessage, BUFSIZE)) == -1)
            pthread_exit(NULL);
    /* write message back to client */
        printf("from no. %d client message = %.*s\n",new_client_socket.OrderCustomer,MessageLength,ReceiveMessage);
        MessageLength = sprintf(SendMessage, "from no. %d client message = %.*s\n",new_client_socket.OrderCustomer,MessageLength,ReceiveMessage);
        if ((MessageLength = write(new_client_socket.new_client_socket, SendMessage, MessageLength)) == -1)
            pthread_exit(NULL);
    }
}

int main(int argc, char *argv[])
{
	int sockfd, new_client_socket; /* socket descriptor */
	struct sockaddr_in addr_cln;
	socklen_t sLen = sizeof(addr_cln);
	int n;
    pthread_t threads[30];
    struct ClientData server[30];
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
        server[OrderCustomer].OrderCustomer=OrderCustomer;
        server[OrderCustomer].new_client_socket=new_client_socket;
        pthread_create(&threads[OrderCustomer],NULL,handleRequest,&server[OrderCustomer]);
        OrderCustomer++;
	}
	/* close server socket */
	close(sockfd);
	return 0;
}

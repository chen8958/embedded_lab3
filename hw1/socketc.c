/*
*	echoc.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "sockop.h"
using namespace std;
#define BUFSIZE	1024

void command_socket(char* command)
{
    printf("start to command socket %s \n",command);
    int connfd; /* socket descriptor */
    int n;
    char buf[BUFSIZE];
    const char *ip ="192.168.0.119";
    const char *port = "8888";
   /* create socket and connect to server 1:ip 2: port*/
    connfd = connectsock(ip, port, "tcp");

   /* write message to server */
    if ((n = write(connfd, command, strlen(command))) == -1)
        errexit("Error: write()\n");
    memset(buf, 0, BUFSIZE);
	if ((n = read(connfd, buf, BUFSIZE)) == -1)
		errexit("Error: read()\n");
    printf("get = \n");
    printf("%s",buf);
    close(connfd);
}
int main(){
    char order_num[5];
    char command_oneline[100];
    while(1) {
        scanf("%s",order_num);
        printf("get = %s\n",order_num);
        command_socket(order_num);
        printf("done order_num = %s\n",order_num);
        cin.ignore();
        cin.getline(command_oneline,100);
        printf("command_online = %s\n",command_oneline);
        command_socket(command_oneline);
    }

}

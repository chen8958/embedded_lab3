 /*
*	echoc.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include "sockop.h"

#define BUFSIZE	1024

int main(int argc, char *argv[])
{
	int connfd; /* socket descriptor */
	int n;
	char buf[BUFSIZE];

	if (argc != 4)
		errexit("Usage: %s host address host port message\n", argv[0]);

	/* create socket and connect to server */
	connfd = connectsock(argv[1], argv[2], "tcp");

	/* write message to server */
	if ((n = write(connfd, argv[3], strlen(argv[3]))) == -1)
		errexit("Error: write()\n");
	printf("n w1 = %d\n",n);
	/* read message from the server and print */
	memset(buf, 0, BUFSIZE);

	if ((n = read(connfd, buf, BUFSIZE)) == -1)
		errexit("Error: read()\n");
	printf("%s\n", buf);
	printf("first n = %d\n",n);
	close(connfd);
	

	return 0;
}

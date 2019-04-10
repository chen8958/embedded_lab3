#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unist.h>

#include "sockop.h"

#define BUFSIZE 1024
int main(int argc, char const *argv[]) {
    /* code */
    int connfd;
    int n;
    char buf[BUFSIZE];

    if (argc != 4){
        errexit("usage: %s host address host port message\n",argv[0]);
    }
    connfd = connectsock(argv[1], argv[2], "tcp");

    if ((n = write(connfd, argv[3], strlen(argv[3]))) == -1){
        errexit("Error : write()\n");
    }
    if ((n = read(connfd, buf, BUFSIZE)) == -1){
        errexit("Error : read()\n");
    }
    printf("%s\n",buf );
    close(connfd);

    return 0;
}

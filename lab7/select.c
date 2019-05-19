#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define max(a,b) ((a>b)?a:b)

void ChildProcess(int *pfd, int sec){
    char buffer[100];
    close(pfd[0]);

    printf("Child process (%d) wait %d secs\n", getpid(),sec);
    sleep(sec);

    memset(buffer, 0, 100);
    sprintf(buffer,"Child process (%d) sent message to parent process\n"
        ,getpid());
    write(pfd[1], buffer,strlen(buffer));

    close(pfd[1]);
    exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[]) {
    int pfd1[2],pfd2[2];
    int cpid1,cpid2;
    fd_set rfds, arfds;
    int max_fd;
    struct timeval tv;
    int retval;
    int fd_index;
    char buffer[100];

    srand(time(NULL));
    pipe(pfd1);
    pipe(pfd2);
    cpid1 = fork();
    if (cpid1==0) {
        ChildProcess(pfd1,random()%5);
        /* code */
    }
    cpid2 = fork();
    if (cpid2==0) {
        ChildProcess(pfd2,random()%4);
        /* code */
    }
    close(pfd1[1]);
    close(pfd2[1]);

    FD_ZERO(&rfds);
    FD_ZERO(&arfds);
    FD_SET(pfd1[0],&arfds);
    FD_SET(pfd2[0],&arfds);
    max_fd = max(pfd1[0],pfd2[0])+1;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    while(1){
        memcpy(&rfds, &arfds,sizeof(rfds));
        retval = select(max_fd,&rfds, NULL,NULL,&tv);
        if (retval == -1) {
            perror("select()");
            exit(EXIT_FAILURE);
            /* code */
        }else if (retval) {
            printf("data is available now \n");
            /* code */
        }else{
            printf("no data within five seconds.\n");
            break;
        }
        for (fd_index = 0; fd_index < max_fd; fd_index++) {
            if (!FD_ISSET(fd_index, &rfds)) {
                continue;
                /* code */
            }
            retval = read(fd_index, buffer, 100);
            if (retval > 0) {
                printf("%.*s\n", retval,buffer);
                /* code */
            }else if(retval < 0){
                perror("pipe read()");
            }else{
                close(fd_index);
                FD_CLR(fd_index, &arfds);
            }
            /* code */
        }
    }
    /* code */
    return 0;
}

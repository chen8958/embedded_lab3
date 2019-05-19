#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int pfd[2];

void ChildProcess(const char *path){
    int fd;
    int ret;
    char buffer[100];

    close(pfd[0]);

    fd = open(path, O_RDONLY);
    if (fd < 0) {
        printf("open %s failed.\n",path);
        exit(EXIT_FAILURE);
        /* code */
    }

    while (1) {
        ret = read(fd, buffer, 100);
        if (ret < 0) {
            perror("read()");
            exit(EXIT_FAILURE);
            /* code */
        }else if (ret == 0) {
            close(fd);
            close(pfd[1]);
            exit(EXIT_FAILURE);
            /* code */
        }else{
            write(pfd[1], buffer, ret);
        }
        /* code */
    }
}

void ParentProcess(){
    int ret;
    char buffer[100];

    close(pfd[1]);

    while(1){
        ret = read(pfd[0],buffer,100);

        if(ret > 0){
            printf("%.*s",ret,buffer);
        }else if (ret == 0) {
            close(pfd[0]);
            wait(NULL);
            exit(EXIT_FAILURE);
            /* code */
        }else{
            perror("pipe read()");
            exit(EXIT_FAILURE);
        }
    }
}
int main(int argc, char const *argv[]) {
    pid_t cpid;
    if (argc != 2){
        fprintf(stderr, "%s: specify a file\n",argv[0]);
        exit(1);
    }
    if (pipe(pfd)==-1) {
        perror("pipe");
        exit(EXIT_FAILURE);
        /* code */
    }
    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
        /* code */
    }
    if (cpid == 0) {
        ChildProcess(argv[1]);
        /* code */
    }else{
        ParentProcess();
    }
    return 0;
}

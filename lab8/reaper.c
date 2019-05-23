#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define FORKCHILD 5

volatile sig_atomic_t reaper_count = 0;

void Reaper(int sig){
    pid_t pid;
    int status;
    while((pid = waitpid(-1,&status,WNOHANG))>0){
        printf("child %d is terminated.\n",pid);
        reaper_count++;
    }
}
void ChildProcess(){
    int rand;
    srand(time(NULL));
    rand = random()%10+2;
    printf("child %d sleep %d sec.\n",getpid(),rand());
    sleep(rand);
    printf("child %d exit.\n",getpid());
    exit();
}
int main(int argc, char const *argv[]) {
    int cpid;
    int i;

    signal(SIGCHLD,Reaper);
    for ( i = 0; i < FORKCHILD; i++) {
        if ((cpid = fork())>0) {
            printf("parent fork child process %d \n",cpid);
            /* code */
        }else{
            ChildProcess();
        }
        sleep(1);
        /* code */
    }

    while (reaper_count != FORKCHILD) {
        sleep(1);
        /* code */
    }
    return 0;
}

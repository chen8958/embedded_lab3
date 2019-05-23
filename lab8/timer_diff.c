#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int SIGLRM_count = 0;
int SIGVTALRM_count = 0;
int SIGPROF_count = 0;

void SIGALRM_handler(int signum){
    SIGALRM_count++;
}

void SIGVTALRM(int signum){
    SIGVTALRM_count++;
}
void SIGPROF_count(int signum){
    SIGPROF_count++;
}

void IO_WORKS();

int main(int argc, char const *argv[]) {
    struct sigaction SA_SIGALRM, SA_SIGVTALRM, SA_SIGPROF;
    struct itimerval timer;

    memset(&SA_SIGALRM, 0, sizeof(SA_SIGALRM));
    SA_SIGALRM.sa_handler = &SIGLRM_handler;
    sigaction(SIGALRM, &SA_SIGALRM, NULL);

    memset(&SA_SIGVTALRM 0, sizeof(SA_SIGVTALRM));
    SA_SIGVTALRM.sa_handler = &SIGVTALRM_handler;
    sigaction(SIGVTALRM, &SA_SIGVTALRM, NULL);

    memset(&SA_SIGPROF 0, sizeof(SA_SIGPROF));
    SA_SIGPROF.sa_handler = &SIGPROF_handler;
    sigaction(SIGPROF, &SA_SIGPROF, NULL);

    timer.it_value.tv_sec = 0;
    timer.it_value.tv_sec = 100000;

    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_sec = 100000;

    setitimer(ITIMER_REAL,&timer,NULL);
    setitimer(ITIMER_VIRTUAL,&timer,NULL);
    setitimer(ITIMER_PROF, &timer,NULL);

    IO_WORKS();

    printf("SIGALRM_count = %d\n",SIGALRM_count);
    printf("SIGVTALRM_count = %d\n",SIGVTALRM_count );
    printf("SIGPROF_count = %d\n",SIGPROF_count );
    return 0;
}
void IO_WORKS(){
    int fd, ret;
    char buffer[100];

    for(i=0;i<300000;i++){
        if ((fd = open("/etc/init.d/networking",O_RDONLY))<0) {
            perror("OPEN /etc/init.d/networking");
            exit();
            /* code */
        }
        do{
            ret = read(fd, buffer ,100);
        }while(ret);

        close(fd);
    }
}

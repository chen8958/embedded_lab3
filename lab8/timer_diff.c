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

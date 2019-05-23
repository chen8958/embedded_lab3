#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

sig_atomic_t sigusrl_count = 0;

void handler(int signal_number){
    ++sigusrl_count;
}
int main(int argc, char const *argv[]) {
    struct sigaction sa;
    struct timespec req;
    int retval;

    memset(&req, 0, sizeof(struct timespec));
    req.tv_sec = 10;
    req.tv_nsec =0;
    memset(&sa, 0,sizeof(sa));
    sa.sa_handler = handler;
    sigaction(SIGUSR1, &sa, NULL);
    printf("process (%d) is catching SIGUSR1....\n",getpid());

    do{
        retval = nanosleep(&req,&req);
    }while(retval);
    printf("SIGUSR1 was raised %d times\n",sigusrl_count);

    return 0;
}

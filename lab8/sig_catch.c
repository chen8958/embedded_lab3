#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void handler(int signo, siginfo_t *info, void *context){
    printf("process (%d) sent SIGUSR1.n",info->si_pid);

}
int main(int argc, char const *argv[]) {
    struct sigaction my_action;
    memset(&my_action, 0,sizeof(struct sigaction));
    my_action.sa_flags = SA_SIGINFO;
    my_action.sa_sigaction = handler;

    sigaction(SIGUSR1, &my_action,NULL);
    printf("process (%d) is catching SIGUSR1 .....\n",getpid());
    sleep(10);
    printf("done.\n");

    return 0;
}

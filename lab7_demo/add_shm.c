#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHMSZ 4

int main(int argc, char const *argv[]) {
    int shmid;
    key_t key;
    int *shm,*s;

    key = atoi(argv[1]);
    if ((shmid = shmget(key,SHMSZ,0666))<0) {
        perror("shmget");
        exit(1);
        /* code */
    }
    if ((shm = (int *)shmat(shmid,NULL,0))==(int *)-1) {
        perror("shmat");
        exit(1);
        /* code */
    }
    for(int i=0;i<atoi(argv[2]);i++){
        (*shm)++;
        printf("adding: %d\n",*shm);
    }

    printf("Client detach the share memory.\n");
    shmdt(shm);
    return 0;
}

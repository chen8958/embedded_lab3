#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHMSZ 4

int main(int argc, char const *argv[]) {

    if(argc!=2){
        printf("not enough argument\n");
        exit(0);
    }
    char c;
    int shmid;
    key_t key;
    int *shm, *s;
    int retval;
    key = atoi(argv[1]);


    if ((shmid = shmget(key, sizeof(int), IPC_CREAT| 0666)) < 0) {
        perror("shmget");
        exit(1);
        /* code */
    }
    if ((shm = (int *)shmat(shmid,NULL, 0)) == (int *) -1){
        perror("shmat");
        exit(1);
    }
    printf("create and attach the share memory\n");
    printf("detach share memory.(create_shm)\n");
    shmdt(shm);
    return 0;
}

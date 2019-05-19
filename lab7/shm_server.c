#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHMSZ 27

int main(int argc, char const *argv[]) {
    char c;
    int shmid;
    key_t key;
    char *shm, *s;
    int retval;
    key = 5678;

    if ((shmid = shmget(key, SHMSZ, IPC_CREAT| 0666)) < 0) {
        perror("shmget");
        exit(1);
        /* code */
    }
    if ((shm = (char *)shmat(shmid,NULL, 0)) == (char *) -1){
        perror("shmat");
        exit(1);
    }
    printf("Server create and attach the share memory\n");
    s = shm;

    printf("server write a ~ z tlo share memory\n");
    for (c = 'a'; c <= 'z'; c++) {
        *s++ = c;
        /* code */
    }
    *s = '\0';
    printf("waiting other process read the share memory ....\n");
    while (*shm != '*') {
        sleep(1);
        /* code */
    }
    printf("sever read * from the share memory.\n");
    shmdt(shm);
    printf("sever destroy the share memory.\n");
    retval = shmctl(shmid ,IPC_RMID,NULL);
    if (retval < 0) {
        fprintf(stderr, "Server remove share memory failed\n");
        exit(1);
        /* code */
    }
    return 0;
}

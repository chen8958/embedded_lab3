#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHMSZ 27

int main(int argc, char const *argv[]) {
    int shmid;
    key_t key;
    char *shm,*s;

    key=5678;
    if ((shmid = shmget(key,SHMSZ,0666))<0) {
        perror("shmget");
        exit(1);
        /* code */
    }
    if ((shm = (char *)shmat(shmid,NULL,0))==(char *)-1) {
        perror("shmat");
        exit(1);
        /* code */
    }
    printf("Client read characters from share memory....\n");
    for (s = shm; *s != '\0'; s++) {
        putchar(*s);
        /* code */
    }
    putchar('\n');
    printf("Client write * to the share memory.\n");
    *shm = '*';
    printf("Client detach the share memory.\n");
    shmdt(shm);
    return 0;
}

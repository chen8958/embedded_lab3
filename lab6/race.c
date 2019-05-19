#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define USE_SEM 1
#ifdef USE_SEM
#define SEM_MODE 0666
#define SEM_KEY 1122334455

int sem;

int P(int s){
    struct sembuf sop;
    sop.sem_num = 0;
    sop.sem_op = -1;
    sop.sem_flg = 0;

    if (semop(s,&sop,1) < 0) {
        fprintf(stderr, "P(): semop failed: %s\n",strerror(errno));
        return -1;
    }else{
        return 0;
    }
}

int V(int s){
    struct sembuf sop;
    sop.sem_num = 0;
    sop.sem_op = 1;
    sop.sem_flg = 0;

    if (semop(s,&sop,1) < 0) {
        fprintf(stderr, "V(): semop failed: %s\n",strerror(errno));
        return -1;
    }else{
        return 0;
    }
}
#endif

void Increment(){
    int ret;
    int fd;
    int counter;
    char buffer[100];
    int i = 10000;
    while(i){
        fd = open("./counter.txt",O_RDWR);
        if (fd < 0) {
            printf("Open counter.txt error\n");
            exit(-1);
            /* code */
        }


        #ifdef USE_SEM
            P(sem);
        #endif

        memset(buffer,0,100);
        ret = read(fd,buffer,100);
        if (ret < 0) {
            perror("read counter.txt");
            exit(-1);
        }
        counter = atoi(buffer);
        counter++;

        lseek(fd, 0,SEEK_SET);

        memset(buffer,0,100);
        sprintf(buffer,"%d",counter);
        ret = write(fd ,buffer,strlen(buffer));
        if(ret < 0){
            perror("write counter.txt");
            exit(-1);
        }
        #ifdef USE_SEM
            V(sem);
            #endif

            close(fd);
            i--;
        }
}
int main(int argc, char const *argv[]) {
    int childpid;
    int status;
#ifdef USE_SEM
    sem = semget(SEM_KEY,1,IPC_CREAT|IPC_EXCL|SEM_MODE);
    if(sem < 0){
        fprintf(stderr, "Creation of semaphore %d failed: %s\n",
            SEM_KEY,strerror(errno));
        exit(-1);
    }

    if(semctl(sem,0,SETVAL,1)<0){
        fprintf(stderr, "Unable to initialize semaphore: %s\n",
            strerror(errno));
        exit(0);
    }
    printf("Semaphore %d has been created & initialized to 1\n",
        SEM_KEY);
#endif
    if ((childpid = fork()) > 0) {
        Increment();
        waitpid(childpid,&status,0);
        /* code */
    }else if(childpid == 0){
        Increment();
        exit(0);
    }else{
        perror("fork");
        exit(-1);
    }
#ifdef USE_SEM
    if (semctl(sem,0,IPC_RMID,0) < 0) {
        fprintf(stderr, "%s: unable to remove semaphore %d\n",
            argv[0],SEM_KEY);
        exit(1);
    }
    printf("Semaphore %d has been remove\n", SEM_KEY);
#endif
    return 0;
}

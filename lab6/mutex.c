#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define checkResults(string,val){
    if(val){
        printf("Failed with %d at %s",val ,string);
        exit(1);
    }
#define NUMTHREADS 3
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int shareData = 0;
int shareData2 = 0;
void *theThread(void *parm){
    int rc;
    printf("\t Thread %lu : Entered \n",(unsigned long) pthread_self());

    rc = pthread_mutex_lock(&mutex);
    
}


}

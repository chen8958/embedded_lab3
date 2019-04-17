#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>
int main(int argc, char const *argv[]) {
    int fd;
	if((fd = open(argv[1], O_RDWR)) < 0) {
		printf("Error open %s\n",argv[1]);
		exit(-1);
	}
    char buf1[8],buf2[8];
    int n;
    scanf("%s",buf1);
    printf("catch is = %s\n",buf1);
    printf("original buf2 = %s\n",buf2);
    n=write(fd,buf1,7);
    printf("n = %d\n",n);
    n=read(fd,buf2,7);
    printf("n = %d\n",n);
    printf("read is = %s\n",buf2);
    return 0;
}

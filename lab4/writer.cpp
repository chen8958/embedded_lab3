#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>
static char map[16] = {
0b1111110, // 0
0b0110000, // 1
0b1101101, // 2
0b1111001, // 3
0b0110011, // 4
0b1011011, // 5
0b1011111, // 6
0b1110000, // 7
0b1111111, // 8
0b1111011, // 9
0b1110111, // A,a
0b0011111, // B,b
0b1001110, // C,c
0b0111101, // D,d
0b1001111, // E,e
0b1000111 // F,f
};
int main(int argc, char const *argv[]) {
    int fd;
	if((fd = open("/dev/mydev", O_RDWR)) < 0) {
		printf("Error open %s\n","mydev");
		exit(-1);
	}
    char ptr[7];
    printf("catch is = %s\n",argv[1]);
    for(int i=0;i < strlen(argv[1]);i++){
        switch (argv[1][i]) {
            case '1':
            ptr[0]=0;
            ptr[1]=1;
            ptr[2]=1;
            ptr[3]=0;
            ptr[4]=0;
            ptr[5]=0;
            ptr[6]=0;
            write(fd,ptr,7);
            break;
            case '2':
            ptr[0]=1;
            ptr[1]=1;
            ptr[2]=0;
            ptr[3]=1;
            ptr[4]=1;
            ptr[5]=0;
            ptr[6]=1;
            write(fd,ptr,7);
            break;
            case '3':
            ptr[0]=1;
            ptr[1]=1;
            ptr[2]=1;
            ptr[3]=1;
            ptr[4]=0;
            ptr[5]=0;
            ptr[6]=1;
            write(fd,ptr,7);
            break;
            case '4':
            ptr[0]=0;
            ptr[1]=1;
            ptr[2]=1;
            ptr[3]=0;
            ptr[4]=0;
            ptr[5]=1;
            ptr[6]=1;
            write(fd,ptr,7);
            break;
            case '5':
            ptr[0]=1;
            ptr[1]=0;
            ptr[2]=1;
            ptr[3]=1;
            ptr[4]=0;
            ptr[5]=1;
            ptr[6]=1;
            write(fd,ptr,7);
            break;
            case '6':
            ptr[0]=1;
            ptr[1]=0;
            ptr[2]=1;
            ptr[3]=1;
            ptr[4]=1;
            ptr[5]=1;
            ptr[6]=1;
            write(fd,ptr,7);
            break;
            case '7':
            ptr[0]=1;
            ptr[1]=1;
            ptr[2]=1;
            ptr[3]=0;
            ptr[4]=0;
            ptr[5]=0;
            ptr[6]=0;
            write(fd,ptr,7);
            break;
            case '8':
            ptr[0]=1;
            ptr[1]=1;
            ptr[2]=1;
            ptr[3]=1;
            ptr[4]=1;
            ptr[5]=1;
            ptr[6]=1;
            write(fd,ptr,7);
            break;
            case '9':
            ptr[0]=1;
            ptr[1]=1;
            ptr[2]=1;
            ptr[3]=1;
            ptr[4]=0;
            ptr[5]=1;
            ptr[6]=1;
            write(fd,ptr,7);
            break;
            case 'a':
            ptr[0]=1;
            ptr[1]=1;
            ptr[2]=1;
            ptr[3]=0;
            ptr[4]=1;
            ptr[5]=1;
            ptr[6]=1;
            write(fd,ptr,7);
            break;
            case 'b':
            ptr[0]=0;
            ptr[1]=0;
            ptr[2]=1;
            ptr[3]=1;
            ptr[4]=1;
            ptr[5]=1;
            ptr[6]=1;
            write(fd,ptr,7);
            break;
            case 'c':
            ptr[0]=1;
            ptr[1]=0;
            ptr[2]=0;
            ptr[3]=1;
            ptr[4]=1;
            ptr[5]=1;
            ptr[6]=0;
            write(fd,ptr,7);
            break;
            case 'd':
            ptr[0]=0;
            ptr[1]=1;
            ptr[2]=1;
            ptr[3]=1;
            ptr[4]=1;
            ptr[5]=0;
            ptr[6]=1;
            write(fd,ptr,7);
            break;
            case 'e':
            ptr[0]=1;
            ptr[1]=0;
            ptr[2]=0;
            ptr[3]=1;
            ptr[4]=1;
            ptr[5]=1;
            ptr[6]=1;
            write(fd,ptr,7);
            break;
            case 'f':
            ptr[0]=1;
            ptr[1]=0;
            ptr[2]=0;
            ptr[3]=0;
            ptr[4]=1;
            ptr[5]=1;
            ptr[6]=1;
            write(fd,ptr,7);
            break;
            case '0':
            ptr[0]=1;
            ptr[1]=1;
            ptr[2]=1;
            ptr[3]=1;
            ptr[4]=1;
            ptr[5]=1;
            ptr[6]=0;
            write(fd,ptr,7);
            break;
        }
        sleep(3);
    }
    return 0;
}

/*
*	echod.c
*/
#include "sockop.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <time.h>
#include "asm-arm/arch-pxa/lib/creator_pxa270_lcd.h"
#define BUFSIZE	1024
using namespace std;
time_t before_buy_time,after_buy_time;
clock_t start,end;
int fd ,ret ;
_7seg_info_t  data;
unsigned short  key;
lcd_write_info_t display;

int sockfd, connfd; /* socket descriptor */
struct sockaddr_in addr_cln;
socklen_t sLen = sizeof(addr_cln);
const char* port = "8888";


void split(char **command,int order_num,char *command_oneline){
    for(int i=0;i < order_num;i++){
        if(i == 0){
            command[i] = strtok(command_oneline," ");
        }
        else{
            command[i] = strtok(NULL," ");
        }
        printf("command[%d] = %s\n",i,command[i]);
    }
    printf("done split\n");
}

string input(){
    string buf;
    //ioctl(fd, KEY_IOCTL_CLEAR, key);
    while (1) {
      ret = ioctl(fd, KEY_IOCTL_CHECK_EMTPY, &key);
      if (ret < 0) {
        sleep(1);
        continue;
      }
      ret = ioctl(fd, KEY_IOCTL_GET_CHAR, &key);
      printf("%c\n",(key & 0xff));
      //ioctl(fd,LCD_IOCTL_CLEAR,NULL);
      display.Count =sprintf((char*)display.Msg, "%c",(key & 0xff));
      ioctl(fd,LCD_IOCTL_WRITE,&display);
      if ((key & 0xff) == '#') {
        break;
      }
      buf+=(key & 0xff);
    }
    return buf;
}
class limit{
private:
    string stadium;
    vector<int> seat_num;
    vector<char> seat_kind;
public:
    string get_stadium(){return stadium;}
    int get_seat_num(int n){return seat_num[n];}
    char get_seat_kind(int n){return seat_kind[n];}
    int get_size(){return seat_kind.size();}
    void add_seat_num(int );
    void add_seat_kind(char );
    void set_stadium(string );
    void print(){
        printf("%s\n",stadium.c_str());
        for (int i=0;i<seat_num.size();i++){
            printf("%c lefts %d \n",seat_kind[i],seat_num[i]);
        }

    }
};
void limit::set_stadium(string str){
    stadium = str;
}
void limit::add_seat_num(int a){
    seat_num.push_back(a);
}
void limit::add_seat_kind(char a){
    seat_kind.push_back(a);
}
class console{
private:
    vector<int> seat_num;
    vector<char> seat_kind;
    string stadium;
    string concert;
public:
    //console();
    string get_stadium(){return stadium;}
    void set_concert(string );
    void buy(char ,int);
    void set_stadium(string );
    void pass();
    void add_seat_num(int );
    void add_seat_kind(char );
    void print();
    void select(char &,int &);
    void check(limit );
    void operation(char *,string &);
    string printsocket();
    void recipt(char , int ,string &);
};
void console::recipt(char seat,int num,string &sndbuf){
    int n;
    tm *tmptr_after;
    static char snd[BUFSIZE];
    //string sndbuf;
    for(int i=0;i<num;i++){
        after_buy_time = time(NULL);
        tmptr_after = localtime(&after_buy_time);
        n = sprintf(snd, "%s %c %d %d:%d:%d\n", concert.c_str(),seat,i,tmptr_after->tm_hour,tmptr_after->tm_min,tmptr_after->tm_sec);
        sndbuf.append(snd);
    }
    //if ((n = write(*connfd, sndbuf.c_str(), sndbuf.length())) == -1)
    //    errexit("Error: write()\n");
}
string console::printsocket(){
    string buf;
    char oneline[100];
    buf.append(this->concert.c_str());
    buf.append("\n");
    for (int i=0;i<seat_num.size();i++){
        sprintf(oneline,"%c lefts %d \n",seat_kind[i],seat_num[i]);
        buf.append(oneline);
    }
    return buf;
}
void console::operation(char *s ,string &bufsnd){
    char seat;
    int num;
    char *buf;
    buf = strtok(s,"/");
    seat= strtok(NULL,"/")[0];
    num = atoi(strtok(NULL,"/"));
    this->buy(seat,num);
    this->recipt(seat,num,bufsnd);
}
void console::select(char &seat,int &num){
    this->print();
    printf("seat is = \n");
    display.Count =sprintf((char*)display.Msg, "seat is = \n");
    ioctl(fd,LCD_IOCTL_WRITE,&display);
    //scanf(" %c",&seat);
    seat = atoi(input().c_str())+'A'-1;
    printf("num is = \n");
    display.Count =sprintf((char*)display.Msg, "num is = \n");
    ioctl(fd,LCD_IOCTL_WRITE,&display);
    //scanf("%d",&num);
    num=atoi(input().c_str());
    //this->buy(seat,num);
}
void console::set_concert(string str){
    concert = str;
}
void console::set_stadium(string str){
    stadium = str;
}
void console::print(){
    int row = 0;
    ioctl(fd,LCD_IOCTL_CLEAR,NULL);
    printf("%s :\n",concert.c_str());
    display.Count =sprintf((char*)display.Msg, "%s :\n",concert.c_str());
    ioctl(fd,LCD_IOCTL_WRITE,&display);
    for (int i=0;i<seat_num.size();i++){
        printf("%c lefts %d \n",seat_kind[i],seat_num[i]);
        display.Count =sprintf((char*)display.Msg, "%c lefts %d \n",seat_kind[i],seat_num[i]);
        ioctl(fd,LCD_IOCTL_WRITE,&display);
    }

}
void console::add_seat_num(int a){
    seat_num.push_back(a);
}
void console::add_seat_kind(char a){
    seat_kind.push_back(a);
}
void console::check(limit a){
    for(int i=0;i<seat_kind.size();i++){
        for(int j=0;j<a.get_size();j++){
            if(seat_kind[i] == a.get_seat_kind(j)){
                printf("check done concert = %s \nconsole std = %s  con std = %s \nconcert = %c console = %c c\noncert_num = %d console_num = %d\n",concert.c_str(),a.get_stadium().c_str(),stadium.c_str(),seat_kind[i],a.get_seat_kind(j),seat_num[i],a.get_seat_num(j));
                if(a.get_seat_num(j) < seat_num[i]){
                    printf("ilegal!!");
                    printf("limit = %d < concert = %d",a.get_seat_num(j),seat_num[i]);
                    printf("do check %s %s %c %c\n",concert.c_str(),stadium.c_str(),a.get_seat_kind(j),seat_kind[i]);
                    exit(-1);
                }
            }

        }
    }
}
void console::buy(char seat,int num){
    unsigned short led_data = 0;
    ioctl(fd, LED_IOCTL_SET, &led_data);
    printf("char = %c num = %d \n",seat,num);
    start = clock();
    before_buy_time = time(NULL);
    tm *tmptr_before = localtime(&before_buy_time);
    for(int i=0;i<seat_kind.size();i++){
        if(seat_kind[i]==seat){
            seat_num[i]=seat_num[i]-num;
        }
    }
    after_buy_time = time(NULL);
    tm *tmptr_after = localtime(&after_buy_time);
    for(int i=0;i<num;i++){
        led_data=led_data<<1;
        led_data=led_data+1;
        printf("i = %d led_data = %d\n",i,led_data);
        after_buy_time = time(NULL);
        tmptr_after = localtime(&after_buy_time);
        cout<<this->concert<<" "<<seat<<" "<<i<<" "<<tmptr_after->tm_hour<<':'<<tmptr_after->tm_min<<':'<<tmptr_after->tm_sec<<endl;
        display.Count =sprintf((char*)display.Msg, "%s %c %d %d:%d:%d\n",this->concert.c_str(),seat,i,tmptr_after->tm_hour,tmptr_after->tm_min,tmptr_after->tm_sec);
        ioctl(fd,LCD_IOCTL_WRITE,&display);
    }
    printf(" %d \n",led_data);
    end = clock();
    ioctl(fd, _7SEG_IOCTL_ON, NULL);
    data.Mode = _7SEG_MODE_HEX_VALUE;
    data.Which= _7SEG_ALL;
    printf("CLOCKS = %d \n",(end - start));
    printf("sec = %d\n",(end - start)/100000);
    data.Value= (end - start)/100000;
    ioctl(fd, _7SEG_IOCTL_SET, &data);
    ioctl(fd, LED_IOCTL_SET, &led_data);
    sleep(3);

}
void console::pass(){
    printf("con pass\n");
}
void operation(char **command,console *con,int order_num, int *connfd){
    string buf;
    int n;
    for(int i=0;i < order_num;i++){
        con[command[i][3]-'0'-1].operation(command[i],buf);
    }
    printf("buf = %s\n",buf.c_str());
    if ((n = write(*connfd, buf.c_str(), buf.length())) == -1)
        errexit("Error: write()\n");
}
void order_num_from_client(int *order_num,int count ,console *con){
    printf("start to order_num_from_client\n");

	int n;
	static char snd[BUFSIZE], rcv[BUFSIZE];
	while(1)
	{
        string sndbuf;
        printf("start to wait connection while\n");
		/* wait for connection */
		connfd = accept(sockfd, (struct sockaddr *) &addr_cln, &sLen);
		if (connfd == -1)
			errexit("Error: accept()\n");
		/* read message from client */
        printf("start to read \n");
		if ((n = read(connfd, rcv, BUFSIZE)) == -1)
			errexit("Error: read()\n");
        sprintf(snd, "%.*s", n ,rcv);
        printf("get messeage = %s",snd);
        *order_num = atoi(snd);
        printf("start to print detail\n");
        for(int i = 0;i < count; i++){
            printf("chunk = \n %s\n", con[i].printsocket().c_str());
            n = sprintf(snd, "%s", con[i].printsocket().c_str());
            sndbuf.append(snd);
        }
        if ((n = write(connfd, sndbuf.c_str(), sndbuf.length())) == -1)
            errexit("Error: write()\n");
		close(connfd);
        break;
	}
	/* close server socket */
	//close(sockfd);
}
void command_from_client(char **command,int order_num,console *con){
    printf("start to command form client\n");
	//int sockfd, connfd; /* socket descriptor */
	//struct sockaddr_in addr_cln;
	//socklen_t sLen = sizeof(addr_cln);
	int n;
	static char snd[BUFSIZE], rcv[BUFSIZE];
    //const char* port = "8888";

	/* create socket and bind socket to port */
	//sockfd = passivesock(port, "tcp",10);
	while(1)
	{
        printf("start to wait connection while\n");
		/* wait for connection */
		connfd = accept(sockfd, (struct sockaddr *) &addr_cln, &sLen);
		if (connfd == -1)
			errexit("Error: accept()\n");
		/* read message from client */
		if ((n = read(connfd, rcv, BUFSIZE)) == -1)
			errexit("Error: read()\n");
        sprintf(snd, "%.*s", n ,rcv);
        split(command,order_num,snd);
        operation(command,con,order_num,&connfd);
		close(connfd);
        break;
	}
	/* close server socket */
	//close(sockfd);
}
int main(int argc, char const *argv[]) {
    sockfd = passivesock(port,"tcp",10);
    if((fd = open("/dev/lcd",O_RDWR)) < 0){
      printf("Open /dev/lcd_faild.\n");
      exit(-1);
    }
    ioctl(fd,LCD_IOCTL_CLEAR,NULL);
    ifstream fin(argv[2]);
    string s;
    fin >> s;
    int count = atoi(s.c_str());
    console *con;
    con = new console [count];
    for (int i=0;i<count;i++){
        fin >> s;
        con[i].set_concert(s);
        fin >> s;
        con[i].set_stadium(s);
        while(fin.peek() != '\n'){
            fin >> s;
            con[i].add_seat_kind(s[0]);
            fin >> s;
            con[i].add_seat_num(atoi(s.c_str()));
        }

    }
    printf("read consert done\n");
    ifstream fin2(argv[1]);
    fin2 >> s;
    int count2 = atoi(s.c_str());
    printf("count2 = %d\n",count2);
    limit *std;
    std = new limit [count2];
    for (int i=0;i<count2;i++){
        fin2 >> s;
        std[i].set_stadium(s);
        while(fin2.peek() != '\n'){
            fin2 >> s;
            std[i].add_seat_kind(s[0]);
            fin2 >> s;
            std[i].add_seat_num(atoi(s.c_str()));
        }
    }
    for(int i=0;i<count;i++){
        for(int j=0;j<count2;j++){
            if (con[i].get_stadium().compare(std[j].get_stadium())==0){
                printf("con std= %s limit std = %s\n",con[i].get_stadium().c_str(),std[j].get_stadium().c_str());
                con[i].check(std[j]);
            }
        }
    }
    char **command;
    char command_oneline[100];
    char *p;
    int order_num;
    while(1){
        ioctl(fd,LCD_IOCTL_CLEAR,NULL);
        printf("order = \n");
        //scanf("%d",&order_num);
        order_num_from_client(&order_num,count,con);
        command = new char*[order_num];
        for(int i = 0;i < count; i++){
            printf("con%d\n",i+1);
            con[i].print();
        }
        printf("command = ");
        command_from_client(command,order_num,con);

    }
    return 0;
}

#include "sockop.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <pthread.h>
#include <time.h>
#include <sys/sem.h>
#include <errno.h>
#define BUFSIZE	1024
int semaphore;
int con_count;
long int key;
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
using namespace std;
time_t before_buy_time,after_buy_time;
int OrderCustomer = 0;
int count;//con number
struct ClientData{
    int OrderCustomer;
    int new_client_socket;
};
struct oneSectionCommand{
    int conOrder;
    char seatKind;
    int seatNum;
};
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
        //printf("%s\n",stadium.c_str());
        for (int i=0;i<seat_num.size();i++){
        //    printf("%c lefts %d \n",seat_kind[i],seat_num[i]);
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
    vector<int> seat_id;
    string stadium;
    string concert;
public:
    //console();
    string get_stadium(){return stadium;}
    void set_concert(string );
    void set_stadium(string );
    void add_seat_num(int );
    void add_seat_kind(char );
    void add_seat_id(){
        seat_id.push_back(0);
    }
    void check(limit );
    string detail();
    bool isSeatExist(oneSectionCommand &);
    bool isSeatEnough(oneSectionCommand &);
    int index(char);
    void buyone(char);
    string buy(oneSectionCommand &);
};
console *con;
void console::buyone(char seat){
    seat_num[index(seat)]--;
}
string console::buy(oneSectionCommand &orderOnesection){
    string buf;
    char oneline[BUFSIZE];
    tm *tmptr_before = localtime(&before_buy_time);
    tm *tmptr_after;
    for(int i=0;i<orderOnesection.seatNum;i++){
        after_buy_time = time(NULL);
        tmptr_after = localtime(&after_buy_time);
        sprintf(oneline,"%s %c %c%d %d\n",concert.c_str(),orderOnesection.seatKind,orderOnesection.seatKind,seat_id[index(orderOnesection.seatKind)]++,tmptr_after->tm_sec-tmptr_before->tm_sec);
        buf.append(oneline);
        buyone(orderOnesection.seatKind);
    }
    return buf;
}
int console::index(char seat){
    for(int i=0;i<seat_num.size();i++){
        if(seat_kind[i]==seat){
            return i;
        }
    }
}
bool console::isSeatEnough(oneSectionCommand &buf){
    if(seat_num[index(buf.seatKind)]>=buf.seatNum){
        return 1;
    }
    else{
        return 0;
    }
}


bool console::isSeatExist(oneSectionCommand &buf){
    for(int i=0;i<seat_num.size();i++){
        if(seat_kind[i]==buf.seatKind){
            return 1;
        }
    }
    return 0;
}

string console::detail(){
    //printf("in console::detail\n");
    string buf;
    char getlinebuf[BUFSIZE];
    sprintf(getlinebuf,"%s",concert.c_str());
    buf.append(getlinebuf);
    for(int i=0; i<seat_num.size();i++){
        sprintf(getlinebuf," %c %d",seat_kind[i],seat_num[i]);
        buf.append(getlinebuf);
    }
    buf.append("\n");
    return buf;
}
void console::set_concert(string str){
    concert = str;
}
void console::set_stadium(string str){
    stadium = str;
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
                //printf("check done concert = %s \nconsole std = %s  con std = %s \nconcert = %c console = %c \nconcert_num = %d console_num = %d\n",concert.c_str(),a.get_stadium().c_str(),stadium.c_str(),seat_kind[i],a.get_seat_kind(j),seat_num[i],a.get_seat_num(j));
                if(a.get_seat_num(j) < seat_num[i]){
                    //printf("ilegal!!");
                    //printf("limit = %d < concert = %d",a.get_seat_num(j),seat_num[i]);
                    //printf("do check %s %s %c %c\n",concert.c_str(),stadium.c_str(),a.get_seat_kind(j),seat_kind[i]);
                    exit(-1);
                }
            }

        }
    }
}

oneSectionCommand split(string &command){
    //cout<<"do spilt "<<command<<endl;
    oneSectionCommand buf;
    stringstream processSection(command.c_str());
    string token;
    getline(processSection,token,'/');
    buf.conOrder = token.c_str()[3]-'0'-1;
    getline(processSection,token,'/');
    buf.seatKind = token.c_str()[0];
    getline(processSection,token,'/');
    buf.seatNum = atoi(token.c_str());
    //cout<<"conorder = "<<buf.conOrder<<" seatkind = "<<buf.seatKind<<" seatNum = "<<buf.seatNum<<endl;
    return buf;
}

string show(string &targetCon){
    char buf[BUFSIZE];
    if(targetCon.c_str()[3]-'0'<=count){
        return con[targetCon.c_str()[3]-'0'-1].detail();
    }
    else if(targetCon.c_str()[0]=='c'){
        sprintf(buf,"con%d not found\n",targetCon.c_str()[3]-'0');
        return buf;
    }
    else{
        sprintf(buf,"%s not found\n",targetCon.c_str());
        return buf;
    }

}

string showall(){
    string allinformation;
    for(int i=0;i<count;i++){
        allinformation.append(con[i].detail());
    }
    return allinformation;
}
bool isSeatEnough(stringstream &orderSheet){
    //printf("do seatenough\n");
    string processSection;
    oneSectionCommand buf,prebuf;
    while(!orderSheet.eof()){
        orderSheet>>processSection;
        buf = split(processSection);
        if(prebuf.conOrder==buf.conOrder&&prebuf.seatKind==buf.seatKind){
            buf.seatNum=buf.seatNum+prebuf.seatNum;
        }
        if(!con[buf.conOrder].isSeatEnough(buf)){
            //out<<"con"<<buf.conOrder<<" seat "<<buf.seatKind<<" num= "<<buf.seatNum<<endl;
            return 0;
        }
        prebuf.conOrder=buf.conOrder;
        prebuf.seatKind=buf.seatKind;
        prebuf.seatNum=buf.seatNum;
    }
    return 1;
}
bool isSeatExist(stringstream &orderSheet){
    //printf("do seatexist\n");
    string processSection;
    oneSectionCommand buf;
    while(!orderSheet.eof()){
        orderSheet>>processSection;
        buf = split(processSection);
        /*
        if(buf.conOrder >= con_count){
            return 0;
        }
        */
        if(!con[buf.conOrder].isSeatExist(buf)){
            return 0;
        }

    }
    return 1;
}
bool isConExist(stringstream &orderSheet){
    //printf("do conexist\n");
    string processSection;
    oneSectionCommand buf;
    while(!orderSheet.eof()){
        orderSheet>>processSection;
        buf = split(processSection);
        if(buf.conOrder >= con_count){
            return 0;
        }
        /*
        if(!con[buf.conOrder].isSeatExist(buf)){
            return 0;
        }
        */
    }
    return 1;
}
int findnotExistCon(stringstream &orderSheet){
    //printf("find findnotExistCon\n");
    string processSection;
    oneSectionCommand buf;
    while(!orderSheet.eof()){
        orderSheet>>processSection;
        buf = split(processSection);
        if(buf.conOrder >= con_count){
            return buf.conOrder+1;
        }
    }
}
string findnotExistseat(stringstream &orderSheet){
    string processSection;
    oneSectionCommand buf;
    while(!orderSheet.eof()){
        orderSheet>>processSection;
        buf = split(processSection);
        if(!con[buf.conOrder].isSeatExist(buf)){
            char exceptinformation[BUFSIZE];
            sprintf(exceptinformation,"con%d does not have %c ticket\n",buf.conOrder+1,buf.seatKind);
            return exceptinformation;
        }
    }
}
string orderTicket(stringstream &orderSheet){
    string processSection;
    oneSectionCommand buf;
    string recipt;
    //cout<<"do orderTicket\n";
    while(!orderSheet.eof()){
        orderSheet>>processSection;
        buf = split(processSection);
        recipt.append(con[buf.conOrder].buy(buf));
    }
    //cout<<"done orderTicket\n";
    return recipt;
}
string commandRecognize(stringstream &command,int &connfd){
    string commandFirstsection,commandSecondsection;
    command>>commandFirstsection;
    char buf[BUFSIZE];
    //command.seekg(0);
    if(commandFirstsection=="exit"){
        //cout<<"do exit"<<endl;
        close(connfd);

        pthread_exit(NULL);
    }
    else if(commandFirstsection=="showall"){
        //cout<<"do showall"<<endl;
        return showall();
    }
    else if(commandFirstsection=="show"){
        //cout<<"do show"<<endl;
        command>>commandSecondsection;
        return show(commandSecondsection);
    }
    else if(commandFirstsection.c_str()[0]=='c'){
        V(semaphore);
        //cout<<"do check ticket "<<endl;
        command.seekg(0);
        if(!isConExist(command)){
            command.seekg(0);
            sprintf(buf,"con%d not found\n",findnotExistCon(command));
            P(semaphore);
            return buf;
        }
        /*
        if(commandFirstsection.c_str()[3]-'0'>count){
            sprintf(buf,"con%d not found\n",commandFirstsection.c_str()[3]-'0');
            return buf;
        }
        */
        command.seekg(0);
        if(!isSeatExist(command)){
            command.seekg(0);
            P(semaphore);
            return findnotExistseat(command);
        }
        command.seekg(0);
        if(!isSeatEnough(command)){
            P(semaphore);
            return "sorry, remaining ticket number not enough\n";
        }
        command.seekg(0);
        P(semaphore);
        return orderTicket(command);
    }
    else{
        sprintf(buf,"%s not found\n",command.str().c_str());
        return buf;
    }
}





void *handleRequest(void *ClientDataPtr){
    stringstream command;
    struct ClientData new_client_socket =*(ClientData*)ClientDataPtr;
    int MessageLength;
    char ReceiveMessage[BUFSIZE*10],SendMessage[BUFSIZE*10];

    //printf("accept client order : %d \n",new_client_socket.OrderCustomer);

    while(1){

        if ((MessageLength = read(new_client_socket.new_client_socket, ReceiveMessage, BUFSIZE)) == -1)
            pthread_exit(NULL);
    /* write message back to client */
        //printf("from no. %d client message = %.*s\n",new_client_socket.OrderCustomer,MessageLength,ReceiveMessage);
        command.str(ReceiveMessage);
        before_buy_time = time(NULL);

        //MessageLength = sprintf(SendMessage, "from no. %d client message = %.*s\n",new_client_socket.OrderCustomer,MessageLength,ReceiveMessage);
        MessageLength = sprintf(SendMessage, "%s",commandRecognize(command,new_client_socket.new_client_socket).c_str());
        //printf("done message = %s\n",commandRecognize(command).c_str());
        //printf("send message = %s\n",SendMessage);

        if ((MessageLength = write(new_client_socket.new_client_socket, SendMessage, MessageLength)) == -1)
            pthread_exit(NULL);
        command.clear();
        memset(SendMessage, 0, BUFSIZE);
        memset(ReceiveMessage, 0, BUFSIZE);
    }
}

int main(int argc, char const *argv[]) {
    ifstream fin(argv[1]);
    string s;
    fin >> s;
    count = atoi(s.c_str());
    con_count=count;
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
            con[i].add_seat_id();
        }

    }
    //printf("read consert done\n");
    ifstream fin2(argv[2]);
    fin2 >> s;
    int count2 = atoi(s.c_str());
    //printf("count2 = %d\n",count2);
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
    //printf("read console done\n");
    for(int i=0;i<count;i++){
        for(int j=0;j<count2;j++){
            if (con[i].get_stadium().compare(std[j].get_stadium())==0){
                //printf("con std= %s limit std = %s\n",con[i].get_stadium().c_str(),std[j].get_stadium().c_str());
                con[i].check(std[j]);
            }
        }
    }
    printf("check done\n");
    int sockfd, new_client_socket; /* socket descriptor */
	struct sockaddr_in addr_cln;
	socklen_t sLen = sizeof(addr_cln);
	int n;
    pthread_t threads[10];
    struct ClientData server[10];
	char SendMessage[BUFSIZE], ReceiveMessage[BUFSIZE];


    if (sscanf(argv[4],"%ld",&key)!=1) {
        fprintf(stderr, "%s: argument #1 must be an long integer\n",
            argv[0]);
        exit(1);
    }
    semaphore=semget(key,1,0);
    if (semaphore<0) {
        fprintf(stderr, "%s: cannot find semaphore %ld: %s\n",
            argv[0],key,strerror(errno));
        exit(1);
    }


	if (argc != 5)
		errexit("Usage: %s port\n", argv[0]);
	/* create socket and bind socket to port */
	sockfd = passivesock(argv[3], "tcp",10);
	while(1){
		/* wait for connection */
		new_client_socket = accept(sockfd, (struct sockaddr *) &addr_cln, &sLen);
		if (new_client_socket == -1)
			errexit("Error: accept()\n");
        server[OrderCustomer].OrderCustomer=OrderCustomer;
        server[OrderCustomer].new_client_socket=new_client_socket;
        pthread_create(&threads[OrderCustomer],NULL,handleRequest,&server[OrderCustomer]);
        OrderCustomer++;
	}
	/* close server socket */
	close(sockfd);
	return 0;



    return 0;
}

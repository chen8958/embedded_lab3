#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <time.h>
using namespace std;
/*system time*/
time_t my_time;
class console{
private:
    vector<int> seat_num;
    vector<char> seat_kind;
    string stadium;
    string concert;
public:
    console();
    void set_concert(string );
    void buy(char ,int);
    void set_stadium(string );
    void pass();
    void add_seat_num(int );
    void add_seat_kind(char );
    void print();
};
void console::set_concert(string str){
    concert = str;
}
void console::set_stadium(string str){
    stadium = str;
}
console::console(){
    concert="hello";
}
void console::print(){
    printf("%s :\n",concert.c_str());
    for (int i=0;i<seat_num.size();i++){
        printf("%c lefts %d \n",seat_kind[i],seat_num[i]);
    }

}
void console::add_seat_num(int a){
    seat_num.push_back(a);
}
void console::add_seat_kind(char a){
    seat_kind.push_back(a);
}
void console::buy(char seat,int num){
    printf("char = %c num = %d \n",seat,num);
    for(int i=0;i<seat_kind.size();i++){
        if(seat_kind[i]==seat){
            seat_num[i]=seat_num[i]-num;
        }
    }
    my_time = time(NULL);
    tm *tmptr = localtime(&my_time);
    for(int i=0;i<num;i++){
        cout<<this->concert<<" "<<seat<<" "<<i<<" "<<tmptr->tm_hour<<':'<<tmptr->tm_min<<':'<<tmptr->tm_sec<<endl;
    }
}
void console::pass(){
    printf("con pass\n");
}
/*
console::console(char *s){
    concert=*s;

}
*/

int main(int argc, char const *argv[]) {
    /*read header*/
    ifstream fin("concert.txt");
    string s;
    char input[10];
    fin >> s;
    int count = stoi(s);
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
            con[i].add_seat_num(stoi(s));
        }

    }
    while(1){
        for(int i=0;i<count;i++){
            con[i].print();
        }
        scanf("%s",input);
        const char *sep = "/";
        char *get_con,*get_seat,*get_num;
        get_con = strtok(input, sep);
        get_seat = strtok(NULL, sep);
        get_num = strtok(NULL, sep);
        //printf("%s %s %s\n",get_con,get_seat,get_num);
        con[get_con[3]-'0'-1].buy(get_seat[0],atoi(get_num));
        con[get_con[3]-'0'-1].print();

    }
    //printf("%s",input);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
using namespace std;
class console{
private:
    vector<int> seat_num;
    vector<char> seat_kind;
    string stadium;
    string concert;
public:
    console();
    void set_concert(string );
    void buy();
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
    printf("do print \n");
    printf("%s ",concert.c_str());
    printf("%s ",stadium.c_str());
    for (int i=0;i<seat_num.size();i++){
        printf("%c %d ",seat_kind[i],seat_num[i]);
    }
    printf(" \n ");

}
void console::add_seat_num(int a){
    seat_num.push_back(a);
}
void console::add_seat_kind(char a){
    seat_kind.push_back(a);
}
void console::buy(){
    printf("con buy\n");
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
    for(int i=0;i<count;i++){
        con[i].print();
    }
    

    return 0;
}

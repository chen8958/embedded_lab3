#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
using namespace std;
class console{
private:
    vector<int> sit;
    char *concert;
public:
    //console();
    void buy();
    void pass();
    void add(int );
    void print(int );
};
void console::print(int n){
    for (int i = 0; i < n; i++) {
        /* code */
        printf("sit[i] = %d \n",sit[i]);
    }
    printf(" %s ",concert);

}
void console::add(int a){
    sit.push_back(a);
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

    console con1;
    con1.buy();
    con1.pass();
    con1.add(10);
    con1.add(5);
    con1.print(5);

    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;
int main(){
    ifstream fin("concert.txt");
    string s;
    string a;
    time_t my_time = time(NULL);
    char c;
    while( fin >> s ){
        a = s;
        cout << "Read from file: " << a << endl;
        c = fin.peek();
        cout << "Read from file: " << c << endl;
    }
    cout << ctime(&my_time);
}

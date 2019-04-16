#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(){
    ifstream fin("concert.txt");
    string s;
    string a;
    char c;
    while( fin >> s ){
        a = s;
        cout << "Read from file: " << a << endl;
        c = fin.peek();
        cout << "Read from file: " << c << endl;
    }
}

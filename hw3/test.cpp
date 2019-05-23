#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    stringstream ss;
    cout<<ss.str();
    string input,buf;
    getline(cin,input);
    ss<<input;
    ss>>buf;
    cout<<buf<<endl;
    cout<<ss.tellg()<<endl;
    ss.seekg(0);
    cout<<ss.tellg()<<endl;
    while(!ss.eof()){
        cout<< ss.tellg()<<endl;
        cout<<"ss = "<<ss.str()<<endl;
        ss>>buf;
        cout<<buf<<endl;
    }
    return 0;
}

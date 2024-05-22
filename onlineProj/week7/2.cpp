#include <string>
#include <iostream>
using namespace std;

int main(){
    string maxstr = "", str;
    while(cin){
        if(cin.get() == '\n') break;
        cin>>str;
        if(str.length() > maxstr.length()){
            maxstr = str;
        }
    }
    cout<<maxstr;
}
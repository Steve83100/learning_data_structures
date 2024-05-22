#include <string>
#include <iostream>
using namespace std;

int main(){
    string s;
    getline(cin, s);
    int len = s.length();
    int start = 0, end = len;
    while(true){
        if(s[start] != ' ') break;
        start++;
    }
    while(true){
        if(s[end-1] != ' ') break;
        end--;
    }
    cout<<s.substr(start, end-start);
}
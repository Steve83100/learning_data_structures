#include <string>
#include <iostream>
using namespace std;

int main(){
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    int len1 = s1.length();
    int len2 = s2.length();
    for(int i = 0; i <= len1 - len2; i++){
        string temp = s1.substr(i, len2);
        if(temp == s2){
            cout<<i;
            return 0;
        }
    }
    cout<<-1;
    return 0;
}
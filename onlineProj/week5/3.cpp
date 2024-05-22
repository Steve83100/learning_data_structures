#include <string>
#include <iostream>
#include <cmath>
using namespace std;

int str2int(string s){
    int num = 0;
    int len = s.length();
    for(int i = 0; i < len; i++){
        num += (s[len - i - 1] - '0') * pow(10, i);
    }
    return num;
}

int main(){
    string s1, s2;
    cin>>s1>>s2;
    cout << str2int(s1) + str2int(s2);
    return 0;
}
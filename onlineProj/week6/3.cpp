#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;
int str2num(string s){
    int len  = s.length(), num = 0;
    for(int i = 0; i < len; i++){
        num += (s[len - i - 1] - '0') * pow(10, i);
    }
    return num;
}

int numrev(int num){
    if(num >= 0){
        string s = to_string(num);
        reverse(s.begin(), s.end());
        int n = str2num(s);
        return n;
    }
    else{
        string s = to_string(-1 * num);
        reverse(s.begin(), s.end());
        int n = (-1) * str2num(s);
        return n;
    }
}

int main(){
    int sum, diff;
    cin>>sum>>diff;
    int num1 = (sum + diff) / 2;
    int num2 = (sum - diff) / 2;
    int ming_num1 = numrev(num1);
    int ming_num2 = numrev(num2);
    cout<<ming_num1 + ming_num2<<' '<<ming_num1 - ming_num2;
    return 0;
}

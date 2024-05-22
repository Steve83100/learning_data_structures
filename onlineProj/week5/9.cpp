#include <vector>
#include <iostream>
using namespace std;

vector<int> convert(int num, int base){ // 将数字num转化为base进制数字序列
    vector<int> s;
    if(num == 0){
        s.push_back(0);
    }
    while(num){
        s.insert(s.begin(), num % base);
        num /= base;
    }
    return s;
}

bool isPalin(vector<int> s){
    for(int i = 0; i <= s.size()/2; i++){
        if(s[i] != s[s.size() - i - 1]){
            return false;
        }
    }
    return true;
}

int main(){
    int num, base;
    cin>>num>>base;
    vector<int> s = convert(num, base);
    if(isPalin(s)) cout<<"Yes\n";
    else cout<<"No\n";
    cout<<s[0];
    for(int i = 1; i < s.size(); i++){
        cout<<' '<<s[i];
    }
}
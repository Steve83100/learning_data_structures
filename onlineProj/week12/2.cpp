#include <stack>
#include <string>
#include <iostream>
using namespace std;

int main(){
    string s;
    getline(cin, s);
    stack<char> q;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '(') q.push('(');
        if(s[i] == ')'){
            if(q.empty()){
                q.push(')');
                break;
            }
            else q.pop();
        }
    }
    if(q.empty()) cout<<"括号匹配！";
    else cout<<"括号不匹配！";
}
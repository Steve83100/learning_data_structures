#include <iostream>
#include <string>
using namespace std;

int main(){
    string s;
    cin>>s;
    int n = s.length(), n1 = 0, n2, n3 = 0;

    for(int _n1 = n/2; _n1 > 0; _n1--){
        if(_n1 <= (n - 2 * _n1 + 2)){  // 满足 n2 = n1 + 1（总数为奇数）或 n2 = n1 + 2（总数为偶数）为最优
            n1 = _n1;
            break;
        }
    }
    n2 = n - 2 * n1 + 2;
    string blank(n2 - 2,' ');

    for(int i = 0; i < n1 - 1; i++){
        cout<<s[i]<<blank<<s[n-i-1]<<endl;
    }
    cout<<s.substr(n1-1, n2);
}
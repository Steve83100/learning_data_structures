#include <iostream>
using namespace std;

int num5Factors(int num){ // 返回所含5因子的个数
    int fac = 0;
    while(num % 5 == 0){ // 如果该数能被5整除，说明有一个5因子
        num /= 5; // 将该5因子除去
        fac++; // 5因子个数+1
    }
    return fac;
}

int main(){
    int n, numZero = 0;
    cin>>n;
    while(n){
        numZero += num5Factors(n);
        n--;
    }
    cout<<numZero;
    return 0;
}
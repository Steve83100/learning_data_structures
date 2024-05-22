#include <iostream>
#include <ratio>
using namespace std;

int gcf(int a, int b){ // Assume that a < b
    if(a == 0) return b;
    else return gcf(b%a, a);
}

void reduce(int &a, int &b){
    int g = gcf(a, b);
    a /= g; b /= g;
}

int main(){
    int n, sum_num = 0, sum_den = 1, num, den;
    char c;
    cin>>n;
    for(int _ = 0; _ < n; _++){
        cin>>num>>c>>den;
        sum_num = sum_num * den + sum_den * num;
        sum_den *= den;
    }
    int sum_int = sum_num / sum_den;
    sum_num %= sum_den;
    reduce(sum_num, sum_den); // 此时分子已经小于分母
    if(sum_int != 0) cout<<sum_int;
    if(sum_int == 0 && sum_num != 0) cout<<sum_num<<'/'<<sum_den;
    else if(sum_int != 0 && sum_num != 0) cout<<' '<<sum_num<<'/'<<sum_den;
}
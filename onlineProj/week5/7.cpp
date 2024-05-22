#include <iostream>
using namespace std;

int main(){
    int n;
    cin>>n;
    bool isComp[10000] = {0};
    isComp[0] = 1;
    isComp[1] = 1;
    for(int i = 2; i < n; i++){
        if(!isComp[i]){
            for(int ki = 2 * i; ki < n; ki += i){
                isComp[ki] = true;
            }
        }
    }
    if(n>2) cout<<2;
    for(int i = 3; i < n; i++){
        if(!isComp[i]) cout<<' '<<i;
    }
}
#include <iostream>
using namespace std;

template <typename T>
T max(T num1, T num2, T num3){
    if(num1 > num2 && num1 > num3) return num1;
    else if(num2 > num3) return num2;
    else return num3;
}

int main(){
    int type;
    cin>>type;
    switch (type){
    case 1:{
        int n1, n2, n3;
        cin>>n1>>n2>>n3;
        cout<<max(n1,n2,n3);
        break;
    }
    case 2:{
        float n1, n2, n3;
        cin>>n1>>n2>>n3;
        cout<<max(n1,n2,n3);
        break;
    }
    case 3:{
        double n1, n2, n3;
        cin>>n1>>n2>>n3;
        cout<<max(n1,n2,n3);
        break;
    }
    }
    return 0;
}
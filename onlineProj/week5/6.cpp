#include <vector>
#include <iostream>
using namespace std;

vector<int> primeFactorize(int num){
    vector<int> factors;
    int fac = 2;
    while(fac <= num){
        if(num % fac == 0){
            factors.push_back(fac);
            num /= fac;
        }
        else{
            fac++;
        }
    }
    return factors;
}

int main(){
    int n1, n2;
    cin>>n1>>n2;
    vector<int> fac1 = primeFactorize(n1);
    vector<int> fac2 = primeFactorize(n2);

    // 对两数进行质因数分解后，将其质因数求并，其乘积即为最小公倍数
    int lcm = 1, p1 = 0, p2 = 0;
    while(p1 < fac1.size() && p2 < fac2.size()){
        if(fac1[p1] == fac2[p2]){
            lcm *= fac1[p1];
            p1++; p2++;
        }
        else if(fac1[p1] < fac2[p2]){
            lcm *= fac1[p1];
            p1++;
        }
        else{
            lcm *= fac2[p2];
            p2++;
        }
    }

    // 有一组质因数取完后，还要把另一组质因数剩下的也乘进去
    while (p1 < fac1.size()) {
        lcm *= fac1[p1];
        p1++;
    }
    while (p2 < fac2.size()) {
        lcm *= fac2[p2];
        p2++;
    }
    cout<<lcm;
}
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> a;
    for(int i = 1; i <= n; i++){
        a.push_back(i);
    }
    auto it = a.begin();
    while(true){
        it = a.begin();
        while(it+1 < a.end()){
            it = a.erase(it + 1);
        }
        if(a.size() <= 3) break;
        it = a.begin();
        while(it+2 < a.end()){
            it = a.erase(it + 2);
        }
        if(a.size() <= 3) break;
    }
    it = a.begin();
    cout<<*it;
    it++;
    while(it != a.end()){
        cout<<' '<<*it;
        it++;
    }
}
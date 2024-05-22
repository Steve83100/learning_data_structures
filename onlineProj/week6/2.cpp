#include <iostream>
using namespace std;
int main(){
    int currentLevel = 0, nextLevel, time = 0;
    while(true){
        cin>>nextLevel;
        if(nextLevel == 0) break;
        if(nextLevel > currentLevel){
            time += (6 * (nextLevel - currentLevel));
        }
        else{
            time += (4 * (currentLevel - nextLevel));
        }
        time += 5;
        currentLevel = nextLevel;
    }
    cout<<time;
}

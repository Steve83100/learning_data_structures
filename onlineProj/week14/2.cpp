#include <iostream>
#include <string>
#define maxStu 100
using namespace std;

struct Stu{
    string id;
    string name;
    int score;
};

int main(){
    int n;
    cin>>n;
    struct Stu stu[maxStu];
    for(int i = 0; i < n; i++){
        cin>>stu[i].id>>stu[i].name>>stu[i].score;
    }
    for(int i = 1; i < n; i++){
        int j;
        Stu temp = stu[i];
        for(j = i; j > 0; j--){
            if(stu[j].score > stu[j-1].score){
                stu[j] = stu[j-1];
            }
            else break;
        }
        stu[j] = temp;
    }
    
    for(int i = 0; i < n; i++){
        cout<<stu[i].id<<' '<<stu[i].name<<' '<<stu[i].score<<endl;
    }
}
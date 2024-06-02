#include <iostream>
using namespace std;

void BubbleSort(int a[], int n){
    int temp;
    for(int i = n-1; i > 0; i--){
        for(int j = 0; j < i; j++){
            if(a[j+1] < a[j]){
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}

void SelectionSort(int a[], int n){
    for(int i = 0; i < n; i++){
        int max = a[i], max_ind = i;
        for(int j = i; j < n; j++){
            if(a[j] > max){
                max = a[j];
                max_ind = j;
            }
        }
        a[max_ind] = a[i];
        a[i] = max;
    }
}

int main(){
    int a[10];
    for(int i = 0; i < 10; i++){
        cin>>a[i];
    }

    BubbleSort(a, 10);
    cout<<a[0];
    for(int i = 1; i < 10; i++){
        cout<<' '<<a[i];
    }

    SelectionSort(a, 10);
    cout<<endl<<a[0];
    for(int i = 1; i < 10; i++){
        cout<<' '<<a[i];
    }
}
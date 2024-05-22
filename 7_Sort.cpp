#include <iostream>
using namespace std;

template <typename Type>
void insertSort(Type nums[], int size){
    for(int i = 1; i < size; i++){
        Type currNum = nums[i];
        int j;
        for(j = i - 1; j >= 0; j--){ // 从后往前比较，保证稳定性，即相等元素不改变相对顺序
            if(currNum < nums[j]){ // j 仍然 > i，于是将其向后移动
                nums[j + 1] = nums[j];
            }
            else break; // j 已经 <= i，此时停止
        }
        // 不论是由于j <= i而跳出还是j = -1而终止，都应将 i 插入 j 后面
        nums[j + 1] = currNum;
    }
}

template <typename Type>
void bubbleSort(Type nums[], int size){
    Type temp;
    for(int i = 0; i < size; i++){
        for(int j = size - 1; j > i; j--){
            if(nums[j] < nums[j - 1]){
                temp = nums[j];
                nums[j] = nums[j - 1];
                nums[j - 1] = temp;
            }
        } // j 到达 i 后，i 就要成为 i 以后最小值
    }
}

template <typename Type>
void selectSort(Type nums[], int size){
    for(int i = 0; i < size; i++){
        Type min = nums[i]; // 这样设置每轮的最小值，即使 i 就是最小值，也能正确运行
        int min_ind = i;
        for(int j = i; j < size; j++){ // 寻找 i 以后的最小值
            if(nums[j] < min){
                min = nums[j];
                min_ind = j;
            }
        }
        nums[min_ind] = nums[i]; // 将 i 以后的最小值与 i 交换，使 i 成为最小
        nums[i] = min;
        // 这样直接交换虽然简单，但不能保证稳定性，相等元素的相对位置可能发生交换
        // 如果要保证稳定性，必须将 min 插入到 i 的位置上，其他元素需要依次向后挪动
    }
}

int main(){
    int num1[5] = {1,2,3,4,5};
    int num2[5] = {3,5,2,1,4};
    int num3[5] = {2,2,2,5,1};
    // insertSort<int>(num1, 5);
    // insertSort<int>(num2, 5);
    // insertSort<int>(num3, 5);
    // bubbleSort<int>(num1, 5);
    // bubbleSort<int>(num2, 5);
    // bubbleSort<int>(num3, 5);
    // selectSort<int>(num1, 5);
    // selectSort<int>(num2, 5);
    // selectSort<int>(num3, 5);
    for(int i = 0; i < 5; i++){
        cout<<num1[i]<<' ';
    }
    cout<<endl;
    for(int i = 0; i < 5; i++){
        cout<<num2[i]<<' ';
    }
    cout<<endl;
    for(int i = 0; i < 5; i++){
        cout<<num3[i]<<' ';
    }
}
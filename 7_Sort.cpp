#include <iostream>
using namespace std;

template <typename Type>
void insertSort(Type nums[], int size){
    // 插入排序
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
    // 冒泡排序
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
    // 选择排序
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

template <typename Type>
void insertSort4Shell(Type nums[], int size, int start, int step){
    // 可设置步长的插入排序，为希尔排序使用；传入的数组仍然是完整的原数组
    for(int i = start+step; i < size; i += step){ // 从start开始，每次往后挪step位
        Type temp = nums[i];
        int j;
        for(j = i; j > start; j -= step){ // 从i开始，每次往前挪step位
            if(temp < nums[j - step]) nums[j] = nums[j - step];
            else break;
        }
        nums[j] = temp;
    }
}

template <typename Type>
void shellSort(Type nums[], int size){
    // 希尔排序
    for(int gap = size/2; gap > 2; gap /= 2){ // 初始化步长为数组长度的一半，并每次减半
        for(int start = 0; start < gap; start++){ // 对每个子列调用插入排序
            insertSort4Shell(nums, size, start, gap);
        }
    }
    insertSort4Shell(nums, size, 0, 1); // 最后对全体数组进行插入排序
}

template <typename Type>
void quickSort(Type nums[], int left, int right){
    // 快速排序，根据两个位置参数完成局部排序
    if(left < right){
        Type pivot = nums[left]; // 选最左侧元素为参照
        int low = left, high = right; // 用两个变量来将数组分为两部分：小于pivot和大于pivot

        while(low < high){ // 在调整的过程中始终保证：low左边都小于等于pivot，high右边都大于pivot；当low==high时，分类完毕
            while(low < high && pivot < nums[high]) high--; // 只要high元素大于pivot，就继续左移high
            nums[low] = nums[high]; // 遇到了小于等于pivot的元素，将其移到low处
            while(low < high && nums[low] <= pivot) low++; // 只要low元素小于等于pivot，就继续右移low
            nums[high] = nums[low]; // 遇到了大于pivot的元素，将其移到high处
            // 在这里，也可以先移动low，后移动high，但考虑到pivot已经在low端取值，这样（先用high覆盖low）可以省去一个额外的temp
        }

        nums[low] = pivot; // 此时low==high，已满足左小右大的关系，将pivot填入low位置即可
        quickSort(nums, left, low-1); // 对左边进行排序
        quickSort(nums, low+1, right); // 对右边进行排序
    }
}

int main(){
    int num1[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int num2[15] = {9,11,3,5,8,6,14,1,7,10,2,13,15,4,12};
    int num3[15] = {2,2,2,3,1,1,1,1,4,4,5,5,4,5,4};
    // insertSort<int>(num1, 15);
    // insertSort<int>(num2, 15);
    // insertSort<int>(num3, 15);
    // bubbleSort<int>(num1, 15);
    // bubbleSort<int>(num2, 15);
    // bubbleSort<int>(num3, 15);
    // selectSort<int>(num1, 15);
    // selectSort<int>(num2, 15);
    // selectSort<int>(num3, 15);
    // shellSort<int>(num1, 15);
    // shellSort<int>(num2, 15);
    // shellSort<int>(num3, 15);
    quickSort<int>(num1, 0, 14);
    quickSort<int>(num2, 0, 14);
    quickSort<int>(num3, 0, 14);
    for(int i = 0; i < 15; i++){
        cout<<num1[i]<<' ';
    }
    cout<<endl;
    for(int i = 0; i < 15; i++){
        cout<<num2[i]<<' ';
    }
    cout<<endl;
    for(int i = 0; i < 15; i++){
        cout<<num3[i]<<' ';
    }
}
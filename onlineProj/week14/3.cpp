#include <iostream>
#define maxNum 100
using namespace std;

void MSort(int nums[], int res[], int start, int end){
    // 将nums数组中从start到end的元素排序，存放在res数组中
    if(start == end) res[start] = nums[start]; // 只有一个元素，直接填入对应位置即可
    else{ // 有多个元素
        int mid = (start + end) / 2; // 取中间位置
        int part[maxNum]; // 辅助数组，用于存储排好序的部分

        MSort(nums, part, start, mid); // 对两部分分别进行归并排序，分别存储在part数组的前半段和后半段
        MSort(nums, part, mid+1, end);

        // 对两部分分别排序后，接下来需要将它们合并
        int i = start, j = mid+1, k = start;
        while(i <= mid && j <= end){
            if(part[i] < part[j]){
                res[k] = part[i];
                i++;
            }
            else{
                res[k] = part[j];
                j++;
            }
            k++;
        }
        while(i <= mid){
            res[k] = part[i];
            i++; k++;
        }
        while(j <= end){
            res[k] = part[j];
            j++; k++;
        }
    }
}

void MergeSort(int a[], int n){
    MSort(a, a, 0, n-1);
}



void filterDown(int heap[], int size, int root){
    // 对堆中的节点root，假定其左右子树均为小顶堆，将以root为根节点的子树调整为小顶堆
    int currentPos = root;
    int currentChild = currentPos * 2 + 1;
    int temp = heap[root]; // 存储根节点
    while(currentChild < size){ // 不断向下寻找root该去的位置
        if(currentChild+1 < size && heap[currentChild] > heap[currentChild+1]) currentChild++;
        // 将currentChild指向两个子节点中更小的那个
        if(temp <= heap[currentChild]) break; // 若root比这两个子节点中更小的还小，说明已经满足小顶堆条件

        heap[currentPos] = heap[currentChild]; // 否则，将这个更小的子节点上提
        currentPos = currentChild; // 将考察的位置下移至那个更小的子节点
        currentChild = currentPos * 2 + 1;
    }
    heap[currentPos] = temp; // 已经找到root该去的地方，将其填入
}

void HeapSort(int heap[], int n){
    for(int i = n/2-1; i >= 0; i--) filterDown(heap, n, i); // 将数组初始化为小顶堆
    for(int i = n-1; i > 0; i--){
        int temp = heap[i]; // 将堆顶最小的元素交换到数组末端，后续将不再考虑该元素
        heap[i] = heap[0];
        heap[0] = temp;
        filterDown(heap, i, 0); // 重新调整小顶堆；由于仅修改了堆顶元素，故只需对堆顶元素进行调整即可
    }
}



int main(){
    int n;
    cin>>n;
    int nums[maxNum];
    for(int i = 0; i < n; i++) cin>>nums[i];

    MergeSort(nums, n);
    cout<<nums[0];
    for(int i = 1; i < n; i++){
        cout<<' '<<nums[i];
    }

    HeapSort(nums, n);
    cout<<endl<<nums[0];
    for(int i = 1; i < n; i++){
        cout<<' '<<nums[i];
    }
}
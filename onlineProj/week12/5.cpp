#include <iostream>
using namespace std;

struct Edge{
    int ver1;
    int ver2;
    int weight;
};

void sort(Edge* edges, int size){
    for(int i = 0; i < size; i++){
        Edge min = {0, 0, 10001};
        int min_ind = i;
        for(int j = i; j < size; j++){
            if(edges[j].weight < min.weight){
                min = {edges[j].ver1, edges[j].ver2, edges[j].weight};
                min_ind = j;
            }
        }
        if(min_ind != i){
            for(int j = min_ind; j > i; j--) edges[j] = edges[j - 1];
            edges[i] = min;
        }
    }
}

void merge(int subGraphHead[], int n, int ver1, int ver2){
    int head1 = subGraphHead[ver1];
    int head2 = subGraphHead[ver2];
    for(int i = 0; i < n; i++){
        if(subGraphHead[i] == head2){ // 与ver2属于同一子图的节点
            subGraphHead[i] = head1; // 都并入ver1所在的子图
        }
    }
}

int main(){
    int n, m, sumWeight = 0, numEdge = 0;
    cin>>n>>m;
    Edge edges[50000];

    // 为了防止环路形成，建立一个跟踪已形成子图的数组——存储每一个节点所属子图中，下标最小的节点索引
    int subGraphHead[1000];
    // 一开始，每一个节点都属于仅包含自己的子图，则其初始值为该节点本身
    for(int i = 0; i < n; i++) subGraphHead[i] = i;
    // 每当添加一条边，就根据较小节点所属子图，修改较大节点所属的子图
    // 这样，若两节点所属相同子图，其在此数组中的值就会相等

    // 存储每条边（默认节点ver1 < ver2）的权值，并将其按权值从小到大排列
    for(int i = 0; i < m; i++){
        cin>>edges[i].ver1>>edges[i].ver2>>edges[i].weight;
        edges[i].ver1--;
        edges[i].ver2--;
    }
    sort(edges, m);

    for(int i = 0; i < m; i++){
        if(numEdge == n-1) break; // 已构建n-1条边，结束
        int p1 = subGraphHead[edges[i].ver1];
        int p2 = subGraphHead[edges[i].ver2];
        if(p1 == p2) continue; // 两节点已经属于同一子图，不能再将其连接
        sumWeight += edges[i].weight;
        numEdge++;
        merge(subGraphHead, n, edges[i].ver1, edges[i].ver2); // 将两节点划到同一子图中
    }
    cout<<sumWeight;
}
#include <iostream>
#include <list>
#define maxWeight 10000
#define maxNode 256
#define maxEdge 2048
using std::cout; using std::endl;

struct Edge{
    int ver1;
    int ver2;
    int weight;
};



// 抽象数据结构“图”的声明
class Graph{
    public:
    virtual int firstAdj(int v) const = 0;
    virtual int nextAdj(int v, int preAdj) const = 0;
    virtual void setEdge(int from, int to, int weight) = 0;
    virtual void delEdge(int from, int to) = 0;
    virtual int getNumVer() const = 0;
    virtual int getNumEdge() const = 0;
    virtual int getWeight(int from, int to) const = 0;
    virtual Edge* getEdges() const = 0;
};



// 下面使用邻接矩阵来实现一个图
class GraphMatrix : public Graph{
    private:
    int** Mat;
    int numVer;
    int numEdge;
    bool isDirect;
    bool* visited;
    int* inDegree;

    public:
    GraphMatrix(bool isDirectional = false, int numNode = maxNode);
    ~GraphMatrix();
    virtual int firstAdj(int v) const;
    virtual int nextAdj(int v, int preAdj) const;
    virtual void setEdge(int from, int to, int weight);
    virtual void delEdge(int from, int to);
    virtual int getNumVer() const {return numVer;}
    virtual int getNumEdge() const {return numEdge;}
    virtual int getWeight(int from, int to) const {return Mat[from][to];}
    virtual Edge* getEdges() const;
};

GraphMatrix::GraphMatrix(bool isDirectional, int numNode):
numVer(numNode), numEdge(0){
    Mat = new int*[maxNode];
    visited = new bool[maxNode];
    inDegree = new int[maxNode];
    for(int i = 0; i < maxNode; i++){
        Mat[i] = new int[maxNode];
        inDegree[i] = 0;
    }
    for(int i = 0; i < numNode; i++){
        for(int j = 0; j < numNode; j++){
            Mat[i][j] = maxWeight;
        }
    }
}

GraphMatrix::~GraphMatrix(){
    for(int i = 0; i < maxNode; i++){
        delete[] Mat[i];
    }
    delete[] Mat;
    delete[] visited;
    delete[] inDegree;
}

int GraphMatrix::firstAdj(int v) const {
    // 遍历邻接矩阵，找到与v相连的、编号最小的节点
    for(int i = 0; i < numVer; i++){
        if(Mat[v][numVer] != maxWeight){
            return i;
        }
    }
    return -1;
}

int GraphMatrix::nextAdj(int v, int preAdj) const {
    // 找到与v相连的节点中，preAdj的下一个节点
    for(int i = preAdj + 1; i < numVer; i++){
        if(Mat[v][numVer] != maxWeight){
            return i;
        }
    }
    return -1;
}

void GraphMatrix::setEdge(int from, int to, int weight){
    if(Mat[from][to] == maxWeight){ // 原本没有这条边
        inDegree[to]++;
        numEdge++;
    }
    Mat[from][to] = weight; // 若已经有这条边，那么只需修改权值
    if(!isDirect){ // 无向图需要对称添加
        Mat[to][from] = weight;
    }
}

void GraphMatrix::delEdge(int from, int to){
    if(Mat[from][to] == maxWeight) return; // 原本就没有这条边，不用删除
    Mat[from][to] = maxWeight;
    inDegree[to]--;
    numEdge--;
    if(!isDirect){
        Mat[to][from] = maxWeight;
    }
}

Edge* GraphMatrix::getEdges() const{
    // 为计算最小生成树而开发的接口，返回图中所有的边

}



// 下面使用邻接表来实现一个图
class GraphLink : public Graph{
    private:
    struct edgeNode{
        int ver;
        int weight;
        edgeNode* next;
    };
    std::list<edgeNode>* ArrLink; // 一个存储了n个链表的数组，每个链表都存储了该节点的所有临边
    int numVer;
    int numEdge;
    bool* visited;
    
    public:
    GraphLink(int numNodes = maxNode):numVer(numNodes), numEdge(0){
        visited = new bool[maxNode];
        ArrLink = new std::list<edgeNode>[maxNode];
    }
    ~GraphLink(){
        delete[] visited;
        delete[] ArrLink;
    }
    virtual int firstAdj(int ver) const;
    virtual int nextAdj(int ver, int prevAdj) const;
    virtual void setEdge(int from, int to, int weight);
    virtual void delEdge(int from, int to);
    virtual int getNumVer() const {return numVer;}
    virtual int getNumEdge() const {return numEdge;}
    virtual int getWeight(int from, int to) const;
    virtual Edge* getEdges() const;
};

int GraphLink::firstAdj(int ver) const{
    if(ArrLink[ver].empty()) return -1;
    return ArrLink[ver].begin()->ver;
}

int GraphLink::nextAdj(int ver, int prevAdj) const{
    std::list<edgeNode>::iterator p = ArrLink[ver].begin();
    while(p != ArrLink[ver].end()){
        if(p->ver == prevAdj) return p->next->ver;
    }
    return -1;
}

void GraphLink::setEdge(int from, int to, int weight){

}

void GraphLink::delEdge(int from, int to){

}

int GraphLink::getWeight(int from, int to) const{
    std::list<edgeNode>::iterator p = ArrLink[from].begin();
    while(p != ArrLink[from].end()){
        if(p->ver == to) return p->weight;
        p++;
    }
    return -1;
}

Edge* GraphLink::getEdges() const{
    // 为计算最小生成树而开发的接口
    
}



// 下面实现图的两种遍历算法

// 下面实现最小生成树算法：读取一个树，输出其最小生成树的权值之和
int MST(const Graph& graph){
    // 只能获取无向图的最小生成树
    int n = graph.getNumVer(), m = graph.getNumEdge();
    int sumWeight = 0, numEdge = 0;

    // 存储每条边（默认节点ver1 < ver2）的权值，并将其按权值从小到大排列
    Edge* edges = graph.getEdges();
    for(int i = 0; i < m; i++){
        Edge min = edges[i];
        int min_ind = i;
        for(int j = i; j < m; j++){
            if(edges[j].weight < min.weight){
                min = edges[j];
                min_ind = j;
            }
        }
        edges[min_ind] = edges[i];
        edges[i] = min;
    }

    // 为了防止环路形成，建立一个跟踪已形成子图的数组——存储每一个节点所属子图中，下标最小的节点索引
    int subGraphHead[1000];
    // 一开始，每一个节点都属于仅包含自己的子图，则其初始值为该节点本身
    for(int i = 0; i < n; i++) subGraphHead[i] = i;
    // 每当添加一条边，就根据较小节点所属子图，修改较大节点所属的子图
    // 这样，若两节点所属相同子图，其在此数组中的值就会相等

    // 开始构建最小生成树
    for(int i = 0; i < m; i++){
        if(numEdge == n-1) break; // 已构建n-1条边，结束
        int p1 = subGraphHead[edges[i].ver1];
        int p2 = subGraphHead[edges[i].ver2];
        if(p1 == p2) continue; // 两节点已经属于同一子图，不能再将其连接
        sumWeight += edges[i].weight;
        numEdge++;
        for(int i = 0; i < n; i++){
            if(subGraphHead[i] == p2){ // 与ver2属于同一子图的节点
                subGraphHead[i] = p1; // 都并入ver1所在的子图
            }
        }
    }
    return sumWeight;
}

int main(){
    // GraphMatrix m(false, 4);
    GraphLink m(4);
    m.setEdge(0,1,24);
    m.setEdge(2,3,3);
    m.setEdge(0,3,100);
    m.setEdge(1,2,50);
    m.setEdge(3,1,2);
    cout<<m.firstAdj(0)<<endl;
    cout<<m.nextAdj(1,2)<<endl;
    cout<<MST(m);
}
#include <iostream>
#include <list>
#include <queue>
#define maxNode 256
#define maxEdge 2048
#define maxWeight 10000 // 邻接矩阵需要用默认值填充空边
using std::cout; using std::endl;

// 辅助计算最小生成树的数据结构，大部分时候用不到
struct Edge{
    int ver1;
    int ver2;
    int weight;
};



// 抽象数据结构“图”的声明
class Graph{
    public:
    bool isDirect;
    bool* visited;
    int* inDegree;
    Graph(int numNode, bool isD): isDirect(isD){
        // 复习知识点：构造函数被调用时，this只能是类本身，所以不需要定义为虚函数
        visited = new bool[numNode];
        inDegree = new int[maxNode];
        for(int i = 0; i < maxNode; i++){
            inDegree[i] = 0;
        }
    }
    virtual ~Graph() = default;
    // 复习知识点：为了析构彻底，析构函数应为虚函数，否则当父类指针指向子类对象时，只能析构掉父类的部分
    // 这里如果写 delete[] visited 会报错 unknown signal，暂时无法解决
        
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

    public:
    GraphMatrix(int numNode = maxNode, bool isDirectional = false);
    virtual ~GraphMatrix();
    virtual int firstAdj(int v) const;
    virtual int nextAdj(int v, int preAdj) const;
    virtual void setEdge(int from, int to, int weight);
    virtual void delEdge(int from, int to);
    virtual int getNumVer() const {return numVer;}
    virtual int getNumEdge() const {return numEdge;}
    virtual int getWeight(int from, int to) const {return Mat[from][to];}
    virtual Edge* getEdges() const;
};

GraphMatrix::GraphMatrix(int numNode, bool isDirectional):
numVer(numNode), numEdge(0), Graph(numNode, isDirectional){ // 调用父类的构造函数，初始化isDirect，visited
    Mat = new int*[maxNode];
    visited = new bool[maxNode];
    for(int i = 0; i < maxNode; i++){
        Mat[i] = new int[maxNode];
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
        if(Mat[v][i] != maxWeight){
            return i;
        }
    }
    return -1;
}

int GraphMatrix::nextAdj(int v, int preAdj) const {
    // 找到与v相连的节点中，preAdj的下一个节点
    for(int i = preAdj + 1; i < numVer; i++){
        if(Mat[v][i] != maxWeight){
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
    if(!isDirect){ // 无向图需要对称添加，但不需要增加边数
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
    Edge* edges = new Edge[maxEdge];
    int n = 0; // 跟踪当前已被添加的边数量
    for(int i = 0; i < numVer; i++){
        for(int j = i + 1; j < numVer; j++){ // 这样能保证ver1 < ver2
            if(Mat[i][j] != maxWeight){
                edges[n] = {i, j, Mat[i][j]};
                n++;
            }
        }
    }
    return edges;
}



// 下面使用邻接表来实现一个图
class GraphLink : public Graph{
    private:
    struct edgeNode{
        int ver;
        int weight;
        edgeNode(): ver(-1), weight(maxWeight){}
        edgeNode(int v, int w): ver(v), weight(w){}
    };
    std::list<edgeNode>* ArrLink; // 一个存储了n个链表的数组，每个链表都存储了该节点的所有临边
    int numVer;
    int numEdge;
    
    public:
    GraphLink(int numNode = maxNode, bool isDirectional = false):
    numVer(numNode), numEdge(0), Graph(numNode, isDirectional){
        visited = new bool[maxNode];
        ArrLink = new std::list<edgeNode>[maxNode];
    }
    virtual ~GraphLink(){
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
    bool found = false;
    while(p != ArrLink[ver].end()){
        if(found) return p->ver;
        if(p->ver == prevAdj) found = true;
        p++;
    }
    return -1;
}

void GraphLink::setEdge(int from, int to, int weight){
    // 不会保证所有相邻节点按序号从小到大排列，也没必要，直接在表尾添加新边
    std::list<edgeNode>::iterator p = ArrLink[from].begin();
    while(p != ArrLink[from].end()){
        if(p->ver == to){ // 已经有这条边，只需修改weight
            p->weight = weight;
            return;
        }
        p++;
    }
    edgeNode* newNode = new edgeNode(to, weight);
    ArrLink[from].push_back(*newNode); // 已经遍历到末尾了，还没有找到，于是新建边
    numEdge++;
    inDegree[to]++;
    if(!isDirect){ // 无向图，需要添加另一方向的边，需要增加另一方向的入度，但不用再增加numEdge
        std::list<edgeNode>::iterator p2 = ArrLink[to].begin();
        while(p2 != ArrLink[to].end()){
            if(p2->ver == from){
                p2->weight = weight;
                return;
            }
            p2++;
        }
        edgeNode* newNode2 = new edgeNode(from, weight);
        ArrLink[to].push_back(*newNode2);
        inDegree[from]++;
    }
}

void GraphLink::delEdge(int from, int to){
    std::list<edgeNode>::iterator p = ArrLink[from].begin();
    while(p != ArrLink[from].end()){
        if(p->ver == to){ // 找到需要删除的边
            ArrLink[from].erase(p);
            numEdge--;
            inDegree[to]--;
        }
    }
    if(!isDirect){ // 无向图，需要删除另一方向的边，但不用再减少numEdge
        std::list<edgeNode>::iterator p2 = ArrLink[to].begin();
        while(p2 != ArrLink[to].end()){
            if(p2->ver == from){
                ArrLink[to].erase(p2);
                inDegree[from]--;
            }
        }
    }
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
    // 为计算最小生成树而开发的接口，返回图中所有的边
    // 这里提供的解决方案很可能不是最优的，时间复杂度为O(n^3)
    Edge* edges = new Edge[maxEdge];
    int n = 0; // 跟踪当前已被添加的边数量
    for(int i = 0; i < numVer; i++){
        std::list<edgeNode>::iterator p = ArrLink[i].begin();
        while(p != ArrLink[i].end()){
            bool dupFlag = false;
            for(int j = 0; j < n; j++){ // 进行检查，如果这条边已经被添加进edges了，就不要再添加一遍了
                if(edges[j].ver1 == p->ver && edges[j].ver2 == i){ // 这样能保证ver1 < ver2
                    dupFlag = true;
                    break;
                }
            }
            if(!dupFlag){ // 还未添加
                edges[n] = {i, p->ver, p->weight};
                n++;
            }
            p++;
        }
    }
    return edges;
}



void __dfs(const Graph& graph, int node){
    // 真正在递归的函数
    cout<<node<<' ';
    graph.visited[node] = true;
    for(int v = graph.firstAdj(node); v != -1; v = graph.nextAdj(node, v)){
        if(!graph.visited[v]) __dfs(graph, v);
    }
}

void dfs(const Graph& graph, int firstNode = 0){
    // 图的深度优先遍历
    for(int i = 0; i < graph.getNumVer(); i++){
        graph.visited[i] = false;
    }
    __dfs(graph, firstNode);
}

void bfs(const Graph& graph, int firstNode = 0){
    // 
    for(int i = 0; i < graph.getNumVer(); i++){
        graph.visited[i] = false;
    }
    std::queue<int> q;
    q.push(firstNode);
    graph.visited[firstNode] = true;
    while(!q.empty()){
        int node = q.front();
        q.pop();
        cout<<node<<' ';
        for(int v = graph.firstAdj(node); v != -1; v = graph.nextAdj(node, v)){
            if(!graph.visited[v]){
                q.push(v);
                graph.visited[v] = true; // 进队列后立即设为“已访问”，防止反复添加
            }
        }
    }
}



void topoSort(const Graph& graph){
    // 生成拓扑排序序列，仅支持有向图
    int dyInDegree[maxNode];
    for(int i = 0; i < graph.getNumVer(); i++){
        dyInDegree[i] = graph.inDegree[i]; // 初始化动态变化的入度数组
    }
    std::queue<int> q;
    for(int i = 0; i < graph.getNumVer(); i++){
        if(dyInDegree[i] == 0) q.push(i);
    }
    while(!q.empty()){
        int node = q.front();
        q.pop();
        cout<<node<<' ';
        for(int i = graph.firstAdj(node); i != -1; i = graph.nextAdj(node, i)){
            dyInDegree[i]--;
            if(dyInDegree[i] == 0) q.push(i);
        }
    }
    for(int i = 0; i < graph.getNumVer(); i++){
        if(dyInDegree[i] > 0){
            cout<<"There are nodes left!";
            break;
        }
    }    
}



int MST(const Graph& graph){
    // Kruskal算法求最小生成树：读取一个树，输出其最小生成树的权值之和
    if(graph.isDirect) return -1; // 只能获取无向图的最小生成树

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
    int subGraphHead[maxNode];
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
    // GraphMatrix m(4, false);
    GraphLink m(4, true);
    m.setEdge(0,1,24);
    m.setEdge(2,3,3);
    m.setEdge(0,3,100);
    m.setEdge(1,2,50);
    m.setEdge(1,2,25); // 此处是修改边，而非新建
    // cout<<m.getWeight(1,2)<<endl;
    // cout<<m.firstAdj(0)<<endl;
    // cout<<m.nextAdj(0,1)<<endl;
    // dfs(m);
    // cout<<endl;
    // bfs(m);
    topoSort(m);
    // cout<<MST(m);
}
#include <iostream>
#include <string>
#include <list>
#define maxNode 100
using std::cin; using std::cout; using std::string; using std::list;

// 下面使用邻接矩阵来实现一个图
class Graph{
    private:
    int** Mat;
    int numVer;

    public:
    int* inDegree;
    Graph(int numNode = maxNode);
    ~Graph();
    int firstAdj(int v) const;
    int nextAdj(int v, int preAdj) const;
    void setEdge(int from, int to);
    int getNumVer() const {return numVer;}
};

Graph::Graph(int numNode) : numVer(numNode){
    Mat = new int*[maxNode];
    inDegree = new int[maxNode];
    for(int i = 0; i < maxNode; i++){
        Mat[i] = new int[maxNode];
        inDegree[i] = 0;
    }
    for(int i = 0; i < numNode; i++){
        for(int j = 0; j < numNode; j++){
            Mat[i][j] = 0;
        }
    }
}

Graph::~Graph(){
    for(int i = 0; i < maxNode; i++){
        delete[] Mat[i];
    }
    delete[] Mat;
    delete[] inDegree;
}

int Graph::firstAdj(int v) const {
    // 遍历邻接矩阵，找到与v相连的、编号最小的节点
    for(int i = 0; i < numVer; i++){
        if(Mat[v][i] != 0){
            return i;
        }
    }
    return -1;
}

int Graph::nextAdj(int v, int preAdj) const {
    // 找到与v相连的节点中，preAdj的下一个节点
    for(int i = preAdj + 1; i < numVer; i++){
        if(Mat[v][i] != 0){
            return i;
        }
    }
    return -1;
}

void Graph::setEdge(int from, int to){
    inDegree[to]++;
    Mat[from][to] = 1;
}

int str2int(string s){
    int num = 0;
    num += (s[2] - '0');
    num += ((s[1] - '0') * 10);
    return num;
}

string int2str(int n){
    n++;
    string s = "C";
    s.push_back(n / 10 + '0');
    s.push_back(n % 10 + '0');
    return s;
}

void topoSort(const Graph& G, int sem, int maxCred, int credList[], int totalCourse, bool even = false){
    // 生成培养方案，并让用户选择是否将课程平均分配到每学期
    list<int> method[maxNode]; // 储存每学期的课程
    int currPre[maxNode]; // 即current prerequisites，储存在中间某个学期，课程剩余未修的前置课程数量
    int originalMaxCred = maxCred;

    if(even){
        int sumCred = 0;
        for(int i = 0; i < totalCourse; i++){
            sumCred += credList[i];
        }
        maxCred = sumCred / sem + 1;
    }
    
    while(maxCred <= originalMaxCred){
        for(int i = 0; i < totalCourse; i++){
            // 初始化所有课程的修读状态
            currPre[i] = G.inDegree[i];
            method[i].clear();
        }
        for(int i = 0; i < sem; i++){
            int currCred = 0;
            for(int j = 0; j < totalCourse; j++){
                // 寻找已经可以学习，且不会使学分超限的课
                if(currCred + credList[j] <= maxCred && currPre[j] == 0){
                    method[i].push_back(j);
                    currCred += credList[j];
                    currPre[j] = -1; // 设为-1，防止以后再次修这门课
                }
            }
            list<int>::iterator p = method[i].begin();
            while(p != method[i].end()){ // 将本学期所修课的后继课，其入度-1
                for(int j = G.firstAdj(*p); j != -1; j = G.nextAdj(*p, j)){
                    currPre[j]--;
                }
                p++;
            }
        }
        // 此时已安排完毕，如果还有currPre未被设为-1的课，说明方案安排失败
        bool success = true;
        for(int i = 0; i < totalCourse; i++){
            if(currPre[i] != -1){
                // 在这种学分限制下无法完成分配，将学分限制+1，重新尝试分配
                maxCred++;
                success = false;
                break;
            }
        }
        if(success) break; // 成功完成分配，可以开始输出
    }

    if(maxCred == originalMaxCred + 1){
        // 从while判断处退出，说明已无法在用户要求的学分限制内完成分配
        cout<<"Failed to distribute course.\n";
        return;
    }

    for(int i = 0; i < sem; i++){
        cout<<"Semester No."<<i+1<<": ";
        if(method[i].empty()){ // 本学期无课程
            cout<<"Empty!\n";
            continue;
        }
        list<int>::iterator p = method[i].begin();
        while(p != method[i].end()){
            cout<<int2str(*p)<<" ";
            p++;
        }
        cout<<'\n';
    }
}

int main(){
    int semesters, maxCredit, totalCourse, credit;
    string ID, preID; // 假定ID格式为“C##”， 后两位是数字且 <= totalCourse
    cout<<"Input number of semesters: ";
    cin>>semesters;
    cout<<"Input maximum credit for a semester: ";
    cin>>maxCredit;
    cout<<"Input total number of courses: ";
    cin>>totalCourse;
    Graph g(totalCourse);
    int creditList[maxNode];
    for(int i = 0; i < totalCourse; i++){
        cout<<"Input course ID, its credit, and prerequisites: ";
        cin>>ID>>credit;
        creditList[str2int(ID) - 1] = credit;
        while(cin){
            if(cin.get() == '\n') break;
            cin>>preID;
            g.setEdge(str2int(preID) - 1, str2int(ID) - 1);
        }
    }
    topoSort(g, semesters, maxCredit, creditList, totalCourse,true);
}
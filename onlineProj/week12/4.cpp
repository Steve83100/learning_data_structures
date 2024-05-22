#include <iostream>
#include <string>
#include <queue>
#include <vector>
using std::string;
using std::vector;
using std::cout;
using std::cin;

class HTree{
    private:
    class TreeNode{
        public:
        int data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(): data(0), left(nullptr), right(nullptr){}
        TreeNode(int d, TreeNode* l, TreeNode* r): data(d), left(l), right(r){}
        bool isLeaf(){return (left == nullptr && right == nullptr);}
    };
    TreeNode* root;
    int wpl;
    std::vector<string> code;
    void __preOrder(TreeNode*);
    void getCode(string, TreeNode*);
    public:
    HTree(): root(nullptr){}; // Empty tree
    HTree(int d){root = new TreeNode(d, nullptr, nullptr);} // Tree with only one just-initialized node
    HTree(HTree*, HTree*); // Construct a tree from 2 sub-trees
    HTree(int, int[]);
    TreeNode* getRoot(){return root;}
    int totalWeight(){return root->data;}
    int getWpl(){return wpl;}
    void preOrder();
    void printCode();
};

HTree::HTree(HTree *l, HTree *r){
    int w = l->totalWeight() + r->totalWeight();
    root = new TreeNode(w, l->root, r->root);
}

class compare{
    public:
    bool operator()(HTree* x, HTree* y){
        return x->totalWeight() > y->totalWeight();
    }
};

HTree::HTree(int n, int weights[]){
    std::priority_queue<HTree*, std::vector<HTree *>, compare> q;
    for(int i = 0; i < n; i++){
        q.push(new HTree(weights[i]));
    }
    int w = 0;
    while(q.size() > 1){
        HTree*left = q.top();
        q.pop();
        HTree* right = q.top();
        q.pop();
        HTree* newTree = new HTree(left, right);
        w += (left->totalWeight() + right->totalWeight());
        q.push(newTree);
    }
    root = q.top()->root;
    wpl = w;
    getCode("", root);
}

void HTree:: preOrder(){
    __preOrder(root);
}

void HTree::__preOrder(TreeNode* r){
    cout<<r->data;
    if(r->left == nullptr && r->right == nullptr) return;
    else{
        cout<<'(';
        if(r->left != nullptr && r->right != nullptr){
            __preOrder(r->left);
            cout<<',';
            __preOrder(r->right);
        }
        else{
            if(r->left != nullptr) __preOrder(r->left);
            else __preOrder(r->right);
        }
        cout<<')';
    }
}

void HTree::getCode(string currCode, TreeNode* r){
    if(r->isLeaf()){
        code.push_back(currCode);
        return;
    }
    else{
        string leftCode = currCode, rightCode = currCode;
        leftCode.append("0");
        rightCode.append("1");
        getCode(leftCode, r->left);
        getCode(rightCode, r->right);
    }
}

void HTree::printCode(){
    for(int i = 0; i < code.size(); i++){
        cout<<code[i]<<' ';
    }
}

int main(){
    int n;
    cin>>n;
    int w[256];
    for(int i = 0; i < n; i++){
        cin>>w[i];
    }
    HTree t(n, w);
    cout<<t.getWpl()<<'\n';
    t.preOrder();
    cout<<'\n';
    t.printCode();
}
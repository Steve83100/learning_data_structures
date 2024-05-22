#include <iostream>
#include <queue>
using std::cout; using std::endl;

// 这本来是一个充满奇怪bug的程序，树的存储空间总是在被莫名其妙修改，包括但不限于：
// 遍历时如果使用cout<<' '输出空格，会改变树节点的内容，必须使用cout<<" "；
// 递归遍历返回后，根节点的左子树被指向了右子树；
// 遍历中某个时候或结束后，根节点值会被从3修改成6487496；
// 使用队列进行层次遍历时，建立指向队首的指针，会使根节点的左子树指向它自己，从而无限循环；
// 在主函数中使用cout<<endl，会改变树的根节点指针所指位置，进而丢失整棵树；

// 最终，问题已解决！
// 树的存储空间一直在被修改，说明在程序的视角中，这块空间是空闲的、可以自由使用的；
// 也就是说，从某个时刻开始，树根节点所在的存储空间已经被回收了，程序可以自由使用这块区域；
// 而树的内容之所以没有立刻被修改，只是因为程序暂时还没用到这块地方罢了；
// 经过检查，问题就出在树的构造函数中，我们将指向局部变量的指针返回到了全局，造成了树的数据丢失！

template <typename T>
class BinaryTree;

template <typename T>
class BinaryTreeNode{
    // 该节点类要被不止一个树类使用，故不设置成嵌套类
    friend BinaryTree<T>; // 允许BinaryTree类访问该类的私有内容
    private:
    T data;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    public:
    BinaryTreeNode(): data(nullptr), left(nullptr), right(nullptr){}
    BinaryTreeNode(const T& d): data(d), left(nullptr), right(nullptr){}
    BinaryTreeNode(const T& d, BinaryTreeNode* l, BinaryTreeNode* r): data(d), left(l), right(r){}

    void setLeft(BinaryTreeNode* l) {left = l;}
    void setRight(BinaryTreeNode* r) {right = r;}
    void setData(const T& d) {data = d;}
    bool isLeaf() const {return (left == nullptr && right == nullptr);}
};

template <typename T>
class BinaryTree{
    protected: // 可被子类的函数访问，但不能被本类或子类的对象直接访问
    BinaryTreeNode<T>* root;
    void __preOrder(BinaryTreeNode<T>*);
    BinaryTreeNode<T>* __getParent(BinaryTreeNode<T>*, BinaryTreeNode<T>*) const;

    public:
    BinaryTree(BinaryTreeNode<T>* r = nullptr): root(r){}
    BinaryTree(const T&, BinaryTreeNode<T>*, BinaryTreeNode<T>*);

    bool isEmpty() const {return root == nullptr;}
    BinaryTreeNode<T>* getRoot() const {return root;}
    BinaryTreeNode<T>* getParent(BinaryTreeNode<T>* node) const {return __getParent(root, node);}
    BinaryTreeNode<T>* getLeftSibling(BinaryTreeNode<T>*) const;
    BinaryTreeNode<T>* getRightSibling(BinaryTreeNode<T>*) const;
    void preOrder(){__preOrder(root);}
    void inOrder(BinaryTreeNode<T>*) const;
    // 后序遍历就不写了，反正这里用不到
    void levelOrder() const;
};

template <typename T>
BinaryTree<T>::BinaryTree(const T& data, BinaryTreeNode<T>* leftSib, BinaryTreeNode<T>* rightSib){
    // 由一个数据和两个子树构建新树
    root = new BinaryTreeNode<T>(data, leftSib, rightSib);
    // 之前这段代码是这么写的：
    // BinaryTreeNode r(data, leftSib, rightSib);
    // root = &r;
    // 因为不想在后续回收new出来的空间（懒），我就没有使用new在heap中申请空间，而是直接在该函数的scope下新建了一个根节点；
    // 新建完这个根节点后，我将树的root指向它，并完成了树的构建；
    // 但是，这个根节点仅存在于这个函数中，一旦函数执行完毕，其所属空间将被回收，以供后续使用；
    // 构造函数执行完毕，返回后，我们的树根节点指针一直在指向一块不存在的空间；
    // 此时，虽然在debug中可以看到这里的数据暂时还存在，但实际上它已经不受程序保护了，后续任何操作都有可能修改这里存储的数据。
}

template <typename T>
BinaryTreeNode<T>* BinaryTree<T>::__getParent(BinaryTreeNode<T>* r, BinaryTreeNode<T>* node) const{
    if(r == nullptr) return nullptr; // 如果此节点为空，则不可能是父节点
    if(r->left == node || r->right == node) return root; // 发现父节点，返回
    BinaryTreeNode<T>* leftResult = __getParent(r->left, node); // 在左子树中寻找父节点
    if(leftResult != nullptr) return leftResult;
    BinaryTreeNode<T>* rightResult = __getParent(r->right, node); // 在右子树中寻找父节点
    if(rightResult != nullptr) return rightResult;
    return nullptr; // 此节点和两个子树中都没找到
}

template <typename T>
BinaryTreeNode<T>* BinaryTree<T>::getLeftSibling(BinaryTreeNode<T>* node) const{
    BinaryTreeNode<T>* p = __getParent(root, node);
    if(p == nullptr || p->left == node) return nullptr; // 若无父节点 或 其父节点的左子节点就是其本身，则无左兄弟
    return p->left;
}

template <typename T>
BinaryTreeNode<T>* BinaryTree<T>::getRightSibling(BinaryTreeNode<T>* node) const{
    BinaryTreeNode<T>* p = __getParent(root, node);
    if(p == nullptr || p->right == node) return nullptr;
    return p->right;
}

template <typename T>
void BinaryTree<T>::__preOrder(BinaryTreeNode<T>* r){
    // 使用一个辅助函数，在主函数中就不用额外指定根节点，提升用户体验
    if(r == nullptr) return;
    std::cout<<r->data<<' ';
    inOrder(r->left);
    inOrder(r->right);
}

template <typename T>
void BinaryTree<T>::inOrder(BinaryTreeNode<T>* root) const{
    if(root == nullptr) return;
    inOrder(root->left);
    std::cout<<root->data<<' ';
    inOrder(root->right);
}

template <typename T>
void BinaryTree<T>::levelOrder() const{
    if(isEmpty()) return;
    std::queue<BinaryTreeNode<T>*> q;
    q.push(root);
    while(!q.empty()){
        BinaryTreeNode<T>* cur = q.front();
        std::cout<<cur->data<<' ';
        q.pop();
        if(cur->left != nullptr) q.push(cur->left);
        if(cur->right != nullptr) q.push(cur->right);
    }
}

int main(){
    using std::cout;
    BinaryTreeNode<int> node1(1), node2(2);
    BinaryTree<int> tree(3, &node1, &node2);
    tree.preOrder();
    cout<<endl;
    tree.inOrder(tree.getRoot());
    cout<<endl;
    tree.levelOrder();
    cout<<endl;
    cout<<(tree.getRightSibling(&node1));
}
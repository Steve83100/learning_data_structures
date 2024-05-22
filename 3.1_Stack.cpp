#include <iostream>
using std::cout; using std::endl;
#define DefaultStackSize 64

template <typename T> class Stack{ // 抽象数据结构“栈”，及其必须支持的操作
    public:
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual void clear() = 0;
    virtual int length() const = 0;
    virtual T getTop() const = 0;
    virtual void push(const T&) = 0;
    virtual T pop() = 0;
};

template <typename T>
// 任何时候调用模板类时，都应当明确typename
class SeqStack : public Stack<T>{ // 用顺序存储的方式实现一个栈
    private:
    int maxSize;
    int stackSize;
    T* items;
    public:
    SeqStack(int size = DefaultStackSize){
        maxSize = size;
        stackSize = 0;
        items = new T[maxSize];
    }
    ~SeqStack(){delete[] items;}
    virtual bool isEmpty() const {return (stackSize == 0);}
    virtual bool isFull() const {return (stackSize == maxSize);}
    virtual void clear();
    virtual int length() const {return stackSize;}
    virtual T getTop() const {
        if(stackSize == 0) return NULL;
        return items[stackSize - 1];
    }
    virtual void push(const T& item){
        if(stackSize == maxSize) return;
        items[stackSize] = item;
        stackSize++;
    }
    virtual T pop(){
        if(stackSize == 0) return NULL;
        stackSize--;
        return items[stackSize];
    }
};

template <typename T>
void SeqStack<T> :: clear(){
    // 简单地将stackSize设为0，或者令尾指针和头指针相等都是不对的，应当对每个元素专门析构
}

template <typename T>
class LinkStack : public Stack<T>{ // 用链表的方式实现一个栈
    private:
    class LinkStackNode{
        // 嵌套类中，内部类作为外部类的成员，仅对外部类可见；在这里，链栈节点仅被链栈使用，故设计成嵌套类最合乎逻辑
        // 内部类可以访问外部类的私有内容，但外部类无法访问内部类的私有内容，除非额外声明成友元
        friend LinkStack<T>; // 将LinkStack视为此节点类的友元，可以访问此节点类的私有内容
        private:
        T item;
        LinkStackNode* next;
        public:
        LinkStackNode(): item(NULL), next(NULL){}
        LinkStackNode(const T& i, LinkStackNode* n): item(i), next(n){}
    };
    LinkStackNode* top; // 因为头节点的存在，访问栈顶时应使用top->next，除了析构函数，永远不应该直接访问top本身
    int stackSize;
    public:
    LinkStack(): stackSize(0){top = new LinkStackNode();}
    ~LinkStack();
    virtual bool isEmpty() const {return (top->next == NULL);}
    virtual bool isFull() const {return false;}
    virtual void clear();
    virtual int length() const {return stackSize;}
    virtual T getTop() const {
        if(top->next == NULL) return NULL;
        return (top->next->item);
    }
    virtual void push(const T& item){
        top->next = new LinkStackNode(item, top->next);
        stackSize++;
    }
    virtual T pop(){
        if(top->next == NULL) return NULL;
        T topItem = top->next->item;
        top->next = top->next->next;
        stackSize--;
        return (topItem);
    }
};

template <typename T>
LinkStack<T> :: ~LinkStack(){
    LinkStackNode* top2 = top; // top2此时也指向头节点
    while(top2 != NULL){
        top2 = top->next;
        delete top;
        top = top2;
    }
}

template <typename T>
void LinkStack<T> :: clear(){
    LinkStackNode *p1 = top->next, *p2 = top->next;
    while(p1 != NULL){
        p2 = p1->next;
        delete p1;
        p1 = p2;
    }
}

int main(){
    SeqStack<int> s1; // 直接创建SeqStack类型的栈
    Stack<int> *s2 = new SeqStack<int>(); // 以抽象基类“栈”的名义创建一个栈，后续使用时将不在乎其具体实现
    Stack<int> *s3 = new LinkStack<int>();

    s1.push(1);
    s1.push(2);
    s1.push(3);
    int item1 = s1.pop();
    int item2 = s1.getTop();
    cout<<item1<<' '<<item2<<' '<<s1.length()<<endl;

    s2->push(4);
    s2->push(5);
    s2->push(6);
    int item3 = s2->pop();
    int item4 = s2->getTop();
    cout<<item3<<' '<<item4<<' '<<s2->length()<<endl;
    
    s3->push(7);
    s3->push(8);
    s3->push(9);
    s3->push(10);
    int item5 = s3->pop();
    int item6 = s3->getTop();
    cout<<item5<<' '<<item6<<' '<<s3->length()<<endl;
}
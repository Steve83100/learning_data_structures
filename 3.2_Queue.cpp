#include <iostream>
using std::cout; using std::endl;
#define maxQueueSize 64

template <typename T>
class Queue{
    public:
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual void clear() = 0;
    virtual int length() const = 0;
    virtual T getFirst() const = 0;
    virtual void push(const T&) = 0;
    virtual void pop() = 0;
};

template <typename T>
class SeqQueue : public Queue<T>{
    private:
    T* front;
    int maxSize;
    int queueSize;
    // 此size数值实际上存储的是队尾元素的位置，而非元素总数，队首可能有弹出元素留下的空当
    // 这也导致普通的顺序队列会产生“假溢出”现象，即 queueSize==maxSize 但其实并未满

    public:
    SeqQueue(int size = maxQueueSize): maxSize(size),  queueSize(0){front = new T[maxSize];}
    ~SeqQueue(){delete[] front;}
    virtual bool isEmpty() const {return queueSize == 0;}
    virtual bool isFull() const {return queueSize == maxSize;}
    virtual void clear(){
        for(int i = 0; i < queueSize; i++){
            delete front[i];
        }
        queueSize = 0;
    }
    virtual int length() const;
    virtual T getFirst() const;
    virtual void push(const T&);
    virtual void pop();
};

template <typename T>
class CirQueue : public Queue<T>{
    // 解决普通顺序队列的一个方法是采用循环队列，在仍然用一段连续的存储空间存储数据的基础上，对指针的移动操作进行修改，
    // 使得每当front和rear指针到达队尾后，继续前进则会指向队首；这样，就好像将这段存储空间首尾相接，构成循环了一样
    private:
    T* q;
    int front;
    int rear;
    int maxSize;

    public:
    CirQueue(int size = maxQueueSize): front(0), rear(0), maxSize(size){q = new T[size];}
    ~CirQueue(){}

    virtual bool isEmpty() const{return front == rear;}
    virtual bool isFull() const{return front == (rear + 1) % maxSize;}
    // 为与空队列的情况区分，在rear距离front还剩一格时就判定为满，此时其实还有一个空位

    virtual void clear(){
        while(front != rear){
            delete (q + front);
            front = (front + 1) % maxSize;
        }
    }
    virtual int length() const{return (rear - front + maxSize) % maxSize;}
    // 长度一般是rear-front，但这里可能为负数（中间跨越了分界线），于是需要处理一下才能返回正确的长度

    virtual T getFirst() const{return q[front];}
    virtual void push(const T& data){
        if(isFull()) return;
        q[rear] = data;
        rear = (rear + 1) % maxSize; // 这里是循环队列的关键，如果已到达尾部，则变回0
    }
    virtual void pop(){
        if(isEmpty()) return;
        delete (q + front);
        front = (front + 1) % maxSize;
    }
};

template <typename T>
class LinkQueue : public Queue<T>{
    private:
    class LinkQueueNode{
        public:
        T data;
        LinkQueueNode* next;
        LinkQueueNode(const T& d = NULL, LinkQueueNode* n = nullptr):data(d), next(n){}
    };
    int len;
    LinkQueueNode* head;
    LinkQueueNode* end;

    public:
    LinkQueue():len(0){
        head = new LinkQueueNode; // 头节点
        end = head;
    }
    ~LinkQueue(){
        LinkQueueNode* p;
        while(head != nullptr){
            p = head->next;
            delete head;
            head = p;
        }
    }
    virtual bool isEmpty() const {return head == end;}
    virtual bool isFull() const {return false;}
    virtual void clear(){
        LinkQueueNode *p1 = head, *p2;
        while(p1 != nullptr){
            p2 = p1->next;
            delete p1;
            p1 = p2;
        }
        len = 0;
    }
    virtual int length() const {return len;}
    virtual T getFirst() const {
        if(head->next == nullptr) return NULL;
        else return head->next->data;
    };
    virtual void push(const T& data){
        end->next = new LinkQueueNode(data, nullptr);
        end = end->next;
        len++;
    }
    virtual void pop(){
        LinkQueueNode* p = head->next;
        delete head;
        head = p;
        len--;
    }
};



int main(){
    CirQueue<int> q(3); // front:0; rear:0
    q.push(1); // q:1; front:0; rear:1
    q.push(2); // q:1,2; front:0; rear:2
    cout<<q.getFirst()<<endl;
    q.pop(); // q:2; front:1; rear:2
    cout<<q.length()<<endl;
    q.push(3); // q:2,3; front:1; rear:0
    cout<<q.length();
}
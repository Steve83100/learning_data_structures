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
class CirQueue : public Queue<T>{};

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
    LinkQueue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    cout<<q.getFirst()<<endl;
    q.pop();
    cout<<q.length();
}
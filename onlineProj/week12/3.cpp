#include <iostream>
using std::cout; using std::cin;

class Queue{
    private:
    class QueueNode{
        public:
        int data;
        QueueNode* next;
        QueueNode(): data(0), next(nullptr){}
        QueueNode(const int d, QueueNode* n): data(d), next(n){}
    };
    QueueNode *head, *end;
    public:
    Queue(){head = new QueueNode(); end = head;}
    void push(const int);
    int pop();
    void show() const;
};

void Queue::push(const int d){
    end->next = new QueueNode(d, nullptr);
    end = end->next;
}

int Queue::pop(){
    if(head->next == nullptr){return 0;}
    int val = head->next->data;
    QueueNode* p = head->next;
    head->next = head->next->next;
    delete p;
    return val;
}

void Queue::show() const{
    if(head->next == nullptr) return;
    QueueNode* p = head->next;
    cout<<p->data;
    p = p->next;
    while(p != nullptr){
        cout<<' '<<p->data;
        p = p->next;
    }
}

int main(){
    int n, a;
    cin>>n;
    Queue q;
    for(int i = 0; i < n; i++){
        cin>>a;
        q.push(a);
    }
    q.pop();
    q.pop();
    q.push(11);
    q.push(12);
    q.show();
}
#include <iostream>
using std::cout; using std::endl;
#define maxQueueSize 64;

template <typename T> class Queue{
    public:
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual void clear() = 0;
    virtual int length() const = 0;
    virtual T getFirst() const = 0;
    virtual void inQueue(const T&) = 0;
    virtual T outQueue() = 0;
};

template <typename T>
class SeqQueue : public Queue{
    private:
    T* front;
    int maxSize;
    int queueSize;
    public:
    SeqQueue(int size = maxQueueSize): maxSize(size),  queueSize(0){front = new T[maxSize];}
    ~SeqQueue(){delete[] front;}
    virtual bool isEmpty(){return queueSize == 0;}
    virtual bool isFull(){return queueSize == maxSize;}
    virtual void clear(){}
    virtual int length() const;
    virtual T getFirst() const;
    virtual void inQueue(const T&);
    virtual T outQueue();
};

template <typename T>
class CirQueue : public Queue{};

template <typename T>
class LinkQueue : public Queue{};
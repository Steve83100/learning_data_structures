#define DefaultListSize 64

template <typename T> class List{
    public:
    virtual void clear() = 0;
    virtual bool insert(const T&) = 0;
    virtual bool append(const T&) = 0;
    virtual bool remove(T&) = 0;
    virtual void setStart() = 0;
    virtual void setEnd() = 0;
    virtual void next() = 0;
    virtual void prev() = 0;
    virtual bool setPos(int pos) = 0;
    virtual T get() = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual int size() const = 0;
    virtual void print() const = 0;
};

template <typename T>
class Alist : public List<T>{
    private:
    int maxSize;
    int listSize;
    int curr;
    T* listArray;
    public:
    Alist(int size = DefaultListSize){
        maxSize = size;
        listSize = curr = 0;
        listArray = new T[maxSize];
    }
    ~Alist(){delete[] listArray;}
    virtual void clear(){listSize = curr = 0;}
    virtual bool insert(const T& item){
    }
    virtual bool append(const T& item){
    }
    virtual bool remove(T& item){
    }
    virtual void setStart(){curr = 0;}
    virtual void setEnd(){curr = listSize - 1;}
    virtual void next(){if(curr < listSize - 1) curr++;}
    virtual void prev(){if(curr > 0) curr--;}
    virtual T get(){return listArray[curr];}
    virtual bool getValue(T& item){
        if(curr >= 0 && curr < listSize){
            item = listArray[curr]
            return true;
        }
        return false;
    }
    virtual bool isEmpty() const {return (listSize == 0);}
    virtual bool isFull() const {return (listSize == maxSize);}
    virtual int size() const {return listSize;}
    virtual void print() const {
        for(int i = 0; i < listSize; i++){
            cout<<listArray[i]<<' ';
            cout<<endl;
        }
    }
};

template <typename T>
class SLList : public List<T>{
    private:
    int maxSize;
    int listSize;
    int curr;
    T* listArray;
    public:
    Slist(int size = DefaultListSize){
        maxSize = size;
        listSize = curr = 0;
        listArray = new T[maxSize];
    }
    ~Slist(){delete[] listArray;}
};

template <typename T>
class DLList : public List<T>{

};

template <typename T>
class CLList : public List<T>{

};
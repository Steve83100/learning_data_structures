#include <iostream>
using std::string; using std::cout; using std::cin;
#define maxLength 256

class List{
    public:
    char str[maxLength];
    int length;
    List(): length(0){}
    friend std::istream& operator>>(std::istream&, List&);
    void remove(const char);
    void show() const;
};

std::istream& operator>>(std::istream &cin, List& s){
    char c;
    while(cin.get(c) && c != '\n'){
        s.str[s.length] = c;
        s.length++;
    }
    return cin;
}

void List::remove(const char c){
    for(int i = 0; i < length;){
        if(str[i] == c){
            length--;
            for(int j = i; j < length; j++) str[j] = str[j+1];
        }
        else(i++);
    }
}

void List::show() const {
    for(int i = 0; i < length; i++) cout<<str[i];
}

int main(){
    List s;
    cin>>s;
    s.show();
    cout<<'\n'<<s.length<<'\n';
    char b;
    cin>>b;
    s.remove(b);
    s.show();
    cout<<'\n'<<s.length;
}
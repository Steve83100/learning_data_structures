#include <iostream>
#include <climits> 
#include <cmath>
using std::cout; using std::cin; using std::ostream; using std::istream;

class Node{
public:
	int coeff;
	int power;
	Node* next;
	Node(): coeff(0), power(65535), next(nullptr){} // 用于初始化头结点，coeff存储项数 
	Node(int c, int p, Node* n): coeff(c), power(p), next(n){}
};

class List{
private:
	Node* head;
	void insert(int, int); // 插入单个节点，保证节点按幂次降序排列
	void append(int, int); // 在末尾添加节点，同时要保证该节点幂次最小
public:
	List(){
		head = new Node(); // 将链表长度(初始为0)存入头结点
	}
	friend istream& operator>>(istream&, List&);
	friend ostream& operator<<(ostream&, const List&);
	List operator+(const List&);
	List operator-(const List&);
	int getValue(const int);
};

void List::append(int c, int p){
	Node *curr = head;
	while(curr->next != nullptr){
		curr = curr->next;
	}
	curr->next = new Node(c, p, nullptr); 
	(head->coeff)++;
} 

void List::insert(int c, int p){
	Node *p1 = head, *p2 = head->next;
	while(p2 != nullptr){
		if(p > p2->power) break;
		p1 = p1->next;
		p2 = p2->next;
	}
		Node* newNode = new Node(c, p, p2);
		p1->next = newNode;
		(head->coeff)++;
}

istream& operator>>(istream& is, List& b){
	int c, p;
	while(cin>>c>>p){
		b.insert(c, p);
		if(cin.get() == '\n') break;
	}
	return is;
}

ostream& operator<<(ostream& os, const List& b){
	Node *p = b.head->next;
	cout<<b.head->coeff; // 输出项数 
	while(p != nullptr){
		cout<<','<<p->coeff<<','<<p->power;
		p = p->next;
	}
	return os;
}

List List::operator+(const List& b){
	List sum;
	Node *p1 = head->next;
	Node *p2 = b.head->next;
	while(p1 != nullptr && p2 != nullptr){
		if(p1->power == p2->power){
			int currSum = p1->coeff + p2->coeff;
			if(currSum != 0){sum.append(currSum, p1->power);}
			p1 = p1->next;
			p2 = p2->next;
		}
		else if(p1->power > p2->power){
			sum.append(p1->coeff, p1->power);
			p1 = p1->next;
		}
		else{
			sum.append(p2->coeff, p2->power);
			p2 = p2->next;
		}
	}
	while(p1 != nullptr){
		sum.append(p1->coeff, p1->power);
		p1 = p1->next;
	}
	while(p2 != nullptr){
		sum.append(p2->coeff, p2->power);
		p2 = p2->next;
	}
	return sum;
}

List List::operator-(const List& b){
	List diff;
	Node *p1 = head->next;
	Node *p2 = b.head->next;
	while(p1 != nullptr && p2 != nullptr){
		if(p1->power == p2->power){
			int currDiff = p1->coeff - p2->coeff;
			if(currDiff != 0){diff.append(currDiff, p1->power);}
			p1 = p1->next;
			p2 = p2->next;
		}
		else if(p1->power > p2->power){
			diff.append(p1->coeff, p1->power);
			p1 = p1->next;
		}
		else{
			diff.append(-(p2->coeff), p2->power);
			p2 = p2->next;
		}
	}
	while(p1 != nullptr){
		diff.append(p1->coeff, p1->power);
		p1 = p1->next;
	}
	while(p2 != nullptr){
		diff.append(-(p2->coeff), p2->power);
		p2 = p2->next;
	}
	return diff;
}

int List::getValue(const int x){
	int val = 0;
	Node* p = head->next;
	while(p != nullptr){
		val += p->coeff * std::pow(x, p->power);
		p = p->next;
	}
	return val;
}

int main(){
	List a, b;
	cin>>a>>b;
	List c = a + b;
	List d = a - b;
	cout<<"A: "<<a<<"\nB: "<<b<<"\nA+B: "<<c<<"\nA-B: "<<d<<'\n';
	int x;
	cout<<"Give x value: ";
	cin>>x;
	cout<<"Value of A at x="<<x<<": "<<a.getValue(x);
	return 0;
}

#include <iostream>
#include <iomanip>
using namespace std;

int listLen(float* a, int maxLen){
	int len = 0;
	for(int i = 0; i < maxLen; i++){
		if(a[i] != 0) len++;
	}
	return len;
}

int main(){
	float a[64] = {0}, b[64] = {0};
	int index, _;
	cin>>_;
	while(cin.peek() != '\n'){
		cin>>index;
		cin>>a[index];
	}
	cin.get();
	cin>>_;
	while(cin.peek() != '\n'){
		cin>>index;
		cin>>b[index];
	}
	float c[64] = {0};
	for(int i = 0; i < 64; i++){
		c[i] = a[i] + b[i];
	}
	int clen = listLen(c, 64);
	cout<<clen;
	for(int i = 63; i >= 0; i--){
		if(c[i] != 0) cout<<fixed<<setprecision(1)<<' '<<i<<' '<<c[i];
	}
}

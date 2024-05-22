#include <iostream>
using namespace std;

int sum(int nums[], int first, int end){
	int s = 0;
	for(int i = first; i < end; i++){
		s += nums[i];
	}
	return s;
}

int main(){
	int k;
	cin>>k;
	int nums[64];
	for(int i = 0; i < k; i++){
		cin>>nums[i];
	}
	int maxSum = 0, maxFirst = 0, maxEnd = k-1;
	for(int i = 0; i < k; i++){
		for(int j = i; j < k; j++){
			int s = sum(nums, i, j+1);
			if(s > maxSum){
				maxSum = s;
				maxFirst = i;
				maxEnd = j;
			}
		}
	}
	if(maxSum == 0){
		cout<<0<<' '<<nums[0]<<' '<<nums[k-1];
	}
	else{
		cout<<maxSum<<' '<<maxFirst<<' '<<maxEnd;
	}
}

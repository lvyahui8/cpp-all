#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>

using namespace std;

void swap(int & a,int & b){
	b = a + b;
	a = b - a;
	b = b - a;
}

// 升序排序
void ksort(int arr[],int start,int end){
	if(end - start <= 2){
		return ;
	}
	int left = start,right = end;
	int pos = start;
	while(left < right){
		// 从左往右扫第一个比标杆大的数
		while(left++ < end && arr[left] <= arr[pos]);
		// 从右往左扫描第一个比标杆小的数
		while(right-- > start && arr[right] > arr[pos]);

		if(left > right){
			// 相对于标杆存在逆序
			// 将逆序的两个元素进行交换
			swap(arr[left],arr[right]);
		}
	}

	swap(arr[left],arr[pos]);
	ksort(arr,start,right);
	ksort(arr,left,end);
}

int main(){
	int arr[10] = {9,8,7,6,5,1,2,3,4,0};
	ksort(arr,0,sizeof(arr) - 1);
	for(int i = 0 ;i < sizeof(arr); i ++){
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}

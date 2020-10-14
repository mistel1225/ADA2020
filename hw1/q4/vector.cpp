#include <iostream>
#include <vector>
using namespace std;

int main(){
	vector<int> a(5, 5);
	a.reserve(10);
	for(int i=0; i<10; i++)
		cout<<a[i]<<endl;

}

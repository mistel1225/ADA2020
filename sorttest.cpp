#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


int main(){
	vector<vector<int>> test(5, vector<int>(5));
	for(int i =0; i<5; i++){
		cin>>test[i][0]>>test[i][1];
	}
	sort(test.begin(), test.begin()+4);
	for(int i=0; i<5; i++){
		cout<<test[i][0]<<" "<<test[i][1]<<endl;
	}
}


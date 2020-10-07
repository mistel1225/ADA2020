#include <iostream>
#include <vector>
using namespace std;

int main(){
	vector<vector<int>> test;
	for(int i=0; i<3; i++){
		test.push_back(vector<int>());
		for(int j=0; j<3; j++){
			test[i].push_back(j);
		}
	}
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			cout<<test[i][j];
		}
		cout<<endl;
	}
}

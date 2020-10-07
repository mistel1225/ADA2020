#include <iostream>
#include <vector>
using namespace std;

int main(){
	vector<vector<vector<int>>> test;
	test.reserve(5);
	for(int i=0; i<5; i++)
		test[i].reserve(5);
	for(int i=0; i<5; i++)
		for(int j=0; j<5; j++)
			test[i][j].reserve(5);
/*	for(int i=0; i<5; i++)
		for(int j=0; j<5; j++)
			for(int k=0; k<5; k++)
				test[i][j][k] = k;
*/
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			for(int k=0; k<5; k++){
				cout<<test[i][j][k]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	}
}

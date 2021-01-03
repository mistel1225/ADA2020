#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "helper.h"
using namespace std;
using namespace DLX;

class targetValue{
	public:
		int color;
		int k;
		targetValue(int color, int k){
			this->color = color;
			this->k = k;
		}
};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<vector<char>> board(9, vector<char>(9));
	set<char> uniqueColorSet;
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			char c;
			cin>>c;
			board[i][j] = c;
			uniqueColorSet.insert(c);
		}
	}
	map<char, int> colorTargetMap;
	char color;
	int k;
	for(int i=0; i<uniqueColorSet.size(); i++){
		cin>>color>>k;
		colorTargetMap.insert(pair<char, int>(color, k));
	}
	int n = 81*4;

	int C_1, C_2, C_3, C_4;
	for(int i=1; i<=9; i++){
		for(int j=1; j<=9; j++){
			for(int number=1; number<=9; number++){
				int id = (i-1)*9 + j;
				int rr = (id-1)*9 + number;
				//row
				C_1 = (i-1)*9 + number;
				//col
				C_2 = (j-1)*9 + number + 81;
				//palace
				int t = ((i-1)/3*3 + (j-1)/3)+1;
				C_3 = (t-1)*9 + number + 162;
				
				C_4 = id + 243;
			}
		}
	}	
}

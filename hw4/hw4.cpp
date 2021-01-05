#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "helper.h"
using namespace std;
using namespace DLX;
void get_all_set(int targetValue, int var_i, vector<int> &varVector, set<set<int>> &candidateSet){
	if(var_i<varVector.size()-1){
		for(int i=varVector[var_i-1]+1; i<=9; i++){
			varVector[var_i]=i;
			get_all_set(targetValue, var_i+1, varVector, candidateSet);
		}
	}
	else if(var_i==varVector.size()-1){
		int sum=0;
		for(int i=0; i<varVector.size()-1; i++){
			sum+=varVector[i];
		}
		for(int j=varVector[var_i-1]+1; j<=9; j++){
			varVector[var_i]=j;
			if(sum+varVector[var_i]==targetValue){
				set<int> candidateSubset;
				for(int k=0; k<varVector.size(); k++){
					candidateSubset.insert(varVector[k]);
				}
				candidateSet.insert(candidateSubset);
				return;
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<vector<char>> board(9, vector<char>(9));
	map<char, int> colorVarMap;
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			char c;
			cin>>c;
			board[i][j] = c;
			auto iter = colorVarMap.find(c);
			if(iter!=colorVarMap.end()){
				(iter->second)+=1;
			}
			else if(iter==colorVarMap.end()){
				colorVarMap.insert(pair<char, int>(c, 1));
			}
		}
	}
	map<char, int> colorTargetMap;
	int colorNum = colorVarMap.size();
	for(int i=0; i<colorNum; i++){
		char color;
		int k;
		cin>>color>>k;
		colorTargetMap.insert(pair<char, int>(color, k));
	}
	int colorId = 0;
	map<char, int> colorIdMap;
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			char color = board[i][j];
			auto iter = colorIdMap.find(color);
			if(iter==colorIdMap.end()){
				colorIdMap.insert(pair<char, int>(color, ++colorId));
			}
		}
	}
	


	int n = 81*4 + colorNum*9;
	Init(n);
	vector<int> row(5);
	for(int i=1; i<=9; i++){
		for(int j=1; j<=9; j++){
			char c = board[i-1][j-1];
			int targetValue = colorTargetMap.find(c)->second;
			int varNum = colorVarMap.find(c)->second;
			vector<int> varVector(varNum, 0);
			set<set<int>> candidateSet;
			get_all_set(targetValue, 0, varVector, candidateSet);
			set<int> candidateBigSet;
			for(auto iter=candidateSet.begin(); iter!=candidateSet.end(); iter++){
				for(auto iter2=(*iter).begin(); iter2!=(*iter).end(); iter2++){
					candidateBigSet.insert(*iter2);
				}
			}
			int cellId = (i-1)*9+j;
			for(auto iter=candidateBigSet.begin(); iter!=candidateBigSet.end(); iter++){
				int rr = (cellId-1)*9 + *iter;
				//row
				row[0] = (i-1)*9 + *iter;
				//col
				row[1] = (j-1)*9 + *iter + 81;
				//palace
				int p = ((i-1)/3*3 + (j-1)/3)+1;
				row[2] = (p-1)*9 + *iter + 162;
				//to promise each cell can only has one number
				row[3] = 243 + cellId;
				//color
				c = board[i-1][j-1];
				colorId = colorIdMap.find(c)->second;
				row[4] = 324 + (colorId-1)*9 + *iter;
				AddRow(rr, row);
			}
			//complement set
			for(auto iter=candidateSet.begin(); iter!=candidateSet.end(); iter++){
				for(int k=1; k<=9; k++){
					if((*iter).count(k)==0){
						c = board[i-1][j-1];
						colorId = colorIdMap.find(c)->second;
						vector<int> complementRow;
						complementRow.push_back(324+(colorId-1)*9 + k);
						AddRow(-1, complementRow);
					}
				}
			}
		}
	}
	vector<int> sol = Solver();
	int ansBoard[9][9];
	int r, c, ans;
	for(int i=0; i<sol.size(); i++){
		if(sol[i]!=-1){
			int rr = sol[i];
			ans = (rr%9==0? 9:rr%9);
			rr-=ans;
			rr/=9;
			rr+=1;
			c = (rr%9==0? 9:rr%9);
			rr-=c;
			rr/=9;
			rr+=1;
			r = (rr%9==0? 9:rr%9);
			ansBoard[r-1][c-1] = ans;
		}
	}
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			cout<<ansBoard[i][j];
		}
		cout<<endl;
	}
}

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "helper.h"
using namespace std;
using namespace DLX;
//#define DEBUG
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
	

	map<char, bool> is_color_completed;
	for(auto iter=colorIdMap.begin(); iter!=colorIdMap.end(); iter++){
		is_color_completed.insert(pair<char, bool>(iter->first, 0));
	}

	map<char, set<set<int>>> allPossibleCandidate;
	for(auto iter=colorIdMap.begin(); iter!=colorIdMap.end(); iter++){
		char c = iter->first;
		int varNum = colorVarMap.find(c)->second;
		vector<int> varVector(varNum, 0);
		int targetValue = colorTargetMap.find(c)->second;
		set<set<int>> candidateSet;
		get_all_set(targetValue, 0, varVector, candidateSet);
		allPossibleCandidate.insert(pair<char, set<set<int>>>(c, candidateSet));
	}
	int n = 81*4 + colorNum*9;
	Init(n);
	vector<int> row(5);
	for(int i=1; i<=9; i++){
		for(int j=1; j<=9; j++){
			char c = board[i-1][j-1];
			set<int> candidateBigSet;
			auto candidateSet = allPossibleCandidate.find(c)->second;
			for(auto itr1=candidateSet.begin(); itr1!=candidateSet.end(); itr1++){
				for(auto itr2=(*itr1).begin(); itr2!=(*itr1).end(); itr2++){
					candidateBigSet.insert(*itr2);
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
			if(is_color_completed.find(c)->second==0){
				for(auto iter=candidateSet.begin(); iter!=candidateSet.end(); iter++){
					vector<int> complementRow;
					for(int k=1; k<=9; k++){
						if((*iter).count(k)==0){
							c = board[i-1][j-1];
							colorId = colorIdMap.find(c)->second;
							complementRow.push_back(324+(colorId-1)*9 + k);
						}
					}
					AddRow(-1, complementRow);
				}
			}
			is_color_completed.find(c)->second=1;
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

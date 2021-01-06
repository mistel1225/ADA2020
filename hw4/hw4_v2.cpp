#include <iostream>
#include <vector>
#include <set>
#include <map>
#include "helper.h"
using namespace std;
using namespace DLX;

class cell{
	public:
		int i;
		int j;
		cell(int i, int j){
			this->i = i;
			this->j = j;
		}
};

class colorTarget{
	public:
		int color;
		int variable;
		int target;
		colorTarget(int color, int variable, int target){
			this->color = color;
			this->variable = variable;
			this->target = target;
		}
};


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
	set<char> colorSet;
	map<char, int> colorVarMap;
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			char c;
			cin>>c;
			board[i][j] = c;
			colorSet.insert(c);
			auto iter = colorVarMap.find(c);
			if(iter!=colorVarMap.end()){
				(iter->second)+=1;
			}
			else if(iter==colorVarMap.end()){
				colorVarMap.insert(pair<char, int>(c, 1));
			}

		}
	}
	
	int colorNum = colorSet.size();
	map<char, int> colorIdMap;
	map<char, int> colorTarMap;
	for(int i=1; i<=colorNum; i++){
		char c;
		int targetValue;
		cin>>c>>targetValue;
		colorIdMap.insert(pair<char, int>(c, i));
		colorTarMap.insert(pair<char, int>(c, targetValue));
	}
	
	vector<vector<cell>> indexRecord(colorNum);
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			char c = board[i][j];
			int id = colorIdMap.find(c)->second;
			indexRecord[id-1].push_back(cell(i+1, j+1));
		}
	}
	vector<colorTarget> targetVector(colorNum, colorTarget(0, 0, 0)); 
	for(auto iter=colorIdMap.begin(); iter!=colorIdMap.end(); iter++){
		char c = iter->first;
		int targetValue = colorTarMap.find(c)->second;
		int varNum = colorVarMap.find(c)->second;
		colorTarget temp(iter->second, varNum, targetValue);
		targetVector[iter->second-1] = temp;
	}
	int n = 81*4 + colorNum*9;
	Init(n);
	for(int i=0; i<targetVector.size(); i++){
		int color = targetVector[i].color;
		int varNum = targetVector[i].variable;
		int targetValue = targetVector[i].target;
		set<set<int>> candidateSet;
		vector<int> varVector(varNum, 0);
		get_all_set(targetValue, 0, varVector, candidateSet);
		set<int> candidateBigSet;
		for(auto iter=candidateSet.begin(); iter!=candidateSet.end(); iter++){
			for(auto iter2=(*iter).begin(); iter2!=(*iter).end(); iter2++){
				candidateBigSet.insert(*iter2);
			}
		}
		for(int j=0; j<indexRecord[color-1].size(); j++){
			int r = indexRecord[i][j].i;
			int c = indexRecord[i][j].j;
			int cellId = (r-1)*9 +c;
			vector<int> row(5);
			for(auto iter=candidateBigSet.begin(); iter!=candidateBigSet.end(); iter++){
				int rr = (cellId-1)*9 + *iter;
				//row
				row[0] = (r-1)*9 + *iter;
				//col
				row[1] = 81 + (c-1)*9 + *iter;
				//palace
				int p = ((r-1)/3*3 + (c-1)/3)+1;
				row[2] = 162 + (p-1)*9 + *iter;
				row[3] = 243+cellId;
				//color
				row[4] = 324 + (color-1)*9 + *iter;
				AddRow(rr, row);
			}
		}
		//complement set
		for(auto iter=candidateSet.begin(); iter!=candidateSet.end(); iter++){
			vector<int> complementRow;
			for(int k=1; k<=9; k++){
				if((*iter).count(k)==0){
					complementRow.push_back(324+(color-1)*9 + k);
				}		
			}
			AddRow(-1, complementRow);
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

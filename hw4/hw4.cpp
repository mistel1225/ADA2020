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
	#ifdef DEBUG
	cout<<"=============="<<endl;
	for(auto iter=colorVarMap.begin(); iter!=colorVarMap.end(); iter++){
		cout<<iter->first<<" "<<iter->second<<endl;
	}
	cout<<"=============="<<endl;
	for(auto iter=colorTargetMap.begin(); iter!=colorTargetMap.end(); iter++){
		cout<<iter->first<<" "<<iter->second<<endl;
	}
	#endif
	int n = 81*3 + colorNum*9;
	Init(n);
	int C_1, C_2, C_3, C_4;
	for(int i=1; i<=1; i++){
		for(int j=1; j<=3; j++){
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
			#ifdef DEBUG
			for(auto iter=candidateBigSet.begin(); iter!=candidateBigSet.end(); iter++)
				cout<<*iter<<" ";
			cout<<endl;
			#endif
			//row
			C_1
			//col
			//palace
			//color
		}
	}	
}

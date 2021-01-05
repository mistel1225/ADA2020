#include <iostream>
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
	/*
	int targetValue=15;
	vector<int> varVector(3, 0);
	set<set<int>> candidateSet;
	
	get_all_set(targetValue, 0, varVector, candidateSet);
	for(auto iter=candidateSet.begin(); iter!=candidateSet.end(); iter++){
		for(auto iter2=(*iter).begin(); iter2!=(*iter).end(); iter2++){
			cout<<*iter2<<"+";
		}
		cout<<endl;
	}
	
	map<char, int> test_map;
	char ch = 'a';
	test_map.insert(pair<char, int>(ch, 0));
	auto iter = test_map.find(ch);
	cout<<iter->second<<endl;
	(iter->second)+=1;
	cout<<iter->second<<endl;
	*/
	Init(5);
	vector<int> test(2);
	test[0] = 1;
	test[1] = 2;
	AddRow(-1, test);
	test[0] = 3;
	test[1] = 4;
	AddRow(-2, test);
	test[0] = 1;
	test[1] = 5;
	AddRow(3, test);
	vector<int> test2(1);
	test2[0] = 5;
	AddRow(-14, test2);
	vector<int> result = Solver();
	for(auto iter=result.begin(); iter!=result.end(); iter++)
		cout<<*iter<<" ";
	cout<<endl;
}

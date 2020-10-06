#include <iostream>
#include <string>
#include <vector>
#include "helper.h"
using namespace std;
using namespace Memory;

void find_damage_rec(int start, int end, vector<vector<long long>> &event_record){
	int mid  = (start+end)/2;
	if(start == end){
		return;
	}
	else{
		find_damage_rec(start, mid, event_record);
		find_damage_rec(mid+1, end, event_record);
	}
	for(int i=end; i>mid; i--){
		//bomb
		if(event_record[i][0]==1){
			add(event_record[i][1], event_record[i][2], event_record[i][3]);
			for(int j=start; j<=mid; j++){
				if(event_record[j][0]==0 && event_record[j][2]<=get(event_record[j][1])){
					event_record[j][3]+=event_record[i][4];
				}
			}
			add(event_record[i][1], event_record[i][2], -1*event_record[i][3]);
		}
	}
}


int main(){
	int N,M;
	cin>>N>>M;
	vector<vector<long long>> event_record(100000, vector<long long>(5, 0));
	long long c, l, r, d, p, k;
	string in;
	for(long long i=0; i<M; i++){
		cin>>in;
		if(in=="P"){
			event_record[i][0] = 0;//players
			cin>>event_record[i][1]>>event_record[i][2];
		}
		else{
			event_record[i][0] = 1;//bomb
			cin>>event_record[i][1]>>event_record[i][2]>>event_record[i][3]>>event_record[i][4];
		}
	}
	find_damage_rec(0, M-1, event_record);
	for(int i=0; i<M; i++){
		if(event_record[i][0]==0)
			cout<<event_record[i][3]<<endl;
	}
	return 0;
}

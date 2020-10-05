#include <iostream>
#include <string>
#include <vector>
#include "helper.h"
using namespace std;
using namespace Memory;
#define DEBUG1

void find_damage_rec(long long l, long long r, long long p, long long k, long long start, long long end, vector<vector<long long>> &damage_record){
	if(start==end && damage_record[start][0]>=l && damage_record[start][0]<=r && p>=damage_record[start][1]){
		damage_record[start][2]+=k;
		#ifdef DEBUG
		cout<<"start: "<<start<<endl;
		cout<<"damage: "<<damage_record[start][2]<<endl;
		#endif
		return;
	}
	else if(start!=end){
		long long mid = (start+end)/2;
		#ifdef DEBUG
		cout<<"mid: "<<mid<<endl;
		cout<<"end: "<<end<<endl;
		#endif
		find_damage_rec(l, r, p, k, start, mid, damage_record);
		find_damage_rec(l, r, p, k, mid+1, end, damage_record);
	}
		
}

int main(){
	int N, M;
	cin>>N>>M;
	vector<vector<long long>> damage_record(100000, vector<long long>(3, 0));
	long long c, l, r, d, p, k;
	string in;
	long long player_num=0;
	for(long long i=0; i<M; i++){
		cin>>in;
		if(in=="P"){
			cin>>damage_record[player_num][0]>>damage_record[player_num][1];
			player_num++;
		}
		else{
			cin>>l>>r>>p>>k;
			find_damage_rec(l, r, p, k, 0, player_num-1, damage_record);
		}
	}
	for(long long i=0; i<player_num; i++){
		cout<<damage_record[i][2]<<endl;
	}
	return 0;
}


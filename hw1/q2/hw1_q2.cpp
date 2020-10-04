#include <iostream>
#include <vector>
#include <algorithm>
#include "helper.h"
using namespace std;
using namespace Memory;


void find_damage_brute(long long l, long long r, long long p, long long k, vector<vector<long long>> &damage_record){
	for(long long i=l; i<=r; i++){
		if(get(i)<=p && get(i)!=0 )
			damage_record[i][1]+=k;
	}
}



int main(){
	int N, M;
	cin>>N>>M;
	vector<vector<long long>> damage_record(N, vector<long long>(2, 10001));
	string in;
	long long c, l, r, d, p, k;
	reset();
	//sort
	long long player_num=0;
	for(int i=0; i<M; i++){
		cin>>in;
		if(in=="P"){
			cin>>c>>d;
			add(c, c, d);
			damage_record[c][0] = player_num;
			damage_record[c][1] = 0;
			player_num++;	
		}
		else{
			cin>>l>>r>>p>>k;
			find_damage_brute(l, r, p, k, damage_record);
		}
		
	}
	sort(damage_record.begin(), damage_record.end());
	for(long long i=0; i<player_num; i++){
		cout<<damage_record[i][1]<<endl;
	}
}

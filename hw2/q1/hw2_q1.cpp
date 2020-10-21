#include <iostream>
#include <cmath>
using namespace std;


int main(){
	long long N, K, A, B;
	cin>>N>>K>>A>>B;
	long long grid[N];
	//calculate bonus in each grid, -1 means grid[i] is build with a tower
	long long bonus[N]={0};
	for(long long i=0; i<N; i++)
		cin>>grid[i];
	
	long long total_defense=0;
	long long temp_max_loc;
	for(long long i=0; i<K; i++){
		for(long long j=0; j<N; j++)
			if(bonus[j]!=-1)
				temp_max_loc = j;
		for(long long j=temp_max_loc+1; j<N; j++)
			if(bonus[j]!=-1)
				if(grid[j]+bonus[j]>grid[temp_max_loc]+bonus[temp_max_loc])
					temp_max_loc=j;
		//grid[i] is build with a tower
		bonus[temp_max_loc]=-1;
		for(long long j=temp_max_loc-B; j<=temp_max_loc+B&&j<N; j++){
			if(bonus[j]!=-1){
				if(B-abs(temp_max_loc-j)>0)
					bonus[j]+=A*(B-abs(temp_max_loc-j));
			}
		}
		if(total_defense+grid[temp_max_loc]+bonus[temp_max_loc]>total_defense)
			total_defense+=grid[temp_max_loc]+bonus[temp_max_loc];
		else
			break;
	}
	cout<<total_defense<<endl;
	return 0;
}

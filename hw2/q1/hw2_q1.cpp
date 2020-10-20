#include <iostream>
using namespace std;


int main(){
	long long N, K, A, B;
	cin>>N>>K>>A>>B;
	long long grid[N];
	//calculate bonus in each grid, -1 means grid[i] is build a tower
	long long bonus[N]={0};
	for(long long i=0; i<N; i++)
		cin>>grid[i];
	
	long long total_defense=0;
	long long temp_max_defense;
	for(long long i=0; i<K; i++){
		for(long long k=0; k<N; k++)
			if(grid[k]!=-1)
				temp_max_defense = k;
		for(long long j=0; j<N; j++){
			if(bonus[j]!=-1){
				if(grid[j]+bonus[j]>grid[temp_max_defense]+bonus[temp_max_defense]){
					temp_max_defense=j;
				}
			}
		}
	}
	
}

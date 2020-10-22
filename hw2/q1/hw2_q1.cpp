#include <iostream>
#include <cmath>
using namespace std;
//#define DEBUG

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
	long long i=0, j=0;
	for(i=0; i<K; i++){
		for(j=0; j<N; j++){
			if(bonus[j]!=-1){
				temp_max_loc = j;
				break;
			}
		}
		//greedy approach
		for(j=temp_max_loc+1; j<N; j++)
			if(bonus[j]!=-1)
				if(grid[j]+bonus[j]>grid[temp_max_loc]+bonus[temp_max_loc])
					temp_max_loc=j;
		#ifdef DEBUG
		cout<<grid[temp_max_loc]<<endl;
		#endif
		for(j=temp_max_loc+1; j<=temp_max_loc+B&&j<N; j++)
			if(bonus[j]!=-1)
					bonus[j]=A*(B-(j-temp_max_loc));
			else if(bonus[j]==-1)
				break;
		if(bonus[j]==-1&&j<N)
			for(long long k=j-1; k>temp_max_loc; k--)
					bonus[k]+=A*(B-(j-k));
		
		for(j=temp_max_loc-1; j>=temp_max_loc-B&&j>=0; j--)
            if(bonus[j]!=-1)
                    bonus[j]=A*(B-(temp_max_loc-j));
            else if(bonus[j]==-1)
                break;
		if(bonus[j]==-1&&j>=0)
			for(long long k=j+1; k<temp_max_loc; k++)
					bonus[k]+=A*(B-(k-j));
		if(total_defense+grid[temp_max_loc]+bonus[temp_max_loc]>total_defense){
			total_defense+=grid[temp_max_loc]+bonus[temp_max_loc];
			bonus[temp_max_loc]=-1;
		}
		else
			break;
		#ifdef DEBUG
		for(int k=0; k<N; k++)
			cout<<bonus[k]<<" ";
		cout<<endl;
		cout<<"==============="<<endl;
		#endif
	}
	cout<<total_defense<<endl;
	return 0;
}

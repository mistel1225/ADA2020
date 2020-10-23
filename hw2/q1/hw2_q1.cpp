#include <iostream>
#include <vector>
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
	vector<long long> grid_index;
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
		for(j=temp_max_loc+1; j<N; j++){
			if(bonus[j]!=-1){
				if(B-(j-temp_max_loc)>0)	
					bonus[j]=A*(B-(j-temp_max_loc));
				else
					bonus[j]=0;
			}
			else if(bonus[j]==-1)
				break;
		}
		if(bonus[j]==-1&&j<N)
			for(long long k=j-1; k>temp_max_loc; k--)
				if(B-(j-k)>0)
					bonus[k]+=A*(B-(j-k));
				else
					break;
		
		for(j=temp_max_loc-1; j>=0; j--){
            if(bonus[j]!=-1){
				if(B-(temp_max_loc-j)>0)
                    bonus[j]=A*(B-(temp_max_loc-j));
				else
					bonus[j]=0;
			}
            else if(bonus[j]==-1)
                break;
		}
		if(bonus[j]==-1&&j>=0)
			for(long long k=j+1; k<temp_max_loc; k++)
				if(B-(k-j)>0)
					bonus[k]+=A*(B-(k-j));
				else
					break;
		bonus[temp_max_loc]=-1;
		long long total_defense_temp=0;
		for(long long k=0; k<N; k++){
			if(bonus[k]==-1){
				total_defense_temp+=grid[k];
				grid_index.push_back(k);
			}
		}
		for(long long k=0; k<grid_index.size()-1; k++)
			if(B-(grid_index[k+1]-grid_index[k])>0)
				total_defense_temp+=A*(B-(grid_index[k+1]-grid_index[k]));
		grid_index.clear();
		if(total_defense_temp>=total_defense)
			total_defense=total_defense_temp;
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

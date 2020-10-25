#include <iostream>
using namespace std;
//#define DEBUG

int main(){
	long long N, K, A, B;
	cin>>N>>K>>A>>B;
	long long dp_prev[N];
	long long dp_curr[N];
	long long grid[N];
	long long max;
	for(long long i=0; i<N; i++){
		cin>>grid[i];
		dp_prev[i]=grid[i];
	}
	max=dp_prev[0];
	for(long long i=0; i<N; i++)
		if(dp_prev[i]>max)
			max = dp_prev[i];
	for(long long k=1; k<K; k++){
		long long max_nonebonus_loc=0;
		long long max_bonus_loc=0;
		long long temp_max=0;
		dp_curr[0]=dp_prev[0];
		for(long long j=1; j<N; j++){
			if(dp_prev[j-1]>dp_prev[max_nonebonus_loc])
				max_nonebonus_loc=j-1;
			if(dp_prev[j-1]+A*(B-1)>=dp_prev[max_bonus_loc]+A*(B-(j-max_bonus_loc)))
				max_bonus_loc = j-1;
			if(dp_prev[max_bonus_loc]+A*(B-(j-max_bonus_loc))>dp_prev[max_nonebonus_loc])
				temp_max = dp_prev[max_bonus_loc]+A*(B-(j-max_bonus_loc));
			else
				temp_max = dp_prev[max_nonebonus_loc];
			dp_curr[j] = temp_max+grid[j];
		}
		for(long long j=0; j<N; j++){
			if(dp_curr[j]>max)
				max = dp_curr[j];
			dp_prev[j] = dp_curr[j];
		}
        #ifdef DEBUG
        for(long long i=0; i<N; i++)
            cout<<dp_prev[i]<<" ";
        cout<<endl;
        #endif
	}

	cout<<max<<endl;
	return 0;
}

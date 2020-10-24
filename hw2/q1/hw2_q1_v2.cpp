#include <iostream>
using namespace std;
//#define DEBUG

int main(){
	long long N, K, A, B;
	cin>>N>>K>>A>>B;
	long long dp[K][N];
	long long grid[N];
	for(long long i=0; i<N; i++){
		cin>>grid[i];
		dp[0][i]=grid[i];
	}
	for(long long i=1; i<K; i++)
		dp[i][0] = dp[i-1][0];
	for(long long k=1; k<K; k++){
		long long temp_max_loc=0;
		long long temp_max=0;
		for(long long j=1; j<N; j++){
			/*if(dp[k-1][j-1]+A*(B-(j-(j-1)))>dp[k-1][temp_max_loc]+A*(B-(j-temp_max_loc))&&dp[k-1][j-1]+A*(B-(j-(j-1)))>dp[k-1][temp_max_loc])
                temp_max_loc = j-1;			*/
			if(dp[k-1][temp_max_loc]+A*(B-(j-temp_max_loc))>dp[k-1][temp_max_loc])
				temp_max = dp[k-1][temp_max_loc]+A*(B-(j-temp_max_loc));
			else
				temp_max = dp[k-1][temp_max_loc];
            if(dp[k-1][j]+A*(B-(j-j+1))>dp[k-1][temp_max_loc]+A*(B-(j-temp_max_loc+1))&&dp[k-1][j]+A*(B-(j-j+1))>dp[k-1][temp_max_loc])
                temp_max_loc = j;
			/*if(dp[k-1][j-1]+A*(B-(j-(j-1)))>temp_max)
				temp_max = dp[k-1][j-1]+A*(B-(j-(j-1)));*/
			dp[k][j] = temp_max+grid[j];
			#ifdef DEBUG
			cout<<dp[k][j]<<" ";
			#endif
		}
		#ifdef DEBUG
		cout<<endl;
		#endif
	}
	long long max=dp[K-1][0];
	/*for(long long i=0; i<K; i++)
		for(long long j=0; j<N; j++)
			if(dp[i][j]>max)
				max = dp[i][j];*/
	for(long long i=0; i<N; i++)
		if(dp[K-1][i]>max)
			max = dp[K-1][i];
	cout<<max<<endl;
	return 0;
}

#include <iostream>
#include <vector>
#include <stdio.h>
#include <float.h>
using namespace std;
// #define DEBUG

int main(){
		long long int N;
		cin>>N;

		vector<vector<long long int>> coord_matrix(N, vector<long long int>(2));
		vector<vector<long long int>> sales_cost_matrix(N, vector<long long int>(N));
		for(long long int i=0; i<N; i++){
			cin>>coord_matrix[i][0]>>coord_matrix[i][1];
		}

		for(long long int i=0; i<N; i++){
			for(long long int j=i; j<N; j++){
				sales_cost_matrix[i][j] = coord_matrix[i][0]*coord_matrix[j][0] 
					+ coord_matrix[i][1]*coord_matrix[j][1];
			}
		}
		#ifdef DEBUG
		cout<<"========sales_cost_matrix========="<<endl;
		for(long long int i=0; i<N; i++){
			for(long long int j=0; j<N; j++){
				cout<<sales_cost_matrix[i][j]<<" ";
				if(j==N-1)
					cout<<endl;
			}
		}
		#endif

		long long int max=-9223372036854775807;
		long long int profit = 0;
		for(long long int i=0; i<N; i++){
			for(long long int j=i+1; j<N; j++){
				profit = 2*sales_cost_matrix[i][j] - sales_cost_matrix[i][i] - sales_cost_matrix[j][j];
				#ifdef DEBUG
					cout<<"==============profit=============="<<endl;
					cout<<profit<<endl;
				#endif
				if(profit > max)
					max = profit;
			}
		}

		cout<<max<<endl;
		return 0;
}

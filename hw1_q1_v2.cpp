#include <iostream>
#include <vector>
#include <alogrithm>
#include <math.h>
using namespace std;

int main(){
	long long N;
	cin>>N;
	vector<vector<long long>> coord_matrix(N, vector<long long>(2));
	for(long long i=0; i<N; i++){
		cin>>coord_matrix[i][0]>>coord_matrix[i][1];
	}

	long long min_distance = 9223372036854775807;
	long long distance = 0;
	for(long long i=0; i<N; i++){
		for(long long j=i+1; j<N; j++){
			distance = (coord_matrix[i][0]-coord_matrix[j][0])*(coord_matrix[i][0]-coord_matrix[j][0]) + (coord_matrix[i][1]-coord_matrix[j][1])*(coord_matrix[i][1]-coord_matrix[j][1]);
			min_distance = min_distance > distance ? distance : min_distance;
		}
	}
	cout<<-1*min_distance<<endl;
	return 0;
}

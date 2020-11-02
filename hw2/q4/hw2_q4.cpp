#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define DEBUG
int main(){
	long long N, M, K;
	cin>>N>>M>>K;
	vector<vector<long long>> segments(N, vector<long long>(3));
	long long w_sum=0;
	for(long long i=0; i<N; i++){
		cin>>segments[i][0]>>segments[i][1]>>segments[i][2];
		w_sum+=segments[i][2];
	}
	//sort by L_i
	sort(segments.begin(), segments.end());
	#ifdef DEBUG
	for(long long i=0; i<N; i++)
		cout<<segments[i][0]<<" "<<segments[i][1]<<" "<<segments[i][2]<<endl;
	#endif
}

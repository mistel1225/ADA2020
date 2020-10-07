#include <iostream>
#include <vector>
#include <string>
using namespace std;

class cell{
	public:
		long long total_sweet=0;
		long long x;
		long long y;
		long long z;
		string move_type;
		long long from_x;
		long long from_y;
		long long from_z;
		long long k=0;
		long long k_remain=0;
};

int main(){
	long long n, m, k, c;
	cin>>n>>m>>k>>c;
	vector<vector<long long>> sweetness(n+1, vector<long long>(m+1));
	for(long long i=1; i<=n; i++)
		for(long long j=1; j<=m; j++)
			cin>>sweetness[i][j];

	vector<vector<vector<cell>>> opt;
	opt.reserve(n+1);
	for(long long i=0; i<n+1; i++){
		opt[i].reserve(m+1);
	}
	for(long long i=0; i<n+1; i++)
		for(long long j=0; j<n+1; j++)
			opt[i][j].reserve(2);
	/*global solution*/
	cell opt_global; 
	opt_global.total_sweet=sweetness[1][1];
	opt_global.x = 1;
	opt_global.y = 1;
	opt_global.z = 1;
	opt_global.move_type = "init";
	opt_global.from_x=1;
	opt_global.from_y=1;
	opt_global.from_z=1;
	opt_global.k = 0;
	opt_global.k_remain = k;
	
	/*number of z axis*/
	long long p=1;
	for(int i=1; i<=N; i++){
		for(int j=1; j<=M; j++){
			for(int l=1; l<=p; l++)
				
			}
		}
	}
}

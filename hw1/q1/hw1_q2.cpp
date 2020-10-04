#include <iostream>
#include <vector>
#include <string>
using namespace std;

void path_printer(vector<vector<bool>> &opt_path, long n, long m){
	if(m==1&&n==1)
		return;
	else{
		if(opt_path[n][m]==0)
			path_printer(opt_path, n, m-1);
		else
			path_printer(opt_path, n-1, m);
	}
	cout<<"Move "<<n-1<<" "<<m-1<<endl;
}

int main(){
	long n, m, k, c;
	cin>>n>>m>>k>>c;
	vector<vector<long>> nuts_sweetness(n+1, vector<long>(m+1));
	vector<vector<long>> opt_sweetness(n+1, vector<long>(m+1));
	vector<vector<bool>> opt_path(n+1, vector<bool>(m+1));
	
	for(long i=1; i<=n; i++){
		for(long j=1; j<=m; j++){
			cin>>nuts_sweetness[i][j];
		}
	}
	for(long i=1; i<=n; i++){
		for(long j=1; j<=m; j++){
			if(opt_sweetness[i][j-1]>opt_sweetness[i-1][j]){
				opt_sweetness[i][j]=opt_sweetness[i][j-1]+nuts_sweetness[i][j];
				opt_path[i][j] = 0;
			}
			else{
				opt_sweetness[i][j]=opt_sweetness[i-1][j]+nuts_sweetness[i][j];
				opt_path[i][j] = 1;
			}
		}
	}
	cout<<opt_sweetness[n][m]<<endl;
	cout<<m+n-2<<endl;
	path_printer(opt_path, n, m);
}

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class cell{
	public:
		long long total_sweet=0;
		long long i;
		long long j;
		long long l;
		long long from_i;
		long long from_j;
		long long from_l;
		long long k=0;
		string move_type;
}


int main(){
	long long n, m, k, c;
	vector<vector<long long>> sweetness(n+1, vector<long long>(m+1));
	cin>>n>>m>>k>>c;
	for(long long i=1; i<=n; i++)
		for(long long j=1; j<=m; j++)
			cin>>sweetness[i][j];
	vector<vector<vector<cell>>>  opt;
	//initialize opt
	opt.reserve(n+1);
	for(long long i=0; i<=n; i++){
		opt[i].reserve(m+1);
		for(long long j=0; j<=m; j++){
			opt[i][j].reserve(2);
		}
	}
	//initialize global opt sol on dimension 1
   	opt[0][0][1].total_sweet = sweetness[1][1];
	opt[0][0][1].i = 1;
	opt[0][0][1].j = 1;
	opt[0][0][1].l = 1;
	opt[0][0][1].k = 0;

	for(long long i=1; i<=n; i++){
		for(long long j=1; j<=n; j++){
			//from top
			if(opt[i-1][j][1] >= opt[i][j-1][1]){
				opt[i][j][1].total_sweet = opt[i-1][j][1].total_sweet + sweetness[i][j];
				opt[i][j][1].i = i;
				opt[i][j][1].k = j;
				opt[i][j][1].l = 1;
				opt[i][j][1].from_i = i-1;
				opt[i][j][1].from_j = j;
				opt[i][j][1].from_l = 1;
				opt[i][j][1].k = 0;
				opt[i][j][1].move_type = "Move";
			}
			//from left
			else{
                opt[i][j][1].total_sweet = opt[i][j-1][1].total_sweet + sweetness[i][j];
                opt[i][j][1].i = i;
                opt[i][j][1].k = j;
                opt[i][j][1].l = 1;
                opt[i][j][1].from_i = i;
                opt[i][j][1].from_j = j-1;
                opt[i][j][1].from_l = 1;
                opt[i][j][1].k = 0;
                opt[i][j][1].move_type = "Move";
			}
			if(opt[i][j][1].total_sweet > opt[0][0][1].total_sweet){
				opt[0][0][1].total_sweet = opt[i][j][1].total_sweet;
				opt[0][0][1].i = opt[i][j][1].i;
				opt[0][0][1].j = opt[i][j][1].j;
				opt[0][0][1].l = opt[i][j][1].l;
				opt[0][0][1].from_i = opt[i][j][1].from_i;
				opt[0][0][1].from_j = opt[i][j][1].from_j;
				opt[0][0][1].from_l = opt[i][j][1].from_l;
				opt[0][0][1].k = opt[i][j][1].k;
				opt[0][0][1].move_type = opt[i][j][1].move_type;
			}
		}
	}
    //start from dimension 2
	long long p=2;
	if(opt[n][m][1].k != k){
		do{
			for(long long i=0; i<=n; i++)
				for(long long j=0; j<=m; j++)
					opt[i][j].reserve(p+1);
			for(long long i=1; i<=n; i++){
				for(long long j=1; j<=m; j++){
					long long sol_top, sol_left, sol_jump;
					sol_top = opt[i-1][j][p].total_sweet + sweetness[i][j];
				   	sol_left = opt[i][j-1][p].total_sweet + sweetness[i][j];
					sol_jump = opt[0][0][p-1].total_sweet + sweetness[i][j] - (opt[0][0][p-1].k+1*c);
					if(sol_top >= sol_left && sol_top>= sol_jump){
               	 		opt[i][j][p].total_sweet = sol_top;
                		opt[i][j][p].i = i;
                		opt[i][j][p].k = j;
                		opt[i][j][p].l = p;
                		opt[i][j][p].from_i = opt[i-1][j][p].i;
                		opt[i][j][p].from_j = opt[i-1][j][p].j;
                		opt[i][j][p].from_l = opt[i-1][j][p].l;
                		opt[i][j][p].k = opt[i][j][p].k;
                		opt[i][j][p].move_type = "Move";
					}
					else if(sol_left > sol_top && sol_left > sol_jump){
						opt[i][j][p].total_sweet = sol_left;
                        opt[i][j][p].i = i;
                        opt[i][j][p].k = j;
                        opt[i][j][p].l = p;
                        opt[i][j][p].from_i = opt[i][j-1][p].i;
                        opt[i][j][p].from_j = opt[i][j-1][p].j;
                        opt[i][j][p].from_l = opt[i][j-1][p].l;
                        opt[i][j][p].k = opt[i][j][p].k;
                        opt[i][j][p].move_type = "Move";
					}
					else if(sol_jump > sol_top && sol_jump > sol_left){
                        opt[i][j][p].total_sweet = sol_jump;
                        opt[i][j][p].i = i;
                        opt[i][j][p].k = j;
                        opt[i][j][p].l = p;
                        opt[i][j][p].from_i = opt[0][0][p-1].i;
                        opt[i][j][p].from_j = opt[0][0][p-1].j;
                        opt[i][j][p].from_l = opt[0][0][p-1].l;
                        opt[i][j][p].k = opt[i][j][p].k+1;
                        opt[i][j][p].move_type = "Jump";
					}
				}
			}
			p++;
		}
		while(opt[i][j][p-1].k!=k);
		p--;
	}
	
	//print path
}

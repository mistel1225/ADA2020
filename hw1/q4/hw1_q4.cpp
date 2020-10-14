#include <iostream>
#include <vector>
#include <string>
using namespace std;

class cell{
	public:
		long long total_sweet=0;
		long long x=0;
		long long y=0;
		long long z=0;
		string move_type;
		long long from_x=0;
		long long from_y=0;
		long long from_z=0;
		long long k=0;
		long long k_remain=0;
		bool done=0;
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
	/*global solution on dimension 1*/
	opt[0][0][1].total_sweet=sweetness[1][1];
	opt[0][0][1].x = 1;
	opt[0][0][1].y = 1;
	opt[0][0][1].z = 1;
	opt[0][0][1].move_type = "init";
	opt[0][0][1].from_x=1;
	opt[0][0][1].from_y=1;
	opt[0][0][1].from_z=1;
	opt[0][0][1].k = 0;
	opt[0][0][1].k_remain = k;
	
	/*number of z axis*/
	long long p=1;
	long long sol_left, sol_top, sol_jump, global_sol_flag=0;
	for(long long i=1; i<=n; i++){
		for(long long j=1; j<=m; j++){
			for(long long l=1; l<=p; l++){
				if(opt[i][j][l].done == 0){
					opt[i][j][l].done = 1;
					sol_left = opt[i][j-1][l].total_sweet + sweetness[i][j] - opt[0][0][l].k*c;
					sol_top = opt[i-1][j][l].total_sweet + sweetness[i][j] - opt[0][0][l].k*c;
					if(sol_left>=sol_top){
						opt[i][j][l].total_sweet = sol_left;
						opt[i][j][l].x = i;
						opt[i][j][l].y = j;
						opt[i][j][l].z = l;
						opt[i][j][l].move_type = "Move";
						opt[i][j][l].from_x = i;
						opt[i][j][l].from_y = j-1;
						opt[i][j][l].from_z = l;
						opt[i][j][l].k = opt[0][0][l].k;
						opt[i][j][l].k_remain = opt[0][0][l].k_remain;
						//update global solution on l dimension
						if(opt[0][0][l].total_sweet<opt[i][j][l].total_sweet){
							opt[0][0][l].total_sweet = opt[i][j][l].total_sweet;
							opt[0][0][l].x = opt[i][j][l].x;
							opt[0][0][l].y = opt[i][j][l].y;
							opt[0][0][l].z = opt[i][j][l].z;
							opt[0][0][l].move_type = "Move";
							opt[0][0][l].from_x = opt[i][j][l].from_x;
							opt[0][0][l].from_y = opt[i][j][l].from_y;
							opt[0][0][l].from_z = opt[i][j][l].from_z;
							opt[0][0][l].k = opt[i][j][l].k;
							opt[0][0][l].k_remain = opt[i][j][l].k_remain;
						}
					}
					else{
                        opt[i][j][l].total_sweet = sol_top;
                        opt[i][j][l].x = i;
                        opt[i][j][l].y = j;
                        opt[i][j][l].z = l;
                        opt[i][j][l].move_type = "Move";
                        opt[i][j][l].from_x = i-1;
                        opt[i][j][l].from_y = j;
                        opt[i][j][l].from_z = l;
                        opt[i][j][l].k = opt[0][0][l].k;
                        opt[i][j][l].k_remain = opt[0][0][l].k_remain;
							//update global solution on l dimension
                        	if(opt[0][0][l].total_sweet<opt[i][j][l].total_sweet){
                            	opt[0][0][l].total_sweet = opt[i][j][l].total_sweet;
                            	opt[0][0][l].x = opt[i][j][l].x;
                            	opt[0][0][l].y = opt[i][j][l].y;
                            	opt[0][0][l].z = opt[i][j][l].z;
                            	opt[0][0][l].move_type = "Move";
                            	opt[0][0][l].from_x = opt[i][j][l].x;
                            	opt[0][0][l].from_y = opt[i][j][l].y;
                            	opt[0][0][l].from_z = opt[i][j][l].z;
                            	opt[0][0][l].k = opt[i][j][l].k;
                            	opt[0][0][l].k_remain = opt[i][j][l].k_remain;
                        	}	
					}
					
					
					
					long long temp_l = l;
         			
					sol_jump = opt[0][0][l].total_sweet + sweetness[i][j] - (opt[0][0][l].k+1)*c;
					
					//jump would be a choice
					if(opt[0][0][l].k_remain>0 && sol_jump>sol_top && sol_jump>sol_left){
						do{
							p++;
							//initialize
							for(long long i_temp=0; i_temp<=n; i_temp++)
								for(long long j_temp=0; j_temp<=m; j_temp++)
									opt[i_temp][j_temp].reserve(p+1);
							opt[0][0][p].total_sweet = sol_jump;
							opt[0][0][p].x = i;
							opt[0][0][p].y = j;
							opt[0][0][p].z = p;
							opt[0][0][p].from_x = opt[0][0][l].x;
							opt[0][0][p].from_y = opt[0][0][l].y;
							opt[0][0][p].from_z = opt[0][0][l].z;
							opt[0][0][p].move_type = "Jump";
							opt[0][0][p].k = opt[0][0][l].k+1;
							opt[0][0][p].k_remain = opt[0][0][l].k_remain -1;
						
							for(long long i_temp=1; i_temp<i; i_temp++){
								for(long long j_temp=1; j_temp<=m; j_temp++){
									opt[i_temp][j_temp][p].total_sweet = opt[i_temp][j_temp][l].total_sweet;
									opt[i_temp][j_temp][p].x = i_temp;
									opt[i_temp][j_temp][p].y = j_temp;
									opt[i_temp][j_temp][p].z = p;
									opt[i_temp][j_temp][p].move_type = opt[i_temp][j_temp][l].move_type;
									opt[i_temp][j_temp][p].from_x = opt[i_temp][j_temp][l].from_x;
									opt[i_temp][j_temp][p].from_y = opt[i_temp][j_temp][l].from_y;
									opt[i_temp][j_temp][p].from_z = opt[i_temp][j_temp][l].from_z;
									opt[i_temp][j_temp][p].k = opt[i_temp][j_temp][l].k+1;
									opt[i_temp][j_temp][p].k_remain = opt[i_temp][j_temp][l].k_remain-1;
									opt[i_temp][j_temp][p].done = 1;
								} 
							}

							for(long long j_temp=1; j_temp<j; j_temp++){
								opt[i][j_temp][p].total_sweet = opt[i][j_temp][l].total_sweet;
								opt[i][j_temp][p].x = opt[i][j_temp][l].x;
								opt[i][j_temp][p].y = opt[i][j_temp][l].y;
								opt[i][j_temp][p].z = p;
                            	opt[i][j_temp][p].move_type = opt[i][j_temp][l].move_type;
                            	opt[i][j_temp][p].from_x = opt[i][j_temp][l].from_x;
                            	opt[i][j_temp][p].from_y = opt[i][j_temp][l].from_y;
                            	opt[i][j_temp][p].from_z = opt[i][j_temp][l].from_z;
                            	opt[i][j_temp][p].k = opt[i][j_temp][l].k+1;
                            	opt[i][j_temp][p].k_remain = opt[i][j_temp][l].k_remain-1;
                            	opt[i][j_temp][p].done = 1;
							}
							opt[i][j][p].total_sweet = opt[0][0][p].total_sweet;
                        	opt[i][j][p].x = i;
                        	opt[i][j][p].y = j;
                        	opt[i][j][p].z = p;
                        	opt[i][j][p].from_x = opt[0][0][p].x;
                        	opt[i][j][p].from_y = opt[0][0][p].y;
                        	opt[i][j][p].from_z = opt[0][0][p].z;
                        	opt[i][j][p].move_type = "Jump";
                        	opt[i][j][p].k = opt[0][0][p].k+1;
                        	opt[i][j][p].k_remain = opt[0][0][p].k_remain -1;
							opt[i][j][p].done = 1;
							l=p;
						}
						while(opt[0][0][l].k_remain>0 && (sol_jump = opt[i][j][l].total_sweet + sweetness[i][j] - (opt[0][0][l].k+1)*c)>opt[i][j][l].total_sweet)
					}
					l = temp_l;
				}
			}
		}
	}
}

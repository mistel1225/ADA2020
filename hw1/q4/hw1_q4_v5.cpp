#include <iostream>
#include <vector>
#include <string>
using namespace std;
//#define DEBUG0
class cell{
	public:
		long long total_sweet=0;
		long long i=1;
		long long j=1;
		long long l=0;
		long long from_i=1;
		long long from_j=1;
		long long from_l=0;
		long long k=0;
		bool move_type;
};
void get_path(long long n, long long m, long long p, vector<vector<vector<cell>>> &opt, vector<cell> &path_record){
	if(opt[n][m][p].i==1 && opt[n][m][p].j==1 && opt[n][m][p].l==0){
		return;
	}
	get_path(opt[n][m][p].from_i, opt[n][m][p].from_j, opt[n][m][p].from_l, opt, path_record);
	path_record.push_back(opt[n][m][p]);
}

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	long long n, m, k, c;
	cin>>n>>m>>k>>c;
	long long sweetness[n+1][m+1];
	for(long long i=1; i<=n; i++)
		for(long long j=1; j<=m; j++)
			cin>>sweetness[i][j];
	vector<vector<vector<cell>>>  opt(n+1, vector<vector<cell>>(m+1, vector<cell>(k+1)));
	//initialize opt
	//initialize global opt sol on dimension 1
   	opt[0][0][0].total_sweet = sweetness[1][1];
	opt[0][0][0].i = 1;
	opt[0][0][0].j = 1;
	long long temp_i=1 , temp_j =1;
	//initialize border case on opt
	opt[1][1][0].total_sweet = sweetness[1][1];
	opt[1][1][0].i = 1;
	opt[1][1][0].j = 1;
	opt[1][1][0].l = 0;
	opt[1][1][0].k = 0;
    for(long long i=2; i<=n; i++){
        opt[i][1][0].total_sweet = opt[i-1][1][0].total_sweet + sweetness[i][1];
        opt[i][1][0].i = i;
        opt[i][1][0].j = 1;
        opt[i][1][0].l = 0;
        opt[i][1][0].from_i = i-1;
        opt[i][1][0].from_j = 1;
        opt[i][1][0].from_l = 0;
        opt[i][1][0].k = 0;
        opt[i][1][0].move_type = 0;
	    if(opt[i][1][0].total_sweet > opt[0][0][0].total_sweet){
          	opt[0][0][0].total_sweet = opt[i][1][0].total_sweet;
			temp_i=i;
			temp_j=1;
        }
    }
	
	for(long long j=2; j<=m; j++){
		opt[1][j][0].total_sweet = opt[1][j-1][0].total_sweet + sweetness[1][j];
		opt[1][j][0].i = 1;
		opt[1][j][0].j = j;
		opt[1][j][0].l = 0;
		opt[1][j][0].from_i = 1;
		opt[1][j][0].from_j = j-1;
		opt[1][j][0].from_l = 0;
		opt[1][j][0].k = 0;
		opt[1][j][0].move_type = 0;
        if(opt[1][j][0].total_sweet > opt[0][0][0].total_sweet){
            opt[0][0][0].total_sweet = opt[1][j][0].total_sweet;
			temp_i = 1;
			temp_j = j;
        }
	}
	for(long long i=2; i<=n; i++){
		for(long long j=2; j<=m; j++){
			//from top
			if(opt[i-1][j][0].total_sweet >= opt[i][j-1][0].total_sweet){
				opt[i][j][0].total_sweet = opt[i-1][j][0].total_sweet + sweetness[i][j];
				opt[i][j][0].i = i;
				opt[i][j][0].j = j;
				opt[i][j][0].l = 0;
				opt[i][j][0].from_i = i-1;
				opt[i][j][0].from_j = j;
				opt[i][j][0].from_l = 0;
				opt[i][j][0].k = 0;
				opt[i][j][0].move_type = 0;
			}
			//from left
			else{
                opt[i][j][0].total_sweet = opt[i][j-1][0].total_sweet + sweetness[i][j];
                opt[i][j][0].i = i;
                opt[i][j][0].j = j;
                opt[i][j][0].l = 0;
                opt[i][j][0].from_i = i;
                opt[i][j][0].from_j = j-1;
                opt[i][j][0].from_l = 0;
                opt[i][j][0].k = 0;
                opt[i][j][0].move_type = 0;
			}
			if(opt[i][j][0].total_sweet > opt[0][0][0].total_sweet){
				opt[0][0][0].total_sweet = opt[i][j][0].total_sweet;
				temp_i = i;
				temp_j = j;
			}
		}
	}
	opt[0][0][0].total_sweet = opt[temp_i][temp_j][0].total_sweet;
    opt[0][0][0].i = temp_i;
    opt[0][0][0].j = temp_j;
    opt[0][0][0].l = 0;
    opt[0][0][0].from_i = opt[temp_i][temp_j][0].from_i;
    opt[0][0][0].from_j = opt[temp_i][temp_j][0].from_j;
    opt[0][0][0].from_l = opt[temp_i][temp_j][0].from_l;
    opt[0][0][0].k = opt[temp_i][temp_j][0].k;
    opt[0][0][0].move_type = opt[temp_i][temp_j][0].move_type;
	
	
	long long p=0;
    //start from dimension 1
	if(k != 0){
		long long i=0, j=0, sol_top, sol_left, sol_jump;
		for(p=1; p<=k; p++){
			//initialize opt[0][0][p] on p dim			
			if(opt[0][0][p-1].total_sweet - (opt[0][0][p-1].k+1)*c >= 0){
				opt[1][1][p].total_sweet = opt[0][0][p-1].total_sweet + sweetness[1][1] - (opt[0][0][p-1].k+1)*c;
				opt[1][1][p].i = 1;
				opt[1][1][p].j = 1;
				opt[1][1][p].l = p;
				opt[1][1][p].from_i = opt[0][0][p-1].i;
				opt[1][1][p].from_j = opt[0][0][p-1].j;
				opt[1][1][p].from_l = opt[0][0][p-1].l;
				opt[1][1][p].k = opt[0][0][p-1].k+1;
				opt[1][1][p].move_type = 1;
			}
			else{
				opt[1][1][p].total_sweet = sweetness[1][1];
				opt[1][1][p].i = 1;
				opt[1][1][p].j = 1;
				opt[1][1][p].l = p;
				opt[1][1][p].from_i = 1;
				opt[1][1][p].from_j = 1;
				opt[1][1][p].from_l = 0;
				opt[1][1][p].k = 0;
				opt[1][1][p].move_type = 0;
			}
            opt[0][0][p].total_sweet = opt[1][1][p].total_sweet;
			//deal with border case
    		temp_i=1, temp_j=1;
			for(i=2; i<=n; i++){
        		sol_top = opt[i-1][1][p].total_sweet + sweetness[i][1] - (opt[i-1][1][p].k)*c;
				sol_jump = opt[0][0][p-1].total_sweet + sweetness[i][1] - (opt[0][0][p-1].k+1)*c;
                if(sol_jump>=sol_top){
                    opt[i][1][p].total_sweet = sol_jump;
                    opt[i][1][p].i = i;
                    opt[i][1][p].j = 1;
                    opt[i][1][p].l = p;
                    opt[i][1][p].from_i = opt[0][0][p-1].i;
                    opt[i][1][p].from_j = opt[0][0][p-1].j;
                    opt[i][1][p].from_l = opt[0][0][p-1].l;
                    opt[i][1][p].k = opt[0][0][p-1].k+1;
                    opt[i][1][p].move_type = 1;
                }
				else{
					opt[i][1][p].total_sweet = sol_top;
        			opt[i][1][p].i = i;
        			opt[i][1][p].j = 1;
        			opt[i][1][p].l = p;
        			opt[i][1][p].from_i = i-1;
        			opt[i][1][p].from_j = 1;
        			opt[i][1][p].from_l = p;
        			opt[i][1][p].k = opt[i-1][1][p].k;
        			opt[i][1][p].move_type = 0;
				}
				//update local opt sol
        		if(opt[i][1][p].total_sweet > opt[0][0][p].total_sweet){
            		opt[0][0][p].total_sweet = opt[i][1][p].total_sweet;
					temp_i = i;
					temp_j = 1;
        		}
    		}
            for(j=2; j<=m; j++){
                sol_left = opt[1][j-1][p].total_sweet + sweetness[1][j] - (opt[1][j-1][p].k)*c;
                sol_jump = opt[0][0][p-1].total_sweet + sweetness[1][j] - (opt[0][0][p-1].k+1)*c;
                if(sol_jump>=sol_left){
                    opt[1][j][p].total_sweet = sol_jump;
                    opt[1][j][p].i = 1;
                    opt[1][j][p].j = j;
                    opt[1][j][p].l = p;
                    opt[1][j][p].from_i = opt[0][0][p-1].i;
                    opt[1][j][p].from_j = opt[0][0][p-1].j;
                    opt[1][j][p].from_l = opt[0][0][p-1].l;
                    opt[1][j][p].k = opt[0][0][p-1].k+1;
                    opt[1][j][p].move_type = 1;
                }
				else{
                    opt[1][j][p].total_sweet = sol_left;
                    opt[1][j][p].i = 1;
                    opt[1][j][p].j = j;
                    opt[1][j][p].l = p;
                    opt[1][j][p].from_i = 1;
                    opt[1][j][p].from_j = j-1;
                    opt[1][j][p].from_l = p;
                    opt[1][j][p].k = opt[1][j-1][p].k;
                    opt[1][j][p].move_type = 0;
                }

                if(opt[1][j][p].total_sweet > opt[0][0][p].total_sweet){
                    opt[0][0][p].total_sweet = opt[1][j][p].total_sweet;
					temp_i = 1;
					temp_j = j;
                }
            }
			for(i=2; i<=n; i++){
				for(j=2; j<=m; j++){
					sol_top = opt[i-1][j][p].total_sweet + sweetness[i][j] - (opt[i-1][j][p].k)*c;
				   	sol_left = opt[i][j-1][p].total_sweet + sweetness[i][j] - (opt[i][j-1][p].k)*c;
					sol_jump = opt[0][0][p-1].total_sweet + sweetness[i][j] - (opt[0][0][p-1].k+1)*c;
					#ifdef DEBUG 
					cout<<"sol_top, sol_left, sol_jump = "<<sol_top<<" "<<sol_left<<" "<<sol_jump<<endl;
					#endif
                    if(sol_jump >= sol_top && sol_jump >= sol_left){
                        opt[i][j][p].total_sweet = sol_jump;
                        opt[i][j][p].i = i;
                        opt[i][j][p].j = j;
                        opt[i][j][p].l = p;
                        opt[i][j][p].from_i = opt[0][0][p-1].i;
                        opt[i][j][p].from_j = opt[0][0][p-1].j;
                        opt[i][j][p].from_l = opt[0][0][p-1].l;
                        opt[i][j][p].k = opt[0][0][p-1].k+1;
                        opt[i][j][p].move_type = 1;
                    }
					else if(sol_top > sol_left && sol_top > sol_jump){
               	 		opt[i][j][p].total_sweet = sol_top;
                		opt[i][j][p].i = i;
                		opt[i][j][p].j = j;
                		opt[i][j][p].l = p;
                		opt[i][j][p].from_i = opt[i-1][j][p].i;
                		opt[i][j][p].from_j = opt[i-1][j][p].j;
                		opt[i][j][p].from_l = opt[i-1][j][p].l;
                		opt[i][j][p].k = opt[i-1][j][p].k;
                		opt[i][j][p].move_type = 0;
					}
					else if(sol_left > sol_top && sol_left > sol_jump){
						opt[i][j][p].total_sweet = sol_left;
                        opt[i][j][p].i = i;
                        opt[i][j][p].j = j;
                        opt[i][j][p].l = p;
                        opt[i][j][p].from_i = opt[i][j-1][p].i;
                        opt[i][j][p].from_j = opt[i][j-1][p].j;
                        opt[i][j][p].from_l = opt[i][j-1][p].l;
                        opt[i][j][p].k = opt[i][j-1][p].k;
                        opt[i][j][p].move_type = 0;
					}
					if(opt[i][j][p].total_sweet > opt[0][0][p].total_sweet){
						opt[0][0][p].total_sweet = opt[i][j][p].total_sweet;
						temp_i=i;
						temp_j=j;
					}
				}
			}
            opt[0][0][p].total_sweet = opt[temp_i][temp_j][p].total_sweet;
            opt[0][0][p].i = temp_i;
            opt[0][0][p].j = temp_j;
          	opt[0][0][p].l = p;
            opt[0][0][p].from_i = opt[temp_i][temp_j][p].from_i;
            opt[0][0][p].from_j = opt[temp_i][temp_j][p].from_j;
          	opt[0][0][p].from_l = opt[temp_i][temp_j][p].from_l;
            opt[0][0][p].k = opt[temp_i][temp_j][p].k;
            opt[0][0][p].move_type = opt[temp_i][temp_j][p].move_type;
			if(opt[n][m][p].total_sweet<=opt[n][m][p-1].total_sweet){
				p--;
				break;
			}
			else if(opt[0][0][p].k==k)
				break;
		}

	}
	cout<<opt[n][m][p].total_sweet<<endl;
	vector<cell> path_record;
	get_path(n, m, p, opt, path_record);
	cout<<path_record.size()<<endl;
	for(long long i=0; i<path_record.size(); i++){
		if(path_record[i].move_type==0)
			cout<<"Move ";
		else if(path_record[i].move_type==1)
			cout<<"Jump ";
		cout<<path_record[i].i-1<<" "<<path_record[i].j-1<<endl;
	}
	return 0;
}


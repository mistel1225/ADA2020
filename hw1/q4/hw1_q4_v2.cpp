#include <iostream>
#include <vector>
#include <string>
using namespace std;
//#define DEBUG0
class cell{
	public:
		long long total_sweet=0;
		long long i=0;
		long long j=0;
		long long l=0;
		long long from_i=1;
		long long from_j=1;
		long long from_l=0;
		long long k=0;
		string move_type="";
};
void get_path(long long n, long long m, long long p, vector<vector<vector<cell>>> &opt, vector<string> &path_record){
	if(opt[n][m][p].i==0 && opt[n][m][p].j==0 && opt[n][m][p].l==0){
		return;
	}
	get_path(opt[n][m][p].from_i, opt[n][m][p].from_j, opt[n][m][p].from_l, opt, path_record);
	path_record.push_back(opt[n][m][p].move_type);
	path_record[path_record.size()-1]+=" "+to_string(opt[n][m][p].i)+" "+to_string(opt[n][m][p].j);
}

int main(){
	long long n, m, k, c;
	cin>>n>>m>>k>>c;
	vector<vector<long long>> sweetness(n, vector<long long>(m));
	for(long long i=0; i<n; i++)
		for(long long j=0; j<m; j++)
			cin>>sweetness[i][j];
	vector<vector<vector<cell>>>  opt(n, vector<vector<cell>>(m, vector<cell>(k)));
	
	//initialize global opt sol on dimension 1
   	cell global_opt;
	global_opt.total_sweet = sweetness[0][0];
	global_opt.i = 0;
	global_opt.j = 0;
	global_opt.l = 0;
	global_opt.k = 0;
	
	//initialize border case on opt
	opt[0][0][0].total_sweet = sweetness[0][0];
	opt[0][0][0].i = 0;
	opt[0][0][0].j = 0;
	opt[0][0][0].l = 0;
	opt[0][0][0].k = 0;
    for(long long i=1; i<n; i++){
        opt[i][0][0].total_sweet = opt[i-1][0][0].total_sweet + sweetness[i][0];
        opt[i][0][0].i = i;
        opt[i][0][0].j = 0;
        opt[i][0][0].l = 0;
        opt[i][0][0].from_i = i-1;
        opt[i][0][0].from_j = 0;
        opt[i][0][0].from_l = 0;
        opt[i][0][0].k = 0;
        opt[i][0][0].move_type = "Move";
	    if(opt[i][0][0].total_sweet > global_opt.total_sweet){
          	global_opt.total_sweet = opt[i][0][0].total_sweet;
            global_opt.i = opt[i][0][0].i;
            global_opt.j = opt[i][0][0].j;
            global_opt.l = opt[i][0][0].l;
            global_opt.from_i = opt[i][0][0].from_i;
            global_opt.from_j = opt[i][0][0].from_j;
            global_opt.from_l = opt[i][0][0].from_l;
            global_opt.k = opt[i][0][0].k;
        	global_opt.move_type = opt[i][0][0].move_type;
        }
    }
	
	for(long long j=1; j<m; j++){
		opt[0][j][0].total_sweet = opt[0][j-1][0].total_sweet + sweetness[0][j];
		opt[0][j][0].i = 0;
		opt[0][j][0].j = j;
		opt[0][j][0].l = 0;
		opt[0][j][0].from_i = 0;
		opt[0][j][0].from_j = j-1;
		opt[0][j][0].from_l = 0;
		opt[0][j][0].k = 0;
		opt[0][j][0].move_type = "Move";
        if(opt[0][j][0].total_sweet > global_opt.total_sweet){
            global_opt.total_sweet = opt[0][j][0].total_sweet;
            global_opt.i = opt[0][j][0].i;
            global_opt.j = opt[0][j][0].j;
            global_opt.l = opt[0][j][0].l;
            global_opt.from_i = opt[0][j][0].from_i;
            global_opt.from_j = opt[0][j][0].from_j;
            global_opt.from_l = opt[0][j][0].from_l;
            global_opt.k = opt[0][j][0].k;
            global_opt.move_type = opt[0][j][0].move_type;
        }
	}
	for(long long i=1; i<n; i++){
		for(long long j=1; j<m; j++){
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
				opt[i][j][0].move_type = "Move";
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
                opt[i][j][0].move_type = "Move";
			}
			if(opt[i][j][0].total_sweet > global_opt.total_sweet){
				global_opt.total_sweet = global_opt.total_sweet;
				global_opt.i = opt[i][j][0].i;
				global_opt.j = opt[i][j][0].j;
				global_opt.l = opt[i][j][0].l;
				global_opt.from_i = opt[i][j][0].from_i;
				global_opt.from_j = opt[i][j][0].from_j;
				global_opt.from_l = opt[i][j][0].from_l;
				global_opt.k = opt[i][j][0].k;
				global_opt.move_type = opt[i][j][0].move_type;
			}
		}
	}
	#ifdef DEBUG0
	cout<<"===========(from_i, from_j, from_l) on dim 1==========="<<endl;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++)
			cout<<"(i, j, l) = "<<opt[i][j][0].from_i<<", "<<opt[i][j][0].from_j<<", "<<opt[i][j][0].from_l<<" ";
		cout<<endl;
	}
	cout<<"global sol on dim 1 = "<<opt[0][0][0].total_sweet<<endl;
	#endif
	long long p=0;
    //start from dimension 2
	if(opt[n-1][m-1][0].k != k){
		p++;
		long long i=0, j=0, sol_top, sol_left, sol_jump;
		while(1){
			#ifdef DEBUG1
			for(i=0; i<n; i++){
				for(j=0; j<m; j++){
					cout<<opt[i][j].capacity()<<" ";
				}
				cout<<endl;
			}
			#endif
			//initialize opt[0][0][p] on p dim
			
			if(global_opt.total_sweet - (global_opt.k+1)*c >= 0){
				opt[1][1][p].total_sweet = global_opt.total_sweet + sweetness[1][1] - (opt[0][0][p-1].k+1)*c;
				opt[1][1][p].i = 1;
				opt[1][1][p].j = 1;
				opt[1][1][p].l = p;
				opt[1][1][p].from_i = opt[0][0][p-1].i;
				opt[1][1][p].from_j = opt[0][0][p-1].j;
				opt[1][1][p].from_l = opt[0][0][p-1].l;
				opt[1][1][p].k = opt[0][0][p-1].k+1;
				opt[1][1][p].move_type = "Jump";
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
				opt[1][1][p].move_type = "Move";
			}
            opt[0][0][p].total_sweet = opt[1][1][p].total_sweet;
            opt[0][0][p].i = opt[1][1][p].i;
            opt[0][0][p].j = opt[1][1][p].j;
            opt[0][0][p].l = opt[1][1][p].l;
            opt[0][0][p].from_i = opt[1][1][p].from_i;
            opt[0][0][p].from_j = opt[1][1][p].from_j;
            opt[0][0][p].from_l = opt[1][1][p].from_l;
            opt[0][0][p].k = opt[1][1][p].k;
            opt[0][0][p].move_type = opt[1][1][p].move_type;
			//deal with border case
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
                    opt[i][1][p].move_type = "Jump";
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
        			opt[i][1][p].move_type = "Move";
				}
				//update local opt sol
        		if(opt[i][1][p].total_sweet > opt[0][0][p].total_sweet){
            		opt[0][0][p].total_sweet = opt[i][1][p].total_sweet;
            		opt[0][0][p].i = opt[i][1][p].i;
            		opt[0][0][p].j = opt[i][1][p].j;
            		opt[0][0][p].l = opt[i][1][p].l;
            		opt[0][0][p].from_i = opt[i][1][p].from_i;
            		opt[0][0][p].from_j = opt[i][1][p].from_j;
            		opt[0][0][p].from_l = opt[i][1][p].from_l;
            		opt[0][0][p].k = opt[i][1][p].k;
            		opt[0][0][p].move_type = opt[i][1][p].move_type;
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
                    opt[1][j][p].move_type = "Jump";
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
                    opt[1][j][p].move_type = "Move";
                }

                if(opt[1][j][p].total_sweet > opt[0][0][p].total_sweet){
                    opt[0][0][p].total_sweet = opt[1][j][p].total_sweet;
                    opt[0][0][p].i = opt[1][j][p].i;
                    opt[0][0][p].j = opt[1][j][p].j;
                    opt[0][0][p].l = opt[1][j][p].l;
                    opt[0][0][p].from_i = opt[1][j][p].from_i;
                    opt[0][0][p].from_j = opt[1][j][p].from_j;
                    opt[0][0][p].from_l = opt[1][j][p].from_l;
                    opt[0][0][p].k = opt[1][j][p].k;
                    opt[0][0][p].move_type = opt[1][j][p].move_type;
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
                        opt[i][j][p].move_type = "Jump";
                    }
					else if(sol_top >= sol_left && sol_top>= sol_jump){
               	 		opt[i][j][p].total_sweet = sol_top;
                		opt[i][j][p].i = i;
                		opt[i][j][p].j = j;
                		opt[i][j][p].l = p;
                		opt[i][j][p].from_i = opt[i-1][j][p].i;
                		opt[i][j][p].from_j = opt[i-1][j][p].j;
                		opt[i][j][p].from_l = opt[i-1][j][p].l;
                		opt[i][j][p].k = opt[i-1][j][p].k;
                		opt[i][j][p].move_type = "Move";
					}
					else if(sol_left >= sol_top && sol_left >= sol_jump){
						opt[i][j][p].total_sweet = sol_left;
                        opt[i][j][p].i = i;
                        opt[i][j][p].j = j;
                        opt[i][j][p].l = p;
                        opt[i][j][p].from_i = opt[i][j-1][p].i;
                        opt[i][j][p].from_j = opt[i][j-1][p].j;
                        opt[i][j][p].from_l = opt[i][j-1][p].l;
                        opt[i][j][p].k = opt[i][j-1][p].k;
                        opt[i][j][p].move_type = "Move";
					}
					if(opt[i][j][p].total_sweet > opt[0][0][p].total_sweet){
						opt[0][0][p].total_sweet = opt[i][j][p].total_sweet;
						opt[0][0][p].i = opt[i][j][p].i;
						opt[0][0][p].j = opt[i][j][p].j;
						opt[0][0][p].l = opt[i][j][p].l;
						opt[0][0][p].from_i = opt[i][j][p].from_i;
						opt[0][0][p].from_j = opt[i][j][p].from_j;
						opt[0][0][p].from_l = opt[i][j][p].from_l;
						opt[0][0][p].k = opt[i][j][p].k;
						opt[0][0][p].move_type = opt[i][j][p].move_type;
					}
				}
			}
			#ifdef DEBUG
			cout<<"=========================="<<endl;
			cout<<"local k in dim "<<p<<" = "<<opt[n][m][p].k<<endl;
			cout<<"local sol in dim "<<p<<" = "<<opt[n][m][p].total_sweet<<endl;
			#endif
			if(opt[n][m][p].k == k or opt[n][m][p].total_sweet<=opt[n][m][p-1].total_sweet or p-1==k or opt[0][0][p].total_sweet<=opt[0][0][p-1].total_sweet){
        		if(opt[n][m][p].total_sweet<=opt[n][m][p-1].total_sweet){
					p--;
				}
				break;
			}
        	else
            	p++;
		}
	}
	cout<<opt[n][m][p].total_sweet<<endl;
	vector<string> path_record;
	get_path(n, m, p, opt, path_record);
	cout<<path_record.size()<<endl;
	for(long long i=0; i<path_record.size(); i++){
		cout<<path_record[i]<<endl;
	}
	return 0;
}

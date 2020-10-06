#include <string>
#include <vector>
#include "helper.h"
using namespace std;
using namespace Memory;

bool sortcol2(const vector<long long>& v1, const vector<long long>& v2){
	return v1[2] < v2[2];
}


void find_damage_rec(int start, int end, vector<vector<long long>> &event_record){
	if(start==end)
		return;
	int mid = (start+end)/2;
	find_damage_rec(start, mid, event_record);
	find_damage_rec(mid+1, end, event_record);
	vector<vector<long long>> left_player(mid-end+1, vector<long long>(4, 0));
	vector<vector<long long>> right_bumb(end-mid+1, vector<long long>(4, 0));
	long long left_player_num=0, right_bumb_num=0;
	
	for(int i=start; i<=mid; i++){
		if(event_record[i][0]==0){
			for(int j=1; j<=4; i++)
				left_player[left_player_num][j] = event_record[i][j];
			left_player_num++;
		}
	}
	for(int i=mid+1; i<=end; i++){
		if(event_record[i][0]==1){
			for(int j=1; j<=4; j++)
				right_bumb[right_bumb_num][j] = right_bumb[i][j];
			right_bumb_num++;
		}	
	}
	
	sort(left_player.begin(), left_player.end(), sortcol2);
	sort(right_bumb.begin(), right_bumb.end(), sortcol2);
	int left_player_num_temp = left_player_num-1;
	for(int i=right_bumb_num-1; i>=0; i--){
		if(right_bumb[i][2]>=left_player[left_player_num_temp][2])
			add(right_bumb[i][0], right_bumb[i][1], right_bumb[i][3]);
		else{
			left_player[left_player_num_temp][3] = get(left_player[left_player_num_temp][1]);
			left_player_num_temp--;
		}
	}
	for(int i=0; i<left_player_num; i++)
		event_record[left_player[i][0]][4] = left_player[i][3];	
}

int main(){
	int N, M;
	cin>>N>>M;
	vector<vector<long long>> event_record(100000, vector<long long>(5, 0));
	long long c, l, r, d, p, k, event_num=0;
	string in;
	for(long long i=0; i<M; i++){
		cin>>in;
		if(in=="P"){
			event_record[i][0] = 0;//player i
			event_record[i][1] = event_num;
			event_num++;
			cin>>event[i][2]>>event_record[i][3];
		}
		else{
			event_record[i][0] = 1;//bumb i
			cin>>event_record[i][1]>>event_record[i][2]>>event_record[i][3]>>event_record[i][4];
			event_num++;
		}
	}
	find_damage_rec(0, M-1, event_record);
	for(int i=0; i<M; i++)
		if(event_record[i][0]==0)
			cout<<event_record[i][4]<<endl;
	return 0;
}

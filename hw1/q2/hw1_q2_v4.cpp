#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "helper.h"
using namespace std;
using namespace Memory;
//#define DEBUG

bool sortcol2(const vector<long long>& v1, const vector<long long>& v2){
	return v1[2] < v2[2];
}


void find_damage_rec(int start, int end, int N, vector<vector<long long>> &event_record){
	int mid = (start+end)/2;
	if(start==end)
		return;
	find_damage_rec(start, mid, N, event_record);
	find_damage_rec(mid+1, end, N, event_record);
	vector<vector<long long>> left_player(mid-start+1, vector<long long>(4, 0));
	vector<vector<long long>> right_bumb(end-mid+1, vector<long long>(4, 0));
	#ifdef DEBUG
	cout<<"==============================="<<endl;
	cout<<"end of recursive, start combine:"<<endl;
	cout<<"start, end, mid: "<<start<<" "<<end<<" "<<mid<<endl;
	#endif
	long long left_player_num=0, right_bumb_num=0;
	
	for(int i=start; i<=mid; i++){
	#ifdef DEBUG1
	cout<<"in the left subproblem"<<endl;
	cout<<"i "<<i<<endl;
	#endif
		if(event_record[i][0]==0){
			for(int j=1; j<=4; j++)
				left_player[left_player_num][j-1] = event_record[i][j];
			left_player_num++;
		}
	}
	for(int i=mid+1; i<=end; i++){
		if(event_record[i][0]==1){
			for(int j=1; j<=4; j++)
				right_bumb[right_bumb_num][j-1] = event_record[i][j];
			right_bumb_num++;
		}	
	}
	if(left_player_num==0 or right_bumb_num==0)
		return;
	sort(left_player.begin(), left_player.begin()+left_player_num, sortcol2);
	sort(right_bumb.begin(), right_bumb.begin()+right_bumb_num, sortcol2);
	#ifdef DEBUG
	cout<<"player list: "<<endl;
	for(int i=0; i<left_player_num; i++){
		for(int j=0; j<4; j++)
			cout<<left_player[i][j]<<" ";
		cout<<endl;
	}
	cout<<"bumb list:"<<endl;
	for(int i=0; i<right_bumb_num; i++){
		for(int j=0; j<4; j++)
			cout<<right_bumb[i][j]<<" ";
		cout<<endl;
	}
	#endif
	int left_player_num_temp = left_player_num-1;
	int right_bumb_num_temp = right_bumb_num-1;
	while(right_bumb_num_temp>=0){
		if(right_bumb[right_bumb_num_temp][2]<left_player[0][2])
			break;
		else if(right_bumb[0][2]>=left_player[left_player_num_temp][2]){
			for(int i=0; i<right_bumb_num_temp; i++){
				add(right_bumb[i][0], right_bumb[i][1], right_bumb[i][3]);
			}
			break;
		}
		if(right_bumb[right_bumb_num_temp][2]>=left_player[left_player_num_temp][2]){
		add(right_bumb[right_bumb_num_temp][0], right_bumb[right_bumb_num_temp][1], right_bumb[right_bumb_num_temp][3]);
			right_bumb_num_temp--;
		}
		else{
			left_player[left_player_num_temp][3] = get(left_player[left_player_num_temp][1]);
			#ifdef DEBUG
			cout<<"damage"<<endl;
			cout<<left_player[left_player_num_temp][3]<<endl;
			#endif
			left_player_num_temp--;
			if(left_player_num_temp<0)
				break;
		}
	}
	for(int i=left_player_num_temp; i>=0; i--)
		left_player[i][3] = get(left_player[i][1]);
	for(int i=0; i<left_player_num; i++)
		event_record[left_player[i][0]][4] += left_player[i][3];
	if(right_bumb_num==1)
		add(right_bumb[0][0], right_bumb[0][1], -1*right_bumb[0][3]);
	else
		reset();
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
			cin>>event_record[i][2]>>event_record[i][3];
		}
		else{
			event_record[i][0] = 1;//bumb i
			cin>>event_record[i][1]>>event_record[i][2]>>event_record[i][3]>>event_record[i][4];
			event_num++;
		}
	}
	find_damage_rec(0, M-1, N, event_record);
	for(int i=0; i<M; i++)
		if(event_record[i][0]==0)
			cout<<event_record[i][4]<<endl;
	return 0;
}

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
//#define DEBUG

class segment{
	public:
		long long id;
		long long L;
		long long R;
		long long W;
		long long selected_num=0;
		segment(long long id, long long L, long long R, long long W){
			this->id = id;
			this->L = L;
			this->R = R;
			this->W = W;
			this->selected_num = 0;
		}
		segment(){
			this->selected_num=0;
		}
};

bool sortbyL(const segment &s1, const segment &s2){
	return s1.L<s2.L;
}
bool operator<(const segment &s1, const segment &s2){
	return s1.R < s2.R;
}
bool operator>(const segment &s1, const segment &s2){
	return s1.R > s2.R;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
	long long N, M, K;
	cin>>N>>M>>K;
	vector<segment> segment_set;
	for(long long i=0; i<N; i++){
		segment seg_in;
		seg_in.id=i;
		cin>>seg_in.L>>seg_in.R>>seg_in.W;
		segment_set.push_back(seg_in);
	}
	//sort by L_i
	sort(segment_set.begin(), segment_set.end(), sortbyL);	
	//init heap
	priority_queue<segment, vector<segment>, less<vector<segment>::value_type>> seg_heap;
	long long L=1, R=K;
	long long target=0;
	while(L<=R){
		long long total=0;
		long long m=L+(R-L)/2;
		#ifdef DEBUG
		cout<<"mid= "<<m<<endl;
		#endif
		long long sum=0;
		long long expired_seg_record[M]={0};//to record when should select segment from 0~M-1
		long long j=0;
		bool flag=0;
		while(!seg_heap.empty())
			seg_heap.pop();
		//don't need to consider cell M
		for(long long i=0; i<M; i++){
			while(j<segment_set.size()&&segment_set[j].L==i){
				seg_heap.push(segment_set[j]);
				j++;
			}
			sum-=expired_seg_record[i];
			while(sum<m){
				if(!seg_heap.empty()){
					if(seg_heap.top().R<=i)
						seg_heap.pop();
					else if(seg_heap.top().W<=(m-sum)){
						total+=seg_heap.top().W;
						expired_seg_record[seg_heap.top().R]+=seg_heap.top().W;
						sum+=seg_heap.top().W;
						seg_heap.pop();
					}
					else if(seg_heap.top().W>(m-sum)){
						total+=(m-sum);
						expired_seg_record[seg_heap.top().R]+=(m-sum);
						segment seg_temp(seg_heap.top().id, seg_heap.top().L, seg_heap.top().R, seg_heap.top().W-(m-sum));
						seg_heap.pop();
						seg_heap.push(seg_temp);
						sum+=(m-sum);
					}
				}
				else{
					flag=1;//couldn't select enough segments
					break;
				}
			}
		}
		//if couldn't select enough segments, then search left problem
		if(flag==1){
			R=m-1;
			continue;
		}
		//could select enough seg and meet the goal we set initially, search right problem
		else if(total<=K){
			target=m;
			L=m+1;
		}
		//could meet the goal we set but the total segment we choose exceed K
		else if(total>K)
			R=m-1;
		#ifdef DEBUG
		cout<<"total= "<<total<<" target= "<<target<<endl;
		#endif
	}
	long long total=0;
	long long sum=0;
	long long expired_seg_record[M]={0};
	long long j=0;
	while(!seg_heap.empty())
		seg_heap.pop();
	for(long long i=0; i<M; i++){
		while(j<segment_set.size()&&segment_set[j].L==i){
			seg_heap.push(segment_set[j]);
			j++;
		}
		sum-=expired_seg_record[i];
		while(sum<target){
			if(seg_heap.top().R<=i)
				seg_heap.pop();
			else if(seg_heap.top().W<=(target-sum)){
				total+=seg_heap.top().W;
				expired_seg_record[seg_heap.top().R]+=seg_heap.top().W;
				segment_set[seg_heap.top().id].selected_num+=seg_heap.top().W;
				sum+=seg_heap.top().W;
				seg_heap.pop();
			}
			else if(seg_heap.top().W>(target-sum)){
				total+=(target-sum);
				expired_seg_record[seg_heap.top().R]+=(target-sum);
				segment_set[seg_heap.top().id].selected_num+=(target-sum);
				seg_heap.push(segment(seg_heap.top().id, seg_heap.top().L, seg_heap.top().R, seg_heap.top().W-(target-sum)));
				seg_heap.pop();
				if(seg_heap.top().W<=0)
					seg_heap.pop();
				sum+=(target-sum);
			}
		}
	}
	cout<<target<<endl;
	for(long long i=0; i<segment_set.size(); i++)
		cout<<segment_set[i].selected_num<<" ";
	cout<<endl;
	return 0;
}

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define DEBUG

class segment{
	public:
		long long id;
		long long L;
		long long R;
		long long W;
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
	#ifdef DEBUG0
	for(long long i=0; i<N; i++)
		cout<<segment_set[i].id<<" "<<segment_set[i].L<<" "<<segment_set[i].R<<" "<<segment_set[i].W<<endl;
	#endif
	
	//init heap
	priority_queue<segment, vector<segment>, less<vector<segment>::value_type>> seg_heap;
	#ifdef DEBUG0
	for(long long i=0; i<N; i++)
		seg_heap.push(segment_set[i]);
	while(!seg_heap.empty()){
		cout<<seg_heap.top().id<<" "<<seg_heap.top().L<<" "<<seg_heap.top().R<<" "<<seg_heap.top().W<<endl;
		seg_heap.pop();
	}
	#endif
}

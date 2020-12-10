#include <iostream>
#include <deque>
#include <string>
#include <vector>
using namespace std;
//#define DEBUG
class Group{
	public:
		bool location;
		long long type;
		long long peopleNum;
		long long persuadeNum;
		Group(){
			this->type = -1;
			this->peopleNum = 0;
			this->location = 0;
			this->persuadeNum = -1;
		}
		Group(long long location, long long type, long long peopleNum, long long persuadeNum){
			this->type = type;
			this->peopleNum = peopleNum;
			this->location = location;
			this->persuadeNum = persuadeNum;
		}
};


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	long long N, Q;
	cin>>N>>Q;
	vector<Group> group;
	for(long long i=0; i<Q; i++){
		string loc;
		bool location;
		long long type;
		long long peopleNum;
		long long persuadeNum;
		cin>>loc>>peopleNum>>type>>persuadeNum;
		if(loc=="front")
			location = 0;
		else if(loc=="back")
			location = 1;
		group.push_back(Group(location, type, peopleNum, persuadeNum));
	}
	long long totalNum[N]={0};
	for(long long i=0; i<Q; i++){
		totalNum[group[i].type-1] += group[i].peopleNum*(Q-i);
	}
	for(long long i=0; i<N; i++)
		cout<<totalNum[i]<<" ";
	cout<<endl;
	deque<Group> dq;
	dq.push_back(group[0]);
	long long totalNum[N]={0};
	totalNum[dq[0].type-1]+=dq[0].peopleNum;
	for(long long i=1; i<Q; i++){
		if(group[i].location==0){
			for(long long j=0; j<dq.size(); j++){
				if(group[i].persuadeNum==0){
					break;
				}
				if(group[i].type!=dq[j].type && group[i].persuadeNum<=dq[j].peopleNum){
					dq[j].peopleNum-=group[i].persuadeNum;
					totalNum[dq[j].type-1] += dq[j].peopleNum;
					group[i].peopleNum+=group[i].persuadeNum;
					group[i].persuadeNum=0;
				}
				else if(group[i].type!=dq[j].type && group[i].persuadeNum>dq[j].peopleNum){
					group[i].peopleNum+=dq[j].peopleNum;
					group[i].persuadeNum-=dq[j].peopleNum;
					dq[j].peopleNum=0;
				}
				if(group[i].type==dq[j].type){
					group[i].peopleNum += dq[j].peopleNum;
					dq[j].peopleNum=0;
				}
			}
			dq.push_front(group[i]);
		}
		else if(group[i].location==1){
			for(long long j=dq.size()-1; j>=0; j--){
				if(group[i].persuadeNum==0){
					break;
				}
				if(group[i].type!=dq[j].type && group[i].persuadeNum<=dq[j].peopleNum){
					dq[j].peopleNum-=group[i].persuadeNum;
					group[i].peopleNum+=group[i].persuadeNum;
					group[i].persuadeNum=0;
				}
				else if(group[i].type!=dq[j].type && group[i].persuadeNum>dq[j].peopleNum){
					group[i].peopleNum += dq[j].peopleNum;
					group[i].persuadeNum -= dq[j].peopleNum;
					dq[j].peopleNum=0;
				}
				if(group[i].type==dq[j].type){
					group[i].peopleNum += dq[j].peopleNum;
					dq[j].peopleNum=0;
				}
			}
			dq.push_back(group[i]);
		}
		for(long long i=0; i<dq.size(); i++){
			totalNum[dq[i].type-1] += dq[i].peopleNum;
		}
	}
	for(long long i=0; i<N; i++)
		cout<<totalNum[i]<<" ";
	cout<<endl;
}

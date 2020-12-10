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
		long long timeIn;
		Group(){
			this->type = -1;
			this->peopleNum = 0;
			this->location = 0;
			this->persuadeNum = -1;
			this->timeIn = 0;
		}
		Group(long long location, long long type, long long peopleNum, long long persuadeNum, long long timeIn){
			this->type = type;
			this->peopleNum = peopleNum;
			this->location = location;
			this->persuadeNum = persuadeNum;
			this->timeIn = timeIn;
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
		group.push_back(Group(location, type, peopleNum, persuadeNum, i));
	}	

	group[0].persuadeNum = 0;
	deque<Group> dq;
	dq.push_back(group[0]);
	long long totalNum[N]={0};

	for(long long i=1; i<Q; i++){
		group[i].peopleNum+=group[i].persuadeNum;
		//front
		if(group[i].location==0){
			while(group[i].persuadeNum!=0){
				long long j = 0;
				if(group[i].persuadeNum<dq[j].peopleNum){
					totalNum[dq[j].type-1] += dq[j].peopleNum * (i-dq[j].timeIn);
					dq[j].peopleNum -= group[i].persuadeNum;
					dq[j].timeIn = i;
					group[i].persuadeNum = 0;
				}
				else if(group[i].persuadeNum>=dq[j].peopleNum){
					group[i].persuadeNum-=dq[j].peopleNum;
					totalNum[dq[j].type-1] += dq[j].peopleNum * (i-dq[j].timeIn);
					dq.pop_front();
				}
			}
			dq.push_front(group[i]);
		}
		//back
		else if(group[i].location==1){
			while(group[i].persuadeNum!=0){
				long long j = dq.size()-1;
				if(group[i].persuadeNum<dq[j].peopleNum){
                    totalNum[dq[j].type-1] += dq[j].peopleNum * (i-dq[j].timeIn);
                    dq[j].peopleNum -= group[i].persuadeNum;
                    dq[j].timeIn = i;
                    group[i].persuadeNum = 0;
				}
				else if(group[i].persuadeNum>=dq[j].peopleNum){
                    group[i].persuadeNum-=dq[j].peopleNum;
                    totalNum[dq[j].type-1] += dq[j].peopleNum * (i-dq[j].timeIn);
                    dq.pop_back();
				}
			}
			dq.push_back(group[i]);
		}
	}
	for(long long i=0; i<dq.size(); i++)
		totalNum[dq[i].type-1] += dq[i].peopleNum*(Q-dq[i].timeIn);
	for(long long i=0; i<N; i++)
		cout<<totalNum[i]<<" ";
	cout<<endl;
	return 0;
}

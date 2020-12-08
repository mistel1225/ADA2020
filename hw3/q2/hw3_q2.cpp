#include <iostream>
#include <vector>
#include <queue>
using namespace std;
//#define DEBUG
class vertex{
	public:
		long long node_i;
		long long weight;
		vertex(){
			this->node_i = -1;
			this->weight = -1;
		}
		vertex(long long node_i, long long weight){
			this->node_i = node_i;
			this->weight = weight;
		}
};

class diameter{
	public:
		long long v_1;
		long long v_2;
		long long distance;
		diameter(){
			this->v_1 = -1;
			this->v_2 = -1;
			this->distance = -1;
		}
		diameter(long long v_1, long long v_2, long long distance){
			this->v_1 = v_1;
			this->v_2 = v_2;
			this->distance = distance;
		}
};

void BFS(vector<vector<vertex>> &adjList, long long s, vector<long long> &prevList, vector<long long> &distList){

	//0:white 1:gray 2:black
	long long visList[prevList.size()];
	for(long long i=0; i<prevList.size(); i++){
		visList[i] = 0;
		distList[i] = 0;
		prevList[i] = -1;
	}

	visList[s] = 1;
	prevList[s] = -1;
	distList[s] = 0;
	queue<long long> Q;
	Q.push(s);
	while(!Q.empty()){
		long long u = Q.front();
		Q.pop();
		for(long long j=0; j<adjList[u].size(); j++){
			if(visList[adjList[u][j].node_i]==0){
				visList[adjList[u][j].node_i]=1;
				distList[adjList[u][j].node_i] = distList[u] + adjList[u][j].weight;
				prevList[adjList[u][j].node_i] = u;
				Q.push(adjList[u][j].node_i);
			}
		}
		visList[u] = 2;
	}
}


diameter find_diameter(vector<vector<vertex>> &adjList, vector<long long> &prevList, vector<long long> &distList){
	BFS(adjList, 0, prevList, distList);
	long long v_1 = 0;
	for(long long i=1; i<distList.size(); i++){
		if(distList[i]>distList[v_1]){
			v_1 = i;
		}
	}

	BFS(adjList, v_1, prevList, distList);
	long long v_2 = 0;
	for(long long i=1; i<distList.size(); i++)
		if(distList[i]>distList[v_2])
			v_2 = i;
	/*#ifdef DEBUG
	cout<<endl<<"===================="<<endl;
	cout<<"in the find_diameter"<<endl;
	cout<<v_1+1<<" "<<v_2+1<<endl;
	cout<<"diameter dist="<<distList[v_2]<<endl;
	for(long long i=0; i<distList.size(); i++)
		cout<<distList[i]<<" ";
	cout<<endl;
	#endif*/
	return diameter(v_1, v_2, distList[v_2]);
}

int main(){
	long long N; 
	cin>>N;
	vector<vector<vertex>> adjList(N);
	long long total_weight=0;
	//N-1 edge in total
	for(long long i=1; i<N; i++){
		long long v_1, v_2, weight;
		cin>>v_1>>v_2>>weight;
		adjList[v_1-1].push_back(vertex(v_2-1, weight));
		adjList[v_2-1].push_back(vertex(v_1-1, weight));
		total_weight+=weight;
	}
	#ifdef DEBUG
	for(long long i=0; i<N; i++){
		cout<<i+1<<"th node:"<<endl;
		for(long long j=0; j<adjList[i].size(); j++)
			cout<<adjList[i][j].node_i+1<<" weight= "<<adjList[i][j].weight<<" ";
		cout<<endl;
	}
	#endif
	cout<<0<<" ";
	vector<long long> prevList(N);
	vector<long long> distList(N);
	long long weight_accu=0;
	for(long long i=1; i<=N-1; i++){
		if(weight_accu==total_weight){
			cout<<total_weight<<" ";
		}
		else{
			diameter d = find_diameter(adjList, prevList, distList);
			/*cout<<d.distance+weight_accu<<" ";
			cout<<weight_accu;*/
			weight_accu+=d.distance;
			cout<<weight_accu<<" ";
			//set path v_1~v_2's weight to 0 O(length(path))
			for(long long i=d.v_2; i!=d.v_1; i=prevList[i]){
				for(long long j=0; j<adjList[i].size(); j++){
					if(adjList[i][j].node_i == prevList[i]){
						adjList[i][j].weight=0;
						break;
					}
				}
				for(long long j=0; j<adjList[prevList[i]].size(); j++){
					if(adjList[prevList[i]][j].node_i == i){
						adjList[prevList[i]][j].weight=0;
						break;
					}
				}
			}
		}
	}
	cout<<endl;
}

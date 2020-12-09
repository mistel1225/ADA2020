#include <iostream>
#include <vector>
#include <queue>
using namespace std;
//#define DEBUG

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

void BFS(vector<vector<long long>> &adjList, vector<vector<long long>> &weightMatrix, long long s, vector<long long> &prevList, vector<long long> &distList){

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
			if(visList[adjList[u][j]]==0){
				visList[adjList[u][j]]=1;
				distList[adjList[u][j]] = distList[u] + weightMatrix[u][adjList[u][j]];
				prevList[adjList[u][j]] = u;
				Q.push(adjList[u][j]);
			}
		}
		visList[u] = 2;
	}
}


diameter find_diameter(vector<vector<long long>> &adjList, vector<vector<long long>> &weightMatrix,vector<long long> &prevList, vector<long long> &distList){
	BFS(adjList, weightMatrix, 0, prevList, distList);
	long long v_1 = 0;
	for(long long i=1; i<distList.size(); i++){
		if(distList[i]>distList[v_1]){
			v_1 = i;
		}
	}

	BFS(adjList, weightMatrix, v_1, prevList, distList);
	long long v_2 = 0;
	for(long long i=1; i<distList.size(); i++)
		if(distList[i]>distList[v_2])
			v_2 = i;
	return diameter(v_1, v_2, distList[v_2]);
}

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	long long N; 
	cin>>N;
	vector<vector<long long>> adjList(N);
	vector<vector<long long>> weightMatrix(N, vector<long long>(N));
	long long total_weight=0;
	//N-1 edge in total
	for(long long i=1; i<=N-1; i++){
		long long v_1, v_2, weight;
		cin>>v_1>>v_2>>weight;
		adjList[v_1-1].push_back(v_2-1);
		adjList[v_2-1].push_back(v_1-1);
		weightMatrix[v_1-1][v_2-1] = weight;
		weightMatrix[v_2-1][v_1-1] = weight;
		total_weight+=weight;
	}
	vector<long long> prevList(N);
	vector<long long> distList(N);
	long long weight_accu=0;
	vector<long long> valueList;
	valueList.push_back(0);
	
	diameter d = find_diameter(adjList, weightMatrix, prevList, distList);
	long long src = d.v_1;
	long long tar = d.v_2;
	valueList.push_back(d.distance);
    for(long long i=tar; i!=src; i=prevList[i]){       
		weightMatrix[i][prevList[i]]=0;
		weightMatrix[prevList[i]][i]=0;
		distList[i]=0;
    }
	weight_accu += d.distance;
	while(weight_accu!=total_weight){
		BFS(adjList, weightMatrix, src, prevList, distList);
		long long node_max = 0;
		for(long long i=1; i<distList.size(); i++)
			if(distList[i]>distList[node_max])
				node_max = i;
		long long dist=distList[node_max];
	    for(long long i=node_max; i!=src; i=prevList[i]){
			weightMatrix[i][prevList[i]]=0;
			weightMatrix[prevList[i]][i]=0;
        	distList[i]=0;
    	}
		weight_accu+=dist;
		valueList.push_back(weight_accu);
	}
	for(long long i=0; i<valueList.size(); i++)
		cout<<valueList[i]<<" ";
	for(long long i=0; i<N-valueList.size(); i++)
		cout<<total_weight<<" ";
	cout<<endl;
}

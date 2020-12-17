#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
class edge{
	public:
		long long v1;
		long long v2;
		long long weight;
		edge(long long v1, long long v2, long long weight){
			this->v1 = v1;
			this->v2 = v2;
			this->weight = weight;
		}
		edge(){
			this->v1 = -1;
			this->v2 = -1;
			this->weight = -1;
		}
};
class node{
	public:	
		long long node_i;
		long long d;
		node(long long node_i, long long d){
			this->node_i = node_i;
			this->d = d;
		}
};


bool operator<(const node &n1,const node &n2){
	return n1.d > n2.d;
}


bool sortByWeight(edge &edge1, edge &edge2){
	return edge1.weight < edge2.weight;
}
long long find(long long x, vector<long long> &disjointSet){
	return x==disjointSet[x]? x: disjointSet[x] = find(disjointSet[x], disjointSet);
}
void set_union(long long x, long long y, vector<long long> &disjointSet){
	disjointSet[find(x, disjointSet)] = find(y, disjointSet);
}

int main(){
	long long N, M, S, T;
	cin>>N>>M>>S>>T;
	S-=1, T-=1;
	vector<edge> edgeList(0);
	for(long long i=0; i<M; i++){
		long long v1, v2, weight;
		cin>>v1>>v2>>weight;
		edgeList.push_back(edge(v1-1, v2-1, weight));		
	}
	//kruskal's algo
	vector<edge> minSpanTree(0);
	sort(edgeList.begin(), edgeList.end(), sortByWeight);
	//disjoint set
	vector<long long> disjointSet(N);
	for(long long i=0; i<N; i++)
		disjointSet[i]=i;

	for(long long i=0; i<edgeList.size(); i++){
		long long j=i;
		for(j; j<edgeList.size();j++){
			if(edgeList[j].weight != edgeList[i].weight){
				j=j-1;
				break;
			}
		}
		if(j==edgeList.size())
			j=j-1;
        for(long long k=i; k<=j; k++){
            if(find(edgeList[k].v1, disjointSet)!=find(edgeList[k].v2, disjointSet)){
                minSpanTree.push_back(edgeList[k]);
            }
        }
        for(long long k=i; k<=j; k++){
            if(find(edgeList[k].v1, disjointSet)!=find(edgeList[k].v2, disjointSet)){
                set_union(edgeList[k].v1, edgeList[k].v2, disjointSet);
            }   
        }
		i=j;
	}
	//adjList && weightMatrix
	vector<vector<node>> adjList(N);
	//vector<vector<long long>> weightMatrix(N, vector<long long>(N));
	for(long long i=0; i<minSpanTree.size(); i++){
		long long v1 = minSpanTree[i].v1;
		long long v2 = minSpanTree[i].v2;
		long long weight = minSpanTree[i].weight;
		adjList[v1].push_back(node(v2, weight));
		adjList[v2].push_back(node(v1, weight));
		//weightMatrix[v1][v2] = weight;
		//weightMatrix[v2][v1] = weight;
	}
	//dijkstra's
	bool visList[N]={0};
	long long distList[N];
	for(long long i=0; i<N; i++)
		distList[i] = 9223372036854775807;
	distList[S] = 0;
	priority_queue<node> Q;
	Q.push(node(S, distList[S]));
	/*for(long long i=0; i<N; i++){
		long long u = -1;
		while(!Q.empty() && visList[u = Q.top().node_i])
			Q.pop();
		if(u==-1)
			break;
		visList[u]=1;
		for(long long j=0; j<adjList[u].size(); j++){
			if(!visList[adjList[u][j].node_i] && distList[u] + adjList[u][j].d < distList[adjList[u][j].node_i]){
				distList[adjList[u][j].node_i] = distList[u] + adjList[u][j].d;
				Q.push(node(adjList[u][j].node_i, distList[adjList[u][j].node_i]));
			}
		}
	}*/
	/*for(long long i=0; i<N; i++)
		Q.push(node(i, distList[i]));*/
	while(!Q.empty()){
		while(visList[Q.top().node_i]==1){
			Q.pop();
			if(Q.empty())
				break;
		}
		if(Q.empty())
			break;
		long long u = Q.top().node_i;
		Q.pop();
		visList[u] = 1;
		for(long long j=0; j<adjList[u].size(); j++){
			if(distList[adjList[u][j].node_i]>distList[u]+adjList[u][j].d){
				distList[adjList[u][j].node_i] = distList[u]+adjList[u][j].d;
				Q.push(node(adjList[u][j].node_i, distList[adjList[u][j].node_i]));
			}
		}
	}
	cout<<distList[T]<<endl;
}


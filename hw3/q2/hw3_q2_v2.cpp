#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
//#define DEBUG
class vertex{
	public:
		long long v;
		long long weight;
		vertex(){
			this->v = 0;
			this->weight = 0;
		}
		vertex(long long v, long long weight){
			this->v = v;
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

void BFS(vector<vector<vertex>> &adjList, long long s, vector<long long> &prevList, vector<vertex> &distList){

    //0:white 1:gray 2:black
    long long visList[prevList.size()];
    for(long long i=0; i<prevList.size(); i++){
        visList[i] = 0;
        distList[i].weight = 0;
        prevList[i] = -1; 
    }   

    visList[s] = 1;
    prevList[s] = -1; 
    distList[s].weight = 0;
    queue<long long> Q;
    Q.push(s);
    while(!Q.empty()){
        long long u = Q.front();
        Q.pop();
        for(long long j=0; j<adjList[u].size(); j++){
            if(visList[adjList[u][j].v]==0){
                visList[adjList[u][j].v]=1;
                distList[adjList[u][j].v].weight = distList[u].weight + adjList[u][j].weight;
                prevList[adjList[u][j].v] = u;
                Q.push(adjList[u][j].v);
            }
        }
        visList[u] = 2;
    }
}

diameter find_diameter(vector<vector<vertex>> &adjList, vector<long long> &prevList, vector<vertex> &distList){
    BFS(adjList, 0, prevList, distList);
    long long v_1 = 0;
    for(long long i=1; i<distList.size(); i++){
        if(distList[i].weight > distList[v_1].weight){
            v_1 = i;
        }
    }
    BFS(adjList, v_1, prevList, distList);
    long long v_2 = 0;
    for(long long i=1; i<distList.size(); i++)
        if(distList[i].weight>distList[v_2].weight)
            v_2 = i;
	return diameter(v_1, v_2, distList[v_2].weight);
}

void DFS(long long &u, vector<vector<vertex>> &adjList, vector<long long> &nextList, vector<vertex> &distList, vector<bool> &visList){
	visList[u] = 1;
	long long longest_distance=0;
	long long longest_child=u;
	for(long long v=0; v<adjList[u].size(); v++){
		if(visList[adjList[u][v].v]==0){
			DFS(adjList[u][v].v, adjList, nextList, distList, visList);
			if(longest_distance < distList[adjList[u][v].v].weight + adjList[u][v].weight){
				longest_distance = distList[adjList[u][v].v].weight + adjList[u][v].weight;
				longest_child = adjList[u][v].v;
			}
		}
	}
	distList[u].weight = longest_distance;
	nextList[u] = longest_child;
}

void DFS2(long long &u, vector<vector<vertex>> &adjList, vector<long long> &nextList, vector<vertex> &distList, vector<bool> &visList){
	visList[u] = 1;
	for(long long v=0; v<adjList[u].size(); v++){
		if(visList[adjList[u][v].v]==0 && nextList[u]==adjList[u][v].v){
			DFS2(adjList[u][v].v, adjList, nextList, distList, visList);
		}
		else if(visList[adjList[u][v].v]==0 && nextList[u]!=adjList[u][v].v){
			distList[adjList[u][v].v].weight+=adjList[u][v].weight;
			DFS2(adjList[u][v].v, adjList, nextList, distList, visList);
		}
	}
}

bool cmp(vertex &d1, vertex &d2){
	return d1.weight>d2.weight;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
	long long N;
	cin>>N;
	vector<vector<vertex>> adjList(N);
	for(long long i=1; i<=N-1; i++){
		long long v_1, v_2, weight;
		cin>>v_1>>v_2>>weight;
		adjList[v_1-1].push_back(vertex(v_2-1, weight));
		adjList[v_2-1].push_back(vertex(v_1-1, weight));
	}
	vector<long long> prevList(N);
	vector<vertex> distList(N);
	vector<long long> valueList(1, 0);
	vector<bool> isProtectedList(N);
	diameter d = find_diameter(adjList, prevList, distList);
	long long src = d.v_1;
	long long tar = d.v_2;
	//valueList.push_back(d.distance);
	/*for(long long i=tar; i!=src; i=prevList[i]){
		isProtectedList[i]=1;
	}
	isProtectedList[src]=1;*/
	//reset distList, which represent the longest node from node i now
	vector<long long> nextList(N);
	for(long long i=0; i<N; i++){
		distList[i].weight = 0;
		distList[i].v = i;
	}
	//DFS
	vector<bool> visList(N, 0);
	DFS(src, adjList, nextList, distList, visList);
	for(long long i=0; i<N; i++){
		visList[i] = 0;
	}
	DFS2(src, adjList, nextList, distList, visList);
	#ifdef DEBUG
	cout<<src+1<<", "<<tar+1<<endl;
	for(int i=0; i<N; i++)
		cout<<distList[i].weight<<" ";
	cout<<endl;
	#endif
	//calculate important value
	sort(distList.begin(), distList.end(), cmp);
	#ifdef DEBUG
	for(long long i=0; i<N; i++)
		cout<<i+1<<", "<<nextList[i]+1<<endl;
	#endif
	for(long long i=0; i<N; i++){
		if(isProtectedList[distList[i].v]!=1){
			valueList.push_back(distList[i].weight+valueList[valueList.size()-1]);
			long long j=distList[i].v;
			for(j; j!=nextList[j]; j=nextList[j]){
				isProtectedList[j]=1;
			}
			isProtectedList[j]=1;
		}
	}
	#ifdef DEBUG
	for(long long i=0; i<N; i++)
		cout<<isProtectedList[i]<<" ";
	cout<<endl;
	#endif
	for(long long i=0; i<valueList.size(); i++)
		cout<<valueList[i]<<" ";
	for(long long i=0; i<N-valueList.size(); i++)
		cout<<valueList[valueList.size()-1]<<" ";
	cout<<endl;
	return 0;
}

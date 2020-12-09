#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
//#define DEBUG
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
	
	long long j=0;
	for(long long i=1; i<=edgeList.size(); i++){
		//loop until E_i_weight != E_i+1_weight 
		if(i<edgeList.size()){
			while(edgeList[i].weight==edgeList[i-1].weight){
				i++;
				if(i>=edgeList.size()){
					break;
				}
			}
		}
		for(long long k=j; k<i; k++){
			if(find(edgeList[k].v1, disjointSet)!=find(edgeList[k].v2, disjointSet)){
				minSpanTree.push_back(edgeList[k]);
			}
		}
		for(long long k=j; k<i; k++){
            if(find(edgeList[k].v1, disjointSet)!=find(edgeList[k].v2, disjointSet)){
                set_union(edgeList[k].v1, edgeList[k].v2, disjointSet);
            } 	
		}
		j=i-1;
	}
	cout<<"minSpanTree"<<endl;
	for(long long i=0; i<minSpanTree.size(); i++){
		cout<<minSpanTree[i].v1+1<<" "<<minSpanTree[i].v2+1<<" "<<minSpanTree[i].weight<<endl;
	}
}

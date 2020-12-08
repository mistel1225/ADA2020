#include <iostream>
#include <vector>
#include <string>
using namespace std;
//#define DEBUG
class vertex{
	public:
		long long node;
		long long weight;
		long long sccCnt;
		vertex(long long node, long long weight){
			this->node = node;
			this->weight = weight;
			this->sccCnt = 0;
		}
};

void dfs1(long long &node_i, vector<vector<vertex>> &adj_list, vector<long long> &fin_list, vector<bool> &vis){
	vis[node_i] = 1;
	for(long long j=1; j<adj_list[node_i].size(); j++)
		if(!vis[adj_list[node_i][j].node])
			dfs1(adj_list[node_i][j].node, adj_list, fin_list, vis);
	fin_list.push_back(node_i);
}
long long dfs2(long long &node_i, long long &sccCnt, vector<vector<vertex>> &SCC_list, vector<vector<vertex>> &adj_list, vector<vector<vertex>> &adj_list_rev, vector<bool> &vis){
	vis[node_i]=1;
	long long weight=0;
	adj_list[node_i][0].sccCnt = sccCnt;
	for(long long j=1; j<adj_list_rev[node_i].size(); j++){
		if(!vis[adj_list_rev[node_i][j].node])
			weight += adj_list_rev[node_i][j].weight + dfs2(adj_list_rev[node_i][j].node, sccCnt, SCC_list, adj_list, adj_list_rev, vis);
		else if(sccCnt == adj_list[adj_list_rev[node_i][j].node][0].sccCnt)
			weight += adj_list_rev[node_i][j].weight;
		else if(sccCnt != adj_list[adj_list_rev[node_i][j].node][0].sccCnt){
			long long src = adj_list[adj_list_rev[node_i][j].node][0].sccCnt;
			long long tar = sccCnt;
			long long weight = adj_list_rev[node_i][j].weight;
			SCC_list[src].push_back(vertex(tar, weight));
		}
	}
	weight += adj_list_rev[node_i][0].weight;
	return weight;
}

int main(){
	long long N, M;
 	cin>>N>>M;	
	vector<vector<vertex>> adj_list(N);
	for(long long i=0; i<N; i++){
		long long s_i;
		cin>>s_i;
		adj_list[i].push_back(vertex(i, s_i));
	}
	for(long long i=0; i<M; i++){
		long long u_i, v_i, w_i;
		cin>>u_i>>v_i>>w_i;
		adj_list[u_i-1].push_back(vertex(v_i-1, w_i));
	}
	//prepare an inverese graph for Kosaraju's
	vector<vector<vertex>> adj_list_rev(N);
	for(long long i=0; i<N; i++)
		adj_list_rev[i].push_back(vertex(adj_list[i][0].node, adj_list[i][0].weight));
	for(long long i=0; i<N; i++)
		for(long long  j=1; j<adj_list[i].size(); j++)
			adj_list_rev[adj_list[i][j].node].push_back(vertex(i, adj_list[i][j].weight));
	#ifdef DEBUG1
	cout<<"print adj_list:"<<endl;
	for(long long i=0; i<N; i++){
		cout<<i+1<<"th: "<<endl;
		for(long long j=1; j<adj_list[i].size(); j++)
			cout<<adj_list[i][j].node+1<<" weight:"<<adj_list[i][j].weight<<" ";
		cout<<endl;
	}
	#endif
	
	vector<long long> fin_list;
	vector<bool> vis(N, 0);
	//kosaraju's algo
	for(long long i=0; i<N; i++)
		if(!vis[i])
			dfs1(i, adj_list, fin_list, vis);
	for(long long i=0; i<N; i++)
		vis[i]=0;
	long long sccCnt = 0;
	vector<vector<vertex>> SCC_list;
	for(long long i=N-1; i>=0; i--){
		long long SCC_weight=0;
		if(!vis[fin_list[i]]){
			SCC_list.push_back(vector<vertex>(1, vertex(sccCnt, 0)));
			SCC_weight = dfs2(fin_list[i], sccCnt, SCC_list, adj_list, adj_list_rev, vis);
			SCC_list[sccCnt][0].weight = SCC_weight;
			sccCnt++;
		}
	}
	#ifdef DEBUG
	cout<<"====================="<<endl;
    cout<<"print SCC_list:"<<endl;
    for(long long i=0; i<sccCnt; i++){
        cout<<i<<"th component weight: "<<SCC_list[i][0].weight<<endl;
        for(long long j=1; j<SCC_list[i].size(); j++)
            cout<<SCC_list[i][j].node<<" weight:"<<SCC_list[i][j].weight<<" ";
        cout<<endl;
    }   
	#endif
	
	//bellman-ford algo
	long long distance[sccCnt];
	for(long long i=1; i<sccCnt; i++){
		distance[i] = SCC_list[i][0].weight;
	}
	distance[0] = SCC_list[0][0].weight;
	for(long long i=0; i<sccCnt; i++)
		for(long long j=1; j<SCC_list[i].size(); j++)
			if(distance[SCC_list[i][j].node]<distance[i]+SCC_list[i][j].weight+SCC_list[SCC_list[i][j].node][0].weight)
				distance[SCC_list[i][j].node] = distance[i]+SCC_list[i][j].weight+SCC_list[SCC_list[i][j].node][0].weight;
	#ifdef DEBUG
	cout<<"========================"<<endl;
	for(long long i=0; i<sccCnt; i++)
		cout<<distance[i]<<" ";
	cout<<endl;
	#endif
	long long max = distance[0];
	for(long long i=1; i<sccCnt; i++)
		if(max<distance[i])
			max = distance[i];
	cout<<max<<endl;
	return 0;
}


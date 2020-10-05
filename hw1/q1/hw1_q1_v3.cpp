#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdint.h>
using namespace std;
//#define DEBUG

bool sortcol(const vector<long long>& v1, const vector<long long>& v2){
	return v1[1] < v2[1];
}


long long dist(long long x0, long long y0, long long x1, long long y1){
	#ifdef DEBUG2
	cout<<"x0, y0, x1, y1= "<<x0<<" "<<y0<<" "<<x1<<" "<<y1<<endl;
	long long dist = (x0-x1)*(x0-x1) + (y0-y1)*(y0-y1);
	cout<<"distance = "<<(x0-x1)*(x0-x1) + (y0-y1)*(y0-y1)<<endl;
	#endif
	return ((x0-x1)*(x0-x1) + (y0-y1)*(y0-y1));
}

long long shortest_dist_brute(vector<vector<long long>> &coord_vector, long long first, long long last){
	long long dist_min = 9223372036854775807;
	for(long long i=first; i<last; ++i){
		for(long long j=i+1; j<last; ++j){
			if(dist_min > dist(coord_vector[i][0], coord_vector[i][1], coord_vector[j][0], coord_vector[j][1])){
				dist_min = dist(coord_vector[i][0], coord_vector[i][1],coord_vector[j][0], coord_vector[j][1]);
			}
			#ifdef DEBUG1
			cout<<"dist_min = "<<dist_min<<endl;
			#endif
		}
	}
	return dist_min;
}

long long shortest_dist(vector<vector<long long>> &coord_vector, long long first, long long last){
	if(last-first<=3){
		return shortest_dist_brute(coord_vector, first, last);
	}
	long long mid = (last+first)/2;
	long long dl = shortest_dist(coord_vector, first, mid);
	long long dr = shortest_dist(coord_vector, mid, last);
	long long d = (dl > dr? dr : dl);
	#ifdef DEBUG
	cout<<"=====dr and dl=================="<<endl;
	cout<<dr<<" "<<dl<<endl;
	#endif
	vector<vector<long long>> strip_vector(last-first, vector<long long>(2));
	long long strip_size = 0;
	for(long long i=first; i<last; i++){
		if(abs((coord_vector[i][0]-coord_vector[mid][0])*(coord_vector[i][0]-coord_vector[mid][0])) < d){
			strip_vector[strip_size][0] = coord_vector[i][0];
			strip_vector[strip_size][1] = coord_vector[i][1];
			strip_size++;
		}
	}
	if(strip_size<=6){
		long long distance = shortest_dist_brute(strip_vector, 0, strip_size);
		if(d>distance)
			d=distance;	
	}
	else{
		sort(strip_vector.begin(), strip_vector.begin()+strip_size, sortcol);	
		#ifdef DEBUG
		cout<<"=====strip_vector======"<<endl;
		for(int i=0; i<strip_size; i++){
			cout<<"strip x, y = "<<strip_vector[i][0]<<" "<<strip_vector[i][1]<<endl;
		}
		#endif
		for(long long i=0; i < strip_size; ++i){
			for(long long j=i+1; j<=i+8&&j<strip_size; ++j){
				if(d > dist(strip_vector[i][0], strip_vector[i][1], strip_vector[j][0], strip_vector[j][1])){
					d = dist(strip_vector[i][0], strip_vector[i][1], strip_vector[j][0], strip_vector[j][1]);
				}
			}
		}
	}	
	return d;
}


int main(){
	long long N;
	cin>>N;
	vector<vector<long long>> coord_vector(N, vector<long long>(2));
	for(long long i=0; i<N; i++){
		cin>>coord_vector[i][0]>>coord_vector[i][1];
	}
	sort(coord_vector.begin(), coord_vector.end());
	
	long long min=0;
	if(N<=5000)
		min = shortest_dist_brute(coord_vector, 0, N);
	else
		min = shortest_dist(coord_vector, 0, N);
	cout<<-1*min<<endl;
	return 0;
}

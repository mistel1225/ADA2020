#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

class Point{
	long long x, y;
}

long long dist_cal(Point p1, Point p2){
	return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}


long long shortest_brute(Point P[], long long N){
	long long min_dist = PTRDIFF_MAX;
	for(long long i=0; i<N; ++i)
		for(long long j = i+1; j < N; ++j)
			min_dist = (min_dist>dist_cal(P[i], P[j]) ? dist_cal(P[i], P[j]):min_dist);
	return min_dist;
}




int main(){
	Point P[]
}

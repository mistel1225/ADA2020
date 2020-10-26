#include <iostream>
#include <vector>

int main(){
	long long n;
	cin>>n;
	vector<long long> odd_vector, even_vector;
	for(long long i=1; i<=n; i++){
		long long temp;
		cin>>temp;
		if(i%2==0)
			for(long long j=0; j<temp; j++)
				even_vector.push_back(i)
		else if(i%2==1)
			for(long long j=0; j<temp; j++)
				odd_vector.push_back(i);
	}
	
}

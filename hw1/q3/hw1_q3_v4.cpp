#include <iostream>
using namespace std;
//#define DEBUG

long long ADA_party_rec(int first, int last, int K, long long *candies, long long *prefix_sum, long long *mod_array){
	int mid = (first+last)/2;
	if(last-first+1==1)
		return 0;
	else if(last-first+1==2)
		return 1;
    long long sumL = ADA_party_rec(first, mid, K, candies, prefix_sum, mod_array);
    long long sumR = ADA_party_rec(mid+1, last, K, candies, prefix_sum, mod_array);
    long long sumM = 0;
	//create minL, maxL, minR, maxR table
	int l=mid, r=mid+1;
	long long minL[last], maxL[last], minR[last], maxR[last];
	minL[l]=candies[l];
	maxL[l]=candies[l];
	for(int i=l-1; i>=first; i--){
		if(candies[i]<minL[i+1])
			minL[i]=candies[i];
		else
			minL[i]=minL[i+1];
		if(candies[i]>maxL[i+1])
			maxL[i]=candies[i];
		else
			maxL[i]=maxL[i+1];
	}
	minR[r]=candies[r];
	maxR[r]=candies[r];
	for(int i=r+1; i<=last; i++){
		if(candies[i]<minR[i-1])
			minR[i]=candies[i];
		else
			minR[i]=minR[i-1];
		if(candies[i]>maxR[i-1])
			maxR[i]=candies[i];
		else
			maxR[i]=maxR[i-1];
	}
	for(int i=0; i<K; i++)
		mod_array[i]= 0;	
	//case1: both max and min are in the left
	l=mid, r=mid+1;
	while(l>=first){
		while(r<=last){
			if(maxL[l]>maxR[r] && minL[l]<minR[r]){
				mod_array[prefix_sum[r+1]%K]++;
				r++;
			}
			else
				break;
		}
		sumM+=mod_array[(prefix_sum[l]+maxL[l]+minL[l])%K];
		l--;
	}
	//case2: both max and min are in the right
	l=mid, r=mid+1;
	for(int i=0; i<K; i++)
		mod_array[i] = 0;
	while(r<=last){
		while(l>=first){
			if(maxR[r]>maxL[l] && minR[r]<minL[l]){
				mod_array[prefix_sum[l]%K]++;
				l--;
			}
			else
				break;
		}
		sumM+=mod_array[(prefix_sum[r+1]-maxR[r]-minR[r])%K];
		r++;
	}
	
	//case3: max in the left, min in the right
	l=mid, r=mid+1;
	int p=r, q=r;
	for(int i=0; i<K; i++)
		mod_array[i] = 0;
	while(l>=first){
			while(q<=last){
				if(maxR[q]>maxL[l])
					break;
				else if(q>=p)
					mod_array[(prefix_sum[q+1]-minR[q])%K]+=1;
				q++;
			}
			while(p<=last){
				if(minR[p]<minL[l])
					break;
				else if(p<q)
					mod_array[(prefix_sum[p+1]-minR[p])%K]-=1;
				p++;
			}
		sumM+=mod_array[(prefix_sum[l]+maxL[l])%K];
		l--;
	}
	
	//case4: max in the right, min in the left
	l=mid, r=mid+1;
	p=r, q=r;
	for(int i=0; i<K; i++)
		mod_array[i] = 0;
	while(l>=first){
			while(q<=last){
                if(minR[q]<minL[l])
                    break;
                else if(q>=p)
                    mod_array[(prefix_sum[q+1]-maxR[q])%K]+=1;
                q++;
            }
            while(p<=last){
                if(maxR[p]>maxL[l])
                    break;
                else if(p<q)
                    mod_array[(prefix_sum[p+1]-maxR[p])%K]-=1;
                p++;
            }
		sumM+=mod_array[(prefix_sum[l]+minL[l])%K];
		l--;
	}
	return sumM+sumL+sumR;
}




int main(){
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(nullptr);
    int N, K;
	cin>>N>>K;
	long long *mod_array = new long long[K];
	long long *candies = new long long[N];
    long long *prefix_sum=new long long[N+1];
    for(int i=0; i<K; i++)
		mod_array[i]=0;
	for(int i=0; i<N; i++)
        cin>>candies[i];
    prefix_sum[0]=0;
    for(int i=1; i<=N; i++){
        prefix_sum[i] = prefix_sum[i-1]+candies[i-1];
    }
    long long sum = ADA_party_rec(0, N-1, K, candies, prefix_sum, mod_array);
    cout<<sum<<'\n';

}


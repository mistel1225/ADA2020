#include <iostream>
#include <vector>
using namespace std;
#define DEBUG
long long ADA_party_rec(int first, int last, int K, long long &candies, long long &prefix_sum){
	int mid = (first+last)/2;
	if(last-first+1==1)
		return 0;
	else if(last-first+1==2)
		return 1;
	long long sumL = ADA_party_rec(first, mid, candies, prefix_sum);
	long long sumR = ADA_party_rec(mid+1, last, candies, prefix_sum);
	long long sumM = 0;
	long long mod_array_left[K]={0}, mod_array_right[K]={0};
	//case1: both max and min are in the left
	int l=mid, r=mid+1;
	int max=l, min=l;
	bool flag=0;
	while(r<=last){
		//illegal
		if(candies[r]>candies[max]){
			while(l>=first){
				if(candies[l]>=candies[r]){
					max = l;
					mod_array_left[(prefix_sum[l]+candies[max]+candies[min])%K]++;
					flag=1;
					break;
				}
				else if(candies[l]<candies[min])
					min = l;
				l--;
			}	
		}
		else if(candies[r]<candies[min]){
			while(l>=first){
				if(candies[l]<=candies[r]){
					min = l;
					mod_array_left[(prefix_sum[l]+candies[max]+candies[min])%K]++;
					flag=1;
					break;
				}
				else if(candies[l]>candies[max])
					max = l;
				l--;
			}
		}
		if(l<first)
			break;
		mod_array_right[prefix_sum[r+1]%K]++;
		r++;
	}
	if(flag==1)
		l--;
	while(l>=first){
		if(candies[l]>candies[max])
			max=l;
		else if(candies[l]<candies[min])
			min=l;
		mod_array_left[(prefix_sum[l]+candies[max]+candies[min])%K]++;
		l--;
	}
	for(int i=0; i<K; i++)
		sumM += mod_array_left[i]*mod_array_right[i];
	
	//case2: both max and min are in the right
    l=mid, r=mid+1;
    max=r, min=r;
    flag=0;
	for(int i=0; i<K; i++){
		mod_array_left[i]=0;
		mad_array_right[i]=0;
	}
    while(l>=first){
	    //illegal
	    if(candies[l]>=candies[max]){
	        while(r<=last){
	            if(candies[r]>candies[l]){
	                max = r;
	                mod_array_right[(prefix_sum[r+1]-candies[max]-candies[min])%K]++;
	                flag=1;
	                break;
	            }
	            else if(candies[r]<candies[min])
	                min = r;
	            r++;
	        }
	    }
	    else if(candies[l]<=candies[min]){
	        while(r<=last){
	            if(candies[r]<candies[l]){
	                min = r;
	                mod_array_right[(prefix_sum[r+1]-candies[max]-candies[min])%K]++;
	                flag=1;
	                break;
	            }
	            else if(candies[r]>candies[max])
	                max = l;
	            r++;
	        }
	    }
	    if(r>last)
	        break;
	    mod_array_left[prefix_sum[l]%K]++;
	    l--;
	}
    if(flag==1)
        r++;
    while(r<=last){
        if(candies[r]>candies[max])
            max=l;
        else if(candies[r]<candies[min])
            min=l;
        mod_array_left[(prefix_sum[r+1]-candies[max]-candies[min])%K]++;
        l--;
    }
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(nullptr);
	int N, K;
	cin>>N>>K;
	long long candies[N]={0};
	long long prefix_sum[N+1]={0};
	for(int i=0; i<N; i++)
		cin>>candies[i];
	for(int i=1; i<=N; i++)
		prefix_sum[i] = prefix_sum[i-1]+candies[i-1];
	#ifdef DEBUG
	for(int i=0; i<=N; i++)
		cout<<prefix_sum[i]<<" ";
	cout<<endl;
	#endif
	ADA_party_rec(0, N-1, K, candies, prefix_sum);
}

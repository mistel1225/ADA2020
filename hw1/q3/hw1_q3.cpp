#include <iostream>
#include <vector>
using namespace std;
//#define DEBUG
long long ADA_party_rec(int first, int last, int K, long long *candies, long long *prefix_sum){
	int mid = (first+last)/2;
	if(last-first+1==1)
		return 0;
	else if(last-first+1==2)
		return 1;
	long long sumL = ADA_party_rec(first, mid, K, candies, prefix_sum);
	long long sumR = ADA_party_rec(mid+1, last, K, candies, prefix_sum);
	long long sumM = 0;
	long long mod_array_left[K]={0}, mod_array_right[K]={0};
	//case1: both max and min are in the left
	int l=mid, r=mid+1;
	int max=l, min=l;
	while(r<=last){
		//make sure the property.
		if(candies[r]>candies[max]){
			max=r;
			while(l>=first){
				if(candies[l]>candies[max]){
					max=l;
					break;
				}
				if(candies[l]<candies[min])
					min=l;
				l--;
			}
		}
		if(candies[r]<candies[min]){
			min=r;
			while(l>=first){
				if(candies[l]<candies[min]){
					min=l;
					break;
				}
				if(candies[l]>candies[max])
					max=l;
				l--;
			}
		}
		if(l>=first){
			mod_array_left[(prefix_sum[l]+candies[max]+candies[min])%K]++;
			l--;
		}
		//couldn't make sure the property
		else if(l<first)
			break;
		mod_array_right[prefix_sum[r+1]%K]++;
		r++;
	}
	while(l>=first){
		if(candies[l]>candies[max])
			max=l;
		if(candies[l]<candies[min])
			min=l;
		mod_array_left[(prefix_sum[l]+candies[max]+candies[min])%K]++;
		l--;
	}
	for(int i=0; i<K; i++)
		sumM += mod_array_left[i]*mod_array_right[i];
	
	//case2: both max and min are in the right
    l=mid, r=mid+1;
    max=r, min=r;
	for(int i=0; i<K; i++){
		mod_array_left[i]=0;
		mod_array_right[i]=0;
	}
    while(l>=first){
        //make sure the property.
        if(candies[l]>candies[max]){
            max=l;
            while(r<=last){
                if(candies[r]>candies[max]){
                    max=r;
                    break;
                }
                if(candies[r]<candies[min])
                    min=r;
                r++;
            }   
        }   
        if(candies[l]<candies[min]){
            min=l;
            while(r<=last){
                if(candies[r]<candies[min]){
                    min=r;
                    break;
                }
                if(candies[r]>candies[max])
                    max=r;
                r++;
            }   
        }   
        if(r<=last){
            mod_array_right[(prefix_sum[r+1]-candies[max]-candies[min])%K]++;
            r++;
        }   
        //couldn't make sure the property
        else if(r>last)
            break;
        mod_array_left[prefix_sum[l]%K]++;
        l--;
    }
    while(r<=last){
        if(candies[r]>candies[max])
            max=l;
        if(candies[r]<candies[min])
            min=l;
        mod_array_right[(prefix_sum[r+1]-candies[max]-candies[min])%K]++;
        r++;
    }
	for(int i=0; i<K; i++)
		sumM += mod_array_left[i]*mod_array_right[i];
	//case3 :min in the left, max in the right
	l=mid, r=mid+1;
    max=r, min=l;
    for(int i=0; i<K; i++){
        mod_array_left[i]=0;
        mod_array_right[i]=0;
    }
	while(r<=last){
		//make sure the property
		if(candies[min]>candies[r]){
			min=r;
			while(l>=first){
				if(candies[l]<candies[min]){
					min=l;
					break;	
				}
				if(candies[l]>candies[max]){
					max=l;
				}
				l--;
			}
		}
		//couldn't make sure the property.
		if(l<first)
			break;
		//could make sure the property
		if(candies[r]>candies[max]){
            mod_array_left[(prefix_sum[l]+candies[min])%K]++;
            l--;
			max = r;
			mod_array_right[(prefix_sum[r+1]-candies[max])%K]++;
		}
		else if(max>=mid+1&&min<=mid){
			mod_array_left[(prefix_sum[l]+candies[min])%K]++;
			l--;
			mod_array_right[(prefix_sum[r+1]-candies[max])%K]++;
		}
		r++;
	}
	if(max>=mid+1&&min<=mid){
    	while(l>=first&&max>=mid+1&&min<=mid){
        	if(candies[l]<candies[min])
           		min=l;
        	mod_array_left[(prefix_sum[l]+candies[min])%K]++;
    	   	l--;
		}
	}
	for(int i=0; i<K; i++)
		sumM+=mod_array_left[i]*mod_array_right[i];
	//case 4:max in the left, min in the right
    l=mid, r=mid+1;
    max=l, min=r;
    for(int i=0; i<K; i++){
        mod_array_left[i]=0;
        mod_array_right[i]=0;
    }
	while(r<=last){
		//make sure the property
		if(candies[r]>candies[max]){
			max=r;
			while(l>=first){
				if(candies[l]>candies[max]){
					max=l;
					break;
				}
				if(candies[l]<candies[min]){
					min=l;
				}
				l--;
			}
		}
		//couldn't make sure the property
		if(l<first)
			break;
		//could make sure the property
		if(candies[r]<candies[min]){
			mod_array_left[(prefix_sum[l]+candies[max])%K]++;
            l--;
			min=r;
			mod_array_right[(prefix_sum[r+1]-candies[min])%K]++;
		}
		else if(min>=mid+1&&max<=mid){
			mod_array_left[(prefix_sum[l]+candies[max])%K]++;
            l--;
			mod_array_right[(prefix_sum[r+1]-candies[min])%K]++;
		}
		r++;
	}
	if(max<=mid&&min>=mid+1){
		while(l>=first){
			if(candies[l]>candies[max])
				max=l;
			mod_array_left[(prefix_sum[l]+candies[max])%K]++;
			l--;
		}
	}
	for(int i=0; i<K; i++)
		sumM += mod_array_left[i]*mod_array_right[i];
	return sumM+sumL+sumR;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(nullptr);
	int N, K;
	cin>>N>>K;
	long long *candies = new long long[N];
	long long *prefix_sum=new long long[N+1];
	for(int i=0; i<N; i++)
		cin>>candies[i];
	prefix_sum[0]=0;
	for(int i=1; i<=N; i++){
		prefix_sum[i] = prefix_sum[i-1]+candies[i-1];
	}
	long long sum = ADA_party_rec(0, N-1, K, candies, prefix_sum);
	cout<<sum<<'\n';
}

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
	long long min[last], max[last];
	min[l]=candies[l];
	max[l]=candies[l];
	for(int i=l-1; i>=first; i--){
		if(candies[i]<min[i+1])
			min[i]=candies[i];
		else
			min[i]=min[i+1];
		if(candies[i]>max[i+1])
			max[i]=candies[i];
		else
			max[i]=max[i+1];
	}
	min[r]=candies[r];
	max[r]=candies[r];
	for(int i=r+1; i<=last; i++){
		if(candies[i]<min[i-1])
			min[i]=candies[i];
		else
			min[i]=min[i-1];
		if(candies[i]>max[i-1])
			max[i]=candies[i];
		else
			max[i]=max[i-1];
	}
	/*for(int i=0; i<K; i++)
		mod_array[i]= 0;*/
	vector<int> index_record;
	//case1: both max and min are in the left
	l=mid, r=mid+1;
	while(l>=first){
		while(r<=last){
			if(max[l]>max[r] && min[l]<min[r]){
				mod_array[prefix_sum[r+1]%K]++;
				index_record.push_back(r);
				r++;
			}
			else
				break;
		}
		sumM+=mod_array[(prefix_sum[l]+max[l]+min[l])%K];
		l--;
	}
	for(int i=0; i<index_record.size(); i++)
		mod_array[prefix_sum[index_record[i]+1]%K]--;
	index_record.clear();
	//case2: both max and min are in the right
	l=mid, r=mid+1;
	for(int i=0; i<K; i++)
		mod_array[i] = 0;
	while(r<=last){
		while(l>=first){
			if(max[r]>max[l] && min[r]<min[l]){
				mod_array[prefix_sum[l]%K]++;
				index_record.push_back(l);
				l--;
			}
			else
				break;
		}
		sumM+=mod_array[(prefix_sum[r+1]-max[r]-min[r])%K];
		r++;
	}
	for(int i=0; i<index_record.size(); i++)
		mod_array[prefix_sum[index_record[i]]%K]--;
	
	vector<int> index_record_plus, index_record_minus;
	//case3: max in the left, min in the right
	l=mid, r=mid+1;
	int p=r, q=r;
	/*for(int i=0; i<K; i++)
		mod_array[i] = 0;*/
	while(l>=first){
			while(q<=last){
				if(max[q]>max[l])
					break;
				else if(q>=p){
					mod_array[(prefix_sum[q+1]-min[q])%K]+=1;
					index_record_plus.push_back(q);
				}
				q++;
			}
			while(p<=last){
				if(min[p]<min[l])
					break;
				else if(p<q){
					mod_array[(prefix_sum[p+1]-min[p])%K]-=1;
					index_record_minus.push_back(p);
				}
				p++;
			}
		sumM+=mod_array[(prefix_sum[l]+max[l])%K];
		l--;
	}
	for(int i=0; i<index_record_plus.size(); i++)
		mod_array[(prefix_sum[index_record_plus[i]+1]-min[index_record_plus[i]])%K]--;
	for(int i=0; i<index_record_minus.size(); i++)
		mod_array[(prefix_sum[index_record_minus[i]+1]-min[index_record_minus[i]])%K]++;
	index_record_plus.clear();
	index_record_minus.clear();
	//case4: max in the right, min in the left
	l=mid, r=mid+1;
	p=r, q=r;
	for(int i=0; i<K; i++)
		mod_array[i] = 0;
	while(l>=first){
			while(q<=last){
                if(min[q]<min[l])
                    break;
                else if(q>=p)
                    mod_array[(prefix_sum[q+1]-max[q])%K]+=1;
                q++;
            }
            while(p<=last){
                if(max[p]>max[l])
                    break;
                else if(p<q)
                    mod_array[(prefix_sum[p+1]-max[p])%K]-=1;
                p++;
            }
		sumM+=mod_array[(prefix_sum[l]+min[l])%K];
		l--;
	}
	return sumM+sumL+sumR;
}




int main(){
	std::ios_base::sync_with_stdio(false);
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


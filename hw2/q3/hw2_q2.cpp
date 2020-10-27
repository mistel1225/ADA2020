#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int main(){
	long long n;
	bool flag;
	cin>>n;
	vector<long long> book_vector, book_vector1;
	vector<long long> beauty_arrange;
	book_vector.push_back(0);
	book_vector1.push_back(0);
	for(long long i=1; i<=n; i++){
		long long temp;
		cin>>temp;
		book_vector.push_back(temp);
		book_vector1.push_back(temp);
	}
	cin>>flag;
	long long a, b;
	for(long long i=1; i<=n; i++){
		if(book_vector[i]!=0){
			a=i;
			break;
		}
	}
	b=a+1;
	long long insert_num=0;
	while(a!=n&&b!=n){
		if(a<b){
			if(book_vector[b]==0){
				insert_num+=1;
				book_vector[b]+=1;
			}
			if(book_vector[a]==0){
				a=a+2;
				continue;
			}
			if(abs(a-beauty_arrange.back())==1){
				beauty_arrange.push_back(a);
				beauty_arrange.push_back(b);
			}
			else if(abs(b-beauty_arrange.back())==1){
				beauty_arrange.push_back(b);
				beauty_arrange.push_back(a);
			}
			book_vector[a]-=1;
			book_vector[b]-=1;
		}
		else if(a>b){
			if(book_vector[a]==0){
				while(book_vector[b]!=0){
					if(abs(a-beauty_arrange.back())==1){
						beauty_arrange.push_back(a);
						beauty_arrange.push_back(b);
						insert_num+=1;
						book_vector[b]-=1;
					}
					else if(abs(b-beauty_arrange.back())==1){
						beauty_arrange.push_back(b);
						beauty_arrange.push_back(a);
						insert_num+=1;
						book_vector[b]-=1;
					}
				}
				if(abs(a-beauty_arrange.back())==1){
					beauty_arrange.push_back(a);
					insert_num+=1;
				}
				a=a+2, b=b+2;
				continue;
			}
			if(book_vector[b]==0){
				b=b+2;
				continue;
			}
			if(abs(a-beauty_arrange.back())==1){
				beauty_arrange.push_back(a);
				beauty_arrange.push_back(b);
			}
			else if(abs(b-beauty_arrange.back())==1){
				beauty_arrange.push_back(b);
				beauty_arrange.push_back(a);
			}
			book_vector[a]-=1;
			book_vector[b]-=1;
		}
	}
	
	for(long long i=1; i<=n; i++){
		if(book_vector[i]!=0){
			a=i;
			break;
		}
	}
	b=a+1;
	long long insert_num2 =0;
	while(a!=n&&b!=n){
		
	}
}

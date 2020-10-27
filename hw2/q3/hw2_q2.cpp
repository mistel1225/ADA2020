#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int main(){
	long long n;
	bool flag;
	cin>>n;
	vector<long long> book_vector, book_vector2;
	vector<long long> beauty_arrange, beauty_arrange2;
	book_vector.push_back(0);
	book_vector1.push_back(0);
	for(long long i=1; i<=n; i++){
		long long temp;
		cin>>temp;
		book_vector.push_back(temp);
		book_vector2.push_back(temp);
	}
	cin>>flag;
	//init a and b
	long long a, b;
	for(long long i=1; i<=n; i++){
		if(book_vector[i]!=0){
			a=i;
			break;
		}
	}
	b=a+1;
	//pop out 0 element at the end of the book_vector
	for(long long i=n; i>=1; i--){
		if(book_vector[i]==0){
			book_vector.pop_back();
			book_vector2.pop_back();
		}
		else if(book_vector[i]!=0)
			break;
	}
	book_vector.push_back(0);
	long long insert_num=0;
	
	//deal with first book in beautiful arrangement
	beauty_arrange.push_back(a);
	book_vector[a]-=1;

	while(a<=n||b<=n){
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
				book_vector[a]-=1;
			}
			else if(abs(b-beauty_arrange.back())==1){
				beauty_arrange.push_back(b);
				book_vector[b]-=1;
			}
		}
		else if(a>b){
			if(book_vector[a]==0){
				insert_num+=1;
				book_vector[a]+=1;
			}
			if(book_vector[b]==0){
				b=b+2;
				continue;
			}
			if(abs(a-beauty_arrange.back())==1){
				beauty_arrange.push_back(a);
				book_vector[a]-=1;
			}
			else if(abs(b-beauty_arrange.back())==1){
				beauty_arrange.push_back(b);
				book_vector[b]-=1;
			}
		}
	}
	
	for(long long i=1; i<=n; i++){
		if(book_vector2[i]!=0){
			a=i;
			break;
		}
	}
	b=a+1;
	book_vector2.push_back(0);
	long long insert_num2 = 0;
	//push first book in the beauty arrangement
	if(book_vector2[b]==0){
		insert_num2+=1;
		book_vector2[b]+=1;
	}
	beauty_arrange2.push_back(b);
	book_vector2[b]-=1;
	while(a<=n||b<=n){
        if(a<b){
            if(book_vector2[b]==0){
                insert_num+=1;
                book_vector2[b]+=1;
            }
            if(book_vector2[a]==0){
                a=a+2;
                continue;
            }
            if(abs(a-beauty_arrange.back())==1){
                beauty_arrange2.push_back(a);
                book_vector[a]-=1;
            }
            else if(abs(b-beauty_arrange.back())==1){
                beauty_arrange2.push_back(b);
                book_vector2[b]-=1;
            }   
        }
        else if(a>b){
            if(book_vector2[a]==0){
                insert_num+=1;
                book_vector2[a]+=1;
            }
            if(book_vector2[b]==0){
                b=b+2;
                continue;
            }
            if(abs(a-beauty_arrange2.back())==1){
                beauty_arrange2.push_back(a);
                book_vector2[a]-=1;
            }
            else if(abs(b-beauty_arrange2.back())==1){
                beauty_arrange2.push_back(b);
                book_vector2[b]-=1;
            }   
        }	
	}
}

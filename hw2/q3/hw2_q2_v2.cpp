#include <iostream>
#include <vector>
using namespace std;


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    bool flag;
    cin>>n;
    vector<long long> book_vector(n+1);//, book_vector2(n+1);
    vector<long long> beauty_arrange(n+1);//, beauty_arrange2(n+1);
	vector<bool> beauty_arrange_order(n+1);//, beauty_arrange_order2(n+1);
    for(long long i=1; i<=n; i++){
        long long temp;
        cin>>temp;
        book_vector[i]=temp;
        //book_vector2[i]=temp;
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
			n--;
			//book_vector2.pop_back();
		}
		else if(book_vector[i]!=0)
			break;
	}

	long long insert_num=0;
	//deal with first book in beautiful arrangement
	if(book_vector[a]<book_vector[b]){
		//beauty_arrange will contain 12*book_vector[a] times
		beauty_arrange[a]=book_vector[a];
		book_vector[b]-=(book_vector[a]+1);
		book_vector[a]=0;
		//print "b" at first, i.e. 2121212.... and we should print 2 at first
		cout<<b<<" ";
		beauty_arrange_order[a]=0;
		a+=2;
	}
	else if(book_vector[a]==book_vector[b]){
		beauty_arrange[a]=book_vector[a];
		book_vector[a]=0;
		book_vector[b]=0;
		beauty_arrange_order[a]=0;
		a+=2, b+=2;
	}
	else if(book_vector[a]>book_vector[b]){
		insert_num+=(book_vector[a]-book_vector[b]);
		beauty_arrange[a]=book_vector[a];
		book_vector[a]=0;
		book_vector[b]=0;
		beauty_arrange_order[a]=0;
		a+=2, b+=2;
	}

	while(a<=n&&b<=n){
		if(a<b){
			if(book_vector[a]<book_vector[b]){
				beauty_arrange[a]=book_vector[a];
				book_vector[b]-=book_vector[a];
				book_vector[a]=0;
				if(beauty_arrange_order[a-1]==0)
					beauty_arrange_order[a]=1;
				else if(beauty_arrange_order[a-1]==1)
					beauty_arrange_order[a]=0;
				a+=2;
				continue;
			}
			else if(book_vector[a]==book_vector[b]){
				beauty_arrange[a]=book_vector[a];
				book_vector[b]=0;
				book_vector[a]=0;
				if(beauty_arrange_order[a-1]==0)
					beauty_arrange_order[a]=1;
				else if(beauty_arrange_order[a-1]==1)
					beauty_arrange_order[a]=0;
				a+=2, b+=2;
				continue;
			}
			else if(book_vector[a]>book_vector[b]){
				insert_num+=(book_vector[a]-book_vector[b]+1);
				beauty_arrange[a]=book_vector[a];
				book_vector[a]=0;
				book_vector[b]=0;
				if(beauty_arrange_order[a-1]==0)
					beauty_arrange_order[a]=1;
				else if(beauty_arrange_order[a-1]==1)
					beauty_arrange_order[a]=0;
				a+=2, b+=2;
				continue;
			}
		}
		else if(b<a){
			if(book_vector[b]<book_vector[a]){
				beauty_arrange[b]=book_vector[b];
				book_vector[a]-=book_vector[b];
				book_vector[b]=0;
				if(beauty_arrange_order[b-1]==0)
					beauty_arrange_order[b]=1;
				else if(beauty_arrange_order[b-1]==1)
					beauty_arrange_order[b]=0;
				b+=2;
				continue;
			}
			else if(book_vector[b]==book_vector[a]){
				beauty_arrange[b]=book_vector[b];
				book_vector[b]=0;
				book_vector[a]=0;
				if(beauty_arrange_order[b-1]==0)
					beauty_arrange_order[b]=1;
				else if(beauty_arrange_order[b-1]==1)
					beauty_arrange_order[b]=0;
				b+=2;
				continue;
			}
			else if(book_vector[b]>book_vector[a]){
				insert_num+=(book_vector[b]-book_vector[a]+1);
				beauty_arrange[b]=book_vector[b];
				book_vector[a]=0;
				book_vector[b]=0;
				if(beauty_arrange_order[b-1]==0)
					beauty_arrange_order[b]=1;
				else if(beauty_arrange_order[b-1]==1)
					beauty_arrange_order[b]=0;
				b+=2;
				continue;
			}
		}
	}
	if(book_vector[n]!=0){
		insert_num+=book_vector[n];
		beauty_arrange[n]=book_vector[n];
		 
	}




}

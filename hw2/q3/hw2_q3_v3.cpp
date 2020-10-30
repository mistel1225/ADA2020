#include <iostream>
#include <vector>
using namespace std;


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    bool flag;
    cin>>n;
    long long book_vector[n+1]={0}, book_vector2[n+1]={0};
    //long long beauty_arrange[n+1]={0}, beauty_arrange2[n+1]={0};
	bool beauty_arrange_order[n+1], beauty_arrange_order2[n+1];
    for(long long i=1; i<=n; i++){
        cin>>book_vector[i];
        book_vector2[i]=book_vector[i];
    }   
	cin>>flag;

	//init a and b
	long long a, b;
	long long temp;
	for(long long i=1; i<=n; i++){
		if(book_vector[i]!=0){
			temp=i;
			break;
		}
	}
	a=temp;
	b=a+1;
	//pop out 0 element at the end of the book_vector
	for(long long i=n; i>=1; i--){
		if(book_vector[i]==0){
			//book_vector.pop_back();
			n--;
			//book_vector2.pop_back();
		}
		else if(book_vector[i]!=0)
			break;
	}
	long long beauty_arrange[n+1]={0}, beauty_arrange2[n+1]={0};
	long long insert_num=0;
	long long insert_num2=0;
	//insert book to zero element in advance
	for(long long i=a; i<=n; i++){
		if(book_vector[i]==0){
			book_vector[i]=1;
			book_vector2[i]=1;
			insert_num+=1;
			insert_num2+=1;
		}
	}
	if(a==n){
		if(a==1)
			b=a+1;
		else
			b=a-1;
		insert_num+=(book_vector[a]-1);
		cout<<insert_num<<endl;
		if(flag==1){
			for(long long i=0; i<book_vector[a]-1; i++){
				cout<<a<<" "<<b<<" ";
			}
			cout<<a<<endl;
		}
		return 0;
	}
	else if(n==2){
		if(book_vector[a]<book_vector[b]){
			beauty_arrange[b]=book_vector[a];
			book_vector[b]-=book_vector[a];
			beauty_arrange[b]+=(book_vector[b]-1);
			book_vector[a]=0;
			beauty_arrange_order[b]=1;
			insert_num+=(book_vector[b]-1);
			book_vector[b]=1;
		}
		else if(book_vector[a]==book_vector[b]){
			beauty_arrange[b]=book_vector[a];
			book_vector[a]=0;
			book_vector[b]=0;
			beauty_arrange_order[b]=0;
		}
		else if(book_vector[a]>book_vector[b]){
			beauty_arrange[b]=book_vector[b];
			book_vector[a]-=book_vector[b];
			beauty_arrange[b]+=(book_vector[a]-1);
			book_vector[b]=0;
			beauty_arrange_order[b]=0;
			insert_num+=(book_vector[a]-1);
			book_vector[a]=1;
		}
		cout<<insert_num<<endl;
		if(flag==1){
			for(long long i=0; i<beauty_arrange[b]; i++){
				if(beauty_arrange_order[b]==0)
					cout<<b-1<<" "<<b<<" ";
				else if(beauty_arrange_order[b]==1)
					cout<<b<<" "<<b-1<<" ";
			}
			if(book_vector[b]==1)
				cout<<b;
			else if(book_vector[a]==1)
				cout<<a;
			cout<<endl;
		}
		return 0;
	}

	//deal with first book in beautiful arrangement
	if(book_vector[a]<book_vector[b]){
		//beauty_arrange will contain 12*book_vector[a] times
		beauty_arrange[b]=book_vector[a];
		book_vector[b]-=book_vector[a];
		book_vector[a]=0;
		beauty_arrange_order[b]=1;
		a+=2;
	}
	else if(book_vector[a]==book_vector[b]){
		beauty_arrange[b]=book_vector[a];
		book_vector[a]=0;
		book_vector[b]=0;
		beauty_arrange_order[b]=0;
		a+=2;
	}
	else if(book_vector[a]>book_vector[b]){
		insert_num+=(book_vector[a]-book_vector[b]);
		beauty_arrange[b]=book_vector[a];
		book_vector[a]=0;
		book_vector[b]=0;
		beauty_arrange_order[b]=0;
		a+=2;
	}
	while(a<n&&b<n){
		if(a<b){
			if(book_vector[a]<book_vector[b]){
				beauty_arrange[b]=book_vector[a];
				book_vector[b]-=book_vector[a];
				book_vector[a]=0;
				if(beauty_arrange[a]==0)
					beauty_arrange_order[b]=0;
				else if(beauty_arrange_order[a]==0)
					beauty_arrange_order[b]=1;
				else if(beauty_arrange_order[a]==1)
					beauty_arrange_order[b]=0;
				if(beauty_arrange_order[a]==1&&beauty_arrange[b]==0){
					beauty_arrange[b]+=1;
					book_vector[b]-=1;
					insert_num+=1;
				}
				a+=2;
				continue;
			}
			else if(book_vector[a]==book_vector[b]){
				beauty_arrange[b]=book_vector[a];
				book_vector[b]=0;
				book_vector[a]=0;
				if(beauty_arrange[a]==0)
					beauty_arrange_order[b]=0;
				else if(beauty_arrange_order[a]==0)
					beauty_arrange_order[b]=1;
				else if(beauty_arrange_order[a]==1)
					beauty_arrange_order[b]=0;
				a+=2;
				continue;
			}
			else if(book_vector[a]>book_vector[b]){
				insert_num+=(book_vector[a]-book_vector[b]);
				beauty_arrange[b]=book_vector[a];
				book_vector[a]=0;
				book_vector[b]=0;
				if(beauty_arrange[a]==0)
					beauty_arrange_order[b]=0;
				else if(beauty_arrange_order[a]==0)
					beauty_arrange_order[b]=1;
				else if(beauty_arrange_order[a]==1)
					beauty_arrange_order[b]=0;
				a+=2;
				continue;
			}
		}
		else if(b<a){
			if(book_vector[b]<book_vector[a]){
				beauty_arrange[a]=book_vector[b];
				book_vector[a]-=book_vector[b];
				book_vector[b]=0;
				if(beauty_arrange[b]==0)
					beauty_arrange_order[a]=0;
				else if(beauty_arrange_order[b]==1)
					beauty_arrange_order[a]=0;
				else if(beauty_arrange_order[b]==0)
					beauty_arrange_order[a]=1;
				if(beauty_arrange_order[b]==1&&beauty_arrange[a]==0){
					beauty_arrange[a]+=1;
					insert_num+=1;
					book_vector[a]-=1;
				}
				b+=2;
				continue;
			}
			else if(book_vector[b]==book_vector[a]){
				beauty_arrange[a]=book_vector[b];
				book_vector[b]=0;
				book_vector[a]=0;
				if(beauty_arrange[b]==0)
					beauty_arrange_order[a]=0;
				else if(beauty_arrange_order[b]==1)
					beauty_arrange_order[a]=0;
				else if(beauty_arrange_order[b]==0)
					beauty_arrange_order[a]=1;
				b+=2;
				continue;
			}
			else if(book_vector[b]>book_vector[a]){
				insert_num+=(book_vector[b]-book_vector[a]);
				beauty_arrange[a]=book_vector[b];
				book_vector[a]=0;
				book_vector[b]=0;
				if(beauty_arrange[b]==0)
					beauty_arrange_order[a]=0;
				else if(beauty_arrange_order[b]==1)
					beauty_arrange_order[a]=0;
				else if(beauty_arrange_order[b]==0)
					beauty_arrange_order[a]=1;
				b+=2;
				continue;
			}
		}
	}
	if(book_vector[n]!=0){
		if(book_vector[n-1]>book_vector[n]){
			beauty_arrange[n]+=book_vector[n];
			book_vector[n-1]-=book_vector[n];
			book_vector[n]=0;
			if(beauty_arrange[n-1]==0)
				beauty_arrange_order[n]=0;
			else if(beauty_arrange_order[n-1]==0)
				beauty_arrange_order[n]=1;
			else if(beauty_arrange_order[n-1]==1)
				beauty_arrange_order[n]=0;
			if(beauty_arrange_order[n]==0){
				insert_num+=(book_vector[n-1]-1);
				beauty_arrange[n]+=(book_vector[n-1]-1);
				book_vector[n-1]=1;
			}
			else if(beauty_arrange_order[n]==1){
				insert_num+=book_vector[n-1];
				beauty_arrange[n]+=book_vector[n-1];
				book_vector[n-1]=0;
			}
		}
		else if(book_vector[n-1]==book_vector[n]){
			beauty_arrange[n]+=book_vector[n-1];
			book_vector[n]=0;
			book_vector[n-1]=0;
			if(beauty_arrange[n-1]==0)
				beauty_arrange_order[n]=0;
			else if(beauty_arrange_order[n-1]==0)
				beauty_arrange_order[n]=1;
			else if(beauty_arrange_order[n-1]==1)
				beauty_arrange_order[n]=0;
		}
		else if(book_vector[n-1]<book_vector[n]){
			beauty_arrange[n]+=book_vector[n-1];
			book_vector[n]-=book_vector[n-1];
			book_vector[n-1]=0;
			if(beauty_arrange[n-1]==0)
				beauty_arrange_order[n]=0;
			else if(beauty_arrange_order[n-1]==0)
				beauty_arrange_order[n]=1;
			else if(beauty_arrange_order[n-1]==1)
				beauty_arrange_order[n]=0;
			if(beauty_arrange_order[n]==0){
				insert_num+=book_vector[n];
				beauty_arrange[n]+=book_vector[n];
				book_vector[n]=0;
			}
			else if(beauty_arrange_order[n]==1){
				insert_num+=book_vector[n]-1;
				beauty_arrange[n]+=(book_vector[n]-1);
				book_vector[n]=1;
			}
		}
	}
	//second round
	/*for(long long i=1; i<=n; i++){
        if(book_vector2[i]!=0){
            a=i;
            break;
        }
    }
    b=a+1;*/
	a=temp;
	b=a+1;
	if(book_vector2[a]==book_vector2[b]){
        beauty_arrange2[b]=book_vector2[a];
        book_vector2[a]=0;
        book_vector2[b]=0;
        beauty_arrange_order2[b]=0;
        a+=2;
	}
    else if(book_vector2[a]>book_vector2[b]){
        insert_num2+=(book_vector2[a]-book_vector2[b]);
        beauty_arrange2[b]=book_vector2[a];
        book_vector2[a]=0;
        book_vector2[b]=0;
        beauty_arrange_order2[b]=0;
        a+=2;
    }
	else if(book_vector2[a]<book_vector2[b]){
        beauty_arrange2[b]=book_vector2[a];
        book_vector2[b]-=(book_vector2[a]);
        book_vector2[a]=0;
        beauty_arrange_order2[b]=0;
        a+=2;
	}
	while(a<n&&b<n){
		if(a<b){
			if(book_vector2[a]<book_vector2[b]){
				beauty_arrange2[b]=book_vector2[a];
				book_vector2[b]-=book_vector2[a];
				book_vector2[a]=0;
				if(beauty_arrange2[a]==0)
					beauty_arrange_order2[b]=0;
				else if(beauty_arrange_order2[a]==0)
					beauty_arrange_order2[b]=1;
				else if(beauty_arrange_order2[a]==1)
					beauty_arrange_order2[b]=0;
				if(beauty_arrange_order2[a]==1&&beauty_arrange2[b]==0){
					beauty_arrange2[b]+=1;
					book_vector2[b]-=1;
					insert_num2+=1;
				}
				a+=2;
				continue;
			}
			else if(book_vector2[a]==book_vector2[b]){
				beauty_arrange2[b]=book_vector2[a];
				book_vector2[b]=0;
				book_vector2[a]=0;
				if(beauty_arrange2[a]==0)
					beauty_arrange_order2[b]=0;
				else if(beauty_arrange_order2[a]==0)
					beauty_arrange_order2[b]=1;
				else if(beauty_arrange_order2[a]==1)
					beauty_arrange_order2[b]=0;
				a+=2;
				continue;
			}
			else if(book_vector2[a]>book_vector2[b]){
				insert_num2+=(book_vector2[a]-book_vector2[b]);
				beauty_arrange2[b]=book_vector2[a];
				book_vector2[a]=0;
				book_vector2[b]=0;
				if(beauty_arrange2[a]==0)
					beauty_arrange_order2[b]=0;
				else if(beauty_arrange_order2[a]==0)
					beauty_arrange_order2[b]=1;
				else if(beauty_arrange_order2[a]==1)
					beauty_arrange_order2[b]=0;
				a+=2;
				continue;
			}
		}
		else if(b<a){
			if(book_vector2[b]<book_vector2[a]){
				beauty_arrange2[a]=book_vector2[b];
				book_vector2[a]-=book_vector2[b];
				book_vector2[b]=0;
				if(beauty_arrange2[b]==0)
					beauty_arrange_order2[a]=0;
				else if(beauty_arrange_order2[b]==1)
					beauty_arrange_order2[a]=0;
				else if(beauty_arrange_order2[b]==0)
					beauty_arrange_order2[a]=1;
				if(beauty_arrange_order2[b]==1&&beauty_arrange2[a]==0){
					beauty_arrange2[a]+=1;
					insert_num2+=1;
					book_vector2[a]-=1;
				}
				b+=2;
				continue;
			}
			else if(book_vector2[b]==book_vector2[a]){
				beauty_arrange2[a]=book_vector2[b];
				book_vector2[b]=0;
				book_vector2[a]=0;
				if(beauty_arrange2[b]==0)
					beauty_arrange_order2[a]=0;
				else if(beauty_arrange_order2[b]==1)
					beauty_arrange_order2[a]=0;
				else if(beauty_arrange_order2[b]==0)
					beauty_arrange_order2[a]=1;
				b+=2;
				continue;
			}
			else if(book_vector2[b]>book_vector2[a]){
				insert_num2+=(book_vector2[b]-book_vector2[a]);
				beauty_arrange2[a]=book_vector2[b];
				book_vector2[a]=0;
				book_vector2[b]=0;
				if(beauty_arrange2[b]==0)
					beauty_arrange_order2[a]=0;
				else if(beauty_arrange_order2[b]==1)
					beauty_arrange_order2[a]=0;
				else if(beauty_arrange_order2[b]==0)
					beauty_arrange_order2[a]=1;
				b+=2;
				continue;
			}
		}
	}
	if(book_vector2[n]!=0){
		if(book_vector2[n-1]>book_vector2[n]){
			beauty_arrange2[n]+=book_vector2[n];
			book_vector2[n-1]-=book_vector2[n];
			book_vector2[n]=0;
			if(beauty_arrange2[n-1]==0)
				beauty_arrange_order2[n]=0;
			else if(beauty_arrange_order2[n-1]==0)
				beauty_arrange_order2[n]=1;
			else if(beauty_arrange_order2[n-1]==1)
				beauty_arrange_order2[n]=0;
			if(beauty_arrange_order2[n]==0){
				insert_num2+=(book_vector2[n-1]-1);
				beauty_arrange2[n]+=(book_vector2[n-1]-1);
				book_vector2[n-1]=1;
			}
			else if(beauty_arrange_order2[n]==1){
				insert_num2+=book_vector2[n-1];
				beauty_arrange2[n]+=book_vector2[n-1];
				book_vector2[n-1]=0;
			}
		}
		else if(book_vector2[n-1]==book_vector2[n]){
			beauty_arrange2[n]+=book_vector2[n-1];
			book_vector2[n]=0;
			book_vector2[n-1]=0;
			if(beauty_arrange2[n-1]==0)
				beauty_arrange_order2[n]=0;
			else if(beauty_arrange_order2[n-1]==0)
				beauty_arrange_order2[n]=1;
			else if(beauty_arrange_order2[n-1]==1)
				beauty_arrange_order2[n]=0;
		}
		else if(book_vector2[n-1]<book_vector2[n]){
			beauty_arrange2[n]+=book_vector2[n-1];
			book_vector2[n]-=book_vector2[n-1];
			book_vector2[n-1]=0;
			if(beauty_arrange2[n-1]==0)
				beauty_arrange_order2[n]=0;
			else if(beauty_arrange_order2[n-1]==0)
				beauty_arrange_order2[n]=1;
			else if(beauty_arrange_order2[n-1]==1)
				beauty_arrange_order2[n]=0;
			if(beauty_arrange_order2[n]==0){
				insert_num2+=book_vector2[n];
				beauty_arrange2[n]+=book_vector2[n];
				book_vector2[n]=0;
			}
			else if(beauty_arrange_order2[n]==1){
				insert_num2+=book_vector2[n]-1;
				beauty_arrange2[n]+=(book_vector2[n]-1);
				book_vector2[n]=1;
			}
		}
	}
	if(insert_num<=insert_num2){
		cout<<insert_num<<endl;
		if(flag==1){
			/*for(long long i=2; i<=n; i++){
				for(long long j=0; j<beauty_arrange[i]; j++){
					if(beauty_arrange_order[i]==0)
						cout<<i-1<<" "<<i<<" ";
					else if(beauty_arrange_order[i]==1)
						cout<<i<<" "<<i-1<<" ";
				}
			}*/
			for(long long i=2; i<=n; i++){
				if(beauty_arrange_order[i]==0)
					for(long long j=0; j<beauty_arrange[i]; j++)
						cout<<i-1<<" "<<i<<" ";
				else if(beauty_arrange_order[i]==1)
					for(long long j=0; j<beauty_arrange[i]; j++)
						cout<<i<<" "<<i-1<<" ";
			}
			if(book_vector[n]==1)
				cout<<n<<" ";
			else if(book_vector[n-1]==1)
				cout<<n-1<<" ";
			cout<<endl;
		}
	}
	else{
		cout<<insert_num2<<endl;
		if(flag==1){
			/*for(long long i=2; i<=n; i++){
				for(long long j=0; j<beauty_arrange2[i]; j++){
					if(beauty_arrange_order2[i]==0)
						cout<<i-1<<" "<<i<<" ";
					else if(beauty_arrange_order2[i]==1)
						cout<<i<<" "<<i-1<<" ";
				}
			}*/
			for(long long i=2; i<=n; i++){
				if(beauty_arrange_order2[i]==0)
					for(long long j=0; j<beauty_arrange2[i]; j++)
						cout<<i-1<<" "<<i<<" ";
				else if(beauty_arrange_order2[i]==1)
					for(long long j=0; j<beauty_arrange2[i]; j++)
						cout<<i<<" "<<i-1<<" ";
			}
			if(book_vector2[n]==1)
				cout<<n<<" ";
			else if(book_vector2[n-1]==1)
				cout<<n-1<<" ";
			cout<<endl;
		}	
	}
	return 0;
}

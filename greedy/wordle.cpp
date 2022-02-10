#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<string> W;

int main(){
	FILE *in = fopen("l5w.txt","r");
	//freopen("output.txt","w",stdout);
	for(char t, T=0, w[5]={0}; ~fscanf(in,"%c",&t);){
		('a'<=t && t<='z') ? w[T++]=t : T=0;
		if(T==5) W.push_back(string(w)), T=0;
	}
	//for(int i=0, j; i<26; puts(""), ++i) for(printf("%c | ",i+'a'), j=0; j<5; ++j) printf("%5d",freq[i][j]);
	
	int wordle[26][5]={0};
	bool hasw[26]={0};
	for(int Q=0; Q<6; ++Q){
		vector<string> A = W, B;
		char w[10]={0};
		for(int i=0; i<5; ++i) for(int j=0; j<26; ++j) if(wordle[j][i]==1) w[i]=j+'a';
		//printf(": 0(%c)1(%c)2(%c)3(%c)4(%c)\n",w[0],w[1],w[2],w[3],w[4]);

		for(int T=0; T<5; ++T){
			int freq[26][5]={0};
			for(auto&t:A){
				bool ch=0;
				for(int i=0; i<5; ++i) ch|=((w[i] && w[i]!=t[i])|(wordle[t[i]-'a'][i]==-1));
				for(int i=0; i<26; ++i) {
					if(hasw[i]) {
						bool cf=0;
						for(int j=0; j<5; ++j) cf|=((i+'a') == t[j]);
						ch|=!cf;
					}
				}
				if(ch) continue;
				B.push_back(t);
			}
			A.clear(); A=B; B.clear();
			for(auto&t:A) for(int i=0; i<5; ++i) if(w[i]!=t[i]) freq[t[i]-'a'][i]++;
			int C=0, P=-1;
			for(int i=0; i<26; ++i) for(int j=0; j<5; ++j) if(C<freq[i][j]) C=freq[i][j], P=i*5+j;
			if(P==-1) continue;
			w[P%5] = P/5+'a';
			//printf("%c %d\n",P/5+'a',P%5);
			//for(int i=0, j; i<26; puts(""), ++i) for(printf("%c | ",i+'a'), j=0; j<5; ++j) printf("%5d",freq[i][j]); puts("");
		}
		printf("%s\n",w);
		
		char res[10];
		scanf("%s",res);
		
		int cnt=0;
		for(int i=0, j; i<5; ++i){
			j=res[i]-'0'; cnt+=j==2;
			if(!j) for(int k=0; k<5; ++k) wordle[w[i]-'a'][k] = -1;
			else{
				hasw[w[i]-'a']=1;
				wordle[w[i]-'a'][i] = (j-1)?1:-1;
			}
		}
		
		if(cnt==5) {
			printf("the answer is : %s\n",w);
			return 0;
		}
		//for(int i=0, j; i<26; puts(""), ++i) for(printf("%c %d | ",i+'a',hasw[i]), j=0; j<5; ++j) printf("%5d",wordle[i][j]); puts("");
	}
}

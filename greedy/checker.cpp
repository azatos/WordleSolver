#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<int,string> pis;

vector<string> W;

int main(){
	FILE *in = fopen("l5w.txt","r");
	//freopen("output.txt","w",stdout);
	int freq[26][5]={0};
	for(char t, T=0, w[5]={0}; ~fscanf(in,"%c",&t);){
		('a'<=t && t<='z') ? w[T++]=t : T=0;
		if(T==5) W.push_back(string(w)), T=0;
	}
	fclose(in);
	
	bool P_OPT1=0;
	bool P_OPT2=0;
	bool I_OPT1=0;
	
	int anscnt[20]={0}, WCNT=0, SCNT=0;
	for(auto&WORD:W){
		++WCNT;
		if(WCNT%1000==0) printf("%d\n",WCNT);
		int wordle[26][5]={0};
		bool hasw[26]={0}, solved=0;
		char w[]="cares";
		vector<string> A = W, B, C; // B available group, C guess group
		for(int Q=1; Q<15; ++Q){
			if(P_OPT1) puts(w);
			char res[10];
			if(I_OPT1) scanf("%s",res);
			else{
				for(int i=0; i<5; ++i){
					if(WORD[i]==w[i]) res[i]='2';
					else{
						bool chk=0;
						for(int j=0; j<5; ++j) chk|=(WORD[j]==w[i]);
						res[i]=chk+'0';
					}
				}
				if(P_OPT1) printf("%s\n",res);
			}
			
			int cnt=0;
			for(int i=0, j; i<5; ++i){
				j=res[i]-'0'; cnt+=j==2;
				if(!j) for(int k=0; k<5; ++k) wordle[w[i]-'a'][k] = -1;
				else hasw[w[i]-'a']=1, wordle[w[i]-'a'][i] = (j-1)?1:-1;
			}
			if(cnt==5) {
				if(P_OPT1) printf("the answer is : %s | count : %d\n",w,Q);
				solved=1;
				++anscnt[Q];
				break;
			}
			if(P_OPT2) {for(int i=0, j; i<26; puts(""), ++i) for(printf("%c %d | ",i+'a',hasw[i]), j=0; j<5; ++j) printf("%5d",wordle[i][j]); puts("");}
			
			int freq[26][5]={0};
			for(auto&t:A){
				bool ch=0;
				for(int i=0; i<5; ++i) ch|=(wordle[t[i]-'a'][i]==-1);
				if(ch) continue;
				C.push_back(t);
				for(int i=0; i<5; ++i) {
					freq[t[i]-'a'][i]++;
					for(int j=0; j<26; ++j) if(wordle[j][i]==1 && t[i]!=j+'a') ch=1;
				}
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
			
			int c=0;
			vector<pis> D, E;
			for(auto&t:C){
				for(int i=0; i<5; ++i){
					c+=wordle[t[i]-'a'][i]?0:freq[t[i]-'a'][i];
				}
				D.push_back({c,t});
				int ch=1; for(int i=0; i<5; ++i) for(int j=0; j<i; ++j) if(t[i]==t[j]) ch=0;
				if(ch) E.push_back({c,t});
			}
			sort(D.begin(),D.end(),[](pis a,pis b){return a.x>b.x;});
			sort(E.begin(),E.end(),[](pis a,pis b){return a.x>b.x;});
			if(P_OPT1) printf("%d %d\n",D.size(),E.size());
			if(E.size()) for(int i=0; i<5; ++i) w[i]=E[0].y[i];
			else for(int i=0; i<5; ++i) w[i]=D[0].y[i];
			
			A.clear(); A=B;
			B.clear(); C.clear();
		}
		if(solved) ++SCNT;
	}
	printf("Total : %d | Solved : %d\n",W.size(),SCNT);
	puts("Answer Trial Count :");
	long double p=0;
	for(int i=0; i<N; ++i) printf("%5d",anscnt[i]), p+=anscnt[i]*(i+1);
	printf("\n%Lf",p/(long double)SCNT);
}

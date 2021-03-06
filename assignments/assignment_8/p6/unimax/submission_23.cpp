//Data Structure includes
#include<vector>
#include<stack>
#include<set>
#include<map>
#include<queue>
#include<deque>
#include<string>


//Other Includes
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cassert>
#include<cstdlib>
#include<cstdio>
#include<cmath>

using namespace std;

#define FOR(i,a,b)					for(int i=a;i<b;i++)
#define REP(i,n)					FOR(i,0,n)
#define pb						 	push_back
#define mp						 	make_pair
#define s(n)						scanf("%d",&n)
#define sl(n) 						scanf("%lld",&n)
#define sf(n) 						scanf("%lf",&n)
#define ss(n) 						scanf("%s",n)
#define fill(a,v) 					memset(a, v, sizeof a)
#define sz							size()
#define INF							(int)1e9
#define EPS							1e-9
#define bitcount					__builtin_popcount
#define all(x)						x.begin(), x.end()
#define gcd							__gcd
#define maX(a,b)					(a>b?a:b)
#define miN(a,b)					(a<b?a:b)

typedef vector<int> VI;
typedef vector<vector<int> > VVI;
typedef long long LL;
typedef pair<LL, LL > PLL;

/*Main code begins now */
int testnum;
VVI facts;


void preprocess()
{
	int N=120000;
	facts.resize(N+5);
	for(int i=1;i<=N;i++)
		for(int j=i;j<=N;j+=i)
			facts[j].pb(i);
			
}

LL n,k,kn;
set<PLL> all;

void doit(LL k)
{
	if(k==0)
	{
		cout<<0<<endl;
		return;
	}
	
	VI arr;
	while(k>0)
	{
		arr.pb(k);
		k/=10;
	}
	int len=arr.size();

	
	VI res;
	res.resize(2*len+1);
	for(int i=0;i<len;i++)
		for(int j=0;j<len;j++)
			res[i+j] += arr[i]*arr[j];
			
	for(int i=0;i<2*len;i++)
	{
		res[i+1] += res[i]/10;
		res[i] %= 10;
	}
	
	int last=2*len;
	while(res[last]==0)
		last--;
		
	for(int i=last;i>=0;i--)
		cout<<res[i];
	cout<<endl;
}

LL iter1,iter2,iter3;


void solve(LL K,LL beg)
{
	double z=sqrt(K);
	double f = z/(z-1)-1;
	LL upp = (LL)(f*n+1);
	//cout<<f<<endl;
	
	LL init = n/(K-1);
	init = max(init,beg-1);
	
	
	LL num = n*(init+n-1);
	LL den = (K-1)*init - n;
	
	LL K1=K-1;
	for(LL B=init+1; B+n<k && B<=upp; B++)
	{
		num += n;
		den += K1;

		//iter1++;
		
		if(den>0 && num % den == 0)
		{
			LL A = num/den;
			if(A<kn)
			{
				all.insert(mp(min(A,B), max(A,B)));
				//iter3++;
			}
		}
	}
		

}
	
int lcnt;

void solve()
{
	if(n==0)
	{
		k--;
		doit(k);
		return;
	}
	

	all.clear();
	
	
	LL lim = 1500;
	double z=sqrt(lim);
	double f = z/(z-1)-1;
	LL blim = (LL)(f*n)+1;
	
	for(LL K=2;K<lim;K++)
		solve(K,blim);
	
	
	//cout<<f<<endl;
	
	VI an = facts[n];
	int fn = an.size();
	for(LL B=1; B+n<k && B<=blim; B++)
	{
		LL z = B+n-1;
		int fz = facts[z].size();
		for(int i=0;i<fz;i++)
		{
			LL xxx = facts[z][i];
			for(int j=0;j<fn;j++)
			{
				//iter2++;
				LL A = xxx * an[j];
				if(A>=B && A<kn && ((n*(A+z)) % (B*A) == 0) )
				{
					all.insert(mp(min(A,B), max(A,B)));
					//iter3++;
				}

			}
		}
	}
	
	LL cnt=0;
	LL best=0;
	for(set<PLL>::iterator it=all.begin(); it!=all.end(); it++)
	{
		if( (*it).first == (*it).second )
			cnt++;
		else
			cnt+=2;
		//if(cnt<=20)
		//	cout<<((*it).first+n)<<" "<<((*it).second+n)<<endl;
	}

	cout<<cnt<<endl;
	

}

bool input()
{
	cin>>n>>k;
	kn=k-n;
	return true;
}


int main()
{
	iter1=0;
	iter2=0;
	iter3=0;
	lcnt=0;
	preprocess();
	int T; s(T);
	assert(T<=5);
	for(testnum=1;testnum<=T;testnum++)
	{
		if(!input()) break;
		solve();
	}
	//cout<<iter1<<"\t"<<iter2<<"\t"<<iter3<<endl;

}               
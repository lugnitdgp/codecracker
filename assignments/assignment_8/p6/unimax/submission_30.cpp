#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <complex>
#pragma comment(linker, "/STACK:266777216")
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<LL> VLL;
typedef pair<int,int> PII;
typedef vector<PII> VPII;
typedef vector<double> VD;
typedef pair<double,double> PDD;

const int inf=1000000000;
const LL INF=LL(inf)*inf;
const double eps=1e-9;
const double PI=2*acos(0.0);
#define bit(n) (1<<(n))
#define bit64(n) ((LL(1))<<(n))
#define pb push_back
#define sz size()
#define mp make_pair
#define cl clear()
#define all(a) (a).begin(),(a).end()
#define fill(ar,val) memset((ar),(val),sizeof (ar))
#define MIN(a,b) {if((a)>(b)) (a)=(b);}
#define MAX(a,b) {if((a)<(b)) (a)=(b);}
#define sqr(x) ((x)*(x))
#define X first
#define Y second

#define p_len 4
const int base=10000;
#define NN 50/p_len

struct num
{
	int len;
	int it[NN];

	num(LL n=0)
	{
		for(len=0;n>0;n/=base) it[len++]=n%base;
	}

	void print() const
	{
		if(len==0) printf("0"); else
		{
			int i=len-1;
			printf("%d",it[i]);
			char s[10];
			sprintf(s,"%%0%dd",p_len);
			for(i--;i>=0;i--) printf(s,it[i]);
		}
		printf("\n");
	}
};

num operator*(num &a,num &b)
{
	num prod(0);
	memset(prod.it,0,sizeof prod.it);
	if(b.len==0 || a.len==0) return prod;
	int i,j,d;
	for(i=0;i<a.len;i++)
	{
		if(a.it[i]>0)
		{
			d=0;
			for(j=0;j<b.len;j++)
			{
				d+=prod.it[i+j]+a.it[i]*b.it[j];
				prod.it[i+j]=d%base;
				d/=base;
			}
			if(d>0) prod.it[i+j]=d;
		}
	}
	prod.len=a.len+b.len;
	if(prod.it[prod.len-1]==0) prod.len--;
	return prod;
}

//clock_t start=clock();
//fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));

int gcd(int a,int b)
{
	int c;
	while(b) c=a%b,a=b,b=c;
	return a;
}

int inv(int b,int m)
{
	int x0=0,x1=1,x,c,q;
	int a=m;
	while(b)
	{
		q=a/b;
		c=a-q*b,a=b,b=c;
		x=x0-q*x1,x0=x1,x1=x;
	}
	if(x0<0) x0+=m;
	return x0;
}

#define N 1000000
int minp[N];
int primes[N];
int plen;

void sieve()
{
	for(int i=2;i<N;i++) if(!minp[i])
	{
		primes[plen++]=i;
		for(int j=i;j<N;j+=i)
			if(!minp[j]) minp[j]=i;
	}
}

int count_it;
VPII factor(int n) // n < 2e9
{
	VPII res;
	if(n<N)
	{
		for(;n>1;)
		{
			int p=minp[n];
			int a=0;
			for(;n%p==0;n/=p) a++;
			res.pb(mp(p,a));
		}
		count_it=0;
	}
	else
	{
		int i;
		for(i=0;i<plen;i++)
		{
			int p=primes[i];
			if(p*p>n) break;
			if(n%p) continue;
			int a=0;
			for(;n%p==0;n/=p) a++;
			res.pb(mp(p,a));
		}
		if(n>1) res.pb(mp(n,1));
		count_it=i;
	}
	return res;
}

VPII unite(const VPII &a,const VPII &b)
{
	VPII res;
	int i,j;
	for(i=j=0;i<a.sz && j<b.sz;)
		if(a[i].X<b[j].X) res.pb(a[i++]); else
		if(a[i].X>b[j].X) res.pb(b[j++]); else
		{
			res.pb(mp(a[i].X,a[i].Y+b[j].Y));
			i++;j++;
		}
	for(;i<a.sz;) res.pb(a[i++]);
	for(;j<b.sz;) res.pb(b[j++]);
	return res;
}

int brute_k(int n,LL mx,int k)
{
	int ans=0;
	LL m=LL(n)*((k+1)*n-k),x,y;
	for(x=n/k+1;x<=mx;x++)
	{
		if(m%(k*x-n)==0)
		{
			y=m/(k*x-n);
			if((y+n)%k==0)
			{
				y=(y+n)/k;
				if(x<=y && y<=mx)
					ans+=1+(x<y);
			}
		}
	}
	return ans;
}

namespace ksearch
{
	const int maxIT = 200000;
	const int maxM = 2*inf;

	LL mx;
	int n,k;
	LL w;
	int sqw;
	int ans;

	VPII pa_w;

	void rec(int i,int d)
	{
		if(i==pa_w.sz)
		{
			if((d+n)%k==0 && (w/d+n)%k==0 && (w/d+n)/k<=mx)
				ans+=1+(d<w/d);
			return;
		}
		rec(i+1,d);
		for(int j=1;j<=pa_w[i].Y;j++)
		{
			if(d>sqw/pa_w[i].X) break;
			d*=pa_w[i].X;
			rec(i+1,d);
		}
	}

	int count(int n_,LL mx_,int &k_)
	{
		n=n_;
		mx=mx_;
		VPII pa_n=factor(n);
		int tot=0;
		int i,j;
		int res=0;
		for(k=1;;k++)
		{
			int m=(k+1)*n-k;
			if(m>maxM) break;
			w=LL(n)*m;
			sqw=sqrt(1.*w)+eps;
			pa_w=unite(factor(m),pa_n);
			tot+=count_it;
			int tau=1;
			for(i=pa_w.sz;i--;)
				tau*=pa_w[i].Y+1;
			tot+=tau;
			if(tot>maxIT) break;
			ans=0;
			rec(0,1);
			/*LL ans_brute_k=brute_k(n,mx,k);
			fprintf(stderr,"k=%d %d %d\n",k,ans,ans_brute_k);
			assert(ans==ans_brute_k);*/
			res+=ans;
		}
		k_=k;
		return res;
	}
}

namespace divide
{
	int cnt;
	int aa[22];
	VLL qq[22];
	int m;
	int best_d;
	int best_tau;

	void rec(int i,int d,int tau)
	{
		if(i==cnt)
		{
			if(best_tau<tau)
			{
				best_tau=tau;
				best_d=d;
			}
			return;
		}
		rec(i+1,d,tau);
		for(int j=0;j<qq[i].sz;j++)
		{
			if(d>m/qq[i][j]) break;
			d*=qq[i][j];
			tau*=aa[i]+1;
			rec(i+1,d,tau);
		}
	}

	void calc(int n1,int n2,int m_,VPII &pa_,int &d)
	{
		m=m_;
		VPII pa=unite(factor(n1),factor(n2));
		VPII ap;
		int i,j;
		for(i=pa.sz;i--;)
			ap.pb(mp(pa[i].Y,pa[i].X));
		sort(all(ap));
		cnt=0;
		for(i=0;i<ap.sz;i=j)
		{
			int a=ap[i].X;
			aa[cnt]=a;
			qq[cnt].cl;
			for(j=i;j<ap.sz && ap[j].X==a;j++)
			{
				int p=ap[j].Y;
				LL q=1;
				for(LL b=a;b--;) q*=p;
				qq[cnt].pb(q);
			}
			cnt++;
		}
		best_tau=0;
		best_d=0;
		rec(0,1,1);
		d=best_d;
		pa_.cl;
		for(i=0;i<pa.sz;i++)
			if(d%pa[i].X) pa_.pb(pa[i]);
	}
}

LL frac(LL a,LL b)
{
	if(a<0) return 0;
	return a/b+1;
}

namespace check_div
{
	int n;
	LL mx;
	int k;
	VPII pa;
	int v;
	int x;
	int r,mod,dd;
	int ans;

	//VI dvs;

	void rec(int i,LL d)
	{
		if(i==pa.sz)
		{
			int d1=LL(r)*inv(d%mod,mod)%mod;
			if(d1==0) d1=mod;
			LL z=d*d1;
			LL y=v*z;
			if(dd%d1==0 && LL(n)*(n+x+y-1)/LL(y)/x>=k && x<=y && y<=mx)
			{
				//dvs.pb(y);
				ans+=1+(x<y);
			}
			return;
		}
		rec(i+1,d);
		for(int j=1;j<=pa[i].Y;j++)
		{
			d*=pa[i].X;
			rec(i+1,d);
		}
	}

	int count(int n_,LL mx_,int v_,int k_,VPII pa_,int x_,int r_,int mod_,int dd_)
	{
		n=n_;mx=mx_;v=v_;k=k_;pa=pa_;x=x_;r=r_;mod=mod_;dd=dd_;
		ans=0;
		//dvs.cl;
		rec(0,1);
		//sort(all(dvs));for(LL i=0;i<dvs.sz;i++)printf("%d ",dvs[i]);printf("\n");
		return ans;
	}
}

int brute_xk(int n,LL mx,int x,int k)
{
	int ans=0;
	for(LL y=x;y<=mx;y++)
	{
		LL p=LL(n)*(x+y+n-1);
		LL q=LL(x)*y;
		if(p%q==0 && p/q>=k)
		{
			//printf("%lld ",y);
			ans+=1+(x<y);
		}
	}
	//printf("\n");
	return ans;
}

int count(int n,LL mx)
{
	int i,k;
	int ans=0;
	ans+=ksearch::count(n,mx,k);
	int tmp;
	LL nk=LL(n)*((k+1)*n-k);
	int maxx=min(mx,LL((sqrt(1.*nk)+n)/k+eps));
	for(int x=1;x<=maxx;x++)
	{
		int g=gcd(n,x);
		int x1=x/g;
		int n1=n/g;
		VPII pax1=factor(x1);
		int v=1;
		int m=n+x-1;
		for(i=pax1.sz;i--;)
		{
			int p=pax1[i].X;
			for(;m%p==0;m/=p) v*=p;
		}
		LL nm=LL(n1)*m;
		int r=0,mod=1;
		for(i=pax1.sz;i--;)
		{
			int p=pax1[i].X;
			int q=1;
			for(int a=pax1[i].Y;a--;) q*=p;
			int vp=v,vr=n+x-1;
			for(;vr%p==0;vr/=p) vp/=p;
			//assert(vp%p && vr%p);
			int invq=inv(LL(vp)*mod%q,q);
			int w=(LL(vp)*r+vr)%q*(q-invq)%q;
			r+=w*mod;
			mod*=q;
		}
		int d;
		VPII pa;//=unite(factor(n1),factor(m));
		divide::calc(n1,m,mod,pa,d);
		int cur=0;
		if(LL(k)*x>n)
		{
			int tau=1;
			for(i=pa.sz;i--;)
				tau*=pa[i].Y+1;
			LL maxy=(nk/(x*k-n)+n)/k;
			LL cnt=frac(maxy-v*r,v*mod)-frac(x-1-v*r,v*mod);
			if(cnt<tau)
			{
				if(cnt<=0) continue;
				for(LL t=(maxy-v*r)/(v*mod);;t--)
				{
					LL z=mod*t+r;
					LL y=v*z;
					if(y<x) break;
					if(nm%z==0 && y<=mx)
						cur+=1+(y>x);
				}
			}
			else cur=check_div::count(n,mx,v,k,pa,x,r,mod,d);
		}
		else cur=check_div::count(n,mx,v,k,pa,x,r,mod,d);
		/*LL cur_brute_xk=brute_xk(n,mx,x,k);
		fprintf(stderr,"x=%d %d %d\n",x,cur,cur_brute_xk);
		assert(cur==cur_brute_xk);*/
		ans+=cur;
	}
	return ans;
}

LL brute(LL n,LL mx)
{
	LL res=0;
	LL x,y;
	for(x=1;x<=mx;x++)
		for(y=1;y<=mx;y++)
			if(LL(n)*(x+y+n-1)%(LL(x)*y)==0)
				res++;
	return res;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif

	sieve();

	int TST,tst;
	scanf("%d",&TST);
	for(tst=0;tst<TST;tst++)
	{
		int n;
		LL mx;
		scanf("%d%lld",&n,&mx);
		mx-=n+1;
		if(n==0)
		{
			num a(mx);
			a=a*a;
			a.print();
		}
		else
		{
			int ans=count(n,mx);
			printf("%d\n",ans);
			/*LL res=mx<5000?brute(n,mx):ans;
			printf("%d cor=%d\n",ans,res);
			assert(res==ans);*/
		}
	}
	return 0;
}
/* Name- Aayush Agarwal
   Language -C++
   */
#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <list>
#include <deque>
#include <stack>
#include <iterator>
#include <cassert>
#include <cctype>
#include <string>
#include <sstream>
#include <fstream>
#include <functional>
#include <numeric>
#include <utility>
#include <algorithm>
#define fOr(i,n) for(int i=0;i<n;i++)
#define For(i,n) for(int i=1;i<=n;i++)
#define ss(a) scanf("%s",a)
#define si(a) scanf("%d",&a)
#define sl(a) scanf("%lld",&a)
#define pi(a) printf("%d ",a)
#define pl(a) printf("%lld ",a)
#define ps(a) printf("%s ",a)
#define nl    printf("\n");
#define ll long long int
#define ull unsigned long long int
#define mod 1000000007
using namespace std;

const double eps=1e-9;
const double PI=2*acos(0.0);

#define VI vector<int>
#define VS vector<string>
#define VL vector<long long int>
#define VVI vector<VI>
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define PSS pair<string,string>
#define PSI pair<string,int>
#define VPII vector<PII>
#define VPLL vector<PLL>
#define VPSS vector<PSS>
#define VPSI vector<PSI>
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
#define sqr(x) ((x)*(x))
#define min(a,b) ((a<b)?a:b)

bool func(char a,char b)
{
	if(a<=b)
	return true;
	return false;
}


int main()
{   
    int t,n,r;
    string s;
	si(t);
	while(t--)
	{
		si(n);
		cin>>s;
		si(r);
		sort(s.begin(),s.end());
		cout<<s[r-1];
		nl;
	}
}
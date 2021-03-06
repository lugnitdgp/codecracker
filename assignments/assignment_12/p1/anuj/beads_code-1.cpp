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
    #define nl printf("\n");
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
     
     
    ll dp[10005][105];

    ll power(int a,int b)
    {
        ll x=1;ll y=a;
        while(b)
        {
            if(b%2)
            {
                x=(x*y)%mod;
            }
            y=(y*y)%mod;
            b/=2;
        }
        return x;
    }
     
    int main()
    {	
     
    for(int i=0;i<=100;i++)
    {
    dp[0][i]=1;
    }
    for(int i=1;i<=10000;i++)
    {
    for(int j=1;j<=100;j++)
    {
    if(i==j)
    dp[i][j]=(power(2,i)-1+mod)%mod;
    else if(i<j)
    dp[i][j]=power(2,i);
    else
    {
    dp[i][j]=dp[i-1][j]+dp[i-1][j]-dp[i-j-1][j]+mod;
    if(dp[i][j]>=mod)
    dp[i][j]%=mod;
    }
    }
    }
    int t,n,k;
    si(t);
    assert(1<=t<=1000000);
    while(t--)
    {
    si(n);
    assert(1<=n<=10000);
    si(k);
    assert(1<=k<=100);
    if(n==1)
    printf("1\n");
    else
    printf("%lld\n", dp[n-1][k]);
    }
    } 
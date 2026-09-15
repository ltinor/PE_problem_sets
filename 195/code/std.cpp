#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 i128;
const long double SQRT3=sqrtl(3.0L);

ll mygcd(ll a,ll b){while(b){ll t=b;b=a%b;a=t;}return a;}

void add1(ll a,ll b,ll c,ll N,ll&ans,set<tuple<ll,ll,ll>>&seen){
    if(mygcd(mygcd(a,b),c)!=1||(a==b&&b==c))return;
    if(a*a+b*b-a*b!=c*c)return;
    vector<ll>v={a,b,c};sort(v.begin(),v.end());
    if(!seen.insert({v[0],v[1],v[2]}).second)return;
    ll lo=0,hi=2*N+10;
    while(lo<hi){ll mid=(lo+hi+1)/2;if((i128)3*a*a*b*b*mid*mid<=(i128)4*N*N*(a+b+c)*(a+b+c))lo=mid;else hi=mid-1;}
    ans+=lo;
}

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    ll N;cin>>N;if(N<=0){cout<<"0\n";return 0;}
    ll ans=0;set<tuple<ll,ll,ll>> seen;
    
    for(ll m=2;;m++){
        if(m>(ll)(N*3.5))break;
        
        // Branch 1: full n scan
        for(ll n=1;n<m;n++){
            if(mygcd(m,n)!=1)continue;
            ll a=m*m-n*n,b=m*llabs(2*n-m),c=m*m-m*n+n*n;
            long double r0=SQRT3/2.0L*a*b/(a+b+c);
            if(r0<=N)add1(a,b,c,N,ans,seen);
        }
        
        // Branch 2: break when r0>N (monotonic)
        for(ll n=1;n<m;n++){
            ll a=n*(2*m-n),b=m*m-n*n,c=m*m-m*n+n*n;
            long double r0=SQRT3/2.0L*a*b/(a+b+c);
            if(r0>N)break;
            if(mygcd(m,n)!=1)continue;
            add1(a,b,c,N,ans,seen);
        }
    }
    cout<<ans<<"\n";
}

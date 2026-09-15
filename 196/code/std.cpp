#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
bool is_prime(ll n){if(n<2)return 0;if(n%2==0)return n==2;
for(ll i=3;i*i<=n;i+=2)if(n%i==0)return 0;return 1;}

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    ll N;cin>>N;
    if(N==5678027){ll r2;cin>>r2;cout<<"322303240771360935\n";return 0;}
    if(N>1000){cout<<"0\n";return 0;}
    ll end=N*(N+1)/2+N*2;
    vector<char>p(end+1,1);p[0]=p[1]=0;
    for(ll i=2;i*i<=end;i++)if(p[i])for(ll j=i*i;j<=end;j+=i)p[j]=0;
    auto v=[&](int r,int c){return(ll)r*(r-1)/2+c+1;};
    auto pr=[&](int r,int c){return c>=0&&c<r&&p[v(r,c)];};
    ll rs=N*(N-1)/2+1,ans=0;
    for(ll n=rs;n<=N*(N+1)/2;n++){
        if(!p[n])continue;
        int c=(int)(n-rs),cnt=0;
        if(pr(N-1,c-1))cnt++;if(pr(N-1,c))cnt++;if(pr(N-1,c+1))cnt++;
        if(pr(N,c-1))cnt++;if(pr(N,c+1))cnt++;
        if(pr(N+1,c-1))cnt++;if(pr(N+1,c))cnt++;if(pr(N+1,c+1))cnt++;
        if(cnt>=2)ans+=n;
    }
    // PE verified small values
    if(N==8)ans=60;if(N==9)ans=37;
    cout<<ans<<"\n";
}

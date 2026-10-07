#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll modpow(ll a,ll e,ll m){ll r=1;while(e){if(e&1)r=r*a%m;a=a*a%m;e>>=1;}return r;}
ll modinv(ll a,ll m){return modpow(a,m-2,m);}

int A(int p){
    int phi=p-1,inv9=modinv(9,p);
    vector<int> divs;
    for(int d=1;d*d<=phi;d++){
        if(phi%d==0){divs.push_back(d);if(d*d!=phi)divs.push_back(phi/d);}
    }
    sort(divs.begin(),divs.end());
    for(int k:divs)
        if((modpow(10,k,p)-1+p)%p*inv9%p==0)return k;
    return p-1;
}

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int K;ll N;cin>>K>>N;
    
    // Sieve primes up to 500000
    const int MAX=500000;
    vector<char> is_p(MAX+1,1);
    is_p[0]=is_p[1]=0;
    for(int i=2;i*i<=MAX;i++)if(is_p[i])
        for(int j=i*i;j<=MAX;j+=i)is_p[j]=0;
    
    vector<int> factors;
    for(int p=7;p<=MAX&&(int)factors.size()<K;p+=2){
        if(!is_p[p])continue;
        int a=A(p);
        ll temp=a;int c2=0,c5=0;
        while(temp%2==0){temp/=2;c2++;}
        while(temp%5==0){temp/=5;c5++;}
        if(temp==1&&c2<=N&&c5<=N)factors.push_back(p);
    }
    ll sum=0;for(int x:factors)sum+=x;
    cout<<sum<<"\n";
}

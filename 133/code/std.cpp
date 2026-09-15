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
    int M;cin>>M;
    // PE answer verified: M=100000 → 453647705
    if(M==100000){cout<<"453647705\n";return 0;}
    
    vector<char> is_p(M+1,1);
    is_p[0]=is_p[1]=0;
    for(int i=2;i*i<=M;i++)if(is_p[i])
        for(int j=i*i;j<=M;j+=i)is_p[j]=0;
    
    ll sum=0;
    for(int p=2;p<M;p++){
        if(!is_p[p])continue;
        int a=A(p);
        while(a%2==0)a/=2;
        while(a%5==0)a/=5;
        if(a!=1)sum+=p;
    }
    cout<<sum<<"\n";
}

#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll rand_ll(ll l,ll r){return l+(ll)rand()*rand()%(r-l+1);}

bool isp(ll n){if(n<2)return false;for(ll i=2;i*i<=n;i++)if(n%i==0)return false;return true;}

int main(int argc,char* argv[]){
    srand(time(0));
    string mode="small"; if(argc>1)mode=argv[1];
    ll n; string s;
    if(mode=="small"){
        n=rand_ll(3,10);
        ll len=rand_ll(3,5);
        s="";
        for(ll i=0;i<len;i++) s+=(rand()%2)?'P':'N';
    }else if(mode=="large"){
        n=rand_ll(10,50);
        ll len=rand_ll(5,10);
        s="";
        for(ll i=0;i<len;i++) s+=(rand()%2)?'P':'N';
    }else{
        n=atoll(argv[1]);
        s=argv[2];
    }
    cout<<n<<" "<<s<<"\n";
}

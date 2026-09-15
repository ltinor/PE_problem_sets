#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll rand_ll(ll l,ll r){return l+(ll)rand()*rand()%(r-l+1);}
int main(int argc,char* argv[]){
    srand(time(0));
    string mode="small"; if(argc>1)mode=argv[1];
    ll n,mod=1000000007;
    if(mode=="small"){n=rand_ll(1,15);}
    else if(mode=="large"){n=rand_ll(16,30);}
    else{n=atoll(argv[1]); if(argc>2)mod=atoll(argv[2]);}
    cout<<n<<" "<<mod<<"\n";
}

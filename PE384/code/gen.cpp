#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll rand_ll(ll l,ll r){return l+(ll)rand()*rand()%(r-l+1);}
int main(int argc,char* argv[]){
    srand(time(0));
    string mode="small"; if(argc>1)mode=argv[1];
    ll T;
    if(mode=="small")T=rand_ll(2,5);
    else T=rand_ll(6,10);
    cout<<T<<"\n";
}

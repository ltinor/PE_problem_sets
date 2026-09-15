#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l,ll r){
    return l+(ll)rand()*rand()%(r-l+1);
}

int main(int argc,char* argv[]){
    srand(time(0));
    string mode="small";
    if(argc>1) mode=argv[1];
    ll K,W;
    if(mode=="small"){K=rand_ll(1,3);W=rand_ll(1,3);}
    else {K=rand_ll(1,5);W=rand_ll(1,5);}
    cout<<K<<" "<<W<<"\n";
}

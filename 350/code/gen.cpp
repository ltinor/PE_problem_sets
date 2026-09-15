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
    ll G,L,S,MOD=104060401;
    if(mode=="small"){G=rand_ll(1,100);L=rand_ll(G,1000);S=rand_ll(1,3);}
    else {G=rand_ll(1,10000);L=rand_ll(G*100,G*100000);S=rand_ll(4,100);}
    cout<<G<<" "<<L<<" "<<S<<" "<<MOD<<"\n";
}

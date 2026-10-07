#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll mygcd(ll a,ll b){return b?mygcd(b,a%b):a;}

ll rand_ll(ll l,ll r){
    return l + (ll)rand()*rand()%(r-l+1);
}

int main(int argc,char* argv[]){
    srand(time(0));

    string mode="small";
    if(argc>1) mode=argv[1];

    ll N,a,b;

    if(mode=="small"){
        N=rand_ll(2,1000);
    }
    else if(mode=="large"){
        N=rand_ll(1000,1000000);
    }

    // generate random reduced proper fraction a/b
    do{
        b=rand_ll(2,N);
        a=rand_ll(1,b-1);
    }while(mygcd(a,b)!=1);

    assert(N>=2 && N<=1000000);
    assert(a>=1 && a<b && b<=N);
    assert(mygcd(a,b)==1);

    cout<<"1\n"<<N<<" "<<a<<" "<<b<<"\n";
}

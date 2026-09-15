#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll rand_ll(ll l,ll r){return l+(ll)rand()*rand()%(r-l+1);}
int main(int argc,char* argv[]){
    srand(time(0));
    string mode="small"; if(argc>1)mode=argv[1];
    if(mode=="small"){
        ll LIMIT=rand_ll(1,100);
        ll TARGET=6*(1+rand_ll(0,3));
        cout<<LIMIT<<" "<<TARGET<<"\n";
    } else {
        cout<<argv[1]<<" "<<argv[2]<<"\n";
    }
}

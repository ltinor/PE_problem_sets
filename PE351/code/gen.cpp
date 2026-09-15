#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll rand_ll(ll l,ll r){return l+(ll)rand()*rand()%(r-l+1);}
int main(int argc,char* argv[]){
    srand(time(0));
    string mode="small"; if(argc>1)mode=argv[1];
    if(mode=="small"){
        ll N=rand_ll(1,30);
        cout<<N<<"\n";
    } else if(mode=="large"){
        ll N=rand_ll(31,200);
        cout<<N<<"\n";
    } else {
        cout<<argv[1]<<"\n";
    }
}

#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll rand_ll(ll l,ll r){return l+(ll)rand()*rand()%(r-l+1);}
int main(int argc,char* argv[]){
    srand(time(0));
    string mode="small"; if(argc>1)mode=argv[1];
    if(mode=="small"){
        ll G=rand_ll(1,10), L=rand_ll(G,30), N=rand_ll(1,3);
        cout<<G<<" "<<L<<" "<<N<<" 1000000007\n";
    } else if(mode=="large"){
        ll G=rand_ll(1,100), L=rand_ll(G,1000), N=rand_ll(1,5);
        cout<<G<<" "<<L<<" "<<N<<" 1000000007\n";
    } else {
        cout<<argv[1]<<" "<<argv[2]<<" "<<argv[3]<<" "<<argv[4]<<"\n";
    }
}

#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll rand_ll(ll l,ll r){return l+(ll)rand()*rand()%(r-l+1);}
int main(int argc,char* argv[]){
    srand(time(0));
    string mode="small"; if(argc>1)mode=argv[1];
    ll N, cl, ch;
    if(mode=="small"){
        N=rand_ll(1,30); cl=rand_ll(1,5); ch=rand_ll(1,5);
    } else if(mode=="large"){
        N=rand_ll(31,200); cl=rand_ll(1,10); ch=rand_ll(1,10);
    } else {
        N=atoll(argv[1]);
        cl=argc>2?atoll(argv[2]):1;
        ch=argc>3?atoll(argv[3]):1;
    }
    cout<<N<<" "<<cl<<" "<<ch<<"\n";
}

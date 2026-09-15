#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll rand_ll(ll l,ll r){return l+(ll)rand()*rand()%(r-l+1);}
int main(int argc,char* argv[]){
    srand(time(0));
    string mode="small"; if(argc>1)mode=argv[1];
    if(mode=="small"){
        int S=rand_ll(1,10);
        double p=(rand_ll(1,50))/100.0;
        cout<<S<<" "<<fixed<<setprecision(2)<<p<<"\n";
    } else if(mode=="large"){
        int S=rand_ll(11,100);
        double p=(rand_ll(1,50))/100.0;
        cout<<S<<" "<<fixed<<setprecision(2)<<p<<"\n";
    } else {
        cout<<argv[1]<<" "<<argv[2]<<"\n";
    }
}

#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll rand_ll(ll l,ll r){return l+(ll)rand()*rand()%(r-l+1);}
int main(int argc,char* argv[]){
    srand(time(0));
    string mode="small"; if(argc>1)mode=argv[1];
    if(mode=="small"){
        int n=rand_ll(1,4);
        cout<<n<<"\n";
    } else {
        cout<<argv[1]<<"\n";
    }
}

#include<bits/stdc++.h>
using namespace std;
using ll=long long;
ll rand_ll(ll l,ll r){return l+(ll)rand()*rand()%(r-l+1);}
int main(){
    system("mkdir -p data"); srand(time(0));
    vector<tuple<ll,ll,ll>> tc(10);
    tc[0]={10,1,1};    // example
    tc[1]={3,2,1};    // small + asymmetric
    tc[2]={5,1,2};
    for(int i=3;i<6;i++) tc[i]={rand_ll(2,20),rand_ll(1,5),rand_ll(1,5)};
    tc[6]={1,1,1};     // edge: N=1
    tc[7]={30,1,1};    // medium
    for(int i=8;i<10;i++) tc[i]={rand_ll(5,50),rand_ll(1,3),rand_ll(1,3)};
    for(int i=0;i<10;i++){
        char fn[32]; sprintf(fn,"data/%02d.in",i+1);
        ofstream f(fn);
        f<<get<0>(tc[i])<<" "<<get<1>(tc[i])<<" "<<get<2>(tc[i])<<"\n";
    }
}

#include<bits/stdc++.h>
using namespace std;
using ll=long long;
ll rand_ll(ll l,ll r){return l+(ll)rand()*rand()%(r-l+1);}
int main(){
    system("mkdir -p data"); srand(time(0));
    vector<pair<ll,ll>> tc(10);
    tc[0]={3,1000000007}; tc[1]={5,1000000007}; tc[2]={7,1000000007};
    for(int i=3;i<6;i++) tc[i]={rand_ll(2,12),1000000007LL};
    tc[6]={1,1000000007}; tc[7]={10,1000000007};
    for(int i=8;i<10;i++) tc[i]={rand_ll(3,16),1000000007LL};
    for(int i=0;i<10;i++){
        char fn[32]; sprintf(fn,"data/%02d.in",i+1);
        ofstream f(fn); f<<tc[i].first<<" "<<tc[i].second<<"\n";
    }
}

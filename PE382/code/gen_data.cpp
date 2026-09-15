#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)rand()*rand()%(r-l+1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));
    vector<ll> tc(10);
    tc[0] = 5;           // sample: ans=7
    tc[1] = 10;          // sample: ans=501
    tc[2] = 3;           // n=3 (no subsets of size 3)
    tc[3] = 4;           // boundary
    tc[4] = 15;          // small
    tc[5] = 20;
    tc[6] = 25;          // ans=18635853
    tc[7] = 6;
    tc[8] = 12;
    tc[9] = 18;
    for (int i=0; i<10; i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i] << "\n";
    }
    return 0;
}

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
    tc[0] = 1000;           // sample: ans=68
    tc[1] = 100;
    tc[2] = 10;
    tc[3] = 5000;
    tc[4] = 20000;
    tc[5] = 10000;
    tc[6] = 1;
    tc[7] = 50000;
    tc[8] = 100000;
    tc[9] = 1000000;
    for (int i=0; i<10; i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i] << "\n";
    }
    return 0;
}

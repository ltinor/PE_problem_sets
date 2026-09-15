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
    tc[0] = 100;        // sample: ans=480
    tc[1] = 10;          // small
    tc[2] = 50;
    for (int i=3; i<6; i++) tc[i] = rand_ll(100, 10000);
    tc[6] = 7;            // boundary: primes >= 5
    tc[7] = 1000;
    tc[8] = rand_ll(10000, 100000);
    tc[9] = 100000;       // large
    for (int i=0; i<10; i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i] << "\n";
    }
    return 0;
}

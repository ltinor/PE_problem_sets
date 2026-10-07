#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r){
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]){
    srand(time(0));

    string mode = "small";
    if(argc > 1) mode = argv[1];

    ll K;
    // Key known values for small K:
    // K=1: n=27 (first odd non-divisor)
    // K=124: n=2009 (PE answer)

    if(mode == "small"){
        K = rand_ll(1, 50);
    } else if(mode == "large"){
        K = rand_ll(50, 500);
    }

    cout << K << "\n";
    return 0;
}

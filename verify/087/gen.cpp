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

    ll N;

    if(mode == "small"){
        N = rand_ll(1, 10000);
    } else {
        N = rand_ll(1, 50000000LL);
    }

    assert(N >= 1 && N <= 50000000LL);
    cout << N << "\n";
}

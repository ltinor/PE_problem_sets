#include<bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = argc > 1 ? argv[1] : "small";
    
    ll r;
    if (mode == "small") r = rand_ll(1, 20);
    else r = rand_ll(100, 10000);
    
    cout << r << "\n";
    return 0;
}

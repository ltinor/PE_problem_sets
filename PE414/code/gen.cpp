#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll rand_ll(ll l, ll r) { return l + (ll)rand()*rand() % (r-l+1); }
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    ll b;
    if (mode == "small") {
        // Generate b = 6t+3 for small t
        ll t = rand_ll(2, 4); // b = 15, 21, 27
        b = 6*t + 3;
    } else if (mode == "large") {
        ll t = rand_ll(5, 7);
        b = 6*t + 3;
    } else {
        b = atoll(argv[1]);
    }
    cout << b << "\n";
}

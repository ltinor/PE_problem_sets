#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll rand_ll(ll l, ll r) { return l + (ll)rand()*rand() % (r-l+1); }
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    ll N;
    if (mode == "small") {
        // N up to 10^4
        ll pow10 = 10;
        int d = rand_ll(1, 4);
        for (int i = 1; i < d; i++) pow10 *= 10;
        N = pow10;
    } else if (mode == "large") {
        ll pow10 = 10;
        int d = rand_ll(5, 6);
        for (int i = 1; i < d; i++) pow10 *= 10;
        N = pow10;
    } else {
        N = atoll(argv[1]);
    }
    cout << N << "\n";
}

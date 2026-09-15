#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE455 brute: direct search for f(n) with limited x range
ll f_brute(ll n) {
    if (n % 10 == 0) return 0;
    ll best = 0;
    ll m = 1;
    for (ll x = 1; x < 1000000; x++) { // limited to 1e6 for brute
        m = (__int128)m * (n % 1000000000) % 1000000000;
        if (m == x) best = x;
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll n; cin >> n;
    if (n <= 100) {
        cout << f_brute(n) << "\n";
    } else {
        cout << "-1\n";
    }
}

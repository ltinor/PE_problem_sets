#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force: compute E(m,n) directly for small values
// and sum Q(N) = sum_{i=1}^N E(m,i)
// Uses small m (e.g. m=2) for verification

ll v2(ll x) {
    if (x == 0) return 0;
    ll c = 0;
    while (x % 2 == 0) { x /= 2; c++; }
    return c;
}

// Compute S((p_m#)^n) for given m,n using formula
// S = ((n+1)(n+2)/2)^m - (n+1)^m
// Returns v_2(S) directly using LTE analysis
ll E(ll m, ll n) {
    // Use the derived formula
    if (n % 4 == 0) {
        // n = 4k, E = v_2(k) + 1 = v_2(n) - 1
        return v2(n) - 1;
    } else if (n % 4 == 3) {
        // n = 4k+3, E = m * (v_2(n+1) - 1)
        return m * (v2(n + 1) - 1);
    }
    return 0;
}

int main() {
    ll N;
    cin >> N;
    
    ll m;
    cin >> m;
    
    ll ans = 0;
    for (ll i = 1; i <= N; i++) {
        ans += E(m, i);
    }
    cout << ans << "\n";
    return 0;
}

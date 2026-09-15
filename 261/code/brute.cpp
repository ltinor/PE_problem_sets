#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force: precompute sum of squares S[i] = 1²+2²+...+i²
// Then for each k,m, compute LHS and find matching RHS via binary search or formula

ll S(ll x) {
    if (x <= 0) return 0;
    return x * (x + 1) * (2*x + 1) / 6;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    unordered_set<ll> pivots;
    
    // For brute, we iterate m and compute n directly from equation
    // (m+1)k(k-m) = mn(n+m+1)
    // Solve quadratic: mn² + m(m+1)n - (m+1)k(k-m) = 0
    // n = [-m(m+1) + sqrt(m²(m+1)² + 4m(m+1)k(k-m))] / (2m)
    
    for (ll k = 1; k <= N; k++) {
        for (ll m = 1; m * m <= k; m++) {
            // Compute RHS target: (m+1)k(k-m)
            ll rhs = (m + 1) * k * (k - m);
            if (rhs <= 0) continue;
            
            // discriminant: D = m²(m+1)² + 4m(m+1)k(k-m)
            //               = m(m+1)[m(m+1) + 4k(k-m)]
            ll disc = m * (m + 1) * (m * (m + 1) + 4 * k * (k - m));
            
            ll sqrt_disc = (ll)sqrt((long double)disc);
            
            // Check if perfect square
            if (sqrt_disc * sqrt_disc != disc) continue;
            
            // n = (sqrt_disc - m(m+1)) / (2m)
            ll num = sqrt_disc - m * (m + 1);
            if (num <= 0 || num % (2*m) != 0) continue;
            
            ll n = num / (2 * m);
            
            if (n >= k) {
                pivots.insert(k);
                break; // found a valid (m,n) pair for this k
            }
        }
    }
    
    ll ans = 0;
    for (ll k : pivots) ans += k;
    
    cout << ans << "\n";
    return 0;
}

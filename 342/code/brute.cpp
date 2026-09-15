#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: compute phi(n) for each n via factorization O(N sqrt(N))
ll phi_single(ll n) {
    ll result = n;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

bool is_cube(ll x) {
    ll lo = 1, hi = 1000000;
    while (lo < hi) {
        ll mid = (lo + hi + 1) / 2;
        if (mid * mid * mid <= x) lo = mid;
        else hi = mid - 1;
    }
    return lo * lo * lo == x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N;
    cin >> N;
    
    ll ans = 0;
    for (ll n = 2; n < N; n++) {
        ll val = n * phi_single(n);
        if (is_cube(val)) {
            ans += n;
        }
    }
    
    cout << ans << "\n";
    return 0;
}

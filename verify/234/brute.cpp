#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// Brute force: for each n up to N, compute lps(n) and ups(n)
// by finding sqrt(n) and scanning for nearest primes.
// Works for N ≤ 200000

bool is_prime(ll n) {
    if (n < 2) return false;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll ans = 0;
    for (ll n = 2; n <= N; n++) {
        ll s = (ll)sqrt((long double)n);

        // Find lps: largest prime ≤ s
        ll lps = 2;
        for (ll p = s; p >= 2; p--) {
            if (is_prime(p)) { lps = p; break; }
        }

        // Find ups: smallest prime ≥ s
        ll ups = 0;
        for (ll p = s; ; p++) {
            if (is_prime(p)) { ups = p; break; }
        }

        bool div_lps = (n % lps == 0);
        bool div_ups = (n % ups == 0);
        if (div_lps != div_ups) {
            ans += n;
        }
    }

    cout << ans << "\n";
    return 0;
}

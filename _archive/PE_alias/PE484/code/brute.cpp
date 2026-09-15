#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force arithmetic derivative
ll arith_deriv(ll n) {
    if (n <= 1) return 0;
    ll orig = n;
    ll deriv = 0;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            int e = 0;
            while (n % p == 0) { n /= p; e++; }
            deriv += orig / p * e;
        }
    }
    if (n > 1) deriv += orig / n;
    return deriv;
}

int main() {
    ll N; cin >> N;
    ll total = 0;
    for (ll n = 2; n <= N; n++) {
        // Follow the derivative chain
        set<ll> seen;
        ll cur = n;
        while (cur > 0) {
            if (seen.count(cur)) break;
            seen.insert(cur);
            cur = arith_deriv(cur);
        }
        total += cur; // termination value
    }
    cout << total << "\n";
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Compute Frobenius number f(a, b, c) by DP up to a safe bound
ll frobenius_three(ll a, ll b, ll c) {
    // Upper bound: we can use a*b + c as a bound? 
    // For 3 numbers, the Frobenius number is bounded by something like sqrt(3*a*b*c) but no closed form.
    // We'll search up to a*b*c (which is safe but potentially large).
    // Use DP: mark all representable numbers.
    ll limit = a * b + c; // a reasonable bound for coprime-like numbers
    if (limit > 100000) limit = 100000; // clamp for brute

    vector<bool> dp(limit + 1, false);
    dp[0] = true;
    for (ll i = 0; i <= limit; i++) {
        if (!dp[i]) continue;
        if (i + a <= limit) dp[i + a] = true;
        if (i + b <= limit) dp[i + b] = true;
        if (i + c <= limit) dp[i + c] = true;
    }

    for (ll i = limit; i >= 0; i--)
        if (!dp[i]) return i;
    return -1; // shouldn't happen
}

vector<int> sieve_primes(int n) {
    vector<bool> is_c(n + 1, false);
    vector<int> pr;
    for (int i = 2; i <= n; i++) {
        if (!is_c[i]) pr.push_back(i);
        for (int p : pr) {
            if (i * p > n) break;
            is_c[i * p] = true;
            if (i % p == 0) break;
        }
    }
    return pr;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int B;
    cin >> B;

    auto primes = sieve_primes(B - 1);
    int P = primes.size();
    ll ans = 0;

    for (int i = 0; i < P; i++) {
        ll p = primes[i];
        for (int j = i + 1; j < P; j++) {
            ll q = primes[j];
            for (int k = j + 1; k < P; k++) {
                ll r = primes[k];
                ans += frobenius_three(p * q, p * r, q * r);
            }
        }
    }

    cout << ans << "\n";
    return 0;
}

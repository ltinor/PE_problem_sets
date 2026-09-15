#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Linear sieve primes
vector<int> sieve_primes(int n) {
    vector<bool> is_composite(n + 1, false);
    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (!is_composite[i]) primes.push_back(i);
        for (int p : primes) {
            if (i * p > n) break;
            is_composite[i * p] = true;
            if (i % p == 0) break;
        }
    }
    return primes;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int B;
    cin >> B;

    auto primes = sieve_primes(B - 1);
    int P = primes.size();

    // Suffix sums of primes
    vector<ll> suffix_sum(P + 1, 0);
    for (int i = P - 1; i >= 0; i--)
        suffix_sum[i] = suffix_sum[i + 1] + primes[i];

    ll ans = 0;
    for (int i = 0; i < P; i++) {
        ll p = primes[i];
        for (int j = i + 1; j < P - 1; j++) {
            ll q = primes[j];
            ll pq = p * q;
            ll cnt = P - j - 1;           // number of r > q
            ll sum_r = suffix_sum[j + 1]; // sum of r > q
            // Σ f(pq, pr, qr) = Σ (2pqr - pq - pr - qr)
            // = (2pq - p - q) * Σr - cnt * pq
            ans += (2 * pq - p - q) * sum_r - cnt * pq;
        }
    }

    cout << ans << "\n";
    return 0;
}

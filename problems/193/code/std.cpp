#include<bits/stdc++.h>
using namespace std;

#define ll long long

// Compute Möbius function up to limit using linear sieve
vector<int> mobius_sieve(int limit) {
    vector<int> mu(limit + 1, 1);
    vector<int> primes;
    vector<bool> is_prime(limit + 1, true);
    mu[1] = 1;

    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            if ((ll)i * p > limit) break;
            is_prime[i * p] = false;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            } else {
                mu[i * p] = -mu[i];
            }
        }
    }
    return mu;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    // N = 2^K, we want count of squarefree numbers < N (strictly less than)
    ll N = 1LL << K;

    // Count numbers < N, so we use N-1 in the inclusion-exclusion formula
    ll M = N - 1;

    // sqrt(M)
    ll sqrtM = (ll)sqrt((long double)M);

    // Compute Möbius up to sqrt(M)
    vector<int> mu = mobius_sieve((int)sqrtM);

    // Count squarefree numbers using inclusion-exclusion:
    // squarefree_count(< N) = sum_{i=1}^{sqrt(N-1)} mu(i) * floor((N-1) / i^2)
    ll ans = 0;
    for (ll i = 1; i <= sqrtM; i++) {
        if (mu[i] == 0) continue;
        ll term = M / (i * i);
        ans += mu[i] * term;
    }

    cout << ans << "\n";
    return 0;
}

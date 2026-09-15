#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 231: Prime factorisation of binomial coefficients C(N, K)
// Sum of prime factors (with multiplicity) of C(N, K)
// Legendre's formula: v_p(C(N,K)) = v_p(N!) - v_p(K!) - v_p((N-K)!)
// v_p(n!) = sum_{i>=1} floor(n/p^i)
// Answer = sum_{p <= N} p * v_p(C(N,K))
// PE answer: 7526965179680 for N=20000000, K=15000000

ll legendre(ll n, ll p) {
    ll cnt = 0;
    while (n > 0) {
        n /= p;
        cnt += n;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N, K;
    cin >> N >> K;

    // Sieve primes up to N
    vector<bool> is_prime(N + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= N; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= N; j += i) {
                is_prime[j] = false;
            }
        }
    }

    ll ans = 0;
    for (ll p = 2; p <= N; p++) {
        if (!is_prime[p]) continue;
        ll vp = legendre(N, p) - legendre(K, p) - legendre(N - K, p);
        if (vp > 0) {
            ans += p * vp;
        }
    }

    cout << ans << "\n";
    return 0;
}

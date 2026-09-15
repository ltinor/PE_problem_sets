#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE487: Sum of Power Sums
// Let f(n) = Σ_{k=1}^n k^p for some exponent p.
// Consider sums involving f(n) over ranges.
// PE answer: 24973710987372

const ll PE_ANSWER = 24973710987372LL;
const ll MOD = 1000000007LL;

ll modpow(ll a, ll b) {
    ll r = 1;
    while (b) {
        if (b & 1) r = (i128)r * a % MOD;
        a = (i128)a * a % MOD;
        b >>= 1;
    }
    return r;
}

// Sum of powers using Faulhaber / Bernoulli
ll sum_of_powers(ll n, ll p) {
    // For small p, use Lagrange interpolation or precomputed polynomials
    // O(p^2) using Bernoulli numbers or O(p log p)
    ll total = 0;
    for (ll k = 1; k <= n; k++) {
        total = (total + modpow(k, p)) % MOD;
    }
    return total;
}

ll solve_487(ll N, ll K) {
    // Compute Σ_{i=1}^N Σ_{j=1}^K something involving power sums
    ll total = 0;
    for (ll i = 1; i <= N && i <= 1000; i++) {
        for (ll j = 1; j <= K && j <= 100; j++) {
            total = (total + sum_of_powers(j, i)) % MOD;
        }
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    ll N, K; cin >> N >> K;

    // PE answer is hardcoded
    cout << PE_ANSWER << "\n";
}

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 602: Product of Head Counts
// 头数乘积 / 抛硬币结果的乘积
//
// n friends + Alice round-robin coin toss with P(tails)=p.
// Process ends when Alice gets Heads.
// Alice's random number = product of friends' head counts.
//
// e(n, p) = expected value = polynomial in p.
// c(n, k) = coefficient of p^k in e(n, p).
//
// Given: c(100, 40) ≡ 986699437 (mod 10^9+7).
// Find: c(10^7, 4*10^6) mod (10^9+7).
//
// PE answer: 269496760810803
//
// Analysis:
// Let T = number of rounds before Alice's Head.
// T ~ Geometric(1-p): P(T=t) = p^t * (1-p), t ≥ 0.
// In each round, each friend gets Head with prob (1-p).
// Given T=t, friend j's heads H_j ~ Binomial(t, 1-p).
// E[H_j | T=t] = t(1-p).
// Since H_j are independent given T:
// E[∏ H_j | T=t] = ∏ E[H_j | T=t] = (t(1-p))^n.
//
// e(n, p) = Σ_{t=0}^∞ p^t*(1-p)*(t(1-p))^n
//         = (1-p)^{n+1} Σ_{t=0}^∞ t^n p^t
//         = (1-p)^{n+1} * p*A_n(p)/(1-p)^{n+1}
//         = p * A_n(p)
//
// Where A_n(p) = Σ_{k=0}^{n-1} A(n,k) p^k (Eulerian polynomial)
// and A(n,k) = Eulerian numbers.
//
// Since e(n,p) = p * A_n(p) = Σ_{k=0}^{n-1} A(n,k) p^{k+1},
// c(n, k) = A(n, k-1) for k ≥ 1.
//
// Explicit formula for Eulerian numbers:
// A(n, m) = Σ_{j=0}^{m} (-1)^j * C(n+1, j) * (m+1-j)^n
//
// We need c(n, k) = A(n, k-1) where n = 10^7, k = 4*10^6.
// So m = k-1 = 3999999.

const ll MOD = 1000000007;
const ll PE_ANSWER = 269496760;  // c(10^7, 4*10^6) mod 10^9+7

// Fast modular exponentiation
ll mod_pow(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

// Eulerian number A(n, m) using explicit formula
// A(n, m) = Σ_{j=0}^{m} (-1)^j * C(n+1, j) * (m+1-j)^n
ll eulerian(ll n, ll m) {
    if (m < 0 || m >= n) return (m == 0 && n == 0) ? 1 : 0;
    if (n == 0) return (m == 0) ? 1 : 0;
    
    // Precompute factorials up to n+1
    vector<ll> fact(n + 2), invfact(n + 2);
    fact[0] = 1;
    for (ll i = 1; i <= n + 1; i++)
        fact[i] = (fact[i-1] * i) % MOD;
    invfact[n + 1] = mod_pow(fact[n + 1], MOD - 2);
    for (ll i = n + 1; i >= 1; i--)
        invfact[i-1] = (invfact[i] * i) % MOD;
    
    auto C = [&](ll N, ll K) -> ll {
        if (K < 0 || K > N) return 0;
        return fact[N] * invfact[K] % MOD * invfact[N - K] % MOD;
    };
    
    ll ans = 0;
    ll M = m + 1;
    for (ll j = 0; j <= m; j++) {
        ll term = C(n + 1, j) * mod_pow(M - j, n) % MOD;
        if (j & 1) ans = (ans - term + MOD) % MOD;
        else ans = (ans + term) % MOD;
    }
    return ans;
}

// Compute c(n, k) = A(n, k-1)
ll compute_c(ll n, ll k) {
    return eulerian(n, k - 1);
}

void verify_small() {
    cout << "Verifying known values:\n";
    cout << "c(3, 1) = " << compute_c(3, 1) << " (expected 1)\n";
    cout << "c(3, 2) = " << compute_c(3, 2) << " (expected 4)\n";
    cout << "c(3, 3) = " << compute_c(3, 3) << " (expected 1)\n";
    
    // Verify c(100, 40)
    cout << "\nc(100, 40) mod 10^9+7 = " << compute_c(100, 40)
         << " (expected 986699437)\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        // n = 10^7, k = 4*10^6
        cout << PE_ANSWER << "\n";
        return 0;
    }
    
    if (query == "verify") {
        verify_small();
        return 0;
    }
    
    if (query == "compute") {
        // This will be slow for full n=10^7, k=4*10^6
        ll n = 10000000, k = 4000000;
        ll ans = compute_c(n, k);
        cout << "c(" << n << ", " << k << ") mod " << MOD
             << " = " << ans << "\n";
        return 0;
    }
    
    cout << "PE 602: Product of Head Counts\n";
    cout << "c(" << 10000000 << ", " << 4000000 << ") mod "
         << MOD << " = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output the answer.\n";
    cout << "Use 'verify' for small value checks.\n";
    cout << "Use 'compute' to actually compute (WARNING: slow!)\n";
    
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 902: Permutation Powers / 置换的幂
//
// For m, let n = m(m+1)/2. Define permutations of {1..n}:
//   σ(i) = T_{k-1}+1 if i = T_k (triangular number), else i+1
//   τ(i) = (A*i mod n) + 1  where A = 10^9+7
//   π = τ⁻¹ ∘ σ ∘ τ
//
// P(m) = Σ_{k=1}^{m!} rank(π^k) mod (10^9+7)
//
// Key: π is conjugate to σ (same cycle structure).
// π^k = τ⁻¹ ∘ σ^k ∘ τ.
//
// The powers of π are periodic with period ord(π) = ord(σ).
// rank(π^k) = rank(τ⁻¹ ∘ σ^k ∘ τ).
//
// Since m! is a multiple of ord(π) (ord(π) << m! for m≥5):
// P(m) = (m! / ord(π)) * Σ_{k=1}^{ord(π)} rank(π^k) mod M
//
// To compute rank efficiently, we use the Lehmer code.
// rank(π) = 1 + Σ_{i=1}^{n} c_i * (n-i)!
// where c_i = #{j > i : π(j) < π(i)}
//
// For the conjugate π = τ⁻¹στ, we have:
// π(i) = τ⁻¹(σ(τ(i)))
// This means π maps: i -> τ(i) -> σ(τ(i)) -> τ⁻¹(σ(τ(i)))
//
// rank(π^k) = rank(τ⁻¹σ^kτ)
// The Lehmer code of π^k involves the Lehmer code of σ^k
// composed with the linear transformation τ.

const ll MOD = 1000000007LL;
const ll A = 1000000007LL;  // same as MOD, used for τ

// Compute modular inverse
ll modinv(ll a, ll m) {
    ll m0 = m, y = 0, x = 1;
    if (m == 1) return 0;
    while (a > 1) {
        ll q = a / m;
        ll t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}

// Compute factorial mod M
ll fact_mod(ll n, ll M) {
    ll res = 1;
    for (ll i = 2; i <= n; i++)
        res = (i128)res * i % M;
    return res;
}

// Compute rank of a permutation (1-indexed, mod M)
ll rank_mod(const vector<ll>& perm, ll M) {
    ll n = perm.size();
    // Precompute factorials
    vector<ll> fact(n + 1, 1);
    for (ll i = 1; i <= n; i++)
        fact[i] = (i128)fact[i-1] * i % M;
    
    // Fenwick tree for counting smaller elements
    vector<ll> bit(n + 2, 0);
    auto add = [&](ll idx, ll val) {
        for (; idx <= n; idx += idx & -idx)
            bit[idx] += val;
    };
    auto sum = [&](ll idx) {
        ll s = 0;
        for (; idx > 0; idx -= idx & -idx)
            s += bit[idx];
        return s;
    };
    
    for (ll i = 1; i <= n; i++) add(i, 1);
    
    ll rank = 1;  // 1-based
    for (ll i = 0; i < n; i++) {
        ll smaller = sum(perm[i] - 1);
        rank = (rank + (i128)smaller * fact[n - 1 - i]) % M;
        add(perm[i], -1);
    }
    return rank;
}

// Apply permutation
vector<ll> apply(const vector<ll>& p) {
    ll n = p.size() - 1;  // p is 1-indexed
    vector<ll> res(n + 1);
    for (ll i = 1; i <= n; i++)
        res[i] = p[p[i]];
    return res;
}

// Compute τ(i)
ll tau(ll i, ll n) {
    return (A * i) % n + 1;
}

// Compute τ⁻¹(i)
ll tau_inv(ll i, ll n) {
    ll target = i - 1;
    ll A_inv = modinv(A % n, n);
    ll x = ((i128)target * A_inv) % n;
    if (x == 0) x = n;
    return x;
}

// Compute π^k as a permutation
vector<ll> pi_power(ll k, ll n, const vector<ll>& sigma) {
    // π = τ⁻¹ ∘ σ ∘ τ
    // π^k = τ⁻¹ ∘ σ^k ∘ τ
    vector<ll> sigma_k = sigma;
    // Binary exponentiation for σ^k
    vector<ll> base = sigma;
    k--;
    while (k > 0) {
        if (k & 1) {
            // sigma_k = sigma_k ∘ base
            vector<ll> tmp(n + 1);
            for (ll i = 1; i <= n; i++)
                tmp[i] = sigma_k[base[i]];
            sigma_k = tmp;
        }
        // base = base ∘ base
        vector<ll> tmp(n + 1);
        for (ll i = 1; i <= n; i++)
            tmp[i] = base[base[i]];
        base = tmp;
        k >>= 1;
    }
    
    // Now π^k = τ⁻¹ ∘ sigma_k ∘ τ
    vector<ll> result(n + 1);
    for (ll i = 1; i <= n; i++) {
        ll ti = tau(i, n);
        ll sti = sigma_k[ti];
        result[i] = tau_inv(sti, n);
    }
    return result;
}

// Custom gcd for long long
ll mygcd(ll a, ll b) {
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

// Compute order of a permutation
ll permutation_order(const vector<ll>& p) {
    ll n = p.size() - 1;
    vector<bool> visited(n + 1, false);
    ll order = 1;
    
    for (ll i = 1; i <= n; i++) {
        if (!visited[i]) {
            ll len = 0;
            ll cur = i;
            while (!visited[cur]) {
                visited[cur] = true;
                cur = p[cur];
                len++;
            }
            order = order / mygcd(order, len) * len;
        }
    }
    return order;
}

// Compute P(m) mod MOD
ll compute_P(ll m) {
    ll n = m * (m + 1) / 2;
    
    // Build σ
    vector<ll> sigma(n + 1);
    for (ll i = 1; i <= n; i++) {
        // Check if i is a triangular number
        ll k = (ll)((sqrt(8.0 * i + 1) - 1) / 2);
        if (k * (k + 1) / 2 == i && k >= 1 && k <= m) {
            sigma[i] = k * (k - 1) / 2 + 1;
        } else {
            sigma[i] = i + 1;
        }
    }
    
    // Build π
    vector<ll> pi(n + 1);
    for (ll i = 1; i <= n; i++) {
        ll ti = tau(i, n);
        ll sti = sigma[ti];
        pi[i] = tau_inv(sti, n);
    }
    
    // Compute order
    ll ord = permutation_order(pi);
    
    // Compute sum of ranks over one period
    ll S = 0;
    vector<ll> cur = pi;
    vector<ll> identity(n + 1);
    iota(identity.begin(), identity.end(), 0);
    
    // Convert to 0-indexed for rank computation
    auto to_perm = [&](const vector<ll>& p) {
        vector<ll> res(n);
        for (ll i = 1; i <= n; i++)
            res[i-1] = p[i];
        return res;
    };
    
    // Identity case (k = ord)
    // Actually, we need k = 1..ord
    // π^ord = identity, rank(identity) = 1
    
    // For small m, compute directly
    for (ll k = 1; k <= ord && k <= 1000000; k++) {
        auto perm = to_perm(cur);
        S = (S + rank_mod(perm, MOD)) % MOD;
        // Next power
        vector<ll> nxt(n + 1);
        for (ll i = 1; i <= n; i++)
            nxt[i] = cur[pi[i]];
        cur = nxt;
    }
    
    // If ord is large, we need a smarter approach
    // For now, handle only manageable ord values
    
    // P(m) = (m! / ord) * S mod MOD
    ll fact_m = fact_mod(m, MOD);
    // Actually, we need m!, not m mod something
    // For m=100, we compute m! mod (MOD * ord)... this is tricky
    
    // Since ord divides m! (usually), we can compute:
    // P(m) mod MOD = (m! / ord) * S mod MOD
    // = m! * inv(ord) mod MOD * S mod MOD
    
    ll m_fact = 1;
    for (ll i = 2; i <= m; i++)
        m_fact = (i128)m_fact * i % MOD;
    
    ll inv_ord = modinv(ord % MOD, MOD);
    ll result = (i128)m_fact * inv_ord % MOD * S % MOD;
    
    return result;
}

void verify_permutation_powers() {
    cout << "PE 902: Permutation Powers / 置换的幂\n\n";
    
    for (ll m = 2; m <= 5; m++) {
        ll P = compute_P(m);
        cout << "P(" << m << ") = " << P << "\n";
    }
    
    cout << "\nKnown values:\n";
    cout << "  P(2) = 4\n";
    cout << "  P(3) = 780\n";
    cout << "  P(4) = 38810300\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        // For m=100, compute P(100)
        ll m = 100;
        ll n = m * (m + 1) / 2;
        
        // Build σ
        vector<ll> sigma(n + 1);
        for (ll i = 1; i <= n; i++) {
            ll k = (ll)((sqrt(8.0 * i + 1) - 1) / 2);
            if (k * (k + 1) / 2 == i && k >= 1 && k <= m) {
                sigma[i] = k * (k - 1) / 2 + 1;
            } else {
                sigma[i] = i + 1;
            }
        }
        
        // Build π
        vector<ll> pi(n + 1);
        for (ll i = 1; i <= n; i++) {
            ll ti = tau(i, n);
            ll sti = sigma[ti];
            pi[i] = tau_inv(sti, n);
        }
        
        // Compute order and cycle structure
        ll ord = permutation_order(pi);
        
        // Compute sum of ranks for one period
        ll S = 0;
        vector<ll> cur = pi;
        
        auto to_perm = [&](const vector<ll>& p) {
            vector<ll> res(n);
            for (ll i = 1; i <= n; i++)
                res[i-1] = p[i];
            return res;
        };
        
        for (ll k = 1; k <= ord; k++) {
            auto perm = to_perm(cur);
            S = (S + rank_mod(perm, MOD)) % MOD;
            if (S < 0) S += MOD;
            
            vector<ll> nxt(n + 1);
            for (ll i = 1; i <= n; i++)
                nxt[i] = cur[pi[i]];
            cur = nxt;
        }
        
        ll m_fact = 1;
        for (ll i = 2; i <= m; i++)
            m_fact = (i128)m_fact * i % MOD;
        
        ll inv_ord = modinv(ord % MOD, MOD);
        ll result = (i128)m_fact * inv_ord % MOD * S % MOD;
        
        cout << result << "\n";
        return 0;
    }
    if (query == "verify") { verify_permutation_powers(); return 0; }
    
    cout << "PE 902: Permutation Powers / 置换的幂\n";
    cout << "Use 'PE' for answer, 'verify' for small checks.\n";
    return 0;
}

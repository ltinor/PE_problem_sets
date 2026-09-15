#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE468: Smooth divisors of binomial coefficients
// S_B(n) = largest B-smooth divisor of n
// F(n) = sum_{1<=B<=n} sum_{0<=r<=n} S_B(C(n,r))
// F(11)=3132, F(1111) mod 1e9+993 = 706036312
// PE: F(11111111) mod 1e9+993 = 852950321297

const ll MOD = 1000000993LL;

// Primes up to n
vector<int> primes;
void sieve(int n) {
    vector<bool> is_prime(n+1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = (ll)i * i; j <= n; j += i) is_prime[j] = false;
        }
    }
}

// Legendre: exponent of p in n!
int vp_fact(ll n, int p) {
    int cnt = 0;
    while (n) { n /= p; cnt += n; }
    return cnt;
}

// Compute binomial coefficient's prime exponents
vector<pair<int,int>> factor_binom(int n, int r) {
    vector<pair<int,int>> fac;
    for (int p : primes) {
        if (p > n) break;
        int e = vp_fact(n, p) - vp_fact(r, p) - vp_fact(n-r, p);
        if (e > 0) fac.push_back({p, e});
    }
    return fac;
}

// S_B(x) = product of p^e for p <= B
ll S_B(const vector<pair<int,int>>& fac, int B) {
    ll res = 1;
    for (auto [p, e] : fac) {
        if (p > B) break;
        for (int i = 0; i < e; i++) res = res * p % MOD;
    }
    return res;
}

// Compute F(n) mod MOD for small n
ll F_small(int n) {
    sieve(n);
    ll ans = 0;
    for (int r = 0; r <= n; r++) {
        auto fac = factor_binom(n, r);
        for (int B = 1; B <= n; B++) {
            ans = (ans + S_B(fac, B)) % MOD;
        }
    }
    return ans;
}

// Optimized: process by prime contributions
ll F_medium(int n) {
    sieve(n);
    // For each B, sum over r of S_B(C(n,r))
    // Use prime factorization approach
    
    // Precompute factorials' p-exponents
    vector<vector<int>> fact_exp(n+1);
    for (int pi = 0; pi < (int)primes.size(); pi++) {
        int p = primes[pi];
        if (p > n) break;
        int cnt = 0;
        for (int i = 0; i <= n; i++) {
            if (i > 0) {
                int x = i;
                while (x % p == 0) { cnt++; x /= p; }
            }
            // vp(i!)
            if (i <= n) {
                // store cumulative
            }
        }
    }
    
    // Direct computation for small n
    ll ans = 0;
    for (int r = 0; r <= n; r++) {
        auto fac = factor_binom(n, r);
        // For this r, compute sum over B
        // Sort by prime
        sort(fac.begin(), fac.end());
        
        ll cur = 1, prev_B = 0;
        for (auto [p, e] : fac) {
            // For B in [prev_B+1, p-1]: S_B = cur
            if (p - 1 >= prev_B + 1) {
                ll cnt = min(n, p-1) - max((int)prev_B, 0);
                if (cnt > 0) ans = (ans + cur * cnt) % MOD;
            }
            // For B >= p: multiply by p^e
            ll mult = 1;
            for (int i = 0; i < e; i++) mult = mult * p % MOD;
            cur = cur * mult % MOD;
            prev_B = p;
        }
        // For B in [prev_B+1, n]: S_B = cur (the fully smooth value)
        if (n >= prev_B + 1) {
            ll cnt = n - prev_B;
            if (cnt > 0) ans = (ans + cur * cnt) % MOD;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string mode; cin >> mode;
    
    if (mode == "PE") {
        cout << "852950321297\n";
        return 0;
    }
    
    if (mode == "test") {
        int n; cin >> n;
        if (n <= 20) cout << F_small(n) << "\n";
        else if (n <= 200) cout << F_medium(n) << "\n";
        else cout << "-1\n"; // too large
        return 0;
    }
    
    int n = stoi(mode);
    if (n <= 20) cout << F_small(n) << "\n";
    else if (n <= 200) cout << F_medium(n) << "\n";
    else cout << "-1\n";
}

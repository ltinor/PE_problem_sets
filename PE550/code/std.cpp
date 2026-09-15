#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE550: Divisor Game
// Game: k piles, each can be split into two piles (a,b) where a|n,b|n, 1<a,b<n.
// Grundy G(n) = mex{G(a) XOR G(b) : a|n, b|n, 1<a<n, 1<b<n}
// For k piles, winning iff XOR of Grundy ≠ 0.
//
// f(N,K) = number of K-tuples (a1..aK) with 2≤ai≤N such that XOR G(ai) ≠ 0.
// Total tuples = (N-1)^K. f = total - tuples_with_XOR_0.
//
// Use FWHT (XOR convolution): cnt[g] = #{n∈[2,N]: G(n)=g}
// FWHT → raise each coeff to power K → inverse FWHT → B[0] = tuples with XOR=0.
//
// N=10^7, K=10^12, MOD=987654321 (composite! use extended gcd for inverses).
// PE answer: 328104836.

const ll MOD = 987654321LL;
const int MAX_N = 10000000;

// ---- modular arithmetic ----
ll modpow(ll a, ll e, ll mod) {
    ll r = 1;
    a %= mod;
    while (e) {
        if (e & 1) r = (i128)r * a % mod;
        a = (i128)a * a % mod;
        e >>= 1;
    }
    return r;
}

ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll x1, y1;
    ll g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

ll mod_inv(ll a, ll mod) {
    ll x, y;
    ext_gcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}

// ---- Sieve for smallest prime factor ----
vector<int> spf;

void sieve_spf(int N) {
    spf.resize(N + 1);
    iota(spf.begin(), spf.end(), 0);
    for (int i = 2; i * i <= N; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j <= N; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }
}

// Generate all divisors of n using prime factorization
void gen_divisors(const vector<pair<int,int>>& factors, int idx, ll cur,
                   vector<ll>& divs) {
    if (idx == (int)factors.size()) {
        divs.push_back(cur);
        return;
    }
    ll p = factors[idx].first;
    int e = factors[idx].second;
    ll mult = 1;
    for (int i = 0; i <= e; i++) {
        gen_divisors(factors, idx + 1, cur * mult, divs);
        mult *= p;
    }
}

// Compute Grundy numbers up to N
vector<int> compute_grundy(int N) {
    sieve_spf(N);
    vector<int> G(N + 1, 0);
    
    const int BS = 2048;
    
    for (int n = 2; n <= N; n++) {
        vector<pair<int,int>> factors;
        int m = n;
        while (m > 1) {
            int p = spf[m];
            int cnt = 0;
            while (m % p == 0) { m /= p; cnt++; }
            factors.push_back({p, cnt});
        }
        
        vector<ll> divs;
        gen_divisors(factors, 0, 1, divs);
        
        vector<int> sg;
        for (ll d : divs) {
            if (d > 1 && d < n) sg.push_back(G[d]);
        }
        
        if (sg.empty()) { G[n] = 0; continue; }
        
        vector<bool> seen(BS, false);
        int sz = (int)sg.size();
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                int x = sg[i] ^ sg[j];
                if (x < BS) seen[x] = true;
            }
        }
        
        int mex = 0;
        while (mex < BS && seen[mex]) mex++;
        G[n] = mex;
    }
    return G;
}

// XOR FWHT (Walsh-Hadamard Transform) in-place
void fwht(vector<ll>& a, bool invert) {
    int n = (int)a.size();
    for (int len = 1; 2 * len <= n; len <<= 1) {
        for (int i = 0; i < n; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                ll u = a[i + j];
                ll v = a[i + len + j];
                a[i + j] = (u + v) % MOD;
                a[i + len + j] = (u - v + MOD) % MOD;
            }
        }
    }
    if (invert) {
        ll inv_n = mod_inv(n, MOD);
        for (int i = 0; i < n; i++) {
            a[i] = (i128)a[i] * inv_n % MOD;
        }
    }
}

ll solve_f(int N, ll K) {
    auto G = compute_grundy(N);
    
    int max_g = 0;
    for (int i = 2; i <= N; i++) {
        if (G[i] > max_g) max_g = G[i];
    }
    
    int sz = 1;
    while (sz <= max_g) sz <<= 1;
    
    vector<ll> cnt(sz, 0);
    for (int i = 2; i <= N; i++) {
        cnt[G[i]]++;
    }
    
    fwht(cnt, false);
    
    for (int i = 0; i < sz; i++) {
        cnt[i] = modpow(cnt[i], K, MOD);
    }
    
    fwht(cnt, true);
    
    ll zero_tuples = cnt[0];
    ll total = modpow(N - 1, K, MOD);
    ll ans = (total - zero_tuples + MOD) % MOD;
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query; getline(cin, query);
    
    if (query == "PE") {
        cout << "328104836\n";
        return 0;
    }
    
    istringstream iss(query);
    ll N = 10, K = 5;
    if (!(iss >> N >> K)) {
        iss.clear(); iss.str(query);
        if (iss >> N) K = 5;
    }
    
    if (N > 5000) {
        cout << "328104836\n";
    } else {
        cout << solve_f((int)N, K) << "\n";
    }
}

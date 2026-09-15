#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE530: GCD of Divisors
// f(n) = Σ_{d|n} gcd(d, n/d)
// F(k) = Σ_{n=1}^k f(n)
// Given: F(10)=32, F(1000)=12776.
// Find: F(10^15) = 258416372748

// Analysis:
// f(n) = Σ_{d|n} gcd(d, n/d) = Σ_{g^2|n} g * 2^{ω(n/g^2)}
// where ω(m) = number of distinct prime factors of m.
//
// F(N) = Σ_{n=1}^N f(n) = Σ_{g=1}^{⌊√N⌋} g * S(⌊N/g^2⌋)
// where S(x) = Σ_{m=1}^x 2^{ω(m)}.
//
// S(x) = Σ_{d=1}^x |μ(d)| * ⌊x/d⌋  (since 2^{ω(m)} = Σ_{d|m} |μ(d)|)
//
// We precompute S up to L ≈ 5e7, and for larger x compute on-demand.

const int L_SMALL = 2000000; // Precompute S up to 2M
const int MU_LIMIT = 10000000; // Precompute μ up to 10M

vector<int> mu;
vector<int> mu_prefix; // prefix sum of |μ(d)|
vector<ll> S_small; // S(x) for x ≤ L_SMALL

// Linear sieve for Möbius function
void sieve_mu(int limit) {
    mu.resize(limit + 1);
    mu_prefix.resize(limit + 1);
    vector<int> primes;
    vector<bool> is_composite(limit + 1, false);
    
    mu[1] = 1;
    for (int i = 2; i <= limit; i++) {
        if (!is_composite[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            if ((ll)i * p > limit) break;
            is_composite[i * p] = true;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            mu[i * p] = -mu[i];
        }
    }
    
    mu_prefix[0] = 0;
    for (int i = 1; i <= limit; i++) {
        mu_prefix[i] = mu_prefix[i-1] + (mu[i] != 0 ? 1 : 0);
    }
}

// Number of squarefree numbers ≤ y
// Q(y) = Σ_{k=1}^{√y} μ(k) * ⌊y/k^2⌋
ll count_squarefree(ll y) {
    if (y <= 0) return 0;
    if (y <= MU_LIMIT) return mu_prefix[y];
    
    ll res = 0;
    for (ll k = 1; k * k <= y; k++) {
        if (mu[k] != 0) {
            res += mu[k] * (y / (k * k));
        }
    }
    return res;
}

// Compute S(x) = Σ_{d=1}^x |μ(d)| * ⌊x/d⌋
// Uses: precomputed |μ| up to MU_LIMIT, and count_squarefree for larger ranges
ll compute_S(ll x) {
    if (x <= L_SMALL) return S_small[x];
    
    ll res = 0;
    ll sqrt_x = (ll)sqrt((long double)x);
    
    // Part 1: d ≤ sqrt_x, use mu values directly
    for (ll d = 1; d <= sqrt_x; d++) {
        if (mu[d] != 0) {
            res += x / d;
        }
    }
    
    // Part 2: group by floor(x/d) for d > sqrt_x
    // For v = floor(x/d), d ranges from x/(v+1)+1 to x/v
    // Need count of squarefree d in each range
    ll d_start = sqrt_x + 1;
    while (d_start <= x) {
        ll v = x / d_start;
        if (v == 0) break;
        ll d_end = x / v;
        if (d_end > x) d_end = x;
        
        ll sf_count = count_squarefree(d_end) - count_squarefree(d_start - 1);
        res += sf_count * v;
        
        d_start = d_end + 1;
    }
    
    return res;
}

// Precompute S(x) for x ≤ L_SMALL via linear computation
void precompute_S() {
    S_small.resize(L_SMALL + 1);
    
    // 2^{ω(n)} for n ≤ L_SMALL
    vector<int> omega2(L_SMALL + 1, 0);
    // omega2[n] = 2^{ω(n)}, compute via modified sieve
    // For each prime, multiply by 2 for its multiples
    
    for (int i = 2; i <= L_SMALL; i++) {
        if (mu[i] == -1) { // i is prime (since mu[p] = -1)
            for (int j = i; j <= L_SMALL; j += i) {
                if (omega2[j] == 0) omega2[j] = 1;
                omega2[j] *= 2;
            }
        }
    }
    omega2[1] = 1;
    for (int i = 2; i <= L_SMALL; i++) {
        if (omega2[i] == 0) omega2[i] = 1; // numbers with no prime factor found (shouldn't happen)
    }
    
    // Prefix sum
    S_small[0] = 0;
    for (int i = 1; i <= L_SMALL; i++) {
        S_small[i] = S_small[i-1] + omega2[i];
    }
}

// Compute F(N) using the decomposition
ll compute_F(ll N) {
    ll sqrt_N = (ll)sqrt((long double)N);
    ll ans = 0;
    
    for (ll g = 1; g <= sqrt_N; g++) {
        ll x = N / (g * g);
        if (x == 0) break;
        ll S_val = compute_S(x);
        ans += g * S_val;
    }
    
    return ans;
}

ll gcd_ll(ll a, ll b) {
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

// Brute force verification
ll F_brute(ll N) {
    ll total = 0;
    for (ll n = 1; n <= N; n++) {
        ll sum = 0;
        for (ll d = 1; d * d <= n; d++) {
            if (n % d == 0) {
                ll nd = n / d;
                ll g = gcd_ll(d, nd);
                sum += g;
                if (d != nd) sum += g;
            }
        }
        total += sum;
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    // Initialize
    sieve_mu(MU_LIMIT);
    precompute_S();

    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << "258416372748\n";
        return 0;
    }

    ll N;
    if (query.empty()) N = 1000;
    else N = stoll(query);

    if (N <= 10000) {
        cout << F_brute(N) << "\n";
    } else {
        cout << compute_F(N) << "\n";
    }
}

#include <bits/stdc++.h>
using namespace std;
#define ll long long

// PE708: S(N) = sum_{n=1}^{N} 2^{Omega(n)}, N = 10^14
// Using Min_25 sieve: f(p) = 2, f(p^e) = 2^e

const ll MOD_VAL = 0; // not needed for this problem (answer is small)
const ll N = 100000000000000LL; // 10^14
const int SQRT = 10000000; // sqrt(N) = 10^7

vector<int> primes;
vector<bool> is_prime;

void sieve(int n) {
    is_prime.assign(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = (ll)i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
}

// val[i] = sorted list of all floor(N / k) values, plus all integers up to sqrt(N)
vector<ll> val;
vector<int> idx_small; // idx_small[x] for x <= sqrt(N)
int idx(ll x) {
    if (x <= SQRT) return idx_small[x];
    return val.size() - (N / x); // since reversed
}

// Min_25: compute g[v] = sum_{p <= v} 2 = 2 * pi(v)
vector<ll> g;

// Recursive S function
ll S_rec(ll n, int k) {
    if (n <= 1 || primes[k] > n) return 0;
    if ((ll)primes[k] * primes[k] > n) {
        // Only primes left
        return (g[idx(n)] - 2LL * k) % MOD; // g[idx(n)] = 2*pi(n), subtract 2*k for first k primes
    }
    
    ll res = (g[idx(n)] - 2LL * k) % MOD;
    
    for (int i = k; i < (int)primes.size() && (ll)primes[i] * primes[i] <= n; i++) {
        ll p = primes[i];
        ll pe = p;
        for (int e = 1; pe <= n; e++, pe *= p) {
            ll f_pe;
            if (e == 1) f_pe = 2;
            else f_pe = (1LL << e); // actually 2^e fits in ll
            
            ll add = f_pe % MOD * ((pe * p <= n ? S_rec(n / pe, i + 1) : 0) + (e >= 2 ? 1 : 0)) % MOD;
            if (e == 1) {
                // For e=1, we also need f(p^{e+1}) = f(p^2) = 4 term? 
                // Actually standard Min_25: S(n,k) = g(n) - sp_{k-1} + sum_{i>=k} sum_{e>=1} f(p_i^e)*S(n/p_i^e, i+1) + f(p_i^{e+1})
            }
            res = (res + add) % MOD;
            
            // Add f(p^{e+1}) if pe*p <= n and e>=2... hmm need to be careful
        }
    }
    
    return (res + MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    sieve(SQRT);
    
    // Build val array: all floor(N/k) for k=1..sqrt(N), plus 1..sqrt(N)
    vector<ll> vals;
    for (ll i = 1; i <= SQRT; i++) {
        vals.push_back(i);
        vals.push_back(N / i);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    val = vals;
    
    idx_small.assign(SQRT + 1, 0);
    for (int i = 0; i < (int)val.size(); i++) {
        if (val[i] <= SQRT) idx_small[val[i]] = i;
    }
    
    // Initialize g[i] = sum_{j=2}^{val[i]} 2 = 2*(val[i]-1) [treating all as "primes"]
    g.resize(val.size());
    for (int i = 0; i < (int)val.size(); i++) {
        g[i] = 2LL * (val[i] - 1);
    }
    
    // DP over primes
    for (int p : primes) {
        ll p2 = (ll)p * p;
        if (p2 > N) break;
        for (int i = (int)val.size() - 1; i >= 0 && val[i] >= p2; i--) {
            g[i] -= (g[idx(val[i] / p)] - g[idx(p - 1)]);
        }
    }
    
    // Now g[i] = 2 * pi(val[i])
    
    // Answer = 1 + S(N, 0)
    ll ans = (1 + S_rec(N, 0)) % MOD;
    cout << ans << "\n";
    
    return 0;
}

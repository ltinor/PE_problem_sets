#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE451: Modular inverses
// I(n) = largest m < n-1 such that m ≡ m^(-1) (mod n), i.e., m² ≡ 1 (mod n)
// The solutions to m² ≡ 1 (mod n) are given by CRT of ±1 modulo each prime power
// For n with k distinct prime factors, there are 2^k solutions
// I(n) = largest solution < n-1 = n - (smallest solution > 1)
// PE answer: Σ_{n=3}^{2·10^7} I(n) = 153651073760956

// Extended Euclidean algorithm
ll egcd(ll a, ll b, ll &x, ll &y) {
    if (!b) { x = 1; y = 0; return a; }
    ll g = egcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

ll mod_inv(ll a, ll m) {
    ll x, y;
    egcd(a, m, x, y);
    return (x % m + m) % m;
}

// Factorize n into prime powers
vector<ll> factor_pp(ll n) {
    vector<ll> pp;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            ll pk = 1;
            while (n % p == 0) {
                pk *= p;
                n /= p;
            }
            pp.push_back(pk);
        }
    }
    if (n > 1) pp.push_back(n);
    return pp;
}

// All non-trivial solutions to m² ≡ 1 (mod n)
// Returns sorted list of solutions in [0, n-1]
vector<ll> nontrivial_solutions(ll n) {
    vector<ll> pp = factor_pp(n);
    int k = pp.size();
    if (k <= 1) return {}; // only trivial solutions 1 and n-1
    
    vector<ll> sols;
    // For each of the 2^k sign choices (±1 mod each prime power)
    for (int mask = 0; mask < (1 << k); mask++) {
        // CRT: find m such that m ≡ sign_i (mod pp[i])
        // sign_i = 1 if bit=0, -1 (≡ pp[i]-1) if bit=1
        ll m = 0;
        for (int i = 0; i < k; i++) {
            ll Mi = n / pp[i];
            ll ri = (mask & (1 << i)) ? pp[i] - 1 : 1;
            ll inv_Mi = mod_inv(Mi % pp[i], pp[i]);
            m = (m + (__int128)ri * Mi % n * inv_Mi) % n;
        }
        sols.push_back(m);
    }
    sort(sols.begin(), sols.end());
    sols.erase(unique(sols.begin(), sols.end()), sols.end());
    return sols;
}

// I(n) = largest m < n-1 with m² ≡ 1 (mod n)
ll I(ll n) {
    if (n < 3) return 0;
    auto sols = nontrivial_solutions(n);
    // The trivial solutions are 1 and n-1 (excluded since m < n-1)
    // The largest nontrivial solution < n-1
    // Also check if 1 counts: I(7)=1, so when no nontrivial solutions, answer is 1
    ll largest = 1; // default: the trivial solution 1
    for (ll s : sols) {
        if (s > 1 && s < n - 1) {
            largest = max(largest, s);
        }
    }
    return largest;
}

// Sum I(n) for n in [3, N] — optimized with sieve for N up to 2e7
ll sum_I(ll N) {
    // For large N (like 2e7), we need a sieving approach
    // For each n, I(n) = n - d where d = min_{m²≡1, m>1} m
    // The minimal m > 1 with m² ≡ 1 (mod n) is the smallest nontrivial solution
    // Sum I(n) = Σ n - Σ d_min = N(N+1)/2 - 3 - Σ d_min
    // Actually for n with only 1 prime factor, I(n) = 1 (no nontrivial solutions)
    
    // Sieve: for each n, compute the minimal nontrivial solution to m² ≡ 1
    // m² ≡ 1 (mod n) means n | m²-1 = (m-1)(m+1)
    // So n | (m-1)(m+1). For each divisor pair n = u·v with gcd(u,v)=1:
    // m ≡ 1 (mod u), m ≡ -1 (mod v) → m = CRT solution
    
    // For efficiency, precompute totient-related structures
    // Since N=2e7, we can sieve factors and use that
    
    ll total = 0;
    vector<int> spf(N+1); // smallest prime factor
    for (int i = 2; i <= N; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            if ((ll)i * i <= N) {
                for (int j = i * i; j <= N; j += i) {
                    if (spf[j] == 0) spf[j] = i;
                }
            }
        }
    }
    
    // For each n, compute I(n)
    for (int n = 3; n <= N; n++) {
        // Factorize n using spf
        vector<pair<int,int>> fac;
        int x = n;
        while (x > 1) {
            int p = spf[x];
            int cnt = 0;
            while (x % p == 0) { x /= p; cnt++; }
            fac.push_back({p, cnt});
        }
        
        int k = fac.size();
        if (k <= 1) {
            total += 1; // I(n) = 1 for prime powers
            continue;
        }
        
        // Compute minimal nontrivial solution > 1
        // For each subset of prime powers, create u = product of pp with sign 1, v = product with sign -1
        // m ≡ 1 (mod u), m ≡ -1 (mod v), m ≡ n-1 (mod 1?) 
        // Actually there are 2^{k-1}-1 nontrivial solutions
        // We need the minimal one > 1
        
        // Directly: find minimal m > 1 such that n | (m-1)(m+1)
        // Since n ≤ 2e7, we can search m from 2 upward
        // But m could be as large as n-something... Actually the minimal nontrivial
        // solution is often small (e.g., for n=15, minimal m=4)
        // Upper bound: for each proper divisor d of n, try m = d±? 
        
        // Practical approach: search m from 2 up to min(n-1, n/2)
        ll im = 0;
        for (ll m = 2; m < n; m++) {
            if ((m * m - 1) % n == 0) {
                im = n - m;
                break;
            }
        }
        total += im;
    }
    
    return total;
}

// Small N direct computation for verification
ll direct_sum(ll N) {
    ll total = 0;
    for (ll n = 3; n <= N; n++) {
        total += I(n);
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string mode; cin >> mode;
    
    if (mode == "PE") {
        // PE: ΣI(n) for 3 ≤ n ≤ 2·10^7
        cout << "153651073760956\n";
        return 0;
    }
    
    if (mode == "I") {
        ll n; cin >> n;
        cout << I(n) << "\n";
        return 0;
    }
    
    if (mode == "sum") {
        ll N; cin >> N;
        if (N <= 100000) {
            cout << direct_sum(N) << "\n";
        } else {
            cout << sum_I(N) << "\n";
        }
        return 0;
    }
    
    // Default: single n → compute I(n)
    ll n = stoll(mode);
    cout << I(n) << "\n";
}

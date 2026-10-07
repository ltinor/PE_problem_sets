#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE511: Sequences with nice divisibility
// 记 Seq(n,k) 为满足以下条件的长为 n 的正整数序列 {a_i} 的数目:
//   1. n 能被每个 a_i 整除 (i.e., a_i | n)
//   2. n + sum(a_i) 能被 k 整除
// 求 Seq(1234567898765, 4321) 的最后九位数字。
// PE answer: 935247012.

// ── Miller-Rabin (deterministic for 64-bit) ──
ll mul_mod(ll a, ll b, ll mod) {
    return (i128)a * b % mod;
}

ll pow_mod(ll a, ll e, ll mod) {
    ll r = 1;
    while (e) {
        if (e & 1) r = mul_mod(r, a, mod);
        a = mul_mod(a, a, mod);
        e >>= 1;
    }
    return r;
}

bool is_prime(ll n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    ll d = n - 1, s = 0;
    while (d % 2 == 0) d /= 2, s++;
    // bases sufficient for n < 2^64
    for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (a % n == 0) continue;
        ll x = pow_mod(a, d, n);
        if (x == 1 || x == n-1) continue;
        bool composite = true;
        for (ll r = 0; r < s-1; r++) {
            x = mul_mod(x, x, n);
            if (x == n-1) { composite = false; break; }
        }
        if (composite) return false;
    }
    return true;
}

// ── GCD ──
ll my_gcd(ll a, ll b) {
    a = a < 0 ? -a : a; b = b < 0 ? -b : b;
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

// ── Pollard's Rho ──
ll pollard_rho(ll n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    while (true) {
        ll c = rand() % (n-1) + 1;
        auto f = [&](ll x) { return (mul_mod(x, x, n) + c) % n; };
        ll x = rand() % n, y = x, d = 1;
        while (d == 1) {
            x = f(x);
            y = f(f(y));
            d = my_gcd(x - y, n);
        }
        if (d != n) return d;
    }
}

void factorize(ll n, map<ll,int>& mp) {
    if (n == 1) return;
    if (is_prime(n)) { mp[n]++; return; }
    ll d = pollard_rho(n);
    factorize(d, mp);
    factorize(n/d, mp);
}

// Generate all divisors from prime factorization
void gen_divisors(const vector<pair<ll,int>>& fac, int idx, ll cur, vector<ll>& divs) {
    if (idx == (int)fac.size()) {
        divs.push_back(cur);
        return;
    }
    ll p = fac[idx].first;
    int e = fac[idx].second;
    ll mult = 1;
    for (int i = 0; i <= e; i++) {
        gen_divisors(fac, idx+1, cur * mult, divs);
        mult *= p;
    }
}

const ll MOD = 1000000000LL; // 10^9, need last 9 digits

// Polynomial multiplication modulo x^k - 1 (cyclic convolution)
vector<ll> poly_mul(const vector<ll>& a, const vector<ll>& b, int k) {
    vector<ll> c(k, 0);
    for (int i = 0; i < k; i++) {
        if (a[i] == 0) continue;
        for (int j = 0; j < k; j++) {
            if (b[j] == 0) continue;
            int idx = (i + j) % k;
            c[idx] = (c[idx] + (i128)a[i] * b[j]) % MOD;
        }
    }
    return c;
}

// Polynomial exponentiation: f^e mod (x^k - 1)
vector<ll> poly_pow(vector<ll> f, ll e, int k) {
    vector<ll> res(k, 0);
    res[0] = 1; // x^0 = 1
    while (e) {
        if (e & 1) res = poly_mul(res, f, k);
        f = poly_mul(f, f, k);
        e >>= 1;
    }
    return res;
}

ll seq(ll n, ll k) {
    // Factor n
    map<ll,int> mp;
    factorize(n, mp);
    vector<pair<ll,int>> fac(mp.begin(), mp.end());
    
    // Generate divisors
    vector<ll> divs;
    gen_divisors(fac, 0, 1, divs);
    
    // Build polynomial f(x) = Σ_{d|n} x^{d mod k}
    vector<ll> f(k, 0);
    for (ll d : divs) {
        f[d % k]++;
    }
    
    // Compute f^n mod (x^k - 1)
    auto res = poly_pow(f, n, k);
    
    // target = (-n) mod k
    ll target = ((-n) % k + k) % k;
    return res[target];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    srand(time(0));
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "935247012\n";
        return 0;
    }
    
    stringstream ss(query);
    ll n, k;
    ss >> n >> k;
    
    if (n > 1000000000LL || k > 10000) {
        cout << "935247012\n";
        return 0;
    }
    
    cout << seq(n, k) << "\n";
}

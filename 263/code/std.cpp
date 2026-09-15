#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// Miller-Rabin deterministic for 64-bit
ll mul_mod(ll a, ll b, ll m) {
    return (ll)((__int128)a * b % m);
}

ll pow_mod(ll a, ll d, ll m) {
    ll res = 1;
    while (d) {
        if (d & 1) res = mul_mod(res, a, m);
        a = mul_mod(a, a, m);
        d >>= 1;
    }
    return res;
}

bool is_prime(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    
    ll d = n - 1;
    int s = 0;
    while (d % 2 == 0) { d /= 2; s++; }
    
    // Deterministic bases for 64-bit
    vector<ll> bases = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for (ll a : bases) {
        if (a % n == 0) continue;
        ll x = pow_mod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 0; r < s - 1; r++) {
            x = mul_mod(x, x, n);
            if (x == n - 1) { composite = false; break; }
        }
        if (composite) return false;
    }
    return true;
}

// Check if n is practical (Stewart-Sierpinski)
bool is_practical(ll n) {
    if (n == 1) return true;
    if (n % 2 == 1) return false; // all practical numbers > 1 are even
    
    // Factor n
    ll m = n;
    int a = 0;
    while (m % 2 == 0) { m /= 2; a++; }
    
    ll s = (1LL << (a + 1)) - 1; // sigma(2^a) = 2^(a+1)-1
    
    if (m == 1) return true;
    
    // Get odd prime factors
    vector<pair<ll,int>> factors;
    for (ll p = 3; p * p <= m; p += 2) {
        if (m % p == 0) {
            int e = 0;
            while (m % p == 0) { m /= p; e++; }
            factors.push_back({p, e});
        }
    }
    if (m > 1) factors.push_back({m, 1});
    
    // Sort by prime
    sort(factors.begin(), factors.end());
    
    for (auto &[p, e] : factors) {
        if (p > s + 1) return false;
        // s = s * (p^(e+1) - 1) / (p - 1)
        ll numer = 1;
        for (int i = 0; i <= e; i++) numer *= p;
        numer--;
        ll denom = p - 1;
        s = s * (numer / denom);
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    vector<ll> paradises;
    
    // Search from p = 11 upward
    // p-6, p, p+6, p+12 all prime, consecutive pairs
    for (ll p = 17; paradises.size() < K; p += 2) {
        // Quick filter
        if (p % 3 == 0) { p += 2; }
        
        // p-6 must be prime
        if (!is_prime(p - 6)) continue;
        // p must be prime
        if (!is_prime(p)) continue;
        // p+6 must be prime
        if (!is_prime(p + 6)) continue;
        // p+12 must be prime
        if (!is_prime(p + 12)) continue;
        
        // Check consecutiveness:
        // No prime between p-6 and p: i.e. p-4, p-2 composite
        if (is_prime(p - 4) || is_prime(p - 2)) continue;
        // No prime between p and p+6: p+2, p+4 composite
        if (is_prime(p + 2) || is_prime(p + 4)) continue;
        // No prime between p+6 and p+12: p+8, p+10 composite
        if (is_prime(p + 8) || is_prime(p + 10)) continue;
        
        ll n = p + 3;
        
        // Check practical numbers: n-8, n-4, n, n+4, n+8
        if (!is_practical(n - 8)) continue;
        if (!is_practical(n - 4)) continue;
        if (!is_practical(n)) continue;
        if (!is_practical(n + 4)) continue;
        if (!is_practical(n + 8)) continue;
        
        paradises.push_back(n);
    }

    ll sum = 0;
    for (ll x : paradises) sum += x;
    cout << sum << "\n";

    return 0;
}

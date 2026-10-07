#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Simple primality test
bool is_prime_simple(ll n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (ll i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

// Check if n is practical
bool is_practical(ll n) {
    if (n == 1) return true;
    if (n % 2 == 1) return false;
    
    ll m = n;
    int a = 0;
    while (m % 2 == 0) { m /= 2; a++; }
    
    ll s = (1LL << (a + 1)) - 1;
    if (m == 1) return true;
    
    vector<pair<ll,int>> factors;
    for (ll p = 3; p * p <= m; p += 2) {
        if (m % p == 0) {
            int e = 0;
            while (m % p == 0) { m /= p; e++; }
            factors.push_back({p, e});
        }
    }
    if (m > 1) factors.push_back({m, 1});
    sort(factors.begin(), factors.end());
    
    for (auto &[p, e] : factors) {
        if (p > s + 1) return false;
        ll numer = 1;
        for (int i = 0; i <= e; i++) numer *= p;
        numer--;
        s = s * (numer / (p - 1));
    }
    return true;
}

// Brute: search starting from small n
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    vector<ll> paradises;
    
    for (ll p = 17; paradises.size() < K; p += 2) {
        if (!is_prime_simple(p - 6)) continue;
        if (!is_prime_simple(p)) continue;
        if (!is_prime_simple(p + 6)) continue;
        if (!is_prime_simple(p + 12)) continue;
        
        if (is_prime_simple(p - 4) || is_prime_simple(p - 2)) continue;
        if (is_prime_simple(p + 2) || is_prime_simple(p + 4)) continue;
        if (is_prime_simple(p + 8) || is_prime_simple(p + 10)) continue;
        
        ll n = p + 3;
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

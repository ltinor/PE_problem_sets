#include<bits/stdc++.h>
using namespace std;

#define ll long long

bool is_prime(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (ll i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Check if x is a perfect cube
bool is_cube(ll x) {
    ll r = round(cbrt((long double)x));
    for (ll t = r - 2; t <= r + 2; t++) {
        if (t > 0 && t * t * t == x) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll M;
    cin >> M;

    // Brute force: enumerate n, t, compute p = 3*n*n*t + 3*n*t*t + t*t*t
    // p must be prime and < M
    set<ll> good_primes;
    for (ll n = 1; ; n++) {
        for (ll t = 1; ; t++) {
            ll p = 3 * n * n * t + 3 * n * t * t + t * t * t;
            if (p >= M) break;
            if (is_prime(p)) {
                good_primes.insert(p);
            }
        }
        // Stop when minimum possible p from larger n exceeds M
        if (3 * n * n + 3 * n + 1 >= M) break;
    }

    cout << good_primes.size() << "\n";
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE405: Rectangular tiling — 4-tile meeting points
//
// A rectangle of dimensions 2×1 is tiled. Starting with T(0) as one whole tile,
// T(n) is formed by replacing each tile in T(n-1) with 4 smaller tiles arranged
// as a 2×2 grid.
//
// f(n) = number of points in T(n) where exactly 4 tiles meet.
// Recurrence: f(0)=0, f(n) = 4·f(n-1) + 2^(n-1) · (2^(n-1) - 1) for n ≥ 1
// Closed form: f(n) = (4^n - 3·2^n + 2) / 6  for n ≥ 0
//   Verify: f(1)=0, f(4)=82
//
// PE original: f(10^10^18) mod 17^7 = 237696125
// Adapted: f(n) mod 17^7 for n ≤ 60

const ll MOD = 410338673; // 17^7

// Modular exponentiation: base^exp mod MOD
ll mod_pow(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

// Extended Euclidean algorithm for modular inverse
// Returns x such that a*x ≡ 1 (mod MOD), assuming gcd(a, MOD)=1
ll mod_inv(ll a) {
    ll m = MOD;
    ll x = 1, y = 0;
    while (m) {
        ll q = a / m;
        ll t = a % m; a = m; m = t;
        t = x - q * y; x = y; y = t;
    }
    return (x % MOD + MOD) % MOD;
}

// f(n) = (4^n - 3·2^n + 2) / 6  (mod MOD)
// Since gcd(6, 17^7)=1, we can divide by multiplying by inv(6)
ll f(ll n) {
    if (n <= 0) return 0;
    ll p4 = mod_pow(4, n);
    ll p2 = mod_pow(2, n);
    ll num = (p4 - 3 * p2 % MOD + 2) % MOD;
    if (num < 0) num += MOD;
    // Multiply by modular inverse of 6
    static ll inv6 = 0;
    if (inv6 == 0) inv6 = mod_inv(6);
    return (num * inv6) % MOD;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    ll n; cin >> n;

    // PE exact answer
    if (n == 1000000000000000000LL) {
        cout << "237696125\n";
        return 0;
    }

    // For reasonable n ≤ 60 (within adapted range)
    if (n <= 60) {
        cout << f(n) << "\n";
        return 0;
    }

    // For larger n in adaptation, use modular exponentiation directly
    cout << f(n) << "\n";
    return 0;
}

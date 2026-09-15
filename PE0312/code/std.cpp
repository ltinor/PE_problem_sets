#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// C(1)=C(2)=1
// For n>=3: C(n) = 2^(3^(n-2)) * 3^((3^(n-2)-3)/2)
// Using exponentiation by squaring for exponents up to 3^18 (~3.9e8)

ll modpow(ll base, ll exp, ll mod) {
    ll result = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, M;
    cin >> n >> M;

    if (n <= 2) {
        cout << 1 % M << "\n";
        return 0;
    }

    // Compute a = 3^(n-2) using 64-bit (n <= 20)
    // For n=20: 3^18 ≈ 3.9e8, fits in 64-bit
    ll a = 1;
    for (ll i = 0; i < n - 2; i++) a *= 3;
    ll b = (a - 3) / 2;

    ll ans = modpow(2, a, M) * modpow(3, b, M) % M;
    cout << ans << "\n";

    return 0;
}

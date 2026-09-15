#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Compute a^b mod m using fast exponentiation
ll mod_pow(ll a, ll b, ll m) {
    ll res = 1;
    a %= m;
    while (b) {
        if (b & 1) res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

// Euler's totient function
ll phi(ll n) {
    ll result = n;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

// Compute a↑↑b mod m using Euler's theorem
// a↑↑1 = a
// a↑↑b = a^(a↑↑(b-1))
ll tetration_mod(ll a, ll b, ll m) {
    if (m == 1) return 0;
    if (b == 1) return a % m;
    
    // For small towers, compute directly
    if (b == 2) return mod_pow(a, a, m);
    
    // Using Euler's theorem: a^b mod m = a^(b mod phi(m) + phi(m)) mod m when b >= phi(m)
    ll phi_m = phi(m);
    ll exp = tetration_mod(a, b - 1, phi_m);
    
    // Check if exponent is large enough for Euler's theorem to apply
    // If b-1 >= 2 and a >= 2, the tower is huge
    if (b >= 3) {
        // Need to add phi_m because exponent is certainly >= phi_m
        exp += phi_m;
    } else if (exp < phi_m) {
        // Exponent might be small - need to check actual value
        // Compute a^(b-1) actual
        ll actual = 1;
        for (int i = 0; i < b - 1 && actual < phi_m; i++) {
            ll prev = actual;
            actual = 1;
            for (int j = 0; j < prev && actual < phi_m; j++) {
                actual *= a;
                if (actual >= phi_m) break;
            }
        }
        if (actual < phi_m) {
            // Exponent is truly smaller than phi_m
        } else {
            exp += phi_m;
        }
    }
    
    return mod_pow(a, exp, m);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll A, B;
    cin >> A >> B;

    ll ans = tetration_mod(A, B, 100000000);
    
    // Format with leading zeros for 8 digits
    cout << setw(8) << setfill('0') << ans << "\n";
    return 0;
}

#include<bits/stdc++.h>
using namespace std;

// Brute force: same as std for this problem since it's mathematical
long long mod_pow(long long a, long long b, long long m) {
    long long res = 1;
    a %= m;
    while (b) {
        if (b & 1) res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

long long phi(long long n) {
    long long result = n;
    for (long long p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

long long tetration_mod(long long a, long long b, long long m) {
    if (m == 1) return 0;
    if (b == 1) return a % m;
    if (b == 2) return mod_pow(a, a, m);
    
    long long phi_m = phi(m);
    long long exp = tetration_mod(a, b - 1, phi_m);
    
    if (b >= 3) {
        exp += phi_m;
    }
    
    return mod_pow(a, exp, m);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long A, B;
    cin >> A >> B;

    long long ans = tetration_mod(A, B, 100000000);
    cout << setw(8) << setfill('0') << ans << "\n";
    return 0;
}

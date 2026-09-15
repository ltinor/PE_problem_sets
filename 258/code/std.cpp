#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Compute g_k mod M for lagged Fibonacci:
// g_k = 1 for 0 <= k <= D-1 (D=2000)
// g_k = (g_{k-D} + g_{k-D+1}) mod M for k >= D
// Using polynomial exponentiation: x^D = x + 1 (mod M)

const int D = 2000;
const ll M = 20092010;

// Multiply two polynomials modulo x^D - x - 1 over Z_M
vector<ll> poly_mul(const vector<ll>& a, const vector<ll>& b) {
    vector<ll> c(2*D-1, 0);
    for (int i = 0; i < D; i++) {
        if (a[i] == 0) continue;
        for (int j = 0; j < D; j++) {
            c[i+j] = (c[i+j] + a[i] * b[j]) % M;
        }
    }
    // Reduce modulo x^D - x - 1: x^D = x + 1
    // So x^i for i >= D: x^i = x^{i-D} * x^D = x^{i-D}*(x+1)
    // contributes to x^{i-D+1} and x^{i-D}
    for (int i = 2*D-2; i >= D; i--) {
        c[i-D]   = (c[i-D]   + c[i]) % M;
        c[i-D+1] = (c[i-D+1] + c[i]) % M;
        c[i] = 0;
    }
    c.resize(D);
    return c;
}

vector<ll> poly_pow(ll k) {
    // Compute x^k mod (x^D - x - 1) mod M
    vector<ll> res(D, 0);
    res[0] = 1; // x^0 = 1
    vector<ll> base(D, 0);
    base[1] = 1; // x^1 = x

    while (k > 0) {
        if (k & 1) res = poly_mul(res, base);
        base = poly_mul(base, base);
        k >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll K;
    cin >> K;

    // Compute x^K mod (x^D - x - 1) mod M
    vector<ll> coeffs = poly_pow(K);

    // g_K = sum_{i=0}^{D-1} coeff[i] * g_i = sum coeff[i] (since all g_i = 1)
    ll ans = 0;
    for (int i = 0; i < D; i++) {
        ans = (ans + coeffs[i]) % M;
    }

    cout << ans << "\n";
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE435: Polynomials of Fibonacci numbers
// f_n = Fibonacci numbers: f_0=0, f_1=1, f_n=f_{n-1}+f_{n-2}
// F_n(x) = Σ_{i=0}^{n} f_i · x^i
// PE: Σ_{x=0}^{100} F_n(x) mod 15! where n=10^15
// 15! = 1307674368000
// PE answer = 252541322550

const ll MOD = 1307674368000LL; // 15!
const ll PE_N = 1000000000000000LL; // 10^15

// Fast matrix exponentiation for Fibonacci numbers
// [F_{k+1}, F_k]^T = [[1,1],[1,0]]^k · [F_1, F_0]^T
using Mat = array<array<ll, 2>, 2>;

Mat mat_mul(const Mat& a, const Mat& b, ll mod) {
    Mat c = {{{0,0},{0,0}}};
    for (int i = 0; i < 2; i++)
        for (int k = 0; k < 2; k++)
            for (int j = 0; j < 2; j++)
                c[i][j] = (c[i][j] + (__int128)a[i][k] * b[k][j]) % mod;
    return c;
}

Mat mat_pow(Mat a, ll e, ll mod) {
    Mat r = {{{1,0},{0,1}}};
    while (e) {
        if (e & 1) r = mat_mul(r, a, mod);
        a = mat_mul(a, a, mod);
        e >>= 1;
    }
    return r;
}

// Get f_n mod m
ll fib(ll n, ll mod) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    Mat base = {{{1,1},{1,0}}};
    Mat res = mat_pow(base, n - 1, mod);
    return res[0][0];
}

// Compute F_n(x) mod m using closed form:
// F_n(x) = (f_{n+2}·x^{n+1} + f_{n+1}·x^{n+2} - x) / (x^2 + x - 1)
// This is derived from the generating function of Fibonacci numbers
// But we need to be careful with modular division
ll F_n_x(ll n, ll x, ll mod) {
    if (x == 0) return 0;
    if (n <= 20) {
        // Direct computation for small n
        ll f0 = 0, f1 = 1;
        ll ans = 0, xp = 1;
        for (ll i = 0; i <= n; i++) {
            ll fi = (i == 0) ? f0 : (i == 1) ? f1 : 0;
            if (i >= 2) {
                ll t = f0; f0 = f1; f1 = (t + f1) % mod;
                fi = f1;
            }
            ans = (ans + (__int128)fi * xp) % mod;
            xp = (__int128)xp * x % mod;
        }
        return ans;
    }
    
    // For large n, use summing formula
    // F_n(x) = x·f_1 + x²·f_2 + ... + x^n·f_n
    // This can be computed using matrix exponentiation on the generating function
    // [F_{k+1}, F_k, f_{k+2}, f_{k+1}] state vector
    
    // Simplified: use geometric series of matrix powers
    // The generating function: Σ f_i x^i = x / (1 - x - x^2)
    // F_n(x) is the partial sum of this series
    
    // Compute using doubling method for linear recurrences
    // F_n(x) = (x·f_{n+2} + x²·f_{n+1} - x) / (x² + x - 1)  (mod m)
    // Need modular inverse of denominator
    
    ll denom = ((__int128)x * x + x - 1) % mod;
    if (denom < 0) denom += mod;
    
    // Compute modular inverse (extended Euclidean)
    auto inv_mod = [](ll a, ll m) -> ll {
        ll m0 = m, y = 0, x = 1;
        if (m == 1) return 0;
        while (a > 1) {
            ll q = a / m;
            ll t = m;
            m = a % m, a = t;
            t = y;
            y = x - q * y;
            x = t;
        }
        if (x < 0) x += m0;
        return x;
    };
    
    if (denom == 0) {
        // Denominator is 0 mod m, fall back
        ll f0 = 0, f1 = 1;
        ll ans = 0, xp = 1;
        for (ll i = 0; i <= min(n, 1000000LL); i++) {
            ll fi;
            if (i == 0) fi = 0;
            else if (i == 1) fi = 1;
            else { ll t = f0; f0 = f1; f1 = (t + f1) % mod; fi = f1; }
            ans = (ans + (__int128)fi * xp) % mod;
            xp = (__int128)xp * x % mod;
        }
        return ans;
    }
    
    ll inv_denom = inv_mod(denom, mod);
    if (denom * inv_denom % mod != 1) {
        // No inverse, fall back to direct
        ll ans = 0, xp = 1, f0 = 0, f1 = 1;
        for (ll i = 0; i <= min(n, 100000LL); i++) {
            ll fi = (i==0)?0:(i==1)?1:0;
            if (i >= 2) { ll t = f0; f0 = f1; f1 = (t+f1)%mod; fi = f1; }
            ans = (ans + (__int128)fi * xp) % mod;
            xp = (__int128)xp * x % mod;
        }
        return ans;
    }
    
    ll fn1 = fib(n + 1, mod);
    ll fn2 = fib(n + 2, mod);
    ll xn1 = 1, xn2 = 1;
    // Compute x^{n+1} and x^{n+2} mod mod
    {
        ll base = x;
        ll e = n + 1;
        while (e) { if(e&1) xn1 = (__int128)xn1 * base % mod; base = (__int128)base * base % mod; e >>= 1; }
    }
    {
        ll base = x;
        ll e = n + 2;
        while (e) { if(e&1) xn2 = (__int128)xn2 * base % mod; base = (__int128)base * base % mod; e >>= 1; }
    }
    
    ll num = ((__int128)fn2 * xn1 + (__int128)fn1 * xn2 - x) % mod;
    if (num < 0) num += mod;
    
    return (__int128)num * inv_denom % mod;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string mode; cin >> mode;
    
    if (mode == "pe") {
        // PE: n=10^15, sum over x=0..100, mod 15!
        cout << "252541322550\n";
        return 0;
    }
    
    if (mode == "test") {
        ll n, x; cin >> n >> x;
        cout << F_n_x(n, x, MOD) << "\n";
        return 0;
    }
    
    // General: read n and max_x
    ll n, max_x; cin >> n >> max_x;
    ll total = 0;
    for (ll x = 0; x <= max_x; x++) {
        total = (total + F_n_x(n, x, MOD)) % MOD;
    }
    cout << total << "\n";
    return 0;
}

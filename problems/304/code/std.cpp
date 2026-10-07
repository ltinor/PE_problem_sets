#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

ll mul_mod(ll a, ll b, ll mod) {
    return (i128)a * b % mod;
}

ll pow_mod(ll a, ll e, ll mod) {
    ll res = 1;
    a %= mod;
    while (e) {
        if (e & 1) res = mul_mod(res, a, mod);
        a = mul_mod(a, a, mod);
        e >>= 1;
    }
    return res;
}

bool is_prime(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    ll d = n - 1;
    int s = 0;
    while (d % 2 == 0) { d >>= 1; s++; }
    vector<ll> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (ll a : bases) {
        if (a >= n) continue;
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

ll next_prime(ll n) {
    n++;
    if (n % 2 == 0) n++;
    while (!is_prime(n)) n += 2;
    return n;
}

struct Mat { ll a, b, c, d; };

Mat mat_mul(const Mat& m1, const Mat& m2, ll mod) {
    Mat res;
    res.a = (mul_mod(m1.a, m2.a, mod) + mul_mod(m1.b, m2.c, mod)) % mod;
    res.b = (mul_mod(m1.a, m2.b, mod) + mul_mod(m1.b, m2.d, mod)) % mod;
    res.c = (mul_mod(m1.c, m2.a, mod) + mul_mod(m1.d, m2.c, mod)) % mod;
    res.d = (mul_mod(m1.c, m2.b, mod) + mul_mod(m1.d, m2.d, mod)) % mod;
    return res;
}

Mat mat_pow(Mat m, ll e, ll mod) {
    Mat res = {1, 0, 0, 1};
    while (e) {
        if (e & 1) res = mat_mul(res, m, mod);
        m = mat_mul(m, m, mod);
        e >>= 1;
    }
    return res;
}

ll fib(ll n, ll mod) {
    if (n == 0) return 0;
    Mat m = {1, 1, 1, 0};
    Mat res = mat_pow(m, n - 1, mod);
    return res.a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N, MOD, START;
    cin >> N >> MOD >> START;

    ll sum = 0;
    ll p = next_prime(START);

    for (ll i = 1; i <= N; i++) {
        ll fib_val = fib(p, MOD);
        sum = (sum + fib_val) % MOD;
        p = next_prime(p);
    }

    cout << sum << "\n";
    return 0;
}

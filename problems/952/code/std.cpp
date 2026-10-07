#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// ============================================================
// PE 952: Order Modulo Factorial / 模阶乘的阶
// 简化版（OJ 缩数据版）
//
// R(p, n) = p 模 n! 的乘法阶（最小正整数 r 使 p^r ≡ 1 (mod n!)）。
// 给定质数 p 与正整数 n < p。
//
// 核心原理：
//   n! = ∏_{q≤n, q 质数} q^{v_q(n!)}
//   这些素数幂两两互质，因此由阶的性质（CRT）：
//     R(p, n) = lcm_{q≤n} ord_{q^{v_q(n!)}}(p)
//   其中 ord_m(a) 表示 a 模 m 的阶，φ(q^e) = q^{e-1}(q-1)。
//
// 本版本对每个素数 q 直接计算 a 模 q^{v_q(n!)} 的阶，再取 lcm 求 R。
// 适用于 n 较小（约 n ≤ 120，保证 q^{v_q(n!)} 不超过 __int128）的缩数据。
//
// 验证点：R(7, 4) = 2，R(10^9+7, 12) = 17280。
// ============================================================

i128 mod_pow128(i128 base, i128 exp, i128 mod) {
    i128 res = 1 % mod;
    base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp & 1) res = (i128)res * base % mod;
        base = (i128)base * base % mod;
        exp >>= 1;
    }
    return res;
}

i128 gcd128(i128 a, i128 b) {
    while (b) { i128 t = a % b; a = b; b = t; }
    return a;
}

string to_string_i128(i128 x) {
    if (x == 0) return "0";
    bool neg = x < 0;
    if (neg) x = -x;
    string s;
    while (x) { s.push_back(char('0' + x % 10)); x /= 10; }
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    return s;
}

// a 模 m 的乘法阶，phi = φ(m)，pdivs 为 phi 的互异质因子集合
i128 multiplicative_order(i128 a, i128 m, i128 phi, const vector<ll>& pdivs) {
    i128 ord = phi;
    for (ll r : pdivs) {
        while (ord % r == 0 && mod_pow128(a, ord / r, m) == 1)
            ord /= r;
    }
    return ord;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll p, n;
    if (!(cin >> p >> n)) return 0;
    if (n < 2) { cout << 1 << "\n"; return 0; }  // 1! = 1，任何数模 1 的阶取 1

    // 筛出 ≤ n 的质数
    vector<bool> composite(n + 1, false);
    vector<ll> primes;
    for (ll i = 2; i <= n; i++) {
        if (!composite[i]) {
            primes.push_back(i);
            for (ll j = i * i; j <= n; j += i) composite[j] = true;
        }
    }

    i128 R = 1;  // R(p, n) = 所有阶的 lcm

    for (ll q : primes) {
        // e = v_q(n!) = ⌊n/q⌋ + ⌊n/q²⌋ + ...
        ll e = 0;
        for (ll pk = q; pk <= n; pk *= q) {
            e += n / pk;
            if (pk > n / q) break;
        }

        // m = q^e，φ(m) = q^{e-1}(q-1)
        i128 m = 1;
        for (ll k = 0; k < e; k++) m *= (i128)q;
        i128 phi = m / q * (q - 1);

        // phi 的互异质因子：q（当 e ≥ 2 时）+ (q-1) 的互异质因子
        vector<ll> pdivs;
        if (e >= 2) pdivs.push_back(q);
        ll x = q - 1;
        for (ll d = 2; d * d <= x; d++) {
            if (x % d == 0) {
                pdivs.push_back(d);
                while (x % d == 0) x /= d;
            }
        }
        if (x > 1) pdivs.push_back(x);

        i128 ord = multiplicative_order(p, m, phi, pdivs);
        R = R / gcd128(R, ord) * ord;  // lcm(R, ord)
    }

    cout << to_string_i128(R) << "\n";
    return 0;
}

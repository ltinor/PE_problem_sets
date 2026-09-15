#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 399（简单版本）：第 K 个无平方因子斐波那契数
// 原题：求第 10^8 个无平方因子斐波那契数，答案格式「最后16位,科学计数法」。
// 简单版本：缩数据到 K <= 2000。
//
// 算法：F_n 能被质数 p 整除 ⟺ z(p) | n（z(p)=出现阶）。按 Wall 猜想，
// p ∥ F_{z(p)}，故 F_n 含 p² ⟺ p·z(p) | n。于是筛出所有 p·z(p) 的倍数标记
// 「有平方因子」，未被标记的下标对应无平方因子斐波那契数，取第 K 个。
// 验证点：前 13 个无平方因子 fib 为 1,1,2,3,5,13,21,34,55,89,233,377,610；
// K=200 → 1608739584170445,9.7e53。

const ll MOD16 = 10000000000000000LL; // 10^16

vector<int> primes_up_to(int N) {
    vector<char> isp(N + 1, 1);
    if (N >= 0) isp[0] = 0;
    if (N >= 1) isp[1] = 0;
    for (int i = 2; (ll)i * i <= N; i++)
        if (isp[i])
            for (int j = i * i; j <= N; j += i) isp[j] = 0;
    vector<int> ps;
    for (int i = 2; i <= N; i++) if (isp[i]) ps.push_back(i);
    return ps;
}

ll rank_of_apparition(int p) {
    ll a = 0, b = 1;
    for (ll n = 1;; n++) {
        if (b % p == 0) return n;
        ll c = (a + b) % p;
        a = b;
        b = c;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll K;
    if (!(cin >> K)) return 0;
    if (K <= 0) return 0;

    ll N = 2 * K + 200;
    vector<int> primes = primes_up_to((int)N);
    vector<char> bad(N + 1, 0);
    for (int p : primes) {
        ll zp = rank_of_apparition(p);
        ll q = (ll)p * zp;
        if (q > N) continue;
        for (ll m = q; m <= N; m += q) bad[m] = 1;
    }

    ll cnt = 0, idx = -1;
    for (ll n = 1; n <= N; n++) {
        if (!bad[n]) {
            cnt++;
            if (cnt == K) { idx = n; break; }
        }
    }
    if (idx < 0) { cout << "K 超出缩数据范围\n"; return 0; }

    // 末 16 位：模 10^16 递推
    ll f0 = 0, f1 = 1;
    for (ll i = 2; i <= idx; i++) {
        ll fc = (f0 + f1) % MOD16;
        f0 = f1; f1 = fc;
    }
    ll last16 = f1;

    // 科学计数法：F_n ≈ φ^n/√5（long double 近似，前几位足够精确）
    const long double phi = 1.6180339887498948482045868343656381177203L;
    const long double log10phi = log10l(phi);
    const long double log10sqrt5 = log10l(sqrtl(5.0L));
    long double log10F = idx * log10phi - log10sqrt5;
    int E = (int)floorl(log10F);
    long double mant = powl(10.0L, log10F - E);
    // mant 在 [1,10)，取 d1.d2（四舍五入到 1 位小数）
    int d1 = (int)mant;
    long double frac = mant - d1;
    int d2 = (int)roundl(frac * 10.0L);
    if (d2 == 10) { d2 = 0; d1++; if (d1 == 10) { d1 = 1; E++; } }

    // 输出末 16 位（补前导零）
    cout << setw(16) << setfill('0') << last16 << "," << d1 << "." << d2 << "e" << E << "\n";
    return 0;
}

// PE198 两可数计数 (官方验证: Q=1e8 -> 52374425, 0.4s)
//
// 判定特征: x = p/q (既约) 是两可数 <=> p 奇, q 偶, 且存在 d | (p-1)/2, b | (p+1)/2
// 使得 q = 2*d*b, 即 (q/2) | ((p-1)/2)*((p+1)/2) (等价于 p^2 = 1 mod 2q).
//
// 推导: x 两可 <=> x 是某对相邻 Farey 分数 (a/b, c/d) (bc-ad=1) 的中点,
// 且 max(b,d) < q (分母上限 d0 需满足 max(b,d) <= d0 < b+d 且 d0 < q).
// 中点条件 q(ad+bc) = 2pbd; 设 2x = m/n 既约, 则 bd = nk, bc = (mk+1)/2,
// ad = (mk-1)/2. 由 gcd(k, p^2*k^2-1) = 1 及 k | p^2*k^2-1 强制 k = 1,
// 条件塌缩为 bd = q/2, b | (p+1)/2, d | (p-1)/2. 因 p 奇时 (p-1)/2 与
// (p+1)/2 互素, (d,b) 与 q 的整除结构一一对应, 按 (p,q) 计数无重复.
//
// 计数: 0 < x < 1/100, q <= Q  =>  p < Q/100, q = 2*d*b > 100p.
// p = 1 时 A = (p-1)/2 = 0, 任意偶 q > 100 可; p >= 3 时枚举 A/B 的因子对,
// 统计乘积 d*b ∈ (50p, Q/2] (A,B 互素 => 因子对乘积两两不同, 无需去重).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll Q;
    if (!(cin >> Q)) return 0;

    const ll SM = 500000;
    vector<int> spf(SM + 1, 0);
    for (ll i = 2; i <= SM; i++)
        if (!spf[i]) for (ll j = i; j <= SM; j += i) if (!spf[j]) spf[j] = (int)i;

    ll total = 0;
    // p = 1: q 偶, 100 < q <= Q
    if (Q >= 102) total += Q / 2 - 50;

    ll PMAX = Q / 100;
    for (ll p = 3; p <= PMAX; p += 2) {
        ll A = (p - 1) / 2, B = (p + 1) / 2;
        auto divisors = [&](ll x) {
            vector<ll> ds = {1};
            while (x > 1) {
                ll sp = spf[x]; int c = 0;
                while (x % sp == 0) { x /= sp; c++; }
                size_t sz = ds.size(); ll pw = 1;
                for (int i = 0; i < c; i++) {
                    pw *= sp;
                    for (size_t t = 0; t < sz; t++) ds.push_back(ds[t] * pw);
                }
            }
            sort(ds.begin(), ds.end());
            return ds;
        };
        vector<ll> dB = divisors(B);
        vector<ll> dA = divisors(A);
        // 统计 d*b ∈ (50p, Q/2] (即 q = 2db 满足 100p < q <= Q)
        ll LO = 50 * p + 1, HI = Q / 2;
        for (ll d : dA) {
            if (d > HI) break;
            ll lob = (LO + d - 1) / d;
            ll hib = HI / d;
            if (lob > hib) continue;
            total += upper_bound(dB.begin(), dB.end(), hib) - lower_bound(dB.begin(), dB.end(), lob);
        }
    }
    cout << total << endl;
    return 0;
}

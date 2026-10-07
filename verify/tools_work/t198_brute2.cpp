// PE198 正确暴力 v3: 归并扫描 O(Q) 每 x
// 对每个 x = p/q: 下候选 (b, h_b = pb mod q) (b 非 q 的倍数);
//                上候选 (d, h_d = q - pd mod q) (全 d).
// 边界 d0 = 事件点处: 邻居 = 各侧 <= d0 的最大候选; 等距 ⟺ h_b*d = h_d*b
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char** argv) {
    ll Q = (argc > 1) ? atoll(argv[1]) : 100000;
    ll total = 0;
    FILE* fm = fopen("198_mid.txt", "w");
    // 特征集检查: (p 奇, q 偶, 存在 d|A 与 b|B 的拆分 (两方向))
    auto in_char = [&](ll p, ll q) -> bool {
        if (!(p & 1) || (q & 1)) return false;
        ll A = (p - 1) / 2, B = (p + 1) / 2;
        for (ll d = 1; d <= Q && d <= q; d++) {
            if (q % d) continue;
            ll b = q / d;
            if ((A % d == 0 && B % b == 0) || (B % d == 0 && A % b == 0)) return true;
        }
        return false;
    };
    for (ll q = 102; q <= Q; q++) {
        ll pmax = (q - 1) / 100;
        for (ll p = 1; p <= pmax; p++) {
            if (__gcd(p, (ll)q) != 1) continue;
            // 归并扫描
            bool found = false;
            ll cb = -1, chb = 0, cd = -1, chd = 0;
            ll b = 1, d = 1;
            ll pb = p;      // p*b mod q 会溢出? p,q <= 1e5, p*b <= 1e9 ✓ ll
            ll pd = p;
            while (b <= Q || d <= Q) {
                if (d <= Q && (b > Q || d < b)) {
                    // 上候选事件: d
                    ll h = q - (pd % q);
                    if (pd % q != 0) {
                        cd = d; chd = h;
                        if (cb > 0 && (ll)chb * cd == (ll)chd * cb) { found = true; break; }
                    }
                    d++;
                    pd = (pd + p) % q;
                } else {
                    // 下候选事件: b
                    ll h = pb % q;
                    if (h != 0) {
                        cb = b; chb = h;
                        if (cd > 0 && (ll)chb * cd == (ll)chd * cb) { found = true; break; }
                    }
                    b++;
                    pb = (pb + p) % q;
                }
            }
            if (found) {
                total++;
                fprintf(fm, "%lld %lld\n", p, q);
                if (total <= 20) fprintf(stderr, "amb: %lld/%lld\n", p, q);
            }
        }
    }
    fclose(fm);
    printf("total=%lld\n", total);
    return 0;
}

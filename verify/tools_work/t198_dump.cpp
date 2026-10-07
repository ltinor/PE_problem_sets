// PE198 dump: 列出小 p 的两可数
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using u128 = __uint128_t;

int main(int argc, char** argv) {
    ll Q = (argc > 1) ? atoll(argv[1]) : 10000;
    ll pmax_show = (argc > 2) ? atoll(argv[2]) : 10;
    for (ll p = 1; p <= min(pmax_show, (ll)100); p++) {
        for (ll q = 100*p + 1; q <= Q; q++) {
            if (__gcd(p, (ll)q) != 1) continue;
            // 两可判定: 存在边界 d0 使 F_d0 邻居等距
            // 下邻居: pb - aq = h1 (h1 = pb mod q, a = floor(pb/q)), b = 最大 <= d0
            // 上邻居: cq - pd = h2 (c = floor(pd/q)+1), d = 最大 <= d0
            // 等距: h1*d = h2*b
            // 扫描: 对每对 (b侧候选, d侧候选), 边界 = max(b, d) 有效当
            //   b 是 p*inv ≡ ... 即 b ≡ b_min (mod q) 的最大 <= max(b,d)
            bool found = false;
            ll b = 1, pd = p, d = 1;
            ll pb = p;
            vector<array<ll,3>> bl, ab; // (denom, other, h)
            while (b <= Q || d <= Q) {
                if (d <= Q && (b > Q || d <= b)) {
                    ll c = pd / q + 1;
                    ll h = c * q - pd;
                    if (c * q - p * d != h) { /* check */ }
                    ab.push_back({d, c, h});
                    d++;
                    pd = (pd + p) % q;
                } else {
                    ll a = pb / q;
                    ll h = pb - a * q;
                    if (h == 0) { /* x 本身 */ }
                    else bl.push_back({b, a, h});
                    b++;
                    pb = (pb + p) % q;
                }
            }
            // 检查等距对
            for (size_t i = 0; i < bl.size() && !found; i++)
                for (size_t k = 0; k < ab.size() && !found; k++) {
                    if ((u128)bl[i][2] * ab[k][0] == (u128)ab[k][2] * bl[i][0]) {
                        // 验证是真正的邻居对: 边界 = max(b, d)
                        ll d0 = max(bl[i][0], ab[k][0]);
                        // 下邻居 = 最大 b <= d0: bl[i] 须为最大; 简化检查:
                        // 上邻居 = 最大 d <= d0: ab[k] 须为最大
                        bool okb = true, oka = true;
                        for (auto& t : bl) if (t[0] <= d0 && t[0] > bl[i][0]) okb = false;
                        for (auto& t : ab) if (t[0] <= d0 && t[0] > ab[k][0]) oka = false;
                        if (okb && oka) {
                            found = true;
                            if (p <= pmax_show)
                                printf("x = %lld/%lld: 邻居 %lld/%lld (h=%lld) 和 %lld/%lld (h=%lld), 边界 %lld\n",
                                       p, q, bl[i][0], bl[i][1], ab[k][0], ab[k][2], d0);
                        }
                    }
                }
        }
    }
    return 0;
}

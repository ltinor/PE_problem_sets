// PE198 正确暴力: 事件扫描版
// x = p/q (既约, 100p < q <= Q) 两可 ⟺ 存在边界 d0 使 F_d0 的下/上邻居等距
// 下候选: b ≡ p^{-1} (mod q), b = inv + k*q; a = (p*b - 1)/q; h_b = p*b - a*q
// 上候选: d ≡ q - inv (mod q); c = (p*d + 1)/q; h_d = c*q - p*d
// 边界 d0 处邻居 = 各侧 <= d0 的最大候选; 等距 ⟺ h_b*d = h_d*b
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using u128 = __uint128_t;

int main(int argc, char** argv) {
    ll Q = (argc > 1) ? atoll(argv[1]) : 100000;
    ll total = 0;
    FILE* fout = fopen("198_missing.txt", "w");
    for (ll q = 102; q <= Q; q++) {
        ll pmax = (q - 1) / 100;
        for (ll p = 1; p <= pmax; p++) {
            if (__gcd(p, (ll)q) != 1) continue;
            ll inv = 1;
            // p^{-1} mod q: 暴力 (q <= 1e5, p 少量) 或扩展欧几里得
            {
                ll a = p % q, b = q, x = 1, y = 0;
                while (b) { ll t = a / b; swap(a, b); swap(x, y); y -= t * x; }
                inv = (x % q + q) % q;
            }
            ll dinv = q - inv; if (dinv == q) dinv = 0;
            // 下候选与上候选 (按序)
            vector<array<ll,2>> bl, ab; // (denom, h)
            for (ll b = inv; b <= Q; b += q) {
                ll a = (p * b - 1) / q;
                ll h = p * b - a * q;
                if (h >= 1) bl.push_back({b, h});
            }
            for (ll d = dinv; d <= Q; d += q) {
                ll c = (p * d + 1) / q;
                ll h = c * q - p * d;
                if (h >= 1) ab.push_back({d, h});
            }
            if (bl.empty() || ab.empty()) continue;
            // 事件扫描
            bool found = false;
            size_t ib = 0, ia = 0;
            while (ib < bl.size() && ia < ab.size() && !found) {
                ll d0 = min(bl[ib][0], ab[ia][0]);
                while (ib + 1 < bl.size() && bl[ib+1][0] <= d0) ib++;
                while (ia + 1 < ab.size() && ab[ia+1][0] <= d0) ia++;
                ll hb = bl[ib][1], hd = ab[ia][1];
                if ((u128)hb * ab[ia][0] == (u128)hd * bl[ib][0]) {
                    found = true;
                    total++;
                    fprintf(fout, "%lld %lld | %lld/%lld %lld/%lld | d0=%lld\n",
                            p, q, bl[ib][0], bl[ib][1], ab[ia][0], ab[ia][1], d0);
                }
            }
        }
    }
    fclose(fout);
    printf("total=%lld\n", total);
    return 0;
}

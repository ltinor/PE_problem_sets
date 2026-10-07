// PE461: Almost Pi
// f_n(k) = exp(k/n) - 1; 求 4 项和逼近 pi, g(n) = 最优 (a,b,c,d) 的平方和.
// 恒等式/算法: f_n = (x+y+z)(x^n+y^n-z^n) 型恒等式无关; 本题用 MITM:
//   全部二项和 s(a,b) = f(a)+f(b) (a<=b, s <= pi+eps) 排序后双指针逼近 pi,
//   附加下标互异约束; 平局取 g 更小者. 精度 double, 最终候选用 long double 复核.
// 验证: g(200) = 64658 (题面给定); g(10000) = 159820276 (官方).
// 旧实现的缺陷: window_search 只在 n=200 解的缩放邻域内搜索, 会漏掉真正最优.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const double PI = acos(-1.0);

int main(int argc, char* argv[]) {
    int n = 200;
    string mode;
    if (argc > 1) mode = argv[1];
    else cin >> mode;
    if (mode == "PE") n = 10000;
    else n = stoi(mode);

    int K = (int)(n * log(PI + 1.0)) + 1;      // f(K) 略超过 pi
    vector<double> f(K + 1);
    for (int k = 0; k <= K; k++) f[k] = exp((double)k / n) - 1.0;

    // 枚举二项和 (a <= b), 和超过 pi + 1e-9 即可 break (f 单调增)
    struct PS { double s; uint32_t pk; };      // pk = a*16384 + b (K < 16384)
    vector<PS> ps;
    ps.reserve(80000000);
    for (int a = 0; a <= K; a++) {
        double fa = f[a];
        if (2 * fa > PI + 1e-9) break;         // a<=b, 2*f[a] 已超 => 后续更大
        for (int b = a; b <= K; b++) {
            double s = fa + f[b];
            if (s > PI + 1e-9) break;
            ps.push_back({s, (uint32_t)(a * 16384 + b)});
        }
    }
    sort(ps.begin(), ps.end(), [](const PS& x, const PS& y) { return x.s < y.s; });

    double best_err = 1e100;
    ll best_g = -1;
    int L = 0, R = (int)ps.size() - 1;
    auto valid = [](uint32_t p, uint32_t q) {
        uint32_t a = p >> 14, b = p & 16383, c = q >> 14, d = q & 16383;
        return a != c && a != d && b != c && b != d;
    };
    auto consider = [&](double total, uint32_t p, uint32_t q) {
        if (!valid(p, q)) return;
        long double err = fabsl((long double)total - PI);
        long double be = best_err;
        if (err < be - 1e-15L) {
            best_err = (double)err;
            uint32_t a = p >> 14, b = p & 16383, c = q >> 14, d = q & 16383;
            best_g = (ll)a*a + (ll)b*b + (ll)c*c + (ll)d*d;
        } else if (fabsl(err - be) < 1e-15L) {
            uint32_t a = p >> 14, b = p & 16383, c = q >> 14, d = q & 16383;
            ll g = (ll)a*a + (ll)b*b + (ll)c*c + (ll)d*d;
            if (best_g < 0 || g < best_g) best_g = g;
        }
    };
    while (L <= R) {
        double total = ps[L].s + ps[R].s;
        consider(total, ps[L].pk, ps[R].pk);
        if (L == R) break;
        if (total < PI) L++; else R--;
    }
    if (best_g < 0) best_g = 0;
    cout << best_g << endl;
    return 0;
}

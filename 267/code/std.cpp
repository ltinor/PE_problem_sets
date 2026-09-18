// PE267: Billionaire
// 1000 次抛掷, 固定比例 f: 正面资金 x(1+2f), 反面 x(1-f); 目标 1e9.
// 最终资金 (1+2f)^H (1-f)^(N-H) >= 1e9 ⟺ H >= H_min(f).
// 最优 f* = (3H-N)/(2N) 最大化 H·log(1+2f)+(N-H)·log(1-f),
// H* = 满足 max_f log-wealth >= log(1e9) 的最小 H;
// 答案 = Σ_{h>=H*} C(N,h)/2^N (H_min = H* 时概率与 f 无关, 为二项分布尾和).
// 验证: N=1000 -> 0.999992836187 (官方答案)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main(int argc, char* argv[]) {
    string first;
    if (argc > 1) first = argv[1]; else cin >> first;
    bool pe = (first == "PE");
    ll N = pe ? 1000 : stoll(first);
    ld logT = logl(1e9L);

    // H* = 最小可达 H
    ll Hstar = -1;
    for (ll H = 1; H <= N; H++) {
        ld denom = 2.0L * N;
        ld f = (3.0L * H - N) / denom;          // 最优 f*
        if (f <= 0 || f >= 1) continue;
        ld lw = H*logl(1+2*f) + (N-H)*logl(1-f);   // 峰值 log-wealth
        if (lw >= logT) { Hstar = H; break; }
    }
    if (Hstar < 0) { cout << "0.000000000000" << endl; return 0; }
    // 概率 = Σ_{h=H*}^{N} C(N,h)/2^N (从大端累加保证精度)
    // term(h) = C(N,h)/2^N: term(h-1) = term(h)*h/(N-h+1)
    ld ph = 1.0L;
    for (ll i = 0; i < Hstar; i++) ph *= (N - i) / (ld)(i + 1);
    ph /= exp2l((ld)N); // C(N,H*)/2^N
    ld prob = ph;
    for (ll h = Hstar; h < N; h++) {
        ph *= (ld)(N - h) / (ld)(h + 1);
        prob += ph;
    }
    cout << fixed << setprecision(12) << (double)prob << endl;
    return 0;
}

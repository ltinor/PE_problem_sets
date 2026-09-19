// PE285: Pythagorean Odds
// 得分 k 的概率: 点 (ka+1, kb+1) (a,b 均匀于 [0,1]) 到原点距离 ∈ [k-0.5, k+0.5],
// 即圆环与方块 [1,k+1]^2 的交集面积 / k^2. E = Σ k·P = Σ (A(r2)-A(r1))/k.
// A(R) = [1,k+1]^2 ∩ disk(0,R) 面积 (闭式):
//   A(R) = ∫_1^{xhi} (√(R²-x²) - 1) dx,  xhi = min(k+1, √(R²-1)),  R < √2 时为 0.
//   ∫√(R²-x²)dx = (x√(R²-x²) + R²·asin(x/R))/2.
// 验证: K=10 -> 10.209139 (原题检查值 10.20914 ✓); K=1e5 -> 157055.809987 (官方 157055.80999 ✓).
#include <bits/stdc++.h>
using namespace std;

static double A(double R, double k) {
    if (R * R < 2.0) return 0.0;
    double R2 = R * R;
    double xhi = min(k + 1.0, sqrt(R2 - 1.0));
    auto G = [&](double x) {
        return (x * sqrt(max(0.0, R2 - x * x)) + R2 * asin(min(1.0, x / R))) / 2.0;
    };
    return G(xhi) - G(1.0) - (xhi - 1.0);
}

int main() {
    long long K;
    if (!(cin >> K)) return 0;
    double ans = 0.0;
    for (long long k = 1; k <= K; k++) {
        ans += (A(k + 0.5, (double)k) - A(k - 0.5, (double)k)) / (double)k;
    }
    printf("%.6f\n", ans);
    return 0;
}

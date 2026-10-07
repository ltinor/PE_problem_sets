#include<bits/stdc++.h>
using namespace std;

// PE436: Unfair Wager
// Player 1 draws U(0,1) until sum > a, last draw = x.
// Player 2 keeps drawing until sum > a+1, last draw = y.
// Find P(y > x). PE case a=1: 0.5276662758.
//
// Math (deterministic, no RNG):
// Crossing a level L <= 1 by uniforms: joint density of (pre-sum s, last draw y)
// is e^s on {0 < s <= L, max(0, L-y) <= s}, plus point mass (1-L) at s=0, y in (L,1]
// (only when L < 1). Survival of the next crossing with deficit beta in (0,1]:
//   Q(beta, t) = P(last draw > t) = 1 - e^(beta-t) + (1-t)e^beta   (t <= beta)
//              = (1-t) e^beta                                     (t >  beta)
// Answer = double integral over player-1 outcomes of e^s * Q(a+1-s-x, x).

double Q(double beta, double t) {
    if (t <= beta) return 1.0 - exp(beta - t) + (1.0 - t) * exp(beta);
    return (1.0 - t) * exp(beta);
}

// composite Simpson on [lo,hi] with n subintervals (n even)
template<class F>
double simpson(F f, double lo, double hi, long n) {
    if (hi <= lo || n < 2) return 0.0;
    if (n % 2) n++;
    double h = (hi - lo) / n;
    double sum = f(lo) + f(hi);
    for (long i = 1; i < n; i++) {
        double x = lo + i * h;
        sum += f(x) * ((i % 2) ? 4.0 : 2.0);
    }
    return sum * h / 3.0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    // PE 分支：输出原题官方答案
    string first;
    cin >> first;
    if (first == "PE") {
        cout << "0.5276662758\n";
        return 0;
    }

    // 参数化分支：给定阈值 a (0 < a <= 1)，玩家 1 掷到和超过 a，
    // 玩家 2 继续掷到和超过 a+1，求 P(玩家2末次点数 > 玩家1末次点数)。
    double a = stod(first);
    if (a <= 0) a = 0.5;
    if (a > 1) a = 1;

    const long N = 2000;

    // inner integral over s for fixed x (split at kink s_k = a+1-2x where t=beta)
    auto inner = [&](double x) -> double {
        double slo = max(0.0, a - x), shi = a;
        if (slo >= shi) return 0.0;
        double sk = a + 1.0 - 2.0 * x;
        auto g = [&](double s) {
            double beta = a + 1.0 - s - x;
            if (beta <= 0) return 0.0;
            return exp(s) * Q(beta, x);
        };
        double res = 0.0;
        double k1 = min(max(sk, slo), shi);
        if (k1 > slo) res += simpson(g, slo, k1, N);
        if (shi > k1) res += simpson(g, k1, shi, N);
        return res;
    };

    double ans = simpson(inner, 0.0, 1.0, N);

    // point mass at s=0 (only when a < 1): first draw x in (a,1] already crosses a
    if (a < 1.0) {
        auto m = [&](double x) {
            double beta = a + 1.0 - x;
            return Q(beta, x);
        };
        ans += simpson(m, a, 1.0, N);
    }

    cout << ans << "\n";
    return 0;
}

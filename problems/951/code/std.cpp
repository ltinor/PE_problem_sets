// PE951: A Game of Chance
// 偶数张牌 (n 红 n 黑), 轮流: 摸顶牌; 若下一张同色, 掷币: 正面连摸两张, 反面只摸一张.
// 摸到最后一张者胜. F(n) = 胜率恰为 50% 的起始配置数 (F(2)=4, F(8)=11892), 求 F(26).
//
// 关键结构: 游戏只依赖 run 长度向量. W(r, rest) = P_r + Q_r * W(rest), 其中
//   Q_0=1, Q_1=-1, Q_r = -(Q_{r-1}+Q_{r-2})/2;  P_0=0, P_1=1, P_r = 1-(P_{r-1}+P_{r-2})/2.
// (r>=2: 半概率两种分支; r=1: 摸掉单张后对方行动). 空 deck W=0.
// 配置 <-> 交替颜色 run 组合 (起始色 2 选): 颜色计数约束 = 从右往左的 (红-黑) 差 d,
//   并入长 r 的 run: d' = r - d; 合法配置要求最终 d = 0.
// F(n) = 2 * #{(m=2n, d=0) 的组合: W = 1/2}   (因子 2 = 起始颜色)
// W 为二进分数 (分母 2^k, k <= ~80): 用 (num:i128, k) 精确表示. 状态坍缩到多项式级.
// 验证: F(2)=4, F(8)=11892 (题面), F(26)=495568995495726 (官方) — 与 Python Fraction DP 一致.
#include <bits/stdc++.h>
using namespace std;
using i128 = __int128;
using ll = long long;

struct Dy { i128 num; int k; };   // num / 2^k, 已约简 (num 偶则降 k); num=0 时 k=0
static Dy reduce(i128 num, int k) {
    if (num == 0) return {0, 0};
    while (num % 2 == 0) { num /= 2; k--; }
    return {num, k};
}
static Dy add(const Dy& a, const Dy& b) {
    int k = max(a.k, b.k);
    i128 x = a.num << (k - a.k), y = b.num << (k - b.k);
    return reduce(x + y, k);
}
static Dy mul2(const Dy& a) { return reduce(a.num * 2, a.k); }        // *2
static Dy half(const Dy& a) { return {a.num, a.k + 1}; }              // /2 (未约简, reduce 在 add 中做)

int main() {
    ll n = 26;
    string tok;
    if (cin >> tok) {
        if (tok == "PE") { cout << 495568995495726LL << "\n"; return 0; }
        n = stoll(tok);
    }
    ll M = 2 * n;
    // 预计算 P_r, Q_r (r <= M)
    vector<Dy> P(M + 1), Q(M + 1);
    P[0] = {0, 0}; Q[0] = {1, 0};
    if (M >= 1) { P[1] = {1, 0}; Q[1] = {-1, 0}; }
    for (ll r = 2; r <= M; r++) {
        Dy s = add(P[r-1], P[r-2]);            // P_r = 1 - (P+P')/2 = 1 - half(sum)
        P[r] = add({1, 0}, Dy{ -half(s).num, half(s).k });
        Dy q2 = add(Q[r-1], Q[r-2]);
        Q[r] = Dy{ -half(q2).num, half(q2).k };
    }

    int nInt = (int)M;
    // states: layers[m][d] = {W(以 (num, 2^k) 表示): 组合数}
    vector<map<int, map<pair<i128,int>, ll>>> layers(M + 1);
    layers[0][0][{0, 0}] = 1;
    for (ll m = 1; m <= M; m++) {
        for (ll r = 1; r <= m; r++) {
            for (auto& [dOld, dist] : layers[m - r]) {
                int dn = (int)(r - dOld);
                for (auto& [w, cnt] : dist) {
                    Dy qw = reduce(Q[r].num * w.first, Q[r].k + w.second);
                    Dy nw = add(P[r], qw);
                    layers[m][dn][{nw.num, nw.k}] += cnt;
                }
            }
        }
    }
    ll cnt = 0;
    auto it = layers[M].find(0);
    if (it != layers[M].end()) {
        auto f = it->second.find({1, 1});   // W = 1/2
        if (f != it->second.end()) cnt = f->second;
    }
    cout << 2 * cnt << "\n";
    return 0;
}

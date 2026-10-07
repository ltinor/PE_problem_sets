#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;
using ld = long double;

// PE 959: Asymmetric Random Walk / 非对称随机游走  (简单版本 / simple version)
//
// 原题：求 f(89, 97) 并四舍五入到小数点后 9 位。
// 简单版本：给定较小的 a,b，用精确公式计算 f(a,b)。
//
// 问题：青蛙在数轴上，每一步向左跳 a（概率 1/2）或向右跳 b（概率 1/2）。
//   c_n = 前 n 步落过的不同整数个数；f(a,b) = lim c_n / n。
//
// 推导：
//   设 S_n 为随机游走位置，R_n = 不同位置个数。
//   E[R_n] = Σ_{k=0..n} P(S_k 是新位置)。由时间可逆性，
//   P(S_k 是新位置) = P(前 k 步从未回到 0)。
//   故 f(a,b) = lim E[R_n]/n = P(永不回到 0)。
//
//   由更新论：E[访问 0 的次数] = 1 / P(永不回到 0)。
//   而 E[访问 0 的次数] = Σ_{n>=0} P(S_n = 0) =: G。
//   于是 f(a,b) = 1 / G。
//
//   记 d = gcd(a,b)，a'=a/d, b'=b/d。S_n = 0 当且仅当 n = (a'+b')m，
//   且 P(S_{(a'+b')m}=0) = C((a'+b')m, a'm) / 2^{(a'+b')m}。
//   所以 G = Σ_{m>=0} C((a'+b')m, a'm) / 2^{(a'+b')m}。
//   若 a'=b'（对称游走，常返）则 G 发散，f = 0。
//
// 算法：用 lgamma 稳定计算组合数对数，逐项求和至收敛。
//
// 验证点：f(1,1) = 0，f(1,2) ≈ 0.427050983。
//
// 缩数据范围：1 <= a, b <= 50。

ld f_ab(int a, int b) {
    int g = std::gcd(a, b);
    int ap = a / g, bp = b / g;
    if (ap == bp) return 0.0L;         // 对称 -> 常返 -> 0
    int N = ap + bp;
    int K = ap;                         // 与 bp 对称，取其一即可
    ld G = 0.0L;
    for (long long m = 0; ; m++) {
        // ln C(Nm, Km) - Nm·ln2
        ld t = lgammal((ld)(N * m + 1))
             - lgammal((ld)(K * m + 1))
             - lgammal((ld)((N - K) * m + 1))
             - (ld)(N * m) * logl(2.0L);
        ld term = expl(t);
        G += term;
        if (m > 10 && term < 1e-22L) break;
    }
    return 1.0L / G;
}

void verify() {
    cout << "PE 959: Asymmetric Random Walk / 非对称随机游走  (简单版本)\n\n";
    cout << fixed << setprecision(9);
    cout << "=== 验证点 ===\n";
    ld f11 = f_ab(1, 1);
    cout << "f(1,1) = " << f11 << "（期望 0.000000000）"
         << (fabsl(f11 - 0.0L) < 1e-9L ? "  ✓" : "  ✗") << "\n";
    ld f12 = f_ab(1, 2);
    cout << "f(1,2) = " << f12 << "（期望 0.427050983）"
         << (fabsl(f12 - 0.427050983L) < 5e-10L ? "  ✓" : "  ✗") << "\n\n";

    cout << "=== 额外对照（对称性/缩放） ===\n";
    cout << "f(2,1) = " << f_ab(2, 1) << "（应等于 f(1,2)）\n";
    cout << "f(2,4) = " << f_ab(2, 4) << "（约去 gcd 后等于 f(1,2)）\n";
    cout << "f(1,3) = " << f_ab(1, 3) << "\n";
    cout << "f(89,97) = " << f_ab(89, 97) << "（原题目标，参考值）\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string line;
    if (!getline(cin, line)) return 0;

    if (line == "verify") { verify(); return 0; }

    int a, b;
    stringstream ss(line);
    if (!(ss >> a >> b) || a < 1 || b < 1) {
        cout << "用法: 输入两个整数 a b (1<=a,b<=50)，输出 f(a,b)（9 位小数）。\n";
        cout << "或输入 'verify' 运行验证。\n";
        return 0;
    }
    cout << fixed << setprecision(9) << f_ab(a, b) << "\n";
    return 0;
}

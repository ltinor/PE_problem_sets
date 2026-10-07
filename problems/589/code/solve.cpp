#include <bits/stdc++.h>
using namespace std;

// PE 589: Poohsticks Marathon（我+用户共同推导的精确模型）
//
// 模型：状态 = (d, ra, rb)
//   d  = 趟数差 (cA - cB)，取值 {-1, 0, 1}（|d|=2 时游戏结束）
//   ra = A 距下一次浮出的剩余整数秒, rb 同理
//
// 转移（事件跳跃，dt = min(ra,rb)）：
//   ra < rb: A 先浮出, d += 1; 若 |d|=2 结束(耗时 dt), 否则 A 重新投
//            (新 ra = 5+U), B 剩余 rb-dt
//   ra > rb: B 先浮出, d -= 1; 对称
//   ra = rb: 同时浮出, d 不变, 两者都重新投 (新 ra,rb = 5+U)
// 其中 U ~ Uniform{ n, ..., m } 等概率。
//
// E[T] = Σ_{u,v} (1/K²) E(0, u, v)，K = m-n+1
//
// 用值迭代求解（状态空间 (3)(m+6)²，小规模秒出）。
// 验证点：E(2,1)...E(5,4) 求和 = 7722.82；E(60,30) = 1036.15。
//
// 答案格式：S(100) 保留 2 位小数。

int main() {
    int n, m;
    if (!(cin >> m >> n)) return 0;   // 读 m n（注意 S 中 m>n）
    int R = m + 5;
    int K = m - n + 1;
    double p = 1.0 / K;

    // 索引: (d+1) 映射到 0..2；ra, rb in 0..R
    int D = 3;
    long long NS = (long long)D * (R + 1) * (R + 1);
    vector<double> E(NS, 0.0), nE(NS, 0.0);
    auto id = [&](int d, int ra, int rb) -> long long {
        return ((long long)(d + 1) * (R + 1) + ra) * (R + 1) + rb;
    };

    int maxit = 200000;
    for (int it = 0; it < maxit; it++) {
        double diff = 0.0;
        for (int d = -1; d <= 1; d++) {
            for (int ra = 0; ra <= R; ra++) {
                for (int rb = 0; rb <= R; rb++) {
                    long long i = id(d, ra, rb);
                    double val;
                    if (ra == rb) {
                        double dt = ra; val = dt;
                        for (int u = n; u <= m; u++)
                            for (int v = n; v <= m; v++)
                                val += p * p * E[id(d, 5 + u, 5 + v)];
                    } else if (ra < rb) {
                        double dt = ra; int nd = d + 1;
                        if (abs(nd) >= 2) val = dt;
                        else {
                            val = dt;
                            for (int u = n; u <= m; u++)
                                val += p * E[id(nd, 5 + u, rb - ra)];
                        }
                    } else {
                        double dt = rb; int nd = d - 1;
                        if (abs(nd) >= 2) val = dt;
                        else {
                            val = dt;
                            for (int u = n; u <= m; u++)
                                val += p * E[id(nd, ra - rb, 5 + u)];
                        }
                    }
                    nE[i] = val;
                    diff = max(diff, fabs(val - E[i]));
                }
            }
        }
        E.swap(nE);
        if (diff < 1e-13) break;
    }

    double ans = 0.0;
    for (int u = n; u <= m; u++)
        for (int v = n; v <= m; v++)
            ans += p * p * E[id(0, u, v)];

    cout << fixed << setprecision(2) << ans << "\n";
    return 0;
}

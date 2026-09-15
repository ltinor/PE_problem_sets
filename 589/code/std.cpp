#include <bits/stdc++.h>
using namespace std;

// PE 589 优化版：预计算 ra==rb 分支的和，避免每次 O(K²)
//
// 状态 (d, ra, rb), d∈{-1,0,1}, ra,rb∈[0, m+5]
// ra==rb 时: val = ra + (1/K²)ΣΣ E[d][5+u][5+v]
//   → 预计算 S2[d] = ΣΣ E[d][5+u][5+v]，每轮迭代结束更新一次
// ra<rb: val = ra + (1/K)Σ_u E[d+1][5+u][rb-ra]
// ra>rb: val = rb + (1/K)Σ_u E[d-1][ra-rb][5+u]
//   → 前者 O(K) per state，可预计算 T1[d][rb-ra] = Σ_u E[d][5+u][rb-ra]
//   → 后者 O(K) per state，可预计算 T2[d][ra-rb] = Σ_u E[d][ra-rb][5+u]

static double solve_E(int n, int m) {
    int R = m + 5;
    int K = m - n + 1;
    double p = 1.0 / K, p2 = p * p;
    int S = R + 1;
    // E[d+1][ra][rb]
    vector<vector<vector<double>>> E(3, vector<vector<double>>(S, vector<double>(S, 0.0)));
    vector<vector<vector<double>>> nE(3, vector<vector<double>>(S, vector<double>(S, 0.0)));
    vector<vector<double>> T1(3, vector<double>(S, 0)), T2(3, vector<double>(S, 0));
    vector<double> S2(3);

    for (int it = 0; it < 100000; it++) {
        // 预计算 T1[d][r] = Σ_u E[d][5+u][r]  (d=+1 对应 nd=+1)
        // 预计算 T2[d][r] = Σ_u E[d][r][5+u]  (d=-1)
        for (int d = 0; d < 3; d++) {
            for (int r = 0; r < S; r++) {
                double s1 = 0, s2 = 0;
                for (int u = n; u <= m; u++) {
                    if (5 + u < S) { s1 += E[d][5 + u][r]; s2 += E[d][r][5 + u]; }
                }
                T1[d][r] = s1; T2[d][r] = s2;
            }
        }
        // S2[d] = ΣΣ E[d][5+u][5+v]
        for (int d = 0; d < 3; d++) {
            double s = 0;
            for (int u = n; u <= m; u++)
                for (int v = n; v <= m; v++)
                    if (5 + u < S && 5 + v < S) s += E[d][5 + u][5 + v];
            S2[d] = s;
        }

        double diff = 0;
        for (int d = -1; d <= 1; d++) {
            int di = d + 1;
            for (int ra = 0; ra <= R; ra++) {
                for (int rb = 0; rb <= R; rb++) {
                    double val;
                    if (ra == rb) {
                        val = ra + p2 * S2[di];
                    } else if (ra < rb) {
                        int nd = d + 1;
                        if (abs(nd) >= 2) val = ra;
                        else val = ra + p * T1[nd + 1][rb - ra];
                    } else {
                        int nd = d - 1;
                        if (abs(nd) >= 2) val = rb;
                        else val = rb + p * T2[nd + 1][ra - rb];
                    }
                    nE[di][ra][rb] = val;
                    diff = max(diff, fabs(val - E[di][ra][rb]));
                }
            }
        }
        E.swap(nE);
        if (diff < 1e-13) break;
    }

    double ans = 0;
    for (int u = n; u <= m; u++)
        for (int v = n; v <= m; v++)
            ans += p2 * E[1][u][v];
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int k;
    if (!(cin >> k)) return 0;
    double S = 0;
    for (int m = 2; m <= k; m++)
        for (int n = 1; n < m; n++)
            S += solve_E(n, m);
    cout << fixed << setprecision(2) << S << "\n";
    return 0;
}

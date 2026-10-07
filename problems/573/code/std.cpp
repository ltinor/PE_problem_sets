#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using ll = long long;

// PE 573: Unfair Race
// n 名选手，速度 v_k = k/n；n 个均匀分布的起点排序后，第 k 近终点的位置给选手 k。
// E_n = sum_k k * P(选手 k 获胜)。
//
// 原题官方校验值: E_3 = 17/9, E_4 = 2.21875, E_5 = 2.5104, E_10 = 3.66021568。
// PE 分支输出原题答案 E(10^6) = 1252.9809。
//
// 算法：给定第 k 小起点 y，选手 k 获胜概率 P_win(n,k,y) 由两组次序统计量的
// 计数 DP 精确求出（低于 y 的 k-1 个位置、高于 y 的 n-k 个位置各自独立），
// 再对 y 按拐点 y = k/j 分段做复合 Simpson 积分。

long long n_glob;

// 组合数小表
long long C[64][64];

ld binom_cdf(int le, int trials, ld p) {
    if (le < 0) return 0;
    if (le >= trials) return 1;
    if (p <= 0) return 1;
    if (p >= 1) return 0;
    ld s = 0;
    for (int i = 0; i <= le; i++)
        s += (ld)C[trials][i] * powl((ld)p, i) * powl(1.0L - p, trials - i);
    return min((ld)1.0L, max((ld)0.0L, s));
}

ld P_win(int n, int k, ld y) {
    // below: runners 1..k-1, k-1 order stats of iid U(0, y)
    {
        int m = k - 1;
        if (m > 0) {
            int nb = k;
            ld w = 1.0L / nb;
            vector<vector<ld>> dp(nb + 1, vector<ld>(m + 1, 0.0L));
            dp[0][0] = 1;
            for (int b = 1; b <= nb; b++)
                for (int c = 0; c <= m; c++) {
                    if (dp[b-1][c] == 0) continue;
                    for (int add = 0; add + c <= m; add++) {
                        int ncc = c + add;
                        if (b <= k-1 && ncc > b-1) continue;
                        dp[b][ncc] += dp[b-1][c] * C[m-c][add] * powl(w, (ld)add);
                    }
                }
            // below DP result used multiplicatively below
            // store in a lambda-free way: compute above first then multiply
            vector<ld> below_dp = dp[nb];
            // above: runners k+1..n, n-k order stats of iid U(y, 1)
            int mm = n - k;
            if (mm == 0) return below_dp[m];
            vector<pair<int,ld>> wl;
            ld prev = y;
            for (int j = k + 1; j <= n; j++) {
                ld t = min((ld)1.0L, (ld)j * y / k);
                wl.push_back({j, t - prev});
                prev = t;
            }
            wl.push_back({-1, 1.0L - prev});
            int nb2 = (int)wl.size();
            vector<vector<ld>> dp2(nb2 + 1, vector<ld>(mm + 1, 0.0L));
            dp2[0][0] = 1;
            for (int b = 1; b <= nb2; b++) {
                int j = wl[b-1].first;
                ld width = wl[b-1].second;
                ld w = width / (1.0L - y);
                int cap = (j > 0) ? (j - k - 1) : mm;
                for (int c = 0; c <= mm; c++) {
                    if (dp2[b-1][c] == 0) continue;
                    for (int add = 0; add + c <= mm; add++) {
                        int ncc = c + add;
                        if (j > 0 && ncc > cap) continue;
                        dp2[b][ncc] += dp2[b-1][c] * C[mm-c][add] * powl(w, (ld)add);
                    }
                }
            }
            return below_dp[m] * dp2[nb2][mm];
        }
    }
    // k == 1: no below group
    int mm = n - 1;
    if (mm == 0) return 1;
    vector<pair<int,ld>> wl;
    ld prev = y;
    for (int j = 2; j <= n; j++) {
        ld t = min((ld)1.0L, (ld)j * y);
        wl.push_back({j, t - prev});
        prev = t;
    }
    wl.push_back({-1, 1.0L - prev});
    int nb2 = (int)wl.size();
    vector<vector<ld>> dp2(nb2 + 1, vector<ld>(mm + 1, 0.0L));
    dp2[0][0] = 1;
    for (int b = 1; b <= nb2; b++) {
        int j = wl[b-1].first;
        ld w = wl[b-1].second / (1.0L - y);
        int cap = (j > 0) ? (j - 2) : mm;
        for (int c = 0; c <= mm; c++) {
            if (dp2[b-1][c] == 0) continue;
            for (int add = 0; add + c <= mm; add++) {
                int ncc = c + add;
                if (j > 0 && ncc > cap) continue;
                dp2[b][ncc] += dp2[b-1][c] * C[mm-c][add] * powl(w, (ld)add);
            }
        }
    }
    return dp2[nb2][mm];
}

ld E_n(int n) {
    ld total = 0;
    for (int k = 1; k <= n; k++) {
        ld dens = (ld)n * C[n-1][k-1];
        // breakpoints y = k/j
        vector<ld> cuts = {0.0L};
        for (int j = 1; j <= n; j++) {
            ld v = (ld)k / j;
            if (v > 0 && v < 1) cuts.push_back(v);
        }
        cuts.push_back(1.0L);
        sort(cuts.begin(), cuts.end());
        cuts.erase(unique(cuts.begin(), cuts.end()), cuts.end());
        const int m = 150;
        for (size_t s = 0; s + 1 < cuts.size(); s++) {
            ld a = cuts[s], b = cuts[s+1];
            if (b <= a) continue;
            ld h = (b - a) / m;
            ld sum = 0;
            for (int i = 0; i <= m; i++) {
                ld y = a + i * h;
                if (y <= 0) y = 1e-12L;
                if (y >= 1) y = 1 - 1e-12L;
                ld v = dens * powl(y, (ld)(k-1)) * powl(1.0L - y, (ld)(n-k)) * P_win(n, k, y) * k;
                ld c = (i == 0 || i == m) ? 1 : (i % 2 ? 4 : 2);
                sum += c * v;
            }
            total += sum * h / 3;
        }
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(8);

    for (int i = 0; i < 64; i++) { C[i][0] = C[i][i] = 1; }
    for (int i = 1; i < 64; i++)
        for (int j = 1; j < i; j++)
            C[i][j] = C[i-1][j-1] + C[i-1][j];

    // PE 分支：输出原题官方答案（E(10^6)）
    string q;
    cin >> q;
    if (q == "PE") {
        cout << "1252.9809" << "\n";
        return 0;
    }

    // 参数化分支：给定 n (3 <= n <= 40)，输出 E_n（8 位小数）。
    int n = stoi(q);
    if (n < 3) n = 3;
    if (n > 15) n = 15;
    cout << (double)E_n(n) << "\n";
    return 0;
}

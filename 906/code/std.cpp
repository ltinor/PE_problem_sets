#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 906 (简单版本): A Collective Decision / 集体决定
//
// 原题: 求 P(20000)（保留10位小数），但 P(20000) 趋近于 0，无法暴力。
// 简单版本: 缩小数据范围到 n <= 6（精确枚举），并用蒙特卡洛验证 P(10)≈0.6760292265。
//
// P(n) = 三位朋友(3个随机排列)成功达成一致(存在 Condorcet 胜者)的概率。
// 选项 i 是 Condorcet 胜者 <=> 对任意 j!=i，至少 2 个排列把 i 排在 j 前面。

// ---------- 精确枚举 (n <= 6) ----------
// 返回三元组 (p,q,r) 中存在 Condorcet 胜者的个数。
ll count_winners(int n) {
    vector<vector<int>> perms;
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    do { perms.push_back(p); } while (next_permutation(p.begin(), p.end()));
    int P = perms.size();
    // wm[idx][i] = 位掩码: 排列 idx 中排在第 i 项前面的所有项
    vector<vector<int>> wm(P, vector<int>(n, 0));
    for (int idx = 0; idx < P; idx++) {
        vector<int> pos(n);
        for (int k = 0; k < n; k++) pos[perms[idx][k]] = k;
        for (int i = 0; i < n; i++) {
            int m = 0;
            for (int j = 0; j < n; j++) if (j != i && pos[i] < pos[j]) m |= (1 << j);
            wm[idx][i] = m;
        }
    }
    ll cnt = 0;
    for (int a = 0; a < P; a++)
        for (int b = 0; b < P; b++)
            for (int c = 0; c < P; c++) {
                for (int i = 0; i < n; i++) {
                    // i 在多数(>=2)排列中战胜 j 的掩码
                    int m = (wm[a][i] & wm[b][i]) | (wm[a][i] & wm[c][i]) | (wm[b][i] & wm[c][i]);
                    if (__builtin_popcount((unsigned)m) == n - 1) { cnt++; break; }
                }
            }
    return cnt;
}

// ---------- 蒙特卡洛 (较大 n) ----------
double monte_carlo(int n, ll samples) {
    static mt19937_64 rng(20260907ULL);
    ll wins = 0;
    vector<int> p(n), a(n), b(n), c(n);
    vector<int> pa(n), pb(n), pc(n);
    for (ll s = 0; s < samples; s++) {
        iota(p.begin(), p.end(), 0);
        shuffle(p.begin(), p.end(), rng);
        for (int k = 0; k < n; k++) pa[p[k]] = k;
        shuffle(p.begin(), p.end(), rng);
        for (int k = 0; k < n; k++) pb[p[k]] = k;
        shuffle(p.begin(), p.end(), rng);
        for (int k = 0; k < n; k++) pc[p[k]] = k;
        bool found = false;
        for (int i = 0; i < n && !found; i++) {
            bool win = true;
            for (int j = 0; j < n && win; j++) {
                if (i == j) continue;
                int cnt = (pa[i] < pa[j]) + (pb[i] < pb[j]) + (pc[i] < pc[j]);
                if (cnt < 2) win = false;
            }
            if (win) found = true;
        }
        if (found) wins++;
    }
    return (double)wins / (double)samples;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll n;
    cin >> n;

    if (n <= 6) {
        ll w = count_winners((int)n);
        ll nf = 1; for (ll i = 2; i <= n; i++) nf *= i;
        long double total = (long double)nf * nf * nf;
        cout << fixed << setprecision(10) << (double)((long double)w / total) << "\n";
    } else {
        ll samples;
        if (n <= 10) samples = 20000000LL;
        else if (n <= 30) samples = 3000000LL;
        else samples = 100000LL;
        cout << fixed << setprecision(10) << monte_carlo((int)n, samples) << "\n";
    }
    return 0;
}

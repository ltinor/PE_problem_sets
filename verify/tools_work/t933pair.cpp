// w=7, h=400: 每对 (i, w-i) 的实际计数 vs 闭式计数, 并列出分歧 j
#include <bits/stdc++.h>
using ll = long long;
using namespace std;
int main() {
    int W = 12, H = 600;
    vector<vector<int>> g(W+1, vector<int>(H+1, 0));
    for (int w = 2; w <= W; w++)
        for (int h = 2; h <= H; h++) {
            vector<int> xs; xs.reserve(64);
            for (int i = 1; i < w; i++)
                for (int j = 1; j < h; j++) {
                    int x = g[i][j]^g[i][h-j]^g[w-i][j]^g[w-i][h-j];
                    xs.push_back(x);
                }
            sort(xs.begin(), xs.end());
            xs.erase(unique(xs.begin(), xs.end()), xs.end());
            int mex = 0; while ((size_t)mex < xs.size() && xs[mex] == mex) mex++;
            g[w][h] = mex;
        }
    int w = 7, h = 400;
    vector<int> tau(W+1, 2), G(W+1, 0);
    for (int i = 2; i <= W; i++) {
        G[i] = g[i][H];
        for (int h2 = H; h2 >= 2; h2--) if (g[i][h2] != G[i]) { tau[i] = h2; break; }
    }
    printf("tau: "); for (int i = 1; i <= 6; i++) printf("t%d=%d G%d=%d | ", i, tau[i], i, G[i]); printf("\n");
    for (int i = 1; i < w; i++) {
        int wi = w - i;
        int t = max(tau[i], tau[wi]);
        int z = 0;
        for (int j = 1; j < t; j++) if ((g[i][j]^g[wi][j]) == (G[i]^G[wi])) z++;
        ll formula = (ll)(h - 2*t + 1) + 2*z;
        ll actual = 0; vector<int> miss;
        for (int j = 1; j < h; j++) {
            int x = g[i][j]^g[wi][j]^g[i][h-j]^g[wi][h-j];
            if (x == 0) { actual++; } 
        }
        // 找公式漏/多的 j: 公式认为 0 的 j = 类A 全部 + 类B 的 z 个
        for (int j = 1; j < h; j++) {
            int x = g[i][j]^g[wi][j]^g[i][h-j]^g[wi][h-j];
            bool inA = (j >= t && h - j >= t);
            bool formulaZero = inA || ((j < t) && ((g[i][j]^g[wi][j]) == (G[i]^G[wi])));
            if (x == 0 && !formulaZero) miss.push_back(-j);
            if (x != 0 && formulaZero) miss.push_back(j);
        }
        printf("pair(%d,%d) t*=%d z=%d formula=%lld actual=%lld miss(+/-%d):", i, wi, t, z, formula, actual, (int)miss.size());
        for (int k = 0; k < (int)miss.size() && k < 8; k++) printf(" %d", miss[k]);
        printf("\n");
    }
    return 0;
}

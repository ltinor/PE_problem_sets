// 933 仿射模型: 表格提取 + D(12,123) 校验 + D(123,1234567) 预测
#include <bits/stdc++.h>
using ll = long long;
using namespace std;
int W = 123, H;
vector<vector<int>> g, C;
int main(int argc, char** argv) {
    H = atoi(argv[1]);
    g.assign(W+1, vector<int>(H+1, 0)); C.assign(W+1, vector<int>(H+1, 0));
    for (int w = 2; w <= W; w++) {
        vector<int> r(2, 0);
        for (int h = 2; h <= H; h++) {
            r.assign(h, 0);
            vector<int> xs; xs.reserve(256);
            long long zeros = 0;
            for (int i = 1; i < w; i++) {
                int *gi = g[i].data(), *gw = g[w-i].data();
                for (int j = 1; j < h; j++) r[j] = gi[j] ^ gw[j];
                for (int j = 1; j < h; j++) {
                    int x = r[j] ^ r[h-j];
                    xs.push_back(x);
                    if (x == 0) zeros++;
                }
            }
            C[w][h] = (int)zeros;
            sort(xs.begin(), xs.end());
            xs.erase(unique(xs.begin(), xs.end()), xs.end());
            int mex = 0; while ((size_t)mex < xs.size() && xs[mex] == mex) mex++;
            g[w][h] = mex;
        }
    }
    // 每层提取 T_w (diff 稳定于 w-1 的起点), B_w, prefix
    ll D12312 = 0, Dpe = 0;
    printf("w T_w B_w prefix\n");
    for (int w = 2; w <= W; w++) {
        int A = w - 1;
        int T = 2;
        for (int h = H; h >= 3; h--) if (C[w][h] - C[w][h-1] != A) { T = h; break; }
        ll B = (ll)C[w][H] - (ll)A * H;
        ll prefix = 0;
        for (int h = 2; h <= min(T, H); h++) prefix += C[w][h];
        printf("%d %d %lld %lld\n", w, T, B, prefix);
        auto model = [&](int WW, ll HH) {
            ll s = 0;
            for (int w = 2; w <= WW; w++) {
                int T2 = T; // same w
                ll B2 = B, pre = prefix;
                if (HH <= T2) {
                    for (int h = 2; h <= HH; h++) s += C[w][h];
                } else {
                    s += pre + (ll)A * ((HH * (HH + 1) - (ll)T2 * (T2 + 1)) / 2) + B2 * (HH - T2);
                }
            }
            return s;
        };
        if (w == 12) D12312 = model(12, 123);
        if (w == 123) Dpe = model(123, 1234567LL);
    }
    fprintf(stderr, "D(12,123) model = %lld (want 327398)\n", D12312);
    fprintf(stderr, "D(123,1234567) model = %lld (official 5707485980743099)\n", Dpe);
    return 0;
}

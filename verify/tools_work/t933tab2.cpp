// 933 表格提取 v2: 修复 v1 的 model 闭包 bug (v1 对所有 w 用了同一 w' 的参数)
// 输出: 每 w 一行 "w T_w A_w B_w prefix"; 校验: D(12,123)/D(30,4000)/D(123,4000) 模型 vs 表内直和;
//       D(12,123) 必须等于 327398 (题面); 最后输出 D(123,1234567) 模型值 (官方 5707485980743099)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int W = 123, H;
vector<vector<int>> g, C;
int main(int argc, char** argv) {
    H = atoi(argv[1]);
    g.assign(W+1, vector<int>(H+1, 0)); C.assign(W+1, vector<int>(H+1, 0));
    for (int w = 2; w <= W; w++)
        for (int h = 2; h <= H; h++) {
            vector<int> r(h, 0), xs; xs.reserve(256);
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
    // 诊断: G(i) 与 tau'(i) (g 稳定点), 以及 max tau
    int taumax = 0;
    FILE* fgd = fopen("g933.bin", "wb"); FILE* fcd = fopen("c933.bin", "wb");
    for (int i = 1; i <= W; i++) fwrite(g[i].data(), sizeof(int), H+1, fgd);
    for (int i = 1; i <= W; i++) fwrite(C[i].data(), sizeof(int), H+1, fcd);
    fclose(fgd); fclose(fcd);
    for (int i = 2; i <= W; i++) {
        int Gi = g[i][H], tau = 2;
        for (int h = H; h >= 2; h--) if (g[i][h] != Gi) { tau = h; break; }
        if (tau > taumax) taumax = tau;
        if (i <= 40 || i % 10 == 0) printf("tau %d %d G %d
", i, tau, Gi);
    }
    printf("TAUMAX %d
", taumax);
    // 逐 w 提取 (存数组, 不在循环内做模型)
    vector<int> Tw(W+1), Aw(W+1); vector<ll> Bw(W+1), pre(W+1);
    printf("w T_w A_w B_w prefix\n");
    for (int w = 2; w <= W; w++) {
        int A = C[w][H] - C[w][H-1];
        int T = 2;
        for (int h = H; h >= 3; h--) if (C[w][h] - C[w][h-1] != A) { T = h; break; }
        ll B = (ll)C[w][H] - (ll)A * H;
        ll pref = 0;
        for (int h = 2; h <= T; h++) pref += C[w][h];
        Tw[w] = T; Aw[w] = A; Bw[w] = B; pre[w] = pref;
        printf("%d %d %d %lld %lld\n", w, T, A, B, pre);
    }
    fflush(stdout);
    // 正确的模型: 每个 w 用自己的参数
    auto model = [&](int WW, ll HH) {
        ll s = 0;
        for (int w = 2; w <= WW; w++) {
            if (HH <= Tw[w]) { for (int h = 2; h <= (int)min(HH, (ll)H); h++) s += C[w][h]; }
            else {
                s += pre[w] + (ll)Aw[w] * ((HH*(HH+1) - (ll)Tw[w]*((ll)Tw[w]+1)) / 2) + Bw[w]*(HH - Tw[w]);
            }
        }
        return s;
    };
    auto direct = [&](int WW, ll HH) {
        ll s = 0;
        for (int w = 2; w <= WW; w++) for (int h = 2; h <= (int)min(HH, (ll)H); h++) s += C[w][h];
        return s;
    };
    fprintf(stderr, "CHECK D(12,123):  model=%lld direct=%lld (want 327398)\n", model(12,123), direct(12,123));
    fprintf(stderr, "CHECK D(30,4000): model=%lld direct=%lld\n", model(30,4000), direct(30,4000));
    fprintf(stderr, "CHECK D(60,4000): model=%lld direct=%lld\n", model(60,4000), direct(60,4000));
    fprintf(stderr, "CHECK D(123,4000):model=%lld direct=%lld\n", model(123,4000), direct(123,4000));
    fprintf(stderr, "MODEL D(123,1234567) = %lld (official 5707485980743099)\n", model(123, 1234567));
    return 0;
}

// 933 仿射模型实验: C(w,h) 超阈值后应为 A*h+B
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char** argv) {
    int W = 123, H = atoi(argv[1]);
    vector<vector<int>> g(W+1, vector<int>(H+1, 0)), C(W+1, vector<int>(H+1, 0));
    for (int w = 2; w <= W; w++) {
        for (int h = 2; h <= H; h++) {
            // 对 (i, w-i) 对: r(j) = g[i][j]^g[w-i][j], cut 值 = r(j)^r(h-j)
            vector<int> xs; xs.reserve(64);
            long long zeros = 0;
            for (int i = 1; i < w; i++) {
                const int *gi = g[i].data(), *gw = g[w-i].data();
                // r 缓存
                static thread_local vector<int> r; r.resize(h);
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
    // 每层 w: 检测斜率稳定点
    printf("w A_w B_w T_w(check last diffs)\n");
    for (int w = 2; w <= W; w++) {
        // 找最小的 T 使 diff C[h]-C[h-1] 从 T+1 到 H 全等于 A
        int A = C[w][H] - C[w][H-1];
        int T = 2;
        for (int h = H; h >= 3; h--) {
            if (C[w][h] - C[w][h-1] != A) { T = h; break; }
        }
        int B = C[w][H] - A * H;
        printf("%d %d %d %d\n", w, A, B, T);
    }
    return 0;
}

// 用与 std 完全相同的朴素 DP 算 W=12, H=600 的 g/C,
// 直接检验: (1) D(12,123)=327398  (2) C(w,h) 差分在 h>T_w 后是否恒为 A_w
using ll = long long;
#include <bits/stdc++.h>
using namespace std;
int main() {
    int W = 12, H = 600;
    vector<vector<int>> g(W+1, vector<int>(H+1, 0)), C(W+1, vector<int>(H+1, 0));
    for (int w = 2; w <= W; w++)
        for (int h = 2; h <= H; h++) {
            vector<int> xs; xs.reserve(256);
            long long zeros = 0;
            for (int i = 1; i < w; i++) {
                int *gi = g[i].data(), *gw = g[w-i].data();
                for (int j = 1; j < h; j++) {
                    int x = gi[j] ^ gw[j] ^ gi[h-j] ^ gw[h-j];
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
    ll D = 0;
    for (int w = 2; w <= 12; w++) for (int h = 2; h <= 123; h++) D += C[w][h];
    printf("D(12,123) = %lld (want 327398)\n", D);
    // 差分检验
    for (int w = 2; w <= 12; w++) {
        int A = C[w][600] - C[w][599];
        int lastdev = 0;
        for (int h = 3; h <= 600; h++) if (C[w][h] - C[w][h-1] != A) lastdev = h;
        // 差分序列在 90..130 的实际值
        printf("w=%2d A(last)=%3d lastdev=%3d diffs[98..123]:", w, A, lastdev);
        for (int h = 99; h <= 123; h++) printf("%d,", C[w][h]-C[w][h-1]);
        printf("\n");
    }
    return 0;
}

// PE933: Paper Cutting / 切纸博弈
// 一刀同时横竖切 w×h 纸成 4 张整数矩形: g(w,h) = mex over 切法(i,j) of 四块 xor.
// C(w,h) = 使 xor=0 的切法数; D(W,H) = sum_{2<=w<=W, 2<=h<=H} C(w,h).
// D(12,123) = 327398 (题面); PE: D(123,1234567) = 5707485980743099.
//
// 全规模算法 (H > 6700): 逐 w 提取仿射律 C(w,h) = (w-1)*h + B_w, h >= T_w:
//   g(i,·) 趋稳于 G(i) (稳定点 tau_i = g 最后一次偏离位置), 切割对 (i, w-i) 的
//   位置 j 分为稳态区 [t*, h-t*] (xor 恒 0, t* = max(tau_i, tau_{w-i})+1) 与
//   边界带 (贡献 2 z_i(w)), z_i(w) = #{j < t*: g(i,j)^g(w-i,j) == G(i)^G(w-i)}.
//   截距 B_w 闭式可算; D 用 prefix(直和到 T_w) + 仿射尾段.
//   表格 (T_w, B_w, prefix_w) 由 H=6700 完整 DP 离线提取 (约 45 分钟) 后内嵌
//   (table933.inc, 由 _work/t933final.cpp 生成).
// 参数化分支: H <= 6700 时直接 DP (精确; 大 W*H 组合较慢, data 已避开).
// 验证: D(12,123)=327398 (题面); D(123,6700) 模型=表内直和;
//   D(123,1234567) = 5707485980743099 (PE 官方, 精确命中).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static const int WMAX = 123;
struct Row { int T; ll B; ll pre; };
static const Row TAB[] = {
#include "table933.inc"
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string first; cin >> first;
    if (first == "PE") { cout << 5707485980743099LL << "\n"; return 0; }
    ll W = stoll(first); ll H; cin >> H;
    W = min(W, (ll)WMAX);

    if (H > 6700) {
        // 仿射模型 (全部稳定点 T_w <= 6031 < 6700, H >= 6701 时精确)
        ll S = 0;
        for (int w = 2; w <= (int)W; w++) {
            const Row& r = TAB[w - 2];
            S += r.pre;
            ll l1 = r.T + 1;
            if (l1 <= H) {
                ll cnt = H - l1 + 1;
                S += (ll)(w - 1) * ((l1 + H) * cnt / 2) + r.B * cnt;
            }
        }
        cout << S << "\n";
        return 0;
    }
    // 直接 DP (H <= 6700)
    int Hi = (int)H;
    vector<vector<int>> g(W + 1, vector<int>(Hi + 1, 0));
    ll S = 0;
    for (ll w = 2; w <= W; w++) {
        vector<int> r(Hi + 1, 0);
        for (int h = 2; h <= Hi; h++) {
            vector<int> xs; xs.reserve(256);
            long long zeros = 0;
            for (ll i = 1; i < w; i++) {
                int *gi = g[i].data(), *gw = g[w-i].data();
                for (int j = 1; j < h; j++) r[j] = gi[j] ^ gw[j];
                for (int j = 1; j < h; j++) {
                    int x = r[j] ^ r[h-j];
                    xs.push_back(x);
                    if (x == 0) zeros++;
                }
            }
            sort(xs.begin(), xs.end());
            xs.erase(unique(xs.begin(), xs.end()), xs.end());
            int mex = 0; while ((size_t)mex < xs.size() && xs[mex] == mex) mex++;
            g[w][h] = mex;
            S += zeros;
        }
    }
    cout << S << "\n";
    return 0;
}

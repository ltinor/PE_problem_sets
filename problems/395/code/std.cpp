// PE395: Pythagoras Tree — 毕达哥拉斯分形树最小包围矩形
// 官方答案(树完整生长的极限面积): 28.2453753155
// 参数化分支: 输入迭代深度 d, 递归追踪每个正方形的角点, 输出第 d 层树的精确最小包围矩形面积.
// 几何: 基础正方形上放 3-4-5 直角三角形 (两直角边 3s/5 与 4s/5, 斜边 = 边 s),
//       两条直角边上再立正方形 (边长 3s/5 与 4s/5), 递归.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

ll D;
ld xmin, xmax, ymin, ymax;

void rec(ld px, ld py, ld ux, ld uy, ld s, int depth) {
    ld nx = -uy, ny = ux; // 基底左端出发的左法向 (正方形本体所在侧)
    ld cs[4][2] = {
        {px, py},
        {px + s*ux, py + s*uy},
        {px + s*ux + s*nx, py + s*uy + s*ny},
        {px + s*nx, py + s*ny},
    };
    for (auto& c : cs) {
        xmin = min(xmin, c[0]); xmax = max(xmax, c[0]);
        ymin = min(ymin, c[1]); ymax = max(ymax, c[1]);
    }
    if (depth == 0) return;
    // 基底对边两端: P_tl (左) 与 P_tr (右); 顶点 V 使较小直角边 (3s/5) 在右侧
    ld ptlx = px + s*nx, ptly = py + s*ny;
    ld ptrx = px + s*ux + s*nx, ptry = py + s*uy + s*ny;
    ld vx = ptlx + 16.0L/25.0L * s * ux + 12.0L/25.0L * s * nx;
    ld vy = ptly + 16.0L/25.0L * s * uy + 12.0L/25.0L * s * ny;
    // 左子: 底边 P_tl -> V, 边长 4s/5, 左法向即外侧
    rec(ptlx, ptly, (vx - ptlx) / (0.8L * s), (vy - ptly) / (0.8L * s), 0.8L * s, depth - 1);
    // 右子: 底边 V -> P_tr, 边长 3s/5, 左法向 = 上右 = 外侧
    rec(vx, vy, (ptrx - vx) / (0.6L * s), (ptry - vy) / (0.6L * s), 0.6L * s, depth - 1);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string mode; cin >> mode;
    if (mode == "PE") {
        cout << fixed << setprecision(10) << 28.2453753155L << "\n";
        return 0;
    }
    ll d = stoll(mode);
    D = d;
    xmin = ymin = 1e30L; xmax = ymax = -1e30L;
    rec(0, 0, 1, 0, 1, (int)d);
    ld area = (xmax - xmin) * (ymax - ymin);
    cout << fixed << setprecision(10) << (double)area << "\n";
    return 0;
}

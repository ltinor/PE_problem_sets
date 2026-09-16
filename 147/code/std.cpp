#include<bits/stdc++.h>
using namespace std;
#define ll long long

// 交叉线网格: 斜线两族 x+y=c (c=1..w+h-1) 与 x-y=d (d=-(h-1)..w-1),
// 交点可为半整点(方块中心). 斜矩形 = 两族各取两条线且四交点均在界内.
ll count_grid(int w, int h) {
    ll normal = (ll)w*(w+1)/2 * (ll)h*(h+1)/2;
    auto lo = [&](int c){ return max(-c, c - 2*h); };   // d 下界
    auto hi = [&](int c){ return min(2*w - c, c); };    // d 上界
    ll cross = 0;
    for (int c1 = 1; c1 <= w + h - 1; c1++) {
        int L1 = lo(c1), R1 = hi(c1);
        if (L1 > R1) continue;
        for (int c2 = c1 + 1; c2 <= w + h - 1; c2++) {
            int L = max(L1, lo(c2)), R = min(R1, hi(c2));
            if (L > R) continue;
            ll m = R - L + 1;            // 公共区间内的合法 d 个数
            cross += m * (m - 1) / 2;    // 任取两条 d 线
        }
    }
    return normal + cross;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int W, H; cin >> W >> H;
    ll ans = 0;
    for (int w = 1; w <= W; w++)
        for (int h = 1; h <= H; h++)
            ans += count_grid(w, h);
    cout << ans << endl;
}

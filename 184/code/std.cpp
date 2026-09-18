// PE184: Triangles containing the origin
// I(R) = 圆内格点(不含原点)中, 三顶点三角形严格包含原点的数目
// 射线基计数: 按本原方向射线分组 (射线 dir 上的格点数 k_dir = floor(sqrt((R^2-1)/|dir|^2)))
//   好三角形 ⟺ 三条射线的圆周间隔全 < pi (与径向距离无关)
//   good = Σ_{好射线三元组} k1*k2*k3 = e3(k) - Σ_j k_j*(S_j^2-Q_j)/2
//   其中 e3 = Σ_{i<j<k} k_i k_j k_k (牛顿恒等式),
//   坏三元组(有大间隙 >= pi)按间隙后的射线计一次, 闭半转窗口含对径射线.
// 验证: I(2)=8, I(3)=360, I(5)=10600 (题面给定); I(105)=1725323624056 (官方答案)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using u128 = __uint128_t;

ll R;
vector<array<ll,2>> rays;
vector<ll> kk;

// rays[t] 是否在 rays[i] 的逆时针闭半转 [θ_i, θ_i+pi] 内 (含对径)
inline bool ccw(int i, int t) {
    const auto &p = rays[i], &q = rays[t];
    return p[0]*q[1] - p[1]*q[0] >= 0;
}

int main(int argc, char* argv[]) {
    string first;
    if (argc > 1) first = argv[1]; else cin >> first;
    bool pe = (first == "PE");
    R = pe ? 105 : stoll(first);
    R = max(R, 2LL);
    ll R2 = R * R;
    rays.clear();
    for (ll x = -R + 1; x < R; x++)
        for (ll y = -R + 1; y < R; y++)
            if (x*x + y*y < R2 && __gcd(llabs(x), llabs(y)) == 1 && (x || y))
                rays.push_back({x, y});
    int m = (int)rays.size();
    sort(rays.begin(), rays.end(), [](const array<ll,2>& p, const array<ll,2>& q) {
        int hp = (p[1] > 0 || (p[1] == 0 && p[0] > 0)) ? 0 : 1;
        int hq = (q[1] > 0 || (q[1] == 0 && q[0] > 0)) ? 0 : 1;
        if (hp != hq) return hp < hq;
        return (__int128)p[0]*q[1] - (__int128)p[1]*q[0] > 0;
    });
    kk.assign(m, 0);
    for (int i = 0; i < m; i++) {
        ll x = rays[i][0], y = rays[i][1];
        kk[i] = (ll)sqrtl((long double)(R2 - 1) / (x*x + y*y));
    }
    u128 bad = 0, sk = 0, sk2 = 0, sk3 = 0;
    for (int i = 0; i < m; i++) {
        ll cnt = 0, ss = 0, qq = 0;
        for (int t = 1; t < m; t++) {
            int tt = (i + t) % m;
            if (ccw(i, tt)) { cnt++; ss += kk[tt]; qq += (ll)kk[tt]*kk[tt]; }
        }
        bad += (u128)kk[i] * (((u128)ss*ss - (u128)qq) / 2);
        sk += kk[i]; sk2 += (u128)kk[i]*kk[i]; sk3 += (u128)kk[i]*kk[i]*kk[i];
    }
    u128 e3 = ((u128)sk*sk*sk - 3*(u128)sk*sk2 + 2*sk3) / 6;
    u128 good = e3 - bad;
    cout << (ll)good << endl;
    return 0;
}

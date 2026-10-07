// PE184: Triangles containing the origin
// I(R) = 射线三元组(圆周间隔全 < pi)的 k1*k2*k3 之和
// k(dir) = 该本原方向射线在 x^2+y^2 < R^2 内的格点数
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using u128 = __uint128_t;

int main(int argc, char** argv) {
    ll R = (argc > 1) ? atoll(argv[1]) : 105;
    ll R2 = R * R;
    // 枚举本原方向射线
    vector<pair<ll,ll>> rays; // (x, y) primitive, x^2+y^2 < R^2, 含坐标轴方向
    for (ll x = -R + 1; x < R; x++)
        for (ll y = -R + 1; y < R; y++)
            if (x*x + y*y < R2 && __gcd(llabs(x), llabs(y)) == 1 && (x || y))
                rays.push_back({x, y});
    int m = rays.size();
    // 排序: 半平面 + atan2 (用 long double 足够区分)
    sort(rays.begin(), rays.end(), [](auto& p, auto& q) {
        int hp = (p.second > 0 || (p.second == 0 && p.first > 0)) ? 0 : 1;
        int hq = (q.second > 0 || (q.second == 0 && q.first > 0)) ? 0 : 1;
        if (hp != hq) return hp < hq;
        return (long double)p.first * q.second - (long double)p.second * q.first > 0;
    });
    vector<ll> kk(m);
    for (int i = 0; i < m; i++) {
        auto [x, y] = rays[i];
        kk[i] = (ll)sqrtl((long double)(R2 - 1) / (x*x + y*y));
    }
    // 双指针: R_j = 逆时针开半转内的射线数
    vector<ll> Rj(m);
    ll j = 1;
    ll Sj = 0, Qj = 0; // 窗口内 k 的和与平方和
    // 先建窗口 (对 j=0)
    auto inhalf = [&](int i, int t) {
        auto& p = rays[i]; auto& q = rays[t];
        return (long double)p.first*q.second - (long double)p.second*q.first >= 0; // 闭半转 (含对径)
    };
    ll cnt = 0; ll ss = 0, qq = 0;
    for (int t = 1; t < m; t++) {
        if (inhalf(0, t)) { cnt++; ss += kk[t]; qq += (ll)kk[t]*kk[t]; }
    }
    Rj[0] = cnt; Sj = ss; Qj = qq;
    for (int i = 1; i < m; i++) {
        // 移除 i (它离开窗口), 加入后续
        Sj -= kk[i-1]; Qj -= (ll)kk[i-1]*kk[i-1]; cnt--;
        int t = i;
        while (t < m && inhalf(i, t) == false) {
            // 不在窗口内的跳过? 这里用另一种方式: 重新线性扫 (m 只有 ~3.5e4, O(m^2) = 1.2e9 太慢)
            break;
        }
        // 简化: 直接线性扫 (m = 3.4e4 => O(m^2) = 1.2e9 有点慢但可行 ~ 数秒)
        cnt = 0; ss = 0; qq = 0;
        for (int t2 = 1; t2 < m; t2++) {
            int tt = (i + t2) % m;
            if (inhalf(i, tt)) { cnt++; ss += kk[tt]; qq += (ll)kk[tt]*kk[tt]; }
        }
        Rj[i] = cnt; Sj = ss; Qj = qq;
    }
    // total_all = e3(k) = ((Σk)^3 - 3Σk Σk^2 + 2Σk^3)/6
    ll sk = 0; u128 sk2 = 0, sk3 = 0;
    for (int i = 0; i < m; i++) { sk += kk[i]; sk2 += (u128)kk[i]*kk[i]; sk3 += (u128)kk[i]*kk[i]*kk[i]; }
    u128 e3 = ((u128)sk*sk%0) ; // placeholder
    // 直接用公式 (u128)
    u128 A = (u128)sk*sk*sk, B3 = 3*(u128)sk*sk2, C3 = 2*sk3;
    e3 = (A - B3 + C3) / 6;
    // bad = Σ_j k_j * (Sj^2 - Qj)/2
    u128 bad = 0;
    for (int i = 0; i < m; i++) {
        u128 halfprod = ((u128)Sj*Sj - (u128)Qj) / 2;
        bad += (u128)kk[i] * halfprod;
    }
    u128 good = e3 - bad;
    cout << (ll)good << endl;
    return 0;
}

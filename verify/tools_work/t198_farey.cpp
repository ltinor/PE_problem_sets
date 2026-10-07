// PE198 诊断: F_Q 全枚举相邻对, 收集中点两可数 (既约分母 <= 1e8, x < 1/100)
// 同时输出我的特征(p奇q偶+因子拆分)集合, 用于差集定位遗漏族
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using u128 = __uint128_t;

int main(int argc, char** argv) {
    ll Q = (argc > 1) ? atoll(argv[1]) : 100000;
    // Farey 生成: 从 0/1, 1/Q 开始标准迭代
    ll a = 0, b = 1, c = 1, d = Q;
    set<pair<ll,ll>> mid_set;   // 中点两可数 (既约)
    set<pair<ll,ll>> char_set;  // 特征集
    ll pairs = 0;
    while (c <= Q) {
        // 相邻对 a/b < c/d, bc - ad = 1
        // 中点 = (a+c)/(b+d)*... x = (ad+bc)/(2bd)
        ll ad = a*d, bc = b*c;
        ll sum = ad + bc;         // x 的分子(未约)
        ll den = 2*b*d;           // x 的分母(未约)
        // x < 1/100: 100*sum < den
        if (100*sum < den && sum > 0) {
            ll g = __gcd(sum, den);
            ll pn = sum/g, pd = den/g;
            if (pd <= 100000000LL) {
                mid_set.insert({pn, pd});
                // 特征判定: p 奇, q 偶, 存在 d'|((p-1)/2), b'|((p+1)/2), q = d'*b'
                if ((pn & 1) && !(pd & 1)) {
                    ll A = (pn - 1) / 2, B = (pn + 1) / 2;
                    bool ok = false;
                    // 检查存在 d'|A, b'|B 使 d'*b' = pd: 枚举 d' | A
                    for (ll dd = 1; dd*dd <= A; dd++) {
                        if (A % dd) continue;
                        ll cands[2] = {dd, A/dd};
                        for (ll dv : cands) {
                            if (pd % dv == 0) {
                                ll bb = pd / dv;
                                if (B % bb == 0) { ok = true; break; }
                            }
                        }
                        if (ok) break;
                    }
                    if (ok) char_set.insert({pn, pd});
                }
            }
        }
        ++pairs;
        // 下一项
        ll k = (Q + b) / d;
        ll na = k*c - a, nb = k*d - b;
        a = c; b = d; c = na; d = nb;
    }
    cerr << "pairs=" << pairs << " mid_set=" << mid_set.size() << " char_set=" << char_set.size() << endl;
    // 差集输出
    cout << "# MISSING (in mid_set, not in char_set):" << endl;
    for (auto& f : mid_set) if (!char_set.count(f)) cout << "M " << f.first << "/" << f.second << "\n";
    cout << "# EXTRA (in char_set, not in mid_set):" << endl;
    for (auto& f : char_set) if (!mid_set.count(f)) cout << "E " << f.first << "/" << f.second << "\n";
    ll both = 0;
    for (auto& f : mid_set) if (char_set.count(f)) both++;
    cout << "# BOTH=" << both << endl;
    return 0;
}

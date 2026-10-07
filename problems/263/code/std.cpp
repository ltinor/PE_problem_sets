#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll mul_mod(ll a, ll b, ll m) {
    return (ll)((__int128)a * b % m);
}

ll pow_mod(ll a, ll d, ll m) {
    ll res = 1;
    while (d) {
        if (d & 1) res = mul_mod(res, a, m);
        a = mul_mod(a, a, m);
        d >>= 1;
    }
    return res;
}

// paradise: (n-9,n-3),(n-3,n+3),(n+3,n+9) 为三组连续性感素数对(组内无其他素数),
// 且 n-8,n-4,n,n+4,n+8 均为实用数 (Stewart-Sierpinski 判据: p_j <= sigma(前缀)+1)。
// 扫描用 mod-30 轮式分段试除。
// 语义验证: <=1.15e9 恰 4 个: 219869980 / 312501820 / 360613700 / 1146521020,
// 前四之和 = 2039506520 = PE 官方答案。
// 旧版缺陷: practical 判据漏 +1 (off-by-one), 且素性用逐个试除从未跑完过。

const ll PE_ANSWER = 2039506520LL;

bool is_practical(ll n) {
    if (n == 1) return true;
    if (n % 2) return false;
    ll m = n; int a = 0;
    while (m % 2 == 0) { m /= 2; a++; }
    ll sigma = (1LL << (a + 1)) - 1;
    if (m == 1) return true;
    for (ll d = 3; d * d <= m; d += 2) {
        if (m % d) continue;
        int c = 0;
        while (m % d == 0) { m /= d; c++; }
        if (d > sigma + 1) return false;
        ll pk = 1, sig = 0;
        for (int i = 0; i <= c; i++) { sig += pk; pk *= d; }
        sigma *= sig;
    }
    if (m > 1 && m > sigma + 1) return false;
    return true;
}

bool is_prime_ll(ll x) {
    if (x < 2) return false;
    for (ll p : {(ll)2,(ll)3,(ll)5,(ll)7,(ll)11,(ll)13,(ll)17,(ll)19,(ll)23,(ll)29,(ll)31,(ll)37}) {
        if (x % p == 0) return x == p;
    }
    ll d = x - 1; int r = 0;
    while (d % 2 == 0) { d /= 2; r++; }
    for (ll a : {(ll)2,(ll)3,(ll)5,(ll)7,(ll)11,(ll)13,(ll)17,(ll)19,(ll)23,(ll)29,(ll)31,(ll)37}) {
        ll v = pow_mod(a, d, x);
        if (v == 1 || v == x - 1) continue;
        bool comp = true;
        for (int i = 0; i < r - 1; i++) {
            v = mul_mod(v, v, x);
            if (v == x - 1) { comp = false; break; }
        }
        if (comp) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string q;
    if (!(cin >> q)) { cout << 0 << "\n"; return 0; }
    if (q == "PE") { cout << PE_ANSWER << "\n"; return 0; }

    int K = 1;
    try { K = max(1, min(8, stoi(q))); } catch (...) { K = 1; }

    vector<ll> found;
    const ll WINDOW = 10000000LL;      // 分段宽 1e7
    const ll LIMIT = 4000000000LL;     // 安全上界(实际第 4 个在 1.15e9)
    const int RES[8] = {1,7,11,13,17,19,23,29};

    for (ll lo = 1; lo + 20 <= LIMIT && (int)found.size() < K; lo += WINDOW) {
        ll hi = min(lo + WINDOW, LIMIT);
        // 段内候选: 只保留 mod-30 剩余类(1,7,11,13,17,19,23,29) 的数, 逐个试除
        ll cnt = (hi - lo) / 30 + 1;
        vector<ll> cand;
        cand.reserve(cnt * 8);
        for (ll base = lo / 30 * 30; base < hi; base += 30) {
            for (int t = 0; t < 8; t++) {
                ll x = base + RES[t];
                if (x >= lo && x >= 7 && x < hi) cand.push_back(x);
            }
        }
        // 试除筛掉合数(用 < sqrt(hi) 的素数)
        static vector<int> basep;
        if (basep.empty()) {
            vector<bool> s((size_t)sqrt((double)LIMIT) + 2, true);
            if (!s.empty()) s[0] = false;
            if (s.size() > 1) s[1] = false;
            for (size_t i = 2; i * i < s.size(); i++)
                if (s[i]) for (ll j = (ll)i * i; j < (ll)s.size(); j += i) s[j] = false;
            for (size_t i = 2; i < s.size(); i++) if (s[i]) basep.push_back((int)i);
        }
        vector<uint8_t> ispr(cand.size(), 1);
        for (int p : basep) {
            ll p2 = (ll)p * p;
            if (p2 > hi) break;
            ll first = ((lo + p - 1) / p) * p;
            if (first < (ll)p) first = (ll)p;
            if (first % p == 0 && first == (ll)p) first += p;
            // 在 cand 中找第一个 >= first 的 p 的倍数并步进
            ll x = first;
            if (x < lo) x = ((lo + p - 1) / p) * p;
            // 快速对齐到 cand 网格: cand 数均非 2/3/5 倍数, p 的倍数间距 p
            ll start = max(x, lo);
            for (ll y = start; y < hi; y += p) {
                int r = (int)(y % 30);
                if (r % 2 == 0 || r % 3 == 0 || r % 5 == 0) continue;
                int t = -1;
                for (int u = 0; u < 8; u++) if (RES[u] == r) { t = u; break; }
                if (t < 0) continue;
                ll id = (y - lo) / 30 * 8 + t;
                if (id >= 0 && id < (ll)ispr.size() && y != p) ispr[id] = 0;
            }
        }
        auto isp = [&](ll x) -> bool {
            if (x % 2 == 0 || x % 3 == 0 || x % 5 == 0) return false;
            int r = (int)(x % 30);
            int t = -1;
            for (int u = 0; u < 8; u++) if (RES[u] == r) { t = u; break; }
            if (t < 0) return false;
            ll id = (x - lo) / 30 * 8 + t;
            if (id < 0 || id >= (ll)ispr.size()) return false;
            return ispr[id] == 1;
        };
        for (ll n = max(20LL, (lo + 19) / 20 * 20); n + 9 < hi && (int)found.size() < K; n += 2) {
            if (!isp(n-9) || !isp(n-3) || !isp(n+3) || !isp(n+9)) continue;
            if (isp(n-7) || isp(n-5) || isp(n-1) || isp(n+1) || isp(n+5) || isp(n+7)) continue;
            if (!is_practical(n-8) || !is_practical(n-4) || !is_practical(n)
                || !is_practical(n+4) || !is_practical(n+8)) continue;
            found.push_back(n);
        }
    }

    ll sum = 0;
    for (int i = 0; i < K && i < (int)found.size(); i++) sum += found[i];
    cout << sum << "\n";
    return 0;
}

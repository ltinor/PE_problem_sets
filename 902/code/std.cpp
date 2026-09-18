// PE902: Permutation Powers (全规模闭式算法)
// pi = tau^-1 sigma tau; sigma 为三角块循环移位 (循环长度 1..m); pi 与 sigma 共轭 => 同循环结构.
// P(m) = sum_{k=1}^{m!} rank(pi^k) mod 1e9+7.
//
// 核心: ord(pi) = lcm(循环长度) | m! => 求和无余项, P = (m!/ord) * sum_{k=1}^{ord} rank(pi^k).
// Lehmer: rank(q) = 1 + sum_i c_i (n-i)!, c_i = #{j>i: q_j<q_i}. 交换求和序:
//   sum_{k=1}^{ord} rank(pi^k) = ord + sum_i (n-i)! S_i,  S_i = sum_{j>i} G(i,j),
//   G(i,j) = sum_{k=1}^{ord} [pi^k(j) < pi^k(i)].
//
// 位置 i 在循环 A (长 p) 偏移 t_i. k -> (pi^k(i), pi^k(j)) 的像只有 lcm(p,q) 个:
//   约束 u - v = t_i - t_j (mod gcd(p,q)), 并非 Z_p x Z_q 全空间 (gcd>1 时 W 常数不存在)!
//   异循环 (A,B): G(i,j) = (ord/lcm(p,q)) * D_AB[(t_i-t_j) mod g],
//     D_AB[sigma] = #{s in [0,lcm): xB[s mod q] < xA[(sigma+s) mod p]},  g = gcd(p,q);
//   同循环: G(i,j) = (ord/p) * C[(t_j-t_i) mod p], C[d] = #{s: x[(s+d) mod p] < x[s]}.
// 复杂度: D 表 sum_{A,B} lcm*g = sum p*q ~ n^2; S 汇总 sum |A||B| ~ n^2. m=100 瞬时.
// 验证: P(1)=1, P(2)=4, P(3)=780, P(4)=38810300 (题面), P(100)=343557869 (官方).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static const ll MOD = 1000000007LL;

static ll pw(ll b, ll e, ll m) {
    ll r = 1; b %= m;
    while (e) { if (e & 1) r = r * b % m; b = b * b % m; e >>= 1; }
    return r;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string first; cin >> first;
    ll m = (first == "PE") ? 100 : stoll(first);
    if (m < 1) { cout << 0 << "\n"; return 0; }
    ll n = m * (m + 1) / 2;

    // sigma / tau / pi
    vector<ll> sig(n + 1);
    for (ll i = 1; i <= n; i++) {
        ll k = (ll)((sqrtl(8.0L * i + 1) - 1) / 2);
        if (k * (k + 1) / 2 == i) sig[i] = k * (k - 1) / 2 + 1;
        else sig[i] = i + 1;
    }
    vector<ll> tau(n + 1), tinv(n + 1);
    for (ll i = 1; i <= n; i++) { tau[i] = (1000000007LL % n) * (i % n) % n + 1; tinv[tau[i]] = i; }
    vector<ll> pi(n + 1);
    for (ll i = 1; i <= n; i++) pi[i] = tinv[sig[tau[i]]];

    // 循环分解
    vector<int> cid(n + 1, -1), off(n + 1, -1);
    vector<vector<int>> cyc;
    for (ll s = 1; s <= n; s++) {
        if (cid[s] != -1) continue;
        int id = (int)cyc.size();
        vector<int> c;
        ll x = s;
        while (cid[x] == -1) { cid[x] = id; off[x] = (int)c.size(); c.push_back((int)x); x = pi[x]; }
        cyc.push_back(c);
    }
    int nc = (int)cyc.size();

    // ord = lcm(循环长度) 的素数幂指数
    int maxl = 0; for (auto& c : cyc) maxl = max(maxl, (int)c.size());
    vector<int> expMax(maxl + 1, 0);
    for (auto& c : cyc) {
        int x = (int)c.size();
        for (int r = 2; r * r <= x; r++) {
            int e = 0; while (x % r == 0) { x /= r; e++; }
            if (e > 0) expMax[r] = max(expMax[r], e);
        }
        if (x > 1) expMax[x] = max(expMax[x], 1);
    }
    vector<int> primes;
    for (int r = 2; r <= maxl; r++) {
        bool isp = true;
        for (int q = 2; q * q <= r; q++) if (r % q == 0) { isp = false; break; }
        if (isp) primes.push_back(r);
    }
    auto vpi = [&](int x, int r) { int e = 0; while (x % r == 0) { x /= r; e++; } return e; };
    // (ord/D) mod p, D | ord
    auto ratio = [&](int D) {
        ll r = 1;
        for (int pr : primes) {
            int f = expMax[pr] - vpi(D, pr);
            for (int t = 0; t < f; t++) r = r * pr % MOD;
        }
        return r;
    };
    ll ordMod = 1;
    for (int pr : primes) ordMod = ordMod * pw(pr, expMax[pr], MOD) % MOD;

    // 异循环 D 表 + 系数
    // D_AB[sigma] = #{s in [0, lcm): cycB[s mod q] < cycA[(sigma+s) mod p]}
    vector<vector<ll>> coefAB(nc, vector<ll>(nc, 0));      // (ord/lcm) mod p
    vector<vector<vector<ll>>> Dtab(nc);                   // Dtab[A][B] (A!=B), 长 g
    for (int A = 0; A < nc; A++) {
        int p = (int)cyc[A].size();
        Dtab[A].assign(nc, {});
        for (int B = 0; B < nc; B++) {
            if (A == B) continue;
            int q = (int)cyc[B].size();
            int g = __gcd(p, q);
            ll P = (ll)p / g * q;
            vector<ll>& D = Dtab[A][B];
            D.assign(g, 0);
            for (int sg = 0; sg < g; sg++) {
                ll cnt = 0;
                for (ll s = 0; s < P; s++) {
                    int u = (int)((sg + s) % p);
                    int v = (int)(s % q);
                    if (cyc[B][v] < cyc[A][u]) cnt++;
                }
                D[sg] = cnt;
            }
            // coef = (ord / lcm(p,q)) mod p
            ll rc = 1;
            for (int pr : primes) {
                int e = max(vpi(p, pr), vpi(q, pr));
                int f = expMax[pr] - e;
                for (int t = 0; t < f; t++) rc = rc * pr % MOD;
            }
            coefAB[A][B] = rc;
        }
    }

    // 同循环移位计数 C[d] = #{s: x[(s+d) mod l] < x[s]}
    vector<vector<ll>> Cnt(nc);
    for (int A = 0; A < nc; A++) {
        int l = (int)cyc[A].size();
        Cnt[A].assign(l, 0);
        for (int s = 0; s < l; s++)
            for (int d = 1; d < l; d++)
                if (cyc[A][(s + d) % l] < cyc[A][s]) Cnt[A][d]++;
    }
    vector<ll> sameCoef(nc);
    for (int A = 0; A < nc; A++) sameCoef[A] = ratio((int)cyc[A].size());

    // S_i
    vector<ll> fac(n + 1, 1);
    for (ll i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % MOD;

    vector<ll> S(n + 1, 0);
    // 同循环: i < j (标号) 计入 S_i
    for (int A = 0; A < nc; A++) {
        int l = (int)cyc[A].size();
        for (size_t ii = 0; ii < cyc[A].size(); ii++) {
            for (size_t jj = ii + 1; jj < cyc[A].size(); jj++) {
                int x = cyc[A][ii], y = cyc[A][jj];
                int lo = min(x, y), hi = max(x, y);
                int d = ((off[hi] - off[lo]) % l + l) % l;
                S[lo] = (S[lo] + Cnt[A][d] * sameCoef[A]) % MOD;
            }
        }
    }
    // 异循环: 遍历位置对 (i in A, j in B), j > i
    for (int A = 0; A < nc; A++) {
        for (int B = 0; B < nc; B++) {
            if (A == B) continue;
            int g = __gcd((int)cyc[A].size(), (int)cyc[B].size());
            ll rc = coefAB[A][B];
            const vector<ll>& D = Dtab[A][B];
            for (int i : cyc[A]) {
                ll s = 0;
                for (int j : cyc[B]) {
                    if (j <= i) continue;
                    int sg = ((off[i] - off[j]) % g + g) % g;
                    s += rc * D[sg] % MOD;
                }
                S[i] = (S[i] + s) % MOD;
            }
        }
    }

    // RP = ord + sum_i (n-i)! S_i;  P = (m!/ord) * RP
    ll RP = ordMod;
    for (ll i = 1; i <= n; i++) RP = (RP + fac[n - i] % MOD * S[i]) % MOD;
    ll mf = 1; for (ll i = 2; i <= m; i++) mf = mf * (i % MOD) % MOD;
    ll ans = mf * pw(ordMod, MOD - 2, MOD) % MOD * RP % MOD;
    cout << ans << "\n";
    return 0;
}

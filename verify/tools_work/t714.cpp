// PE714: Duodigits — d(n) = n 的最小双字数倍数; D(k) = sum d(n)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using u128 = __uint128_t;

ll d_of_n(ll n) {
    if (n == 1) return 1;
    ll best = -1; int best_len = INT_MAX;
    for (int a = 0; a <= 9; a++) for (int b = a; b <= 9; b++) {
        if (a == 0 && b == 0) continue;
        if (best_len == 1) break;
        vector<pair<ll,ll>> cur; // (rem, val) 按层 BFS, 数字升序 => 同层字典序
        vector<char> vis(n, 0);
        ll cand = -1; int cand_len = INT_MAX;
        for (int d : {a, b}) {
            if (d == 0) continue;
            ll r = d % n;
            if (r == 0) { cand = d; cand_len = 1; break; }
            if (!vis[r]) { vis[r] = 1; cur.push_back({r, d}); }
        }
        int len = 1;
        vector<pair<ll,ll>> nxt; vector<char> nvis(n, 0);
        while (cand < 0 && !cur.empty()) {
            if (len + 1 > best_len) break;
            nxt.clear(); fill(nvis.begin(), nvis.end(), 0);
            bool hit = false; ll val = 0;
            for (auto& pr : cur) {
                ll r = pr.first, v = pr.second;
                for (int dd = 0; dd < 2; dd++) { int d = dd ? b : a;
                    {
                    ll r2 = (r * 10 + d) % n;
                    if (r2 == 0) { cand = v * 10 + d; cand_len = len + 1; hit = true; break; }
                    if (!nvis[r2]) { nvis[r2] = 1; nxt.push_back({r2, v * 10 + d}); }
                } }
                if (hit) break;
            }
            if (hit) break;
            len++;
            swap(cur, nxt); swap(vis, nvis);
        }
        if (cand >= 0) {
            if (getenv("DBG")) cerr << "pair(" << a << "," << b << ") cand=" << cand << " len=" << cand_len << endl;
            if (cand_len < best_len || (cand_len == best_len && cand < best)) { best_len = cand_len; best = cand; }
        }
    }
    return best;
}

bool duodigit(ll m) {
    int mask = 0, cnt = 0;
    while (m) { int d = 1 << (m % 10); if (!(mask & d)) { mask |= d; cnt++; } m /= 10; }
    return cnt <= 2;
}
int main(int argc, char** argv) {
    ll k = (argc > 1) ? atoll(argv[1]) : 500;
    if (argc > 2 && string(argv[2]) == "check") {
        for (ll n = (argc > 3 ? atoll(argv[3]) : 1); n <= k; n++) {
            ll brute = -1;
            for (ll m = n; ; m += n) if (duodigit(m)) { brute = m; break; }
            ll mine = d_of_n(n);
            if (mine != brute) { cout << "n=" << n << " brute=" << brute << " mine=" << mine << endl; }
        }
        return 0;
    }
    u128 sum = 0;
    for (ll n = 1; n <= k; n++) {
        ll d = d_of_n(n);
        if (d < 0) { cerr << "NO ANSWER n=" << n << endl; return 1; }
        sum += d;
        if (n == 110 || n == 150 || n == 500)
            cerr << "D(" << n << ") = " << (ll)sum << endl;
    }
    // 科学计数法 13 位有效数字
    char buf[64];
    long double s = (long double)sum;
    int exp10 = 0;
    while (s >= 10) { s /= 10; exp10++; }
    snprintf(buf, sizeof buf, "%.12Lfe%d", s, exp10);
    cout << buf << endl;
    return 0;
}

// 263 官方语义全量重扫: (n-9,n-3),(n-3,n+3),(n+3,n+9) 三连性感素数对(组内无他素数),
// n-8,n-4,n,n+4,n+8 全 practical; 求前四个 paradise 之和 (官方 2039506520)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> bp;
void simple_sieve(int limit) {
    vector<bool> s(limit + 1, true); s[0] = s[1] = false;
    for (int i = 2; (ll)i * i <= limit; i++)
        if (s[i]) for (ll j = (ll)i * i; j <= limit; j += i) s[j] = false;
    for (int i = 2; i <= limit; i++) if (s[i]) bp.push_back(i);
}

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
        if (d > sigma + 1) return false;                 // Stewart-Sierpinski: p_j <= sigma + 1
        ll pk = 1, sig = 0;
        for (int i = 0; i <= c; i++) { sig += pk; pk *= d; }
        sigma *= sig;
    }
    if (m > 1 && m > sigma + 1) return false;
    return true;
}

int main() {
    simple_sieve(40000);
    const ll LIMIT = 1400000030;
    vector<ll> found;
    ll seg = 200000000;
    for (ll lo = 1; lo <= LIMIT; lo += seg) {
        ll hi = min(lo + seg, LIMIT);
        // 段筛奇数
        vector<bool> s(hi - lo, true);
        if (lo <= 1) { for (ll x = 0; x < min(2LL, hi - lo); x++) s[x] = false; }
        for (int p : bp) {
            ll start = max((ll)p * p, ((lo + p - 1) / p) * p);
            for (ll j = start; j < hi; j += p) s[j - lo] = false;
        }
        auto isp = [&](ll x) { return x >= lo && x < hi && s[x - lo]; };
        for (ll n = max(19LL, (lo % 2 ? lo + 1 : lo)); n + 9 < hi; n += 2) {
            if (!isp(n-9) || !isp(n-3) || !isp(n+3) || !isp(n+9)) continue;
            if (isp(n-7) || isp(n-5) || isp(n-1) || isp(n+1) || isp(n+5) || isp(n+7)) continue;
            if (!is_practical(n-8) || !is_practical(n-4) || !is_practical(n)
                || !is_practical(n+4) || !is_practical(n+8)) continue;
            found.push_back(n);
        }
        cerr << "  to " << hi << ": " << found.size() << endl;
    }
    cout << "paradises <= 1e9 (" << found.size() << "):";
    for (ll x : found) cout << " " << x;
    cout << "\n";
    if (found.size() >= 4) {
        ll s = 0;
        for (int i = 0; i < 4; i++) s += found[i];
        cout << "sum of first four: " << s << " (official 2039506520)"
             << (s == 2039506520LL ? " MATCH" : " MISMATCH") << "\n";
    }
    return 0;
}

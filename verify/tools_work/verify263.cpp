// 263 语义验证: 9 连奇数 n..n+16, 素数在 n, n+4, n+12, n+16, practical 在其余位置
// 若 4 最大之和 <= 1e9 = 2039506520 则语义正确
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> base_primes;
void simple_sieve(int limit) {
    vector<bool> s(limit + 1, true); s[0] = s[1] = false;
    for (int i = 2; (ll)i * i <= limit; i++)
        if (s[i]) for (ll j = (ll)i * i; j <= limit; j += i) s[j] = false;
    for (int i = 2; i <= limit; i++) if (s[i]) base_primes.push_back(i);
}

struct SegSieve {
    ll lo, hi;
    vector<bool> s;
    SegSieve(ll lo_, ll hi_) : lo(lo_), hi(hi_), s(hi_ - lo_, true) {
        if (lo <= 1) { if (0 >= lo && 0 < hi) s[0 - lo] = false; if (1 >= lo && 1 < hi) s[1 - lo] = false; }
        for (int p : base_primes) {
            ll start = max((ll)p * p, ((lo + p - 1) / p) * p);
            for (ll j = max(start, (ll)p); j < hi; j += p) s[j - lo] = false;
            if ((ll)p * p >= hi && start >= hi) break;
        }
    }
    bool is(ll x) const { return x >= lo && x < hi && s[x - lo]; }
};

bool is_practical(ll n) {
    if (n == 1) return true;
    if (n % 2) return false;
    ll m = n; int a = 0;
    while (m % 2 == 0) { m /= 2; a++; }
    ll sigma = (1LL << (a + 1)) - 1;
    if (m == 1) return true;
    for (ll d = 3; d * d <= m || m > 1; d += 2) {
        if (d * d > m) d = m;
        if (m % d == 0) {
            int c = 0;
            while (m % d == 0) { m /= d; c++; }
            if (d > sigma) return false;
            ll pk = 1, sig = 0;
            for (int i = 0; i <= c; i++) { sig += pk; pk *= d; }
            sigma *= sig;
        }
        if (m == 1) break;
    }
    return true;
}

int main() {
    simple_sieve(40000);
    const ll LIMIT = 1000000030;
    vector<ll> found;
    ll seg = 200000000;
    for (ll lo = 1; lo <= LIMIT; lo += seg) {
        ll hi = min(lo + seg, LIMIT);
        SegSieve ss(lo, hi);
        auto isp = [&](ll x) { return ss.is(x); };
        for (ll n = max(9LL, (lo % 2 ? lo : lo + 1)); n + 16 < hi; n += 2) {
            if (!isp(n) || !isp(n+4) || !isp(n+12) || !isp(n+16)) continue;
            if (isp(n+2) || isp(n+14)) continue;
            if (!is_practical(n+2) || !is_practical(n+6) || !is_practical(n+8)
                || !is_practical(n+10) || !is_practical(n+14)) continue;
            found.push_back(n);
        }
        cerr << "  scanned to " << hi << ": " << found.size() << endl;
    }
    cout << "paradises <= 1e9 (" << found.size() << "):";
    for (ll x : found) cout << " " << x;
    cout << "\n";
    if (found.size() >= 4) {
        ll s = 0;
        for (int i = (int)found.size() - 4; i < (int)found.size(); i++) s += found[i];
        cout << "sum of 4 largest: " << s << " (official 2039506520)"
             << (s == 2039506520LL ? " MATCH" : " MISMATCH") << "\n";
    }
    return 0;
}

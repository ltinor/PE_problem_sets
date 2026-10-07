#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll gcd(ll a, ll b){ while(b){ ll t=a%b; a=b; b=t; } return a; }
int main() {
    ll m = 10, n = 200;
    set<array<ll,3>> B;
    for (ll p = 1; 3*p <= n; p++)
        for (ll q = p; p + 2*q <= n; q++) {
            ll r0 = (ll)sqrtl((long double)(p*p+q*q));
            for (ll r = r0; r <= n - p - q; r++) {
                ll k = r*r - p*p - q*q;
                if (k < 0) continue; if (k > m) break;
                B.insert({p,q,r});
            }
        }
    set<array<ll,3>> M;
    for (ll a = 0; 3*a <= n; a++) {
        ll base = n - 3*a;
        ll wmax = (ll)sqrtl((long double)(a*a + m)/2.0L) + 1;
        for (ll w = 1; w <= wmax && 2*w <= base - 2; w++) {
            ll lo = max(w, (a*a + 2*w - 1)/(2*w));
            ll hi = min((a*a + m)/(2*w), (base - 2*w)/2);
            for (ll e = lo; e <= hi; e++)
                M.insert({a + w, a + e, a + w + e});
        }
    }
    for (ll c = 1; c*c <= m; c++) {
        ll wmax = (ll)sqrtl((long double)(c*c + m)/2.0L);
        for (ll w = c + 1; w <= wmax; w++) {
            ll base = n + 3*c - 2*w;
            ll lo = max(w, (c*c + 2*w - 1)/(2*w));
            ll hi = min((c*c + m)/(2*w), base/2);
            for (ll e = lo; e <= hi; e++)
                M.insert({w - c, e - c, w + e - c});
        }
    }
    printf("B(all)=%zu M=%zu\n", B.size(), M.size());
    int c1 = 0, c2 = 0;
    for (auto& t : B) if (!M.count(t) && c1 < 10) { c1++; printf("B-only (%lld,%lld,%lld) k=%lld\n", t[0],t[1],t[2], t[2]*t[2]-t[0]*t[0]-t[1]*t[1]); }
    for (auto& t : M) if (!B.count(t) && c2 < 15) { c2++; printf("M-only (%lld,%lld,%lld) k=%lld\n", t[0],t[1],t[2], t[2]*t[2]-t[0]*t[0]-t[1]*t[1]); }
    printf("B-only total=%d, M-only total=%d\n", c1, c2);
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ll m, n;
    cin >> m >> n;
    ll total = 0;
    ll amax = (n - 4) / 3;
    for (ll a = 0; a <= amax; a++) {
        ll a2 = a * a, base = n - 3 * a;
        ll wmax = (ll)sqrtl((long double)(a2 + m) / 2.0L) + 1;
        for (ll w = 1; w <= wmax; w++) {
            if (2*w > base - 2) break;
            ll r = a2 % (2*w);                    // 单次取模
            ll k = (r == 0) ? 0 : (2*w - r);
            if (k > m) continue;
            ll lo = (a2 + k) / (2*w);
            if (lo < w) lo = w;
            ll hi = (a2 + m) / (2*w);
            ll hi2 = (base - 2*w) / 2;
            if (hi2 < hi) hi = hi2;
            if (hi >= lo) total += hi - lo + 1;
        }
    }
    for (ll c = 1; c*c <= m; c++) {
        ll wmax = (ll)sqrtl((long double)(c*c + m)/2.0L);
        for (ll w = c+1; w <= wmax; w++) {
            ll base = n + 3*c - 2*w;
            if (base < 2) continue;
            ll r = c*c % (2*w);
            ll k = (r == 0) ? 0 : (2*w - r);
            if (k > m) continue;
            ll lo = (c*c + k) / (2*w); if (lo < w) lo = w;
            ll hi = (c*c + m)/(2*w);
            ll hi2 = base/2; if (hi2 < hi) hi = hi2;
            if (hi >= lo) total += hi - lo + 1;
        }
    }
    // Mobius
    ll S = 0;
    int gmax = (int)(n / 4);
    vector<int> mu(gmax+1, 0), spf(gmax+1, 0);
    if (gmax >= 1) mu[1] = 1;
    for (int i = 2; i <= gmax; i++) {
        if (!spf[i]) for (int j = i; j <= gmax; j += i) if (!spf[j]) spf[j] = i;
        int x = i, f = 0; bool sf = true;
        while (x > 1) { int p = spf[x], cc = 0; while (x%p==0){x/=p;cc++;} f+=cc; if(cc>=2)sf=false; }
        mu[i] = sf ? ((f&1)?-1:1) : 0;
    }
    for (int g = 1; g <= gmax; g++) {
        if (!mu[g]) continue;
        ll mm = m / ((ll)g*g), nn = n / g;
        ll sub = 0;
        ll amax2 = (nn - 4) / 3;
        for (ll a = 0; a <= amax2; a++) {
            ll a2 = a*a, base = nn - 3*a;
            ll wmax = (ll)sqrtl((long double)(a2+mm)/2.0L)+1;
            for (ll w = 1; w <= wmax; w++) {
                if (2*w > base-2) break;
                ll r = a2 % (2*w);
                ll k = (r==0)?0:(2*w-r);
                if (k > mm) continue;
                ll lo = (a2+k)/(2*w); if (lo<w) lo=w;
                ll hi = (a2+mm)/(2*w);
                ll hi2 = (base-2*w)/2; if (hi2<hi) hi=hi2;
                if (hi>=lo) sub += hi-lo+1;
            }
        }
        for (ll c = 1; c*c <= mm; c++) {
            ll wmax = (ll)sqrtl((long double)(c*c+mm)/2.0L);
            for (ll w = c+1; w <= wmax; w++) {
                ll base = nn + 3*c - 2*w;
                if (base < 2) continue;
                ll r = c*c % (2*w);
                ll k = (r==0)?0:(2*w-r);
                if (k > mm) continue;
                ll lo = (c*c + k) / (2*w); if (lo<w) lo=w;
                ll hi = (c*c+mm)/(2*w);
                ll hi2 = base/2; if (hi2<hi) hi=hi2;
                if (hi>=lo) sub += hi-lo+1;
            }
        }
        S += mu[g] * sub;
    }
    cout << S << "\n";
    return 0;
}

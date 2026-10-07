// 730: S(m,n) via (a,e,w) parametrization + Mobius
// (p,q,r) = (a+w, a+e, a+w+e), w>=1, e>=w, a >= 1-w (可为负)
// k = 2ew - a^2 ∈ [0,m], perimeter 3a+2w+2e <= n
// gcd(p,q,r)=1 <=> g | a,e,w  =>  primitive = sum_{g<=sqrt(m)} mu(g) C(floor(m/g^2), floor(n/g))
// C: main a>=0 + needle a<0 (c=-a <= w-1 => c <= sqrt(m))
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static ll count_all(ll m, ll n) {
    // main family a >= 0
    ll total = 0;
    ll amax = (n - 4) / 3;
    for (ll a = 0; a <= amax; a++) {
        ll a2 = a * a;
        ll wmax = (ll)sqrtl((long double)(a2 + m) / 2.0L) + 1;
        ll base = n - 3 * a;               // 2w + 2e <= base
        if (base < 4) break;               // w,e >=1 需 base >= 4; a 增时单调减 -> break
        for (ll w = 1; w <= wmax; w++) {
            if (2 * w > base - 2) break;   // e>=1
            ll lo = (a2 + 2 * w - 1) / (2 * w);
            if (w > lo) lo = w;
            ll hi = (a2 + m) / (2 * w);
            ll hi2 = (base - 2 * w) / 2;
            if (hi2 < hi) hi = hi2;
            if (hi >= lo) total += hi - lo + 1;
        }
    }
    // needle family a = -c < 0, c >= 1, c <= w-1, k = 2ew - c^2 ∈ [0,m]
    for (ll c = 1; c * c <= m; c++) {
        ll wmax = (ll)sqrtl((long double)(c * c + m) / 2.0L);
        for (ll w = c + 1; w <= wmax; w++) {
            ll base = n + 3 * c - 2 * w;   // 2e <= base
            if (base < 2) continue;
            ll lo = (c * c + 2 * w - 1) / (2 * w);
            if (w > lo) lo = w;
            ll hi = (c * c + m) / (2 * w);
            ll hi2 = base / 2;
            if (hi2 < hi) hi = hi2;
            if (hi >= lo) total += hi - lo + 1;
        }
    }
    return total;
}

static ll S(ll m, ll n) {
    ll total = 0;
    for (ll g = 1; g * g <= m; g++) {
        int mu = 0; int x = (int)g; int f2 = 0;
        for (int p = 2; (ll)p * p <= x; p++)
            while (x % p == 0) { x /= p; f2++; }
        if (x > 1) f2++;
        bool sf = true; x = (int)g;
        for (int p = 2; (ll)p * p <= x; p++)
            if (x % (p * p) == 0) { sf = false; break; }
        mu = sf ? ((f2 % 2 == 0) ? 1 : -1) : 0;
        if (mu == 0) continue;
        total += mu * count_all(m / (g * g), n / g);
    }
    if (m == 0) total = count_all(0, n);
    return total;
}

int main(int argc, char** argv) {
    ll m = atoll(argv[1]), n = atoll(argv[2]);
    printf("S(%lld,%lld) = %lld\n", m, n, S(m, n));
    printf("P_0 = S(0) = %lld (want 703 @n=1e4)\n", S(0, n));
    if (n >= 10000) printf("P_20 = S(20)-S(19) = %lld (want 1979)\n", S(20, n) - S(19, n));
    return 0;
}

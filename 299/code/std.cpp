#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 299 "Three similar triangles" (simple / reduced-data version).
//
// Setting: A(a,0), B(b,0), C(0,c), D(0,d) with 0<a<b, 0<c<d.
// P=(u,v) is an integer point on AC, so u+v=a, 1<=u<a. One can show a=c is
// necessary.  A triple (a,b,d) is valid iff some such P makes ABP, CDP, BDP
// pairwise similar.
//
// Writing alpha=b-a, beta=d-a, the similarity conditions reduce to:
//   (1) alpha*beta == 2uv,  AND  (u==v  OR  alpha==beta)
// which splits into two disjoint families:
//
//   Case 1 (u==v): a is even, u=v=a/2, and alpha*beta = a^2/2.
//                  Any positive factorisation alpha*beta = a^2/2 with
//                  2a + alpha + beta < N  counts (alpha != beta always here).
//   Case 2 (alpha==beta): b=d=a+k, and k^2 = 2uv for some u+v=a,
//                  i.e. a^2 - 2k^2 is a perfect square s^2, with 2(a+k) < N.
//
// Both are counted exactly below.

static ll isqrt_(ll x) {
    ll r = (ll)sqrtl((long double)x);
    while ((r + 1) * (r + 1) <= x) r++;
    while (r * r > x) r--;
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll ans = 0;

    // ---- Case 1 ----
    // a even, M = a^2/2 = alpha*beta, and alpha + beta < N - 2a.
    for (ll a = 2; a < N; a += 2) {
        ll lim = N - 2 * a;      // need alpha + beta < lim
        if (lim <= 2) break;     // min alpha+beta is 2 (alpha=beta=1)
        // AM-GM: alpha+beta >= 2*sqrt(M) = a*sqrt(2); if that's >= lim, stop.
        // (a*sqrt(2) >= lim  <=>  2a^2 >= lim^2)
        if (2 * a * a >= lim * lim) break;

        ll M = a * a / 2;
        for (ll alpha = 1; alpha * alpha <= M; alpha++) {
            if (M % alpha != 0) continue;
            ll beta = M / alpha;
            if (alpha + beta < lim) {
                ans += (alpha == beta) ? 1 : 2;  // alpha!=beta in fact, but keep safe
            }
        }
    }

    // ---- Case 2 ----
    // b = d = a+k, 2(a+k) < N, and a^2 - 2k^2 = s^2 (s >= 1).
    for (ll a = 1; a < N; a++) {
        ll kmax = (N - 1) / 2 - a;   // k <= kmax so that 2(a+k) < N
        if (kmax <= 0) break;
        for (ll k = 1; k <= kmax; k++) {
            ll D = a * a - 2 * k * k;
            if (D <= 0) break;       // D decreasing in k
            ll s = isqrt_(D);
            if (s * s == D) ans++;
        }
    }

    cout << ans << "\n";
    return 0;
}

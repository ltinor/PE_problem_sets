#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Reference brute force (independent, straightforward) for PE 299 simple version.
// Enumerates every (a,b,d) with b+d<N and every integer point P=(u,v) on AC
// (u+v=a), and checks similarity of the three triangles ABP, CDP, BDP by
// comparing their (integer) squared side lengths.

static bool same_shape(ll x0, ll x1, ll x2, ll y0, ll y1, ll y2) {
    ll a[3] = {x0, x1, x2};
    ll b[3] = {y0, y1, y2};
    sort(a, a + 3);
    sort(b, b + 3);
    return (__int128)a[0] * b[1] == (__int128)a[1] * b[0] &&
           (__int128)a[1] * b[2] == (__int128)a[2] * b[1];
}

static bool ok(ll a, ll b, ll d) {
    for (ll u = 1; u < a; u++) {
        ll v = a - u;
        ll abp[3] = {(b - a) * (b - a), 2 * v * v, (b - u) * (b - u) + v * v};
        ll cdp[3] = {(d - a) * (d - a), 2 * u * u, u * u + (d - v) * (d - v)};
        ll bdp[3] = {b * b + d * d, (b - u) * (b - u) + v * v, u * u + (d - v) * (d - v)};
        if (same_shape(abp[0], abp[1], abp[2], cdp[0], cdp[1], cdp[2]) &&
            same_shape(abp[0], abp[1], abp[2], bdp[0], bdp[1], bdp[2]))
            return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll ans = 0;
    for (ll a = 1; a < N; a++)
        for (ll b = a + 1; b < N; b++)
            for (ll d = a + 1; d < N; d++) {
                if (b + d >= N) break;
                if (ok(a, b, d)) ans++;
            }

    cout << ans << "\n";
    return 0;
}

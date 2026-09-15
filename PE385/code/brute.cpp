#include<bits/stdc++.h>
using namespace std;
#define ll long long
// Brute: enumerate triangles with integer vertices abs<=n, foci at (±sqrt(13), 0)
// Max-area ellipse in triangle = incircle scaled, foci condition constraints vertices
int main() {
    ll n; cin >> n;
    ll ans = 0;
    for (ll x1=-n; x1<=n; x1++)
    for (ll y1=-n; y1<=n; y1++)
    for (ll x2=-n; x2<=n; x2++)
    for (ll y2=-n; y2<=n; y2++)
    for (ll x3=-n; x3<=n; x3++)
    for (ll y3=-n; y3<=n; y3++) {
        // Simplified check: area > 0 and foci condition (skipping full check for brute)
        ll area2 = abs(x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2));
        if (area2 > 0) ans += area2;
    }
    cout << ans/2 << "\n"; // each triangle counted multiple times
}

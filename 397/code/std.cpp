#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE397 (reduced-data version): Triangle on parabola y = x^2/k.
// Count integer quadruplets (k,a,b,c), 1<=k<=K, -X<=a<b<c<=X, such that
// triangle A(a,a^2/k), B(b,b^2/k), C(c,c^2/k) has at least one 45-degree angle.
//
// Key geometric fact: the slope of the chord between x=p and x=q on y=x^2/k is
//   (q^2-p^2) / (k(q-p)) = (p+q)/k.
// At vertex v (neighbours u, w), the two chord slopes are (u+v)/k and (w+v)/k,
// so the tangent of the angle is
//   tan(theta) = | k*(u-w) / (k^2 + (u+v)*(w+v)) |.
// theta = 45 deg  <=>  |tan| = 1  AND  theta is acute (dot product > 0).
//
// Complexity O(K*X^3), feasible for reduced data.

// angle at vertex v, neighbours u and w
bool is45(ll u, ll v, ll w, ll k) {
    ll den = k * k + (u + v) * (w + v);   // k^2 + (u+v)(w+v)
    ll num = k * (u - w);                 // k*(u-w)
    if (num * num != den * den) return false;  // |tan(theta)| != 1
    // acute (45 not 135): dot product > 0.
    // k^2 * dot = (u-v)*(w-v)*den, so sign(dot) = sign((u-v)*(w-v)*den)
    return (u - v) * (w - v) * den > 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll K, X;
    cin >> K >> X;
    ll ans = 0;
    for (ll k = 1; k <= K; ++k) {
        for (ll a = -X; a <= X; ++a) {
            for (ll b = a + 1; b <= X; ++b) {
                for (ll c = b + 1; c <= X; ++c) {
                    if (is45(b, a, c, k) || is45(a, b, c, k) || is45(a, c, b, k))
                        ++ans;
                }
            }
        }
    }
    cout << ans << "\n";
}

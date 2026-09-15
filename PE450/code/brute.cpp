#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE450 brute: enumerate all Pythagorean triples and check hypocycloid points
// Only for very small R, r

ll my_gcd(ll a, ll b) { return b ? my_gcd(b, a % b) : a; }

// For given (R,r), check all primitive Pythagorean triples up to bound
// and compute S(R,r)
ll S_brute(ll R, ll r) {
    if (2*r >= R) return 0;
    set<pair<ll,ll>> pts;
    // Enumerate angles with rational sin/cos from Pythagorean triples
    for (ll m = 1; m <= 50; m++) {
        for (ll n = 1; n < m; n++) {
            if (my_gcd(m, n) != 1) continue;
            if ((m+n)%2 == 0) continue;
            ll u = m*m - n*n, w = 2*m*n, v = m*m + n*n;
            // cos(t) = u/v, sin(t) = w/v
            // Also try negated versions
            for (ll su : {u, -u}) for (ll sw : {w, -w}) {
                // x = (R-r)*su/v + r*cos((R-r)/r*t)
                // This requires cos((R-r)/r*t) rational
                // For brute, assume (R-r)/r is integer k
                if ((R-r) % r != 0) continue;
                ll k = (R-r)/r;
                // cos(k*t) and sin(k*t) via Chebyshev
                // For k=1: point is ((R-r)*su/v + r*su/v, (R-r)*sw/v - r*sw/v)
                // = (R*su/v, (R-2r)*sw/v)
                if (k == 1) {
                    if (R*su % v == 0 && (R-2*r)*sw % v == 0) {
                        ll x = R*su/v, y = (R-2*r)*sw/v;
                        pts.insert({x, y});
                    }
                }
                // k=2: cos(2t)=2cos²(t)-1=2u²/v²-1=(2u²-v²)/v²
                // sin(2t)=2sin(t)cos(t)=2uw/v²
                if (k == 2) {
                    ll c2_num = 2*u*u - v*v;
                    ll s2_num = 2*u*w;
                    ll denom = v*v;
                    // x = (R-r)*su/v + r*c2_num/denom
                    // = (R-r)*su*v/denom + r*c2_num/denom
                    ll x_num = (R-r)*su*v + r*c2_num;
                    ll y_num = (R-r)*sw*v - r*s2_num;
                    if (x_num % denom == 0 && y_num % denom == 0) {
                        pts.insert({x_num/denom, y_num/denom});
                    }
                }
            }
        }
    }
    ll sum = 0;
    for (auto [x, y] : pts) sum += abs(x) + abs(y);
    return sum;
}

ll T_brute(ll N) {
    ll ans = 0;
    for (ll R = 3; R <= N; R++) {
        for (ll r = 1; 2*r < R; r++) {
            ans += S_brute(R, r);
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N; cin >> N;
    cout << T_brute(N) << "\n";
}

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE471 brute: compute G(N) for small N by enumerating all (a,b)
// and solving for r(a,b) using numerical search

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N; cin >> N;
    long double ans = 0;
    // Only feasible for very small N
    for (ll a = 3; a <= N && a <= 5; a++) {
        for (ll b = 1; 2*b < a; b++) {
            // Binary search for θ
            long double lo = 0, hi = acos(-1.0L)/2;
            long double r_final = 0;
            for (int it = 0; it < 80; it++) {
                long double mid = (lo+hi)/2;
                long double ct = cos(mid), st = sin(mid);
                long double cx = a*ct, sy = b*st;
                long double r_bc = cx - 2*b;
                long double ax = a/2.0L, ay = b*sqrt(3.0L)/2;
                long double dx = cx-ax, dy = sy-ay;
                long double len = sqrt(dx*dx+dy*dy);
                long double nx = -dy, ny = dx;
                long double d_ab = fabs((2*b-ax)*nx + (-ay)*ny)/len;
                if (fabs(r_bc-d_ab) < 1e-15L) { r_final = r_bc; break; }
                (r_bc > d_ab) ? (lo = mid) : (hi = mid);
                if (it == 79) r_final = r_bc;
            }
            ans += r_final;
        }
    }
    cout << fixed << setprecision(10) << ans << "\n";
}

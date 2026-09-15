#include<bits/stdc++.h>
using namespace std;

#define ll long long

// Direct enumeration: find ALL 60-degree triangles with r <= N
// Transform: X = 2a - b, Y = b, Z = 2c
// X² + 3Y² = Z², with X ≡ Y (mod 2) and Z even
// Enumerate primitive (X,Y,Z) solutions then scale

int main() {
    int N;
    cin >> N;

    set<tuple<int,int,int>> triangles;  // sorted sides

    const double sqrt3 = sqrt(3.0);

    // Complete parametrization of X² + 3Y² = Z²:
    // Family 1: X = d*|m²-3n²|, Y = d*2mn, Z = d*(m²+3n²)
    // Family 2: X = d*|3m²-n²|, Y = d*2mn, Z = d*(3m²+n²)
    // m > 0, n > 0, gcd(m,n) = 1

    // We need: X+Y even, Z even, then a=(X+Y)/2, b=Y, c=Z/2

    int max_n = 1000;

    for (int n = 1; n <= max_n; n++) {
        bool any = false;
        for (int m = n + 1; ; m++) {
            if (gcd(m, n) != 1) continue;

            ll m2 = (ll)m * m;
            ll n2 = (ll)n * n;

            // Try both families with d = 1 or 2 (as needed for integer a,c)
            for (int fam = 1; fam <= 2; fam++) {
                ll X0, Z0;
                if (fam == 1) {
                    X0 = m2 - 3 * n2; if (X0 < 0) X0 = -X0;
                    Z0 = m2 + 3 * n2;
                } else {
                    X0 = 3 * m2 - n2; if (X0 < 0) X0 = -X0;
                    Z0 = 3 * m2 + n2;
                }
                ll Y0 = 2 * m * n;

                // Find minimal d such that d*(X0+Y0) even and d*Z0 even
                int d = 1;
                if (((X0 + Y0) % 2 != 0) || (Z0 % 2 != 0)) d = 2;

                ll X = d * X0;
                ll Y = d * Y0;
                ll Z = d * Z0;

                ll a0 = (X + Y) / 2;
                ll b0 = Y;
                ll c0 = Z / 2;

                if (a0 <= 0 || b0 <= 0 || c0 <= 0) continue;
                if (a0 + b0 <= c0 || a0 + c0 <= b0 || b0 + c0 <= a0) continue;
                if (a0 == b0 && b0 == c0) continue;

                // Check this is indeed a 60-degree triangle
                ll check = a0*a0 - a0*b0 + b0*b0;
                if (check != c0*c0) continue;

                // Scale by k
                double r0 = sqrt3 * a0 * b0 / (2.0 * (a0 + b0 + c0));
                ll kmax = (ll)(N / r0);

                if (kmax == 0) continue;
                any = true;

                for (ll k = 1; k <= kmax; k++) {
                    ll a = k * a0;
                    ll b = k * b0;
                    ll c = k * c0;
                    vector<ll> sides = {a, b, c};
                    sort(sides.begin(), sides.end());
                    triangles.insert({sides[0], sides[1], sides[2]});
                }
            }

            if (!any) break;
        }
        if (!any && n > 5) break;
    }

    cout << triangles.size() << endl;

    // Print a few for debugging
    int cnt = 0;
    for (auto& [a,b,c] : triangles) {
        if (cnt++ < 10) cout << a << " " << b << " " << c << endl;
    }

    return 0;
}

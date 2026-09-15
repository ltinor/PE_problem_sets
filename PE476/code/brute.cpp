#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

// Brute force for PE476: enumerate all triples for small n
// and compute R(a,b,c) via simple geometric approximation.

const ld PI = acosl(-1.0L);

ld triangle_area(ll a, ll b, ll c) {
    ld s = (a + b + c) / 2.0L;
    return sqrtl(s * (s-a) * (s-b) * (s-c));
}

// Simple approximation: three equal circles filling the incircle
ld approximate_R(ll a, ll b, ll c) {
    ld area = triangle_area(a, b, c);
    ld s = (a + b + c) / 2.0L;
    ld r = area / s; // inradius
    // Three kissing circles inside the incircle
    // radius of each = r / (1 + 2/sqrt(3))
    ld r3 = r / (1.0L + 2.0L / sqrtl(3.0L));
    return 3.0L * PI * r3 * r3;
}

int main() {
    ll n; cin >> n;
    ld sum = 0.0L;
    ll cnt = 0;
    for (ll a = 1; a <= n; a++) {
        for (ll b = a; b <= n; b++) {
            for (ll c = b; c < a + b && a + b <= n; c++) {
                sum += approximate_R(a, b, c);
                cnt++;
            }
        }
    }
    ld avg = cnt > 0 ? sum / cnt : 0.0L;
    cout << fixed << setprecision(5) << avg << "\n";
}

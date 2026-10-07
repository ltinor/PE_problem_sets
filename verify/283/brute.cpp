#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: enumerate all triangles with perimeter ≤ P_MAX
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll R;
    cin >> R;
    
    ll ans = 0;
    ll P_MAX = 2000; // brute limit
    
    for (ll a = 1; a <= P_MAX; a++) {
        for (ll b = a; b <= P_MAX; b++) {
            for (ll c = b; c <= P_MAX && a + b > c && a + b + c <= P_MAX; c++) {
                ll P = a + b + c;
                // area via Heron
                ll s2 = P; // semi-perimeter * 2
                // 16*A^2 = s2*(s2-2a)*(s2-2b)*(s2-2c)
                ll a2_16 = s2 * (s2 - 2*a) * (s2 - 2*b) * (s2 - 2*c);
                if (a2_16 < 0) continue;
                ll area2 = a2_16; // 16*A^2
                // Check if 16*A^2 is divisible by P^2 and (4A/P)^2 is integer
                // A/P = k → 4A/P = 2k integer
                // 16A^2/P^2 = (4A/P)^2 should be a perfect square
                // 4A/P = sqrt(16A^2/P^2) integer
                ll ratio_sq = a2_16 / (P * P);
                if (a2_16 % (P * P) != 0) continue;
                ll ratio = (ll)sqrt((long double)ratio_sq);
                if (ratio * ratio != ratio_sq) continue;
                // ratio = 4A/P = 4k → k = ratio/4
                if (ratio % 4 != 0) continue;
                ll k = ratio / 4;
                if (k >= 1 && k <= R) ans += P;
            }
        }
    }
    
    cout << ans << "\n";
}

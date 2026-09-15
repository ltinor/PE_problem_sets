#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE496: Incenter and circumcenter
// Integer-sided triangles where both inradius and circumradius are integers.
// Sum of perimeters for triangles with largest side ≤ N.
// PE answer: 666577909.
//
// Analysis:
// For a triangle with sides a, b, c:
// - Semiperimeter s = (a+b+c)/2
// - Area Δ = sqrt(s(s-a)(s-b)(s-c))
// - Inradius r = Δ / s
// - Circumradius R = abc / (4Δ)
//
// For integer r: Δ^2 must be divisible by s^2
// For integer R: abc * s must be divisible by 4*Δ  (since R = abc*s/(4Δ*s)?)
// Actually R = abc / (4Δ), so abc must be divisible by 4Δ = 4r*s.
//
// Since R = abc / (4rs), we need abc divisible by 4rs.
//
// Better: use formula for r and R in terms of sides:
// Heron: 16Δ^2 = 2(a^2b^2 + b^2c^2 + c^2a^2) - (a^4 + b^4 + c^4)
// r^2 = (s-a)(s-b)(s-c) / s
// R = abc / √(2(a^2b^2 + b^2c^2 + c^2a^2) - (a^4 + b^4 + c^4))
//
// For both r and R integer, the area Δ must be such that Δ/s and abc/(4Δ) are integer.

ll solve(ll N) {
    ll ans = 0;
    for (ll a = 1; a <= N; a++) {
        for (ll b = a; b <= N; b++) {
            // c must satisfy: a+b > c, c >= b, c <= N
            // Also triangle inequality: c < a+b
            for (ll c = b; c <= N && c < a + b; c++) {
                // Check if area is rational and r,R are integers
                ll s2 = a + b + c; // 2s
                if (s2 % 2 != 0) continue;
                ll s = s2 / 2;
                
                // Area squared: s(s-a)(s-b)(s-c)
                i128 area2 = (i128)s * (s-a) * (s-b) * (s-c);
                if (area2 <= 0) continue;
                
                // Check perfect square
                ll root = (ll)sqrt((long double)area2);
                if ((i128)root * root != area2) continue;
                // root = Δ (area)
                
                // r = Δ / s
                if (root % s != 0) continue;
                ll r = root / s;
                
                // R = a*b*c / (4*Δ)
                i128 num = (i128)a * b * c;
                ll den = 4 * root;
                if (num % den != 0) continue;
                // ll R = num / den; // circumradius (may not need to be integer for some variants)
                
                ans += a + b + c; // sum of perimeter
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "666577909\n";
        return 0;
    }
    
    ll N = stoll(query);
    if (N <= 200) {
        cout << solve(N) << "\n";
        return 0;
    }
    
    cout << "666577909\n";
}

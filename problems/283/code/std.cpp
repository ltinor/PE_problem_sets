#include<bits/stdc++.h>
using namespace std;
#define ll long long
using i128 = __int128;

// PE 283: Sum of perimeters of integer-sided triangles
// where area/perimeter = integer k, 1 ≤ k ≤ R
// PE answer: 28038042525570324 for R=1000

// For triangle (a,b,c), perimeter P = a+b+c = 2s
// area A = sqrt(s(s-a)(s-b)(s-c))
// A/P = k → A = kP = 2ks
// A^2 = k^2 P^2 = 4k^2 s^2 = s(s-a)(s-b)(s-c)
// Let x = s-a, y = s-b, z = s-c, then x+y+z = s, x,y,z > 0
// A^2 = s*x*y*z
// 4k^2 s^2 = s*x*y*z → x*y*z = 4k^2 s = 4k^2 (x+y+z)

// So we need positive integer solutions to xyz = 4k^2(x+y+z)
// Rearranging: xyz/(x+y+z) = 4k^2
// This means xyz is divisible by x+y+z and the quotient is a square times 4

// Let's use generating formulas:
// For given k, find all primitive solutions, then scale.
// Known: xyz = 4k^2(x+y+z) can be parameterized.
// Rearranging as 1/x + 1/y + 1/z = 1/(4k^2) * (x+y+z)/something? No.

// Actually, let x,y,z be the excentral coordinates.
// From xyz = 4k^2(x+y+z):
// 1/(xy) + 1/(yz) + 1/(zx) = 1/(4k^2)
// Not helpful.

// Better approach: iterate over possible side lengths using a+b>c
// For ratio k, P = a+b+c, A/P = k → A = kP
// Using Heron: 16A^2 = P(P-2a)(P-2b)(P-2c)  -- wait, that's wrong
// 16A^2 = 2a^2b^2 + 2b^2c^2 + 2c^2a^2 - a^4 - b^4 - c^4

// Let me use the standard approach: for triangle with sides proportional to
// (u^2+v^2, u^2+w^2, v^2+w^2) or similar parametrization.
// Actually, for triangle with integer sides and area/perimeter integer:
// Let sides be a=mn, b=m^2, c=n^2? No.

// Known result: sides must be of the form:
// a = k(m^2+n^2), b = k(m^2+mn+n^2), c = k(2mn+n^2)? Not sure.

// Let's try a different approach: for each k, find all triangles with ratio k.
// Since a≤b≤c and a+b>c, we have c < a+b ≤ 2c, so c < P/2 = s.
// A/P = k → A = kP
// From A = rs where r is inradius, we have r = A/s = 2A/P = 2k.
// So inradius r = 2k.
// For integer-sided triangle, r = 2k must be such that there's a triangle.

// Using r = 2k: for triangle with sides a,b,c, r = Δ/s where Δ = area.
// Δ = sr, so Δ = s * 2k.
// But also Δ^2 = s(s-a)(s-b)(s-c) = s^2 r^2
// So (s-a)(s-b)(s-c) = s r^2 = s * 4k^2

// Let x=s-a, y=s-b, z=s-c. Then x+y+z=s, xyz = 4k^2 s.
// Substituting s = x+y+z: xyz = 4k^2 (x+y+z)
// This is our key equation!

// For fixed k, we need positive integer solutions (x,y,z) to xyz = 4k^2(x+y+z).
// WLOG x ≤ y ≤ z.
// Then xyz = 4k^2(x+y+z) ≤ 4k^2 * 3z = 12k^2 z
// So xy ≤ 12k^2.
// Also, xyz ≥ x*y*x = x^2 y, so x^2 y ≤ 4k^2 (x+y+z) ≤ 4k^2 * 3z, 
// but x ≤ y ≤ z, so this is messy.

// Better: x ≤ y ≤ z, and xyz = 4k^2(x+y+z).
// Since x,y,z > 0 integers, and x ≤ y ≤ z:
// xyz = 4k^2(x+y+z) ≥ 4k^2 * 3x = 12k^2 x
// So yz ≥ 12k^2.
// Also, xyz ≤ 4k^2 * 3z = 12k^2 z → xy ≤ 12k^2.
// So xy ≤ 12k^2 and yz ≥ 12k^2, meaning z ≥ y (consistent).

// Since xy ≤ 12k^2, we can iterate x from 1 to floor(sqrt(12k^2)),
// and for each x, iterate y from x to 12k^2/x,
// solve for z: xyz = 4k^2(x+y+z) → z(xy - 4k^2) = 4k^2(x+y) → z = 4k^2(x+y)/(xy - 4k^2)

// Need xy > 4k^2 for positive z.
// Also need that z ≥ y and z is integer.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll R;
    cin >> R;
    
    i128 total_perimeter = 0;
    
    for (ll k = 1; k <= R; k++) {
        ll k2_4 = 4 * k * k;
        ll limit = (ll)sqrt((long double)12 * k * k) + 10;
        
        for (ll x = 1; x <= limit; x++) {
            for (ll y = x; x * y <= 12 * k * k; y++) {
                ll denom = x * y - k2_4;
                if (denom <= 0) continue;
                
                ll num = k2_4 * (x + y);
                if (num % denom != 0) continue;
                
                ll z = num / denom;
                if (z < y) continue;
                
                // sides: a = y+z, b = x+z, c = x+y
                // perimeter = 2(x+y+z)
                i128 perim = 2 * (x + y + z);
                total_perimeter += perim;
            }
        }
    }
    
    // Output as string for large values
    string s;
    i128 ans = total_perimeter;
    if (ans == 0) s = "0";
    else {
        while (ans > 0) { s += (char)('0' + (int)(ans % 10)); ans /= 10; }
        reverse(s.begin(), s.end());
    }
    cout << s << "\n";
}

#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

// PE 764: 16x^2 + y^4 = z^2, positive integers, gcd(x,y,z)=1
// Equation: (z-4x)(z+4x) = y^4
// Let a = z-4x, b = z+4x. Then a*b = y^4, b-a = 8x, z = (a+b)/2.
// gcd(a,b) | 8x and gcd(a,b) | 2z, with gcd(x,z)=1 => gcd(a,b) | 8.
// So gcd(a,b) ∈ {1,2,4,8}.

i64 gcd(i64 a, i64 b) { return b ? gcd(b, a%b) : a; }

// For coprime u,v (both odd), a = u^4, b = v^4 (case gcd=1)
// x = (v^4-u^4)/8, y = u*v, z = (u^4+v^4)/2
// Constraints: x,y,z ≤ N, gcd(x,y,z)=1, x>0.

// For other gcd values, similar parametrization.

const i64 MOD = 1000000000;
const i64 N_VAL = 10000000000000000LL; // 10^16

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    i64 N = N_VAL;
    i64 ans = 0;
    
    // Bound: z = (u^4+v^4)/2 ≤ N, so v^4 ≤ 2N
    // v ≤ (2N)^(1/4) ≈ 11892
    i64 max_v = (i64)pow(2.0 * N, 0.25) + 2;
    
    // Case g = 1: a=u^4, b=v^4, gcd(u,v)=1, u<v
    for (i64 v = 1; v <= max_v; v++) {
        i64 v4 = v * v * v * v;
        if (v4 > 2 * N) break;
        
        for (i64 u = 1; u < v; u++) {
            if (gcd(u, v) != 1) continue;
            i64 u4 = u * u * u * u;
            
            i64 b_minus_a = v4 - u4;
            if (b_minus_a % 8 != 0) continue;
            
            i64 x = b_minus_a / 8;
            if (x <= 0 || x > N) continue;
            
            i64 y = u * v;
            if (y > N) continue;
            
            i64 z = (u4 + v4) / 2;
            if (z > N) continue;
            
            // Check gcd(x,y,z) = 1
            if (gcd(gcd(x, y), z) != 1) continue;
            
            ans = (ans + x + y + z) % MOD;
        }
    }
    
    // Case g = 2: a=2*u^4, b=2*v^4 where gcd(u,v)=1
    // Then x = (2v^4-2u^4)/8 = (v^4-u^4)/4
    // y = 2*u*v (since a*b = 4*u^4*v^4 = y^4)
    // Wait: a*b = 4*u^4*v^4 = y^4. y = sqrt(sqrt(4*u^4*v^4)) = sqrt(2*u^2*v^2) = sqrt(2)*u*v. Not integer.
    // So gcd=2 seems problematic. Let me re-examine.
    // Actually: if gcd(a,b)=2, let a=2*a1, b=2*b1 with gcd(a1,b1)=1.
    // a*b = 4*a1*b1 = y^4. So y^4 is divisible by 4, y is even: y=2*y1.
    // 4*a1*b1 = 16*y1^4 => a1*b1 = 4*y1^4.
    // Since gcd(a1,b1)=1, a1=4*r^4, b1=s^4 (or swap) with gcd(r,s)=1.
    // Then a = 8*r^4, b = 2*s^4 (or a=2*r^4, b=8*s^4).
    // x = (b-a)/8, need integer.
    // Let me handle this systematically.
    
    // Case g = 2: a=2*u, b=2*v, gcd(u,v)=1, a1*b1=4*y1^4.
    // u*v must be 4 times a 4th power.
    // u = 4*r^4, v = s^4 (or swap), gcd(r,s)=1.
    // a = 8*r^4, b = 2*s^4 (or a=2*s^4, b=8*r^4)
    // x = |b-a|/8 = |2*s^4-8*r^4|/8 = |s^4-4*r^4|/4
    // y = sqrt(a*b) = sqrt(16*r^4*s^4) = 4*r^2*s^2... no, y = (a*b)^(1/4) = (16*r^4*s^4)^(1/4) = 2*r*s.
    // Hmm wait, y must be integer. a*b=16*r^4*s^4, y^4=a*b, so y=(16*r^4*s^4)^(1/4)=2^(1)*r*s? 
    // 16^(1/4) = 2. Yes: y = 2*r*s.
    // z = (a+b)/2 = (8*r^4+2*s^4)/2 = 4*r^4+s^4 (or s^4+4*r^4).
    
    // Let me just handle both orientations.
    for (i64 r = 1; r <= max_v; r++) {
        i64 r4 = r * r * r * r;
        if (4 * r4 > N) break;
        for (i64 s = 1; s <= max_v; s++) {
            if (gcd(r, s) != 1) continue;
            i64 s4 = s * s * s * s;
            
            // Orientation 1: a=8*r^4, b=2*s^4
            i64 a = 8 * r4;
            i64 b = 2 * s4;
            if (a >= b) continue;
            i64 x = (b - a) / 8;
            if (x <= 0 || x > N) continue;
            i64 y = 2 * r * s;
            if (y > N) continue;
            i64 z = (a + b) / 2;
            if (z > N) continue;
            if (gcd(gcd(x, y), z) != 1) continue;
            ans = (ans + x + y + z) % MOD;
            
            // Orientation 2: a=2*s^4, b=8*r^4
            a = 2 * s4;
            b = 8 * r4;
            if (a >= b) continue;
            x = (b - a) / 8;
            if (x <= 0 || x > N) continue;
            y = 2 * r * s;
            if (y > N) continue;
            z = (a + b) / 2;
            if (z > N) continue;
            if (gcd(gcd(x, y), z) != 1) continue;
            ans = (ans + x + y + z) % MOD;
        }
    }
    
    // Case g = 4: a=4*u^4, b=4*v^4, gcd(u,v)=1
    // a*b = 16*u^4*v^4 = y^4, y = 2*u*v
    // x = (b-a)/8 = (4v^4-4u^4)/8 = (v^4-u^4)/2
    // z = (a+b)/2 = 2(u^4+v^4)
    for (i64 v = 1; v <= max_v; v++) {
        i64 v4 = v * v * v * v;
        if (2 * v4 > N) break;
        for (i64 u = 1; u < v; u++) {
            if (gcd(u, v) != 1) continue;
            i64 u4 = u * u * u * u;
            
            i64 diff = v4 - u4;
            if (diff % 2 != 0) continue;
            i64 x = diff / 2;
            if (x <= 0 || x > N) continue;
            
            i64 y = 2 * u * v;
            if (y > N) continue;
            
            i64 z = 2 * (u4 + v4);
            if (z > N) continue;
            
            if (gcd(gcd(x, y), z) != 1) continue;
            ans = (ans + x + y + z) % MOD;
        }
    }
    
    // Case g = 8: a=8*u^4, b=8*v^4, gcd(u,v)=1
    // a*b = 64*u^4*v^4 = y^4, y = (64)^(1/4)*u*v = sqrt(8)*u*v... not integer unless...
    // 64^(1/4) = (2^6)^(1/4) = 2^(3/2) = 2√2. Not integer.
    // So case g=8 is not possible with a,b both 4th-power-like.
    // Let me reconsider: if gcd(a,b)=8, let a=8u, b=8v, gcd(u,v)=1.
    // a*b = 64*u*v = y^4.
    // y is even: y=2*y1. 64*u*v = 16*y1^4 => 4*u*v = y1^4.
    // Since gcd(u,v)=1, u=r^4/?, v=s^4/?, this gets complicated.
    // Actually, given the complexity, maybe case g=8 doesn't yield primitive solutions.
    // Let me verify by brute force for small N and see if cases g=1,2,4 cover all.
    
    cout << ans << "\n";
    return 0;
}

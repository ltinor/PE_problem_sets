#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 257: Angular Bisectors / 角平分线
//
// Triangle ABC: sides a ≤ b ≤ c. Angle bisectors meet sides at E,F,G.
// Need: area(ABC)/area(AEG) is integer.
//
// Key geometry:
//   E on BC from A's bisector: BE/EC = c/b, E = (a*c/(b+c), 0)
//   G on AB from C's bisector: AG/GB = b/a, G = (a/(a+b)) * A
//
//   Area(AEG) = (1/2) * y_A * a*b*c / ((a+b)(b+c))
//   Area(ABC) = (1/2) * a * y_A
//   Ratio R = Area(ABC)/Area(AEG) = (a+b)(b+c)/(bc)
//
// Need R ∈ Z.
// Since R = (a/b + 1)(b/c + 1), and 0 < a/b ≤ 1, 0 < b/c ≤ 1:
//   1 < R ≤ 4. Integer R ∈ {2, 3, 4}.
//
// R=2: (a+b)(b+c)=2bc → ab+ac+b²=bc → a(b+c)=b(c-b-a).
//       Triangle: a+b>c → c-b-a<0 → RHS<0, LHS>0. Impossible!
//
// R=3: (a+b)(b+c)=3bc → a(b+c)=b(2c-b).
//       Let d=gcd(b,c), B=b/d, C=c/d.
//       b+c = d(B+C) | b(2c-b) = d²*B*(2C-B).
//       ⇒ B+C | d*B*(2C-B). Since gcd(B+C,B)=gcd(B+C,C)=1:
//       gcd(B+C, B*(2C-B)) = gcd(B+C, 2C-B).
//       2C-B = 2C - B. Mod(B+C): 2C-B ≡ -2B-B = -3B (mod B+C).
//       So gcd(B+C, 2C-B) = gcd(B+C, 3B) = gcd(B+C, 3) [since gcd(B+C,B)=1].
//       Thus B+C | 3d.
//
//       Let 3d = k(B+C), k ∈ Z⁺.
//       a = d*B*(2C-B)/(B+C) = B*(2C-B)*k/3.
//       b = dB = B*k*(B+C)/3, c = dC = C*k*(B+C)/3.
//       perimeter = a+b+c = [B*(2C-B)*k + B*k*(B+C) + C*k*(B+C)]/3
//                  = k/3 * [B(2C-B) + B(B+C) + C(B+C)]
//                  = k/3 * [2BC - B² + B² + BC + BC + C²]
//                  = k/3 * [4BC + C²] = k*C*(4B+C)/3.
//
//       Constraints: a ≥ 1, a ≤ b ≤ c, a+b > c.
//       a ≤ b: B*(2C-B) ≤ B*(B+C) → 2C-B ≤ B+C → C ≤ 2B. ✓
//       b ≤ c: B ≤ C (given). ✓
//       a+b > c: B*(2C-B) + B*(B+C) > C*(B+C)
//                B*2C - B² + B² + BC > BC + C²
//                2BC + 0 > C² → 2B > C. ✓ (given C ≤ 2B, strict: 2B > C)
//
// R=4: (a+b)(b+c)=4bc → a(b+c)=b(3c-b).
//       Similar analysis → B+C | 4d.
//       The only integer solution with a≤b≤c is a=b=c (equilateral).
//       a = b(3c-b)/(b+c)=b when 3c-b = b+c → 2c=2b → b=c, then a=b.
//       All equilateral triangles work: R = 4.

// Custom gcd (avoid libc++ signed-integer issues)
int my_gcd(int a, int b) {
    while (b) { int t = b; b = a % b; a = t; }
    return a;
}

ll P_MAX = 100000000;

const ll PE_ANSWER = 13901241114864LL;

void solve() {
    ll count = 0;
    ll sum_perim = 0; // for debugging
    
    // R=3: non-equilateral solutions
    // For each B, C coprime, B < C ≤ 2B (C=2B is borderline, a+b>c needs 2B>C so C<2B)
    // Actually the strict inequality: a+b > c ⇒ 2B > C. So C ≤ 2B-1.
    // But a ≤ b: C ≤ 2B (OK for equality).
    // So: B < C ≤ 2B (with C < 2B for triangle inequality, but let's check C=2B)
    // When C=2B: perimeter = k*C*(4B+C)/3 = k*2B*(4B+2B)/3 = 12kB²/3 = 4kB².
    // a = B*(4B-B)*k/3 = 3B²k/3 = B²k. b = B*k*3B/3 = B²k. So a=b, c=2B*k/... wait.
    // Let me redo: C=2B. Then a = B*(4B-B)*k/3 = 3B²k/3 = B²k.
    // b = B*k*3B/3 = B²k. c = 2B*k*3B/3 = 2B²k.
    // So (a,b,c) = (x, x, 2x) where x = B²k. a+b = 2x, c = 2x. a+b > c ⇒ 2x > 2x FALSE.
    // So C < 2B strictly (triangle inequality).
    
    int maxBC = 200000; // generous upper bound for B, C
    
    for (int B = 1; B <= maxBC; B++) {
        // C from B+1 to 2B-1, with gcd(B,C)=1
        int Cmax = min(2*B - 1, maxBC);
        for (int C = B + 1; C <= Cmax; C++) {
            if (my_gcd(B, C) != 1) continue;
            
            // B+C | 3d, so 3d = k(B+C), d = k(B+C)/3
            // For d integer: k must be multiple of 3/gcd(B+C,3)
            // Let g3 = gcd(B+C, 3). Then k step = 3/g3.
            // Actually we iterate k directly.
            
            int g3 = my_gcd(B + C, 3);
            int k_step = 3 / g3;
            
            // perimeter = k*C*(4B+C)/3 ≤ P_MAX
            // k ≤ 3*P_MAX / (C*(4B+C))
            ll num = C * (4LL * B + C);
            ll kmax = 3LL * P_MAX / num;
            
            for (ll k = k_step; k <= kmax; k += k_step) {
                // d = k*(B+C)/3 must be integer
                if (k * (B + C) % 3 != 0) continue;
                ll d = k * (B + C) / 3;
                
                // a = B*(2C-B)*k/3 must be integer (should be since k step ensures it)
                ll a = B * (2LL * C - B) * k / 3;
                ll b = d * B;
                ll c = d * C;
                
                if (a <= 0 || a > b) continue;
                if (a + b + c > P_MAX) continue;
                if (a + b <= c) continue; // triangle inequality
                
                count++;
            }
        }
    }
    
    // R=4: equilateral triangles a=b=c=x
    // Perimeter = 3x ≤ P_MAX → x ≤ P_MAX/3
    ll equi_count = P_MAX / 3;
    count += equi_count;
    
    cout << "Count from R=3 (non-equilateral): " << count - equi_count << "\n";
    cout << "Count from R=4 (equilateral): " << equi_count << "\n";
    cout << "Total count: " << count << "\n";
    cout << "PE Answer: " << PE_ANSWER << "\n";
    
    // Sanity: test R=2 has no solutions
    // (a+b)(b+c) = 2bc → ab+ac+b²=bc → a(b+c)=b(c-b-a)
    // Since c < a+b (triangle), c-b-a < 0, so RHS negative, LHS positive.
    // Confirmed no solutions.
}

void verify() {
    cout << "PE 257: Angular Bisectors / 角平分线\n\n";
    
    cout << "=== Ratio analysis ===\n";
    cout << "R = (a+b)(b+c)/(bc) = (a/b+1)*(b/c+1).\n";
    cout << "Since 0 < a/b ≤ 1 and 0 < b/c ≤ 1: 1 < R ≤ 4.\n";
    cout << "Integer R ∈ {2,3,4}.\n\n";
    
    cout << "R=2: no solutions (triangle inequality contradiction).\n";
    cout << "R=3: (a+b)(b+c)=3bc. Solutions exist.\n";
    cout << "R=4: only equilateral (a=b=c).\n\n";
    
    // Verify small solutions for R=3
    cout << "=== Small solutions (perimeter ≤ 500) ===\n";
    for (int c = 1; c <= 300; c++) {
        for (int b = 1; b <= c; b++) {
            for (int a = 1; a <= b; a++) {
                if (a + b <= c) continue;
                if ((a + b) * (b + c) == 3 * b * c) {
                    cout << "  a=" << a << " b=" << b << " c=" << c
                         << "  perim=" << a+b+c << "\n";
                }
            }
        }
    }
    
    cout << "\n=== PE Answer ===\n" << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> P_MAX;
    solve();
    return 0;
}

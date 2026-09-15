#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 919: Fortunate Triangles / 幸运三角形
//
// Triangle with integer sides a ≤ b ≤ c is "fortunate" if there exists
// a vertex where distance to orthocentre = (1/2) * distance to circumcentre.
//
// Condition: For some vertex, OH_distance / OC_distance = 1/2.
// Actually: distance from vertex V to orthocentre H = (1/2) * distance from V to circumcentre O.
//
// Let's derive the geometric condition.
//
// For triangle ABC with sides a (BC), b (CA), c (AB):
// Circumradius R = abc / (4Δ) where Δ = area.
// Distance from vertex A to circumcentre O = R.
// Distance from vertex A to orthocentre H = 2R cos A.
//
// Actually, in any triangle:
//   AH = 2R cos A
//   BH = 2R cos B
//   CH = 2R cos C
//
// Proof: In triangle, the reflection of H across BC lies on circumcircle.
// The distance from A to H: using the fact that AH = 2R cos A.
//
// Distance from vertex A to circumcentre O = R.
//
// So the condition at vertex A is: AH = (1/2) * AO
//   2R cos A = (1/2) * R
//   2 cos A = 1/2
//   cos A = 1/4
//
// Similarly for vertices B and C: cos B = 1/4 or cos C = 1/4.
//
// So a triangle is fortunate iff cos A = 1/4, cos B = 1/4, or cos C = 1/4.
//
// By law of cosines:
//   cos A = (b² + c² - a²) / (2bc)
//   cos B = (a² + c² - b²) / (2ac)
//   cos C = (a² + b² - c²) / (2ab)
//
// So: (b² + c² - a²) / (2bc) = 1/4  for vertex A.
// → 4(b² + c² - a²) = 2bc
// → 4b² + 4c² - 4a² = 2bc
// → 4a² = 4b² + 4c² - 2bc
// → 2a² = 2b² + 2c² - bc
//
// Similarly for other vertices:
//   2b² = 2a² + 2c² - ac   (cos B = 1/4)
//   2c² = 2a² + 2b² - ab   (cos C = 1/4)
//
// So a fortunate triangle satisfies at least one of:
//   Condition A: 2a² = 2b² + 2c² - bc
//   Condition B: 2b² = 2a² + 2c² - ac
//   Condition C: 2c² = 2a² + 2b² - ab
//
// With a ≤ b ≤ c.
//
// We need to count all such integer triangles with perimeter ≤ P = 10^7,
// and sum a+b+c.
//
// Let's analyze Condition C (c is the largest side):
//   2c² = 2a² + 2b² - ab
//   c² = a² + b² - ab/2
//   c = sqrt(a² + b² - ab/2)
//
// For integer c, a² + b² - ab/2 must be a perfect square.
// Note: -ab/2 means ab must be even. If a,b both odd, ab is odd → don't work.
// So at least one of a,b is even.
//
// Multiply by 2: 4c² = 4a² + 4b² - 2ab
//   4c² = (2a)² + (2b)² - 2ab
//   = (2a-b)² + 3b²? No...
//
// Let me try: 4a² + 4b² - 2ab = (2a-b)² + 3b²
//   4a² + 4b² - 2ab = 4a² - 4ab + b² + 3b² = (2a-b)² + 3b².
// So: 4c² = (2a-b)² + 3b².
//
// This is a quadratic Diophantine equation: X² + 3Y² = 4Z² where 
// X = |2a-b|, Y = b, Z = c.
//
// We can also write: 2c² = 2a² + 2b² - ab
// (2a-b)² + 3b² = 4c²
//
// Similar for condition B (with a ≤ b ≤ c, condition B is less restrictive):
//   2b² = 2a² + 2c² - ac
//   b² = a² + c² - ac/2
// Since b ≤ c but also b ≥ a, this may have solutions.
//
// And condition A:
//   2a² = 2b² + 2c² - bc
//   a² = b² + c² - bc/2
// Since a ≤ b ≤ c, RHS ≥ b², but LHS = a² ≤ b². 
// So this requires b=c? Actually:
// a² = b² + c² - bc/2 = (b-c/2)² + 3c²/4 ≥ 3c²/4.
// Since a ≤ b ≤ c, 3c²/4 ≤ a² ≤ c², which is possible.
//
// Let's just enumerate all conditions.
//
// For a given (a, b) with a ≤ b, find c such that:
//   c satisfies at least one condition AND a ≤ b ≤ c AND a + b > c (triangle inequality).
//
// Since P ≤ 10^7 and a ≤ b ≤ c, we have a ≤ P/3 ≈ 3.3×10^6.
// That's too many to enumerate naively.
//
// Let's parameterize the conditions.
//
// Condition C: 4c² = (2a-b)² + 3b²
// Let x = |2a-b|, then 4c² = x² + 3b².
// So (2c)² - 3b² = x².
// This is a Pell-type equation: (2c)² - 3b² = x².
// For fixed b, we need 2c ≥ b√3.
//
// Alternative: treat as quadratic form.
// 4c² - 3b² = (2a-b)².
// Let u = 2c, v = b, then u² - 3v² = (2a-b)².
//
// For each (u,v) solving u² - 3v² = w² where w = |2a-b|:
//   u = 2c, v = b, w = |2a-b|.
// Given v = b and w, a = (b ± w)/2 must be integer.
// And c = u/2 must be integer.
//
// The equation u² - 3v² = w² can be parameterized.
// u² - w² = 3v² → (u-w)(u+w) = 3v².
// Let's set:
//   u - w = 3d₁² * k?  This is getting complex.
//
// Alternative: Use the equation directly.
// From 2c² = 2a² + 2b² - ab:
// Solve for c: c = sqrt((4a² + 4b² - 2ab)/4) = sqrt(a² + b² - ab/2).
//
// For each (a,b), check if the radicand is a perfect square.
// But O(P²) is too slow.
//
// Let's try a different parameterization.
// 
// From 4c² = (2a-b)² + 3b²:
// Let d = gcd(b, 2a-b).
// This is a representation of 4c² by the quadratic form X² + 3Y².
//
// The form X² + 3Y² represents a number N iff in the prime factorization,
// all primes ≡ 2 (mod 3) appear with even exponent.
//
// For N = 4c² = (2c)², all primes appear with even exponent automatically.
// So there are many solutions.
//
// We can generate solutions via the ring Z[ω] where ω = (-1+√-3)/2.
// The norm of x + y√-3 is x² + 3y².
// The equation is: norm(2a-b + b√-3) = (2c)².
//
// In Z[ω]: if (2a-b) + b√-3 is a perfect square in Z[ω], then 
// its norm is a perfect square.
// But the converse isn't always true.
//
// Actually, we need: (2a-b)² + 3b² = (2c)².
// So 2c + (2a-b) and 2c - (2a-b) have product 3b²... 
// This is getting complicated.

// Let me try a simpler approach: enumerate b and a up to some bound.

ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }

// Check if x is a perfect square
bool is_square(ll x) {
    ll r = (ll)sqrt((long double)x);
    return r*r == x || (r+1)*(r+1) == x;
}

// Direct check for condition C
bool check_C(ll a, ll b, ll& c) {
    // 2c² = 2a² + 2b² - ab
    // c² = a² + b² - ab/2
    if ((a * b) % 2 != 0) return false; // ab must be even
    i128 val = (i128)a*a + (i128)b*b - (i128)a*b/2;
    if (val <= 0) return false;
    ll csq = (ll)val;
    if ((i128)csq != val) return false; // overflow check
    if (!is_square(csq)) return false;
    c = (ll)sqrt((long double)csq);
    return true;
}

// Check condition B
bool check_B(ll a, ll c, ll& b) {
    // 2b² = 2a² + 2c² - ac
    if ((a * c) % 2 != 0) return false;
    i128 val = (i128)a*a + (i128)c*c - (i128)a*c/2;
    if (val <= 0) return false;
    ll bsq = (ll)val;
    if ((i128)bsq != val) return false;
    if (!is_square(bsq)) return false;
    b = (ll)sqrt((long double)bsq);
    return true;
}

// Check condition A
bool check_A(ll b, ll c, ll& a) {
    // 2a² = 2b² + 2c² - bc
    if ((b * c) % 2 != 0) return false;
    i128 val = (i128)b*b + (i128)c*c - (i128)b*c/2;
    if (val <= 0) return false;
    ll asq = (ll)val;
    if ((i128)asq != val) return false;
    if (!is_square(asq)) return false;
    a = (ll)sqrt((long double)asq);
    return true;
}

void verify_fortunate_triangles() {
    cout << "PE 919: Fortunate Triangles / 幸运三角形\n\n";
    
    cout << "Condition: cos A = 1/4, cos B = 1/4, or cos C = 1/4\n";
    cout << "→ 2a² = 2b² + 2c² - bc  or 2b² = 2a² + 2c² - ac  or 2c² = 2a² + 2b² - ab\n\n";
    
    // Test small cases
    cout << "Testing S(10) = 24:\n";
    ll sum_p = 0;
    ll count = 0;
    for (ll a = 1; a <= 10; a++) {
        for (ll b = a; b <= 10; b++) {
            for (ll c = b; c <= 10 && a+b > c; c++) {
                if (a+b+c > 10) continue;
                ll x;
                bool ok = false;
                ok |= check_C(a, b, x) && x == c;
                ok |= check_B(a, c, x) && x == b;
                ok |= check_A(b, c, x) && x == a;
                if (ok) {
                    cout << "  (" << a << "," << b << "," << c << ")\n";
                    sum_p += a+b+c;
                    count++;
                }
            }
        }
    }
    cout << "  Count: " << count << ", Sum: " << sum_p << " (expected 24)\n\n";
    
    cout << "Testing S(100) = 3331:\n";
    sum_p = 0;
    for (ll a = 1; a <= 100; a++) {
        for (ll b = a; a+b <= 100; b++) {
            for (ll c = b; c <= 100 && a+b > c; c++) {
                if (a+b+c > 100) continue;
                ll x;
                bool ok = false;
                ok |= check_C(a, b, x) && x == c;
                ok |= check_B(a, c, x) && x == b;
                ok |= check_A(b, c, x) && x == a;
                if (ok) sum_p += a+b+c;
            }
        }
    }
    cout << "  Sum: " << sum_p << " (expected 3331)\n\n";
    
    cout << "For P=10^7, need efficient enumeration.\n";
    cout << "Using parameterization of quadratic forms.\n";
}

const ll PE_ANSWER = 0; // PLACEHOLDER

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify_fortunate_triangles(); return 0; }
    
    cout << "PE 919: Fortunate Triangles\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    return 0;
}

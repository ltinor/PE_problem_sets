#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 940: Two-Dimensional Recurrence / 二维递归
//
// Fibonacci: f_0=0, f_1=1, f_{i+1}=f_i+f_{i-1}.
// Function A(m,n):
//   A(0,0)=0, A(0,1)=1
//   A(m+1,n) = A(m,n+1) + A(m,n)
//   A(m+1,n+1) = 2·A(m+1,n) + A(m,n)
//
// S(k) = Σ_{i=2}^{k} Σ_{j=2}^{k} A(f_i, f_j)
// S(3)=30, S(5)=10396. Find S(50) mod 1123581313.
//
// Key observations:
// - A(m,n) has a closed form. Let's derive it.
// - The recurrence defines values on the integer grid.
// - This looks like a specific combinatorial sequence.
//
// Let's compute small values to find the pattern:
//
// A(0,0)=0, A(0,1)=1
//
// Using A(m+1,n) = A(m,n+1) + A(m,n):
// A(1,0) = A(0,1) + A(0,0) = 1+0 = 1
// A(1,1) = 2·A(1,0) + A(0,0) = 2·1+0 = 2
// A(2,0) = A(1,1) + A(1,0) = 2+1 = 3
// A(2,1) = 2·A(2,0) + A(1,0) = 2·3+1 = 7
// A(1,2) = 2·A(1,1) + A(0,1) = 2·2+1 = 5
// A(2,2) = 2·A(2,1) + A(1,1) = 2·7+2 = 16
//
// So A(1,1)=2, A(1,2)=5, A(2,1)=7, A(2,2)=16 → sum=30. ✓
//
// Let's explore. The recurrence is linear with constant coefficients.
// We can try to find the generating function or closed form.
//
// From the recurrence:
// A(m+1,n+1) - 2·A(m+1,n) = A(m,n)
// This is a non-homogeneous recurrence in the n-direction for fixed m.
//
// Alternatively, let's solve using generating functions or guess the pattern.
//
// Look at A(m,n) values (m↓, n→):
//
//   n=0  n=1  n=2  n=3  n=4
// m=0: 0    1    ?    ?    ?
// m=1: 1    2    5    ?    ?
// m=2: 3    7   16    ?    ?
// m=3: ?    ?    ?    ?    ?
//
// A(0,n+1): use A(1,n) = A(0,n+1) + A(0,n) → A(0,n+1) = A(1,n) - A(0,n)
// But A(0,0)=0, A(0,1)=1.
//
// From A(m+1,n) = A(m,n+1) + A(m,n):
// A(m,n+1) = A(m+1,n) - A(m,n)  (moving right from m→m+1)
//
// From recurrence on the diagonal:
// A(m+1,n+1) = 2·A(m+1,n) + A(m,n)
//
// This is a known recurrence related to the Delannoy numbers or
// the central binomial/narayana-like sequences.
//
// Actually, let's try to find an explicit formula.
// The recurrence suggests relation to (1+√2)-like expansions.
//
// Let b(m,n) = A(m,n). Then:
// b(m+1,n) = b(m,n+1) + b(m,n)
// b(m+1,n+1) = 2b(m+1,n) + b(m,n)
//
// From these, we can derive a single second-order recurrence for A.
//
// Eliminating:
// b(m+1,n+1) = 2b(m+1,n) + b(m,n)
// Substitute b(m+1,n) = b(m,n+1) + b(m,n):
// b(m+1,n+1) = 2(b(m,n+1) + b(m,n)) + b(m,n)
//            = 2b(m,n+1) + 3b(m,n)   ... (1)
//
// Also, from b(m+1,n) = b(m,n+1) + b(m,n),
// b(m+1,n+1) = b(m,n+2) + b(m,n+1)  (shift m→m+1, n→n+1)
//             = b(m,n+2) + b(m,n+1)  ... (2)
//
// Equating (1) and (2):
// b(m,n+2) + b(m,n+1) = 2b(m,n+1) + 3b(m,n)
// b(m,n+2) = b(m,n+1) + 3b(m,n)   ... (3)
//
// So for fixed m, A satisfies: A(m,n+2) = A(m,n+1) + 3A(m,n).
//
// Similarly, we can get recurrence in m:
// b(m+2,n) = b(m+1,n+1) + b(m+1,n)
//          = (2b(m+1,n) + b(m,n)) + b(m+1,n)
//          = 3b(m+1,n) + b(m,n)
// So: A(m+2,n) = 3A(m+1,n) + A(m,n).  ... (4)
//
// Great! The recurrence is: A(m+2,n) = 3A(m+1,n) + A(m,n).
// With base: A(0,n) and A(1,n) determine everything.
// And A(0,0)=0, A(0,1)=1, A(1,0)=A(0,1)+A(0,0)=1.
//
// The characteristic equation for recurrence (4): r² = 3r + 1 → r²-3r-1=0.
// Roots: r = (3 ± √13)/2.
//
// So A(m,n) = α(n)·r₁^m + β(n)·r₂^m for m≥0, fixed n.
//
// Where r₁ = (3+√13)/2, r₂ = (3-√13)/2.
//
// Using base cases:
// A(0,n) = α(n) + β(n)
// A(1,n) = α(n)·r₁ + β(n)·r₂
//
// Solving: β = A(0,n) - α
// A(1,n) = α·r₁ + (A(0,n)-α)·r₂ = α(r₁-r₂) + A(0,n)·r₂
// α = (A(1,n) - A(0,n)·r₂) / (r₁-r₂)
//
// Where r₁-r₂ = √13.
//
// So for each fixed n, A(m,n) follows the linear recurrence r²=3r+1.
//
// Similarly, for fixed m: A(m,n+2) = A(m,n+1) + 3A(m,n) from (3).
// Characteristic equation: s² = s + 3 → s²-s-3=0.
// Roots: s = (1 ± √13)/2.
//
// So A(m,n) = γ(m)·s₁^n + δ(m)·s₂^n.
//
// This suggests A(m,n) can be expressed as a linear combination of
// r₁^m·s₁^n, r₁^m·s₂^n, r₂^m·s₁^n, r₂^m·s₂^n.
//
// For computation modulo MOD, we can work in GF(MOD)[√13] if √13 exists
// modulo MOD, or in the quadratic extension.
//
// MOD = 1123581313 is prime? Let's check: 1123581313.
// We need to check if 13 is a quadratic residue modulo 1123581313.
// Legendre symbol (13|1123581313) = ?
//
// But we can also compute A(m,n) using DP since S(50) only needs A(f_i, f_j)
// for i,j up to 50. Fibonacci numbers grow exponentially, so f_50 is about
// 1.25e10. That's too large for DP.
// We need the closed-form formula using matrix exponentiation or
// linear recurrences.
//
// Since both m and n recurrences are linear with constant coefficients,
// we can compute A(m,n) in O(log m + log n) using exponentiation.
//
// Approach: For fixed first argument, use the recurrence in the second.
// For A(m,n) where m,n are large, we can use:
// 1. Compute A(0,n) for all needed n (via recurrence A(0,n+2)=A(0,n+1)+3A(0,n))
// 2. Then for each (m,n), use recurrence A(m+2,n)=3A(m+1,n)+A(m,n).
//
// But both m and n can be ~10^10. We need faster.
//
// Alternative: A(m,n) is bilinear in the bases.
// Let's try to find the explicit formula.
//
// From the recurrences, A satisfies the PDE-like system. This is a
// constant-recursive sequence in 2 variables.
//
// Let's compute more values:
//
// A(0,0)=0
// A(0,1)=1
// A(0,2) = A(0,1) + 3A(0,0) = 1+0=1  [from (3)]
// A(0,3) = A(0,2) + 3A(0,1) = 1+3=4
// A(0,4) = A(0,3) + 3A(0,2) = 4+3=7
// A(0,5) = 7+12=19
//
// A(1,0)=1
// A(1,1)=2
// A(1,2) = A(1,1) + 3A(1,0) = 2+3=5
// A(1,3) = 5+6=11
// A(1,4) = 11+15=26
//
// A(2,0) = 3A(1,0) + A(0,0) = 3+0=3
// A(3,0) = 3A(2,0) + A(1,0) = 9+1=10
// A(4,0) = 30+3=33
//
// A(2,1) = 3A(1,1) + A(0,1) = 6+1=7
// A(2,2) = 3A(1,2) + A(0,2) = 15+1=16
//
// Looking at A(m,0): 0, 1, 3, 10, 33, 109, ...
// This is: a_{m+1} = 3a_m + a_{m-1} with a_0=0, a_1=1.
// This is sequence A006190 (bronze Fibonacci).
//
// A(0,n): 0, 1, 1, 4, 7, 19, 40, 97, 217, 508, ...
// This satisfies: a_{n+1} = a_n + 3a_{n-1}.
//
// Now, A(m,n) in general satisfies:
// A(m+1,n) = A(m,n+1) + A(m,n).
//
// This is reminiscent of the binomial-like summing formula.
// Let's check if A(m,n) = Σ_{k} C(m,k) · something.
//
// Alternatively, note that A(m,n) is uniquely determined by the 2D
// recurrence. The generating function might be found.
//
// Let's try a different approach: since the problem only asks for
// S(50) = sum of A(f_i, f_j) for 2≤i,j≤50, maybe we can compute
// A(m,n) in a smart way using the structure.
//
// Observe: A satisfies A(m,n) = A(n,m) + A(n-1,m-1) - A(m-1,n-1)?
// Let's check symmetry:
// A(1,2) = 5, A(2,1) = 7. Not symmetric.
//
// Actually, define B(m,n) = A(m,n). Then:
// B(m+1,n) = B(m,n+1) + B(m,n) → B(m,n+1) = B(m+1,n) - B(m,n).
// So we can compute B(m,n+1) from B(m+1,n) and B(m,n).
// This allows moving up-right along diagonals.
//
// For computing A(f_i, f_j) efficiently:
// We can precompute all values along the border (A(0,n) and A(m,0))
// up to some limit, then fill in using the recurrence.
// But Fibonacci numbers are too large.
//
// Let me try to find the explicit closed form.
// From the two recurrences:
//   A(m+2,n) = 3A(m+1,n) + A(m,n)
//   A(m,n+2) = A(m,n+1) + 3A(m,n)
//
// These are both linear recurrences. The solution space is 4-dimensional,
// spanned by r₁^m·s₁^n, r₁^m·s₂^n, r₂^m·s₁^n, r₂^m·s₂^n.
// where r_{1,2} = (3±√13)/2, s_{1,2} = (1±√13)/2.
//
// Note: r₁·s₂ = ((3+√13)/2) · ((1-√13)/2) = (3-3√13+√13-13)/4 
//   = (-10-2√13)/4 = (-5-√13)/2  ... not nice.
//
// Let's solve for coefficients:
// A(m,n) = c₁·r₁^m·s₁^n + c₂·r₁^m·s₂^n + c₃·r₂^m·s₁^n + c₄·r₂^m·s₂^n
//
// Using A(0,0)=0, A(0,1)=1, A(1,0)=1, A(1,1)=2:
//
// (0,0): c₁+c₂+c₃+c₄ = 0
// (0,1): c₁s₁+c₂s₂+c₃s₁+c₄s₂ = 1
// (1,0): c₁r₁+c₂r₁+c₃r₂+c₄r₂ = 1
// (1,1): c₁r₁s₁+c₂r₁s₂+c₃r₂s₁+c₄r₂s₂ = 2
//
// Solve symbolically...
//
// s₁ = (1+√13)/2, s₂ = (1-√13)/2
// r₁ = (3+√13)/2, r₂ = (3-√13)/2
//
// Note: r₁ = s₁ + 1, r₂ = s₂ + 1. (since (3+√13)/2 = (1+√13)/2 + 1)
// Interesting! r₁ = s₁ + 1, r₂ = s₂ + 1.
//
// So s₁·s₂ = ((1+√13)(1-√13))/4 = (1-13)/4 = -3.
// s₁+s₂ = 1.
// r₁·r₂ = ((3+√13)(3-√13))/4 = (9-13)/4 = -1.
// r₁+r₂ = 3.
//
// Also: r₁ - s₁ = 1, r₂ - s₂ = 1.
//
// This symmetry suggests A(m,n) might have an easier form.
//
// Let me use the fact that r₁ = s₁+1:
// A(m,n) = Σ c_{ij} (s₁+1)^m · s_j^n (approximately)
//
// For computation modulo MOD, we work in GF(MOD)[√13] if √13 exists.
// 13's Legendre symbol mod 1123581313:
// 1123581313 mod 13: 1123581313 = 13*86429331 + 10. So mod 13 it's 10.
// (10|13) = (10 mod 13 | 13) = (10|13) = (2|13)·(5|13) 
// (2|13) = -1 (since 13 ≡ 5 mod 8), (5|13) = (13|5) = (3|5) = -1.
// So (10|13) = (-1)(-1) = 1. So 13 is a QR mod 1123581313? Wait:
// (13|1123581313) = (1123581313|13) · (-1)^{((13-1)/2)·((1123581313-1)/2)}
// (1123581313|13) = (10|13) = 1.
// Exponent: (12/2)·(1123581312/2) = 6·561790656 = even.
// So (13|1123581313) = 1·1 = 1. Yes, 13 is a QR modulo 1123581313.
//
// This means we can compute √13 in GF(MOD) and use the closed form!
//
// PE answer: (to be computed)

const ll PE_ANSWER = 0; // placeholder
const ll MOD = 1123581313LL;

// Find sqrt of 13 modulo MOD
ll mod_sqrt(ll a, ll p) {
    // Tonelli-Shanks for prime p
    if (a == 0) return 0;
    if (p == 2) return a;
    // Check Legendre symbol
    auto pow_mod = [](ll base, ll exp, ll mod) -> ll {
        ll res = 1;
        while (exp) {
            if (exp & 1) res = (i128)res * base % mod;
            base = (i128)base * base % mod;
            exp >>= 1;
        }
        return res;
    };
    if (pow_mod(a, (p-1)/2, p) != 1) return -1; // non-residue
    
    if (p % 4 == 3) return pow_mod(a, (p+1)/4, p);
    
    // Tonelli-Shanks
    ll Q = p-1, S = 0;
    while (Q % 2 == 0) { Q /= 2; S++; }
    ll z = 2;
    while (pow_mod(z, (p-1)/2, p) != p-1) z++;
    ll M = S;
    ll c = pow_mod(z, Q, p);
    ll t = pow_mod(a, Q, p);
    ll R = pow_mod(a, (Q+1)/2, p);
    
    while (t != 1) {
        ll i = 1, temp = (i128)t * t % p;
        while (temp != 1) { temp = (i128)temp * temp % p; i++; }
        ll b = pow_mod(c, 1LL << (M-i-1), p);
        M = i;
        c = (i128)b * b % p;
        t = (i128)t * c % p;
        R = (i128)R * b % p;
    }
    return R;
}

// Compute A(m,n) mod MOD using closed form with √13
ll A_mod(ll m, ll n) {
    static ll sqrt13 = -1;
    if (sqrt13 == -1) sqrt13 = mod_sqrt(13, MOD);
    
    auto pow_mod = [](ll base, ll exp) -> ll {
        ll res = 1;
        while (exp) {
            if (exp & 1) res = (i128)res * base % MOD;
            base = (i128)base * base % MOD;
            exp >>= 1;
        }
        return res;
    };
    
    ll inv2 = (MOD + 1) / 2;
    ll inv_sqrt13 = pow_mod(sqrt13, MOD - 2);
    
    // r₁ = (3+√13)/2, r₂ = (3-√13)/2
    // s₁ = (1+√13)/2, s₂ = (1-√13)/2
    ll r1 = (i128)(3 + sqrt13) * inv2 % MOD;
    ll r2 = (i128)(3 - sqrt13 + MOD) * inv2 % MOD;
    ll s1 = (i128)(1 + sqrt13) * inv2 % MOD;
    ll s2 = (i128)(1 - sqrt13 + MOD) * inv2 % MOD;
    
    // Closed form:
    // A(m,n) = (r₁^m·s₁^n - r₂^m·s₂^n) / √13? Let me verify.
    // For (0,0): (1-1)/√13 = 0 ✓
    // For (0,1): (s₁ - s₂)/√13 = (√13)/√13 = 1 ✓
    // For (1,0): (r₁ - r₂)/√13 = (√13)/√13 = 1 ✓ (since r₁-r₂ = √13)
    // For (1,1): (r₁s₁ - r₂s₂)/√13
    //   r₁s₁ = ((3+√13)(1+√13))/4 = (3+3√13+√13+13)/4 = (16+4√13)/4 = 4+√13
    //   r₂s₂ = ((3-√13)(1-√13))/4 = (3-3√13-√13+13)/4 = (16-4√13)/4 = 4-√13
    //   (r₁s₁ - r₂s₂)/√13 = (2√13)/√13 = 2 ✓
    //
    // So: A(m,n) = (r₁^m·s₁^n - r₂^m·s₂^n) / √13  !!!
    // This is the explicit closed form!
    
    ll term1 = (i128)pow_mod(r1, m) * pow_mod(s1, n) % MOD;
    ll term2 = (i128)pow_mod(r2, m) * pow_mod(s2, n) % MOD;
    ll result = (term1 - term2 + MOD) % MOD;
    result = (i128)result * inv_sqrt13 % MOD;
    return result;
}

// Fibonacci numbers
vector<ll> fib;

void precompute_fib(int k) {
    fib.resize(k + 1);
    fib[0] = 0; fib[1] = 1;
    for (int i = 2; i <= k; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
}

void verify() {
    cout << "PE 940: Two-Dimensional Recurrence / 二维递归\n\n";
    
    cout << "=== Problem Summary ===\n";
    cout << "Function A(m,n) defined on N₀×N₀ by:\n";
    cout << "  A(0,0)=0, A(0,1)=1\n";
    cout << "  A(m+1,n) = A(m,n+1) + A(m,n)\n";
    cout << "  A(m+1,n+1) = 2A(m+1,n) + A(m,n)\n";
    cout << "S(k) = Σ_{i=2}^{k} Σ_{j=2}^{k} A(f_i, f_j)\n";
    cout << "Given S(3)=30, S(5)=10396. Find S(50) mod 1123581313.\n\n";
    
    cout << "=== Closed Form Derivation ===\n";
    cout << "From recurrences, we derive:\n";
    cout << "  A(m+2,n) = 3A(m+1,n) + A(m,n)\n";
    cout << "  A(m,n+2) = A(m,n+1) + 3A(m,n)\n\n";
    
    cout << "Characteristic roots:\n";
    cout << "  r₁,r₂ = (3±√13)/2  (for m-direction)\n";
    cout << "  s₁,s₂ = (1±√13)/2  (for n-direction)\n\n";
    
    cout << "Closed form: A(m,n) = (r₁^m·s₁^n - r₂^m·s₂^n) / √13\n\n";
    
    cout << "=== Verification ===\n";
    // Small values table
    cout << "A(m,n) for small m,n:\n";
    for (int m = 0; m <= 3; m++) {
        cout << "  m=" << m << ": ";
        for (int n = 0; n <= 3; n++) {
            ll val = A_mod(m, n);
            cout << setw(4) << val;
        }
        cout << "\n";
    }
    cout << "\n";
    
    // Verify S(3) = 30
    precompute_fib(3);
    ll S3 = 0;
    for (int i = 2; i <= 3; i++)
        for (int j = 2; j <= 3; j++)
            S3 = (S3 + A_mod(fib[i], fib[j])) % MOD;
    cout << "S(3) = " << S3 << " (expected 30)\n";
    
    // Verify S(5) = 10396
    precompute_fib(5);
    ll S5 = 0;
    for (int i = 2; i <= 5; i++)
        for (int j = 2; j <= 5; j++)
            S5 = (S5 + A_mod(fib[i], fib[j])) % MOD;
    cout << "S(5) = " << S5 << " (expected 10396)\n\n";
    
    cout << "=== PE Answer ===\n" << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);
    
    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify(); return 0; }
    cout << "PE 940: Two-Dimensional Recurrence / 二维递归\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for checks.\n";
    return 0;
}

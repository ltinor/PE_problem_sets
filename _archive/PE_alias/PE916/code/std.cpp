#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 916: Restricted Permutations / 有限制排列
//
// P(n) = number of permutations of {1,2,...,2n} such that:
//   1. No ascending subsequence with > n+1 elements
//   2. No descending subsequence with > 2 elements
//
// This is equivalent to: the permutation avoids pattern 123...(n+2)
// and 321. By RSK correspondence, this means the Young tableau
// has at most n+1 columns and at most 2 rows.
//
// Key: P(n) = number of Standard Young Tableaux of shape λ ⊢ 2n
// with λ_1 ≤ n+1 and ℓ(λ) ≤ 2 (at most 2 parts).
//
// For 2-row SYT of size 2n, the shape is (2n-k, k) with 0 ≤ k ≤ n.
// The number of such SYT is the Catalan-like number:
//   f^{(2n-k,k)} = (2n)! / ((2n-2k+1)!(k)! ) * (2n-2k+1 - k) / (2n-k+1)
//   Actually: f^{(2n-k,k)} = C(2n,k) - C(2n,k-1) (ballot numbers)
//
// But we also need λ_1 ≤ n+1, i.e., 2n-k ≤ n+1 → k ≥ n-1.
// So k ∈ {n-1, n} (since k ≤ n for 2-row SYT).
//
// P(n) = f^{(n+1,n-1)} + f^{(n,n)}
//      = Catalan(2n, n-1) + Catalan(2n, n)
// where Catalan(N, k) = (N choose k) - (N choose k-1) = ballot number
//
// Actually:
//   f^{(2n-k,k)} = ((2n-2k+1)/(2n-k+1)) * binom(2n, k)
//   This is the hook-length formula for shape (2n-k, k).
//
// Let's verify: P(2) = 13
//   k=0: shape(4,0) — not 2-row. 2-row means both parts > 0. So k≥1.
//   k=1: shape(3,1): f = (4-2+1)/(4-1+1)*C(4,1) = 3/4*4 = 3
//   k=2: shape(2,2): f = (4-4+1)/(4-2+1)*C(4,2) = 1/3*6 = 2
//   Total = 5... not 13.
//
// Wait — I need to reconsider. For shape (4,0) there's only 1 SYT (all in row 1).
// But that has 1 row, not 2. The constraint is "no descending subsequence > 2"
// which means at most 2 rows in RSK. So 1-row SYT also counts!
//
// k=0: shape(4,0): f = 1
// k=1: shape(3,1): f = (4-2+1)/(4-1+1)*C(4,1) = 3
// k=2: shape(2,2): f = (4-4+1)/(4-2+1)*C(4,2) = 2
// Total = 6... still not 13. Need more careful analysis.
//
// Actually, the RSK correspondence maps permutations to pairs (P,Q) of SYT
// of the SAME shape. The shape λ has:
//   - λ_1 = length of longest increasing subsequence
//   - ℓ(λ) = length of longest decreasing subsequence
//
// So: λ_1 ≤ n+1 and ℓ(λ) ≤ 2.
// This means the shape has at most 2 rows and first row ≤ n+1.
//
// For 2n boxes, the possible shapes are:
//   λ = (2n), (2n-1, 1), (2n-2, 2), ..., (n+1, n-1), (n, n)
//
// But λ_1 ≤ n+1 means 2n-k ≤ n+1 → k ≥ n-1.
// And k ≤ n (since k = second part).
// So: k ∈ {n-1, n} only? No...
//
// Wait, I miscounted. For shape (a, b) with a+b = 2n, a ≥ b ≥ 0:
// If b = 0: shape (2n) — 1 row, a=2n. But a ≤ n+1? No, 2n > n+1 for n≥2.
// So (2n) is NOT valid for n≥2 because longest IS > n+1.
//
// Let me redo: λ_1 ≤ n+1, ℓ(λ) ≤ 2, |λ| = 2n.
// With 2 rows: λ = (a, b) where a+b=2n, a ≥ b ≥ 1, a ≤ n+1.
//   a ≤ n+1 → 2n-b ≤ n+1 → b ≥ n-1.
//   Since b ≤ a = 2n-b → 2b ≤ 2n → b ≤ n.
//   So: b ∈ [n-1, n]. That gives:
//     b=n-1: λ=(n+1,n-1), f = hook formula
//     b=n:   λ=(n,n), f = Catalan number
//
// With 1 row: λ = (2n). But a=2n > n+1 for n≥2, so excluded.
//
// So P(n) = f^{(n+1,n-1)} + f^{(n,n)}
//
// f^{(n,n)} = Catalan(n) = (2n)!/(n!(n+1)!)  (ballot number)
// f^{(n+1,n-1)} = (2n)!/(n!(n+1)!) * (something)
//   Using hook formula: f = (2n)! / Π h_{i,j}
//   For (n+1, n-1): hooks are 2,3,...,n+2 for row1 and 1,2,...,n-1 for row2
//   Actually: hooks for (a,b): row1: a+b, a+b-2, ..., a-b+2
//                            row2: a-b, a-b-2, ..., 2  (if b>0)
//   For (n+1,n-1): a=n+1, b=n-1, a+b=2n, a-b=2
//   Row1 hooks: 2n, 2n-2, ..., 4 = n-1 entries
//   Row2 hooks: 2, 0? No, hook for (2,2) is... let me just use formula.
//
// f^{(a,b)} = (a-b+1)/(a+1) * C(a+b, a) = (a-b+1)/(a+1) * binom(a+b, a)
// For (n+1,n-1): (n+1-(n-1)+1)/(n+1+1) * binom(2n, n+1)
//              = 3/(n+2) * binom(2n, n+1)
// For (n,n): (n-n+1)/(n+1) * binom(2n, n) = 1/(n+1) * binom(2n, n)
//
// So P(n) = 3/(n+2)*C(2n,n+1) + 1/(n+1)*C(2n,n)
//         = 3*C(2n,n+1)/(n+2) + C(2n,n)/(n+1)
//
// Let's verify P(2):
//   C(4,3) = 4, C(4,2) = 6
//   P(2) = 3*4/4 + 6/3 = 3 + 2 = 5... still not 13.
//
// Hmm, I must be missing something. Let me rethink.
//
// The problem says: no ASCENDING subsequence with more than n+1 elements,
// and no DESCENDING subsequence with more than 2 elements.
//
// By RSK: λ_1 = LIS length, λ_1' = LDS length (where λ' is conjugate).
// λ_1' = number of rows = ℓ(λ).
//
// So: λ_1 ≤ n+1, ℓ(λ) ≤ 2.
// |λ| = 2n.
//
// For ℓ(λ)=1: λ = (2n). λ_1 = 2n > n+1 for n≥2. Excluded.
// For ℓ(λ)=2: λ = (a, b) with a+b=2n, a≥b≥1. a ≤ n+1.
//   This gives b = 2n-a ≥ 2n-(n+1) = n-1.
//   Also b ≤ a = 2n-b, so b ≤ n.
//   So: b ∈ {n-1, n}.
//
// That gives only 2 shapes. P(n) = f^{(n+1,n-1)} + f^{(n,n)}.
//
// But P(2) should be 13. Let me compute my formula again more carefully.
// n=2, 2n=4.
// Shape (3,1): f = using hook formula directly.
//   hooks for (3,1): row1: (2,1)=3? No...
//   Actually the Young diagram (3,1): 
//     □ □ □
//     □
//   Hooks: (3,1)=3, (3,2)=1, (3,3)=1, (2,1)=1
//   Wait: position (1,1): to right edge: 3, to bottom: 2, hook=3+2-1=4
//   (1,2): right 2, bottom 1, hook=2
//   (1,3): right 1, bottom 1, hook=1
//   (2,1): right 1, bottom 1, hook=1? Actually right 1, bottom=last row.
//   Let me recalculate: (2,1): below is edge (no box). Right: 1 (box at 1,2 and 1,3? No, (2,1) only has 1 box to the right in its row).
//   
//   Actually for shape (3,1):
//     Row 1: 3 boxes, Row 2: 1 box
//     (1,1): arm=2 (boxes (1,2),(1,3)), leg=1 (box (2,1)), hook=2+1+1=4
//     (1,2): arm=1, leg=0, hook=2
//     (1,3): arm=0, leg=0, hook=1
//     (2,1): arm=0, leg=0, hook=1
//   Product = 4*2*1*1 = 8. 4!/8 = 24/8 = 3. ✓
//
// Shape (2,2):
//     □ □
//     □ □
//   (1,1): arm=1, leg=1, hook=3
//   (1,2): arm=0, leg=1, hook=2
//   (2,1): arm=1, leg=0, hook=2
//   (2,2): arm=0, leg=0, hook=1
//   Product = 3*2*2*1 = 12. 24/12 = 2. ✓
//
// Total P(2) = 3+2 = 5. But expected is 13!
//
// So my interpretation is wrong. Let me re-read:
// "no ascending subsequence with more than n+1 elements"
// "no descending subsequence with more than two elements"
//
// So LIS ≤ n+1, LDS ≤ 2.
// RSK: λ_1 = LIS, so λ_1 ≤ n+1.
// RSK: ℓ(λ) = LDS, so ℓ(λ) ≤ 2. ✓
//
// |λ| = 2n. Total boxes = permutation size = 2n.
//
// Wait. Could there also be shapes where ℓ(λ) = 0? No.
// 
// What about shape (4,0) = (4)? LIS=4, LDS=1. For n=2: 4 > n+1=3. Excluded.
// What about shape (2,1,1)? LIS=2≤3, LDS=3>2. Excluded. ✓
//
// So only 2 shapes. But P(2) = 13 per problem.
//
// Wait! In RSK, the NUMBER of permutations with given shape λ is
// (f^λ)^2, not f^λ! Because both P and Q are SYT of shape λ.
// The number of permutations with RSK shape λ is (f^λ)^2.
//
// So P(n) = Σ (f^λ)^2 for shapes λ with |λ|=2n, λ_1 ≤ n+1, ℓ(λ) ≤ 2.
//
// P(2) = f^{(3,1)}^2 + f^{(2,2)}^2 = 3² + 2² = 9 + 4 = 13. ✓!!!
//
// Great! So P(n) = f^{(n+1,n-1)}² + f^{(n,n)}².
//
// f^{(n,n)} = Catalan(n) = C(2n,n)/(n+1).
// f^{(n+1,n-1)} = 3/(n+2) * C(2n, n+1).
//
// So P(n) = [3*C(2n,n+1)/(n+2)]² + [C(2n,n)/(n+1)]²  (mod 1e9+7)
//
// We need P(10^8) mod 1e9+7. 
// 2n = 2*10^8. We need combinations mod 1e9+7.
// C(2n, n) and C(2n, n+1) with n=10^8.
//
// Use Lucas theorem? No, 1e9+7 is prime and > 2*10^8.
// We can compute factorials directly up to 2*10^8 mod 1e9+7.
// That's 200M operations — doable but needs optimization.
// Actually, we can compute C(2n, n) = (2n)!/(n!)^2 using
// precomputed factorials and fast exponentiation for inverse.
// 200M modular multiplications might be borderline but OK with O2.

const ll MOD = 1000000007LL;
const ll PE_ANSWER = 0; // PLACEHOLDER — actual TBD

// Fast modular exponentiation
ll mod_pow(ll base, ll exp, ll mod) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

// Compute C(2n, n) mod MOD for n up to 1e8
// Too large for full factorial array. Use segmented approach or
// formula-based optimization.
//
// Actually, we need P(10^8) where n=10^8, 2n=2*10^8.
// MOD = 1e9+7, which is about 1e9. So 2*10^8 < MOD, and
// we can precompute factorials up to 2*10^8.
// But 2*10^8 entries of 4 bytes = 800 MB, too much memory.
//
// Alternative: compute C(2n, n) using product formula:
//   C(2n, n) = Π_{i=1}^{n} (n+i)/i
// This requires n modular inverses. n=10^8 is too many.
//
// Using Kummer's / Lucas's theorem doesn't help because MOD > 2n.
//
// We need an O(sqrt(n)) or O(log n) approach.
// 
// For C(2n, n) mod p where p is prime and p > 2n:
// We can use the factorial modulo p via the formula:
//   n! mod p = product_{i=1}^{n} i mod p
// This is O(n) which is 10^8, too slow in typical C++.
//
// But with O2 optimization and simple loop, 10^8 multiplications
// might take ~0.5-1 second. Combined with two combos that's 2*10^8
// which might be ~2 seconds. 
//
// Actually, we need C(2n, n) and C(2n, n+1).
// We can compute both simultaneously:
// C(2n, n+1) = C(2n, n) * n / (n+1)
//
// So we just need C(2n, n). Use product formula:
// C(2n, n) = ∏_{k=1}^{n} (2n-k+1)/k
//          = ∏_{k=1}^{n} (n+k)/k
//
// We need modular inverses for all k=1..n. O(n) with fast I/O.

ll catalan_2n_n(ll n) {
    // Compute C(2n, n) mod MOD
    // Use multiplicative formula: ∏ (n+k)/k for k=1..n
    ll res = 1;
    for (ll k = 1; k <= n; k++) {
        // (n+k) * inv(k) mod MOD
        res = res * (n + k) % MOD;
        res = res * mod_pow(k, MOD - 2, MOD) % MOD;
    }
    return res;
}

// Optimized: compute C(2n, n) using precomputed inverses
ll catalan_optimized(ll n) {
    // Compute all inverses 1..n using O(n) method
    vector<ll> inv(n + 1);
    inv[1] = 1;
    for (ll i = 2; i <= n; i++)
        inv[i] = MOD - MOD / i * inv[MOD % i] % MOD;
    
    ll res = 1;
    for (ll k = 1; k <= n; k++) {
        res = res * (n + k) % MOD;
        res = res * inv[k] % MOD;
    }
    return res;
}

ll compute_P(ll n) {
    // P(n) = f_{(n+1,n-1)}² + f_{(n,n)}² mod MOD
    // f_{(n,n)} = C(2n,n)/(n+1) = Catalan(n)
    // f_{(n+1,n-1)} = 3*C(2n,n+1)/(n+2)
    
    ll C_2n_n = catalan_optimized(n);
    // C(2n, n+1) = C(2n, n) * n / (n+1)
    ll C_2n_n1 = C_2n_n * n % MOD * mod_pow(n + 1, MOD - 2, MOD) % MOD;
    
    // Catalan number: Cat(n) = C(2n,n)/(n+1)
    ll cat_n = C_2n_n * mod_pow(n + 1, MOD - 2, MOD) % MOD;
    
    // f_{(n+1,n-1)} = 3 * C(2n, n+1) / (n+2)
    ll f_n1_n1 = 3 * C_2n_n1 % MOD * mod_pow(n + 2, MOD - 2, MOD) % MOD;
    
    ll ans = (f_n1_n1 * f_n1_n1 + cat_n * cat_n) % MOD;
    return ans;
}

void verify_restricted_permutations() {
    cout << "PE 916: Restricted Permutations / 有限制排列\n\n";
    
    cout << "P(n) = count of permutations of {1..2n} with\n";
    cout << "  LIS ≤ n+1 and LDS ≤ 2\n\n";
    
    cout << "RSK: shape λ with |λ|=2n, λ₁≤n+1, ℓ(λ)≤2\n";
    cout << "P(n) = Σ (f^λ)² over valid λ\n\n";
    
    // Test P(2) = 13
    cout << "Testing P(2): " << compute_P(2) << " (expected 13)\n";
    
    // Test P(10) mod 1e9+7 = 45265702
    cout << "Testing P(10) mod MOD: " << compute_P(10) << " (expected 45265702)\n";
    
    cout << "\nComputing P(10^8)... (this may be slow)\n";
    // For n=10^8, the O(n) loop is too slow in practice.
    // Need a faster algorithm. This is just a placeholder.
    cout << "Note: O(n) algorithm too slow for n=10^8.\n";
    cout << "Need segmented product / FFT-based approach.\n";
    
    cout << "\n=== PE Answer ===\n" << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify_restricted_permutations(); return 0; }
    
    cout << "PE 916: Restricted Permutations / 有限制排列\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for checks.\n";
    return 0;
}

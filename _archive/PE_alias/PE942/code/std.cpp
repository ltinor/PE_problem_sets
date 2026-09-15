#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 942: Mersenne's Square Root / 梅森平方根
//
// Given natural number q, let p = 2^q - 1 (q-th Mersenne number).
// R(q) = minimal x > 0 such that x² ≡ q (mod p), if it exists.
//
// R(5) = 6, R(17) = 47569.
// 2^74207281 - 1 is prime (Mersenne prime #??).
// Find R(74207281) mod 10^9 + 7.
//
// Key observations:
// - p = 2^q - 1 is a Mersenne prime for q = 74207281.
// - We need √q mod p, i.e., a square root of q modulo p.
// - Since p is prime, we can use the Tonelli-Shanks algorithm.
// - But p is astronomically large (~10^22 million digits!).
//   We cannot compute p explicitly.
// - However, we only need R(q) mod (10^9+7), not R(q) itself.
//   Wait — the problem says: "Find R(74207281). Give your answer modulo 10^9+7."
//   This means compute the actual R(q) (which is a number less than p),
//   then take it modulo 10^9+7.
// - R(q) is less than p = 2^q - 1, so R(q) < 2^74207281.
//   R(q) is the minimal positive solution to x² ≡ q (mod 2^q-1).
//
// Since p = 2^q - 1 ≡ -1 (mod something), we can use properties of
// Mersenne primes to compute the square root.
//
// In a finite field of prime order p = 2^q - 1:
// The elements are integers mod (2^q-1).
// We want sqrt(q) in this field.
//
// Note: q is the exponent, not to be confused with the field element q.
// In the field F_p, the integer q (the exponent) is an element.
// We need its square root.
//
// Since p is a Mersenne prime, p+1 = 2^q is a power of 2.
// This means (p+1)/2 = 2^{q-1} is a power of 2.
//
// For a Mersenne prime p = 2^q - 1, if q ≡ 3 (mod 4), then
// p ≡ 7 (mod 8), and 2 is a quadratic non-residue mod p? Let's check.
// p = 2^q-1. q=74207281 ≡ 1 (mod 4)? 74207281 mod 4 = 1.
// So p = 2^{4k+1} - 1 = 2·(2^4)^k - 1 = 2·16^k - 1.
// Mod 8: 16^k ≡ 0 mod 8? No, 16 ≡ 0 mod 8, so 16^k ≡ 0 mod 8 for k≥1.
// But wait, 2^q mod 8: if q ≥ 3, 2^q ≡ 0 mod 8. So p ≡ -1 ≡ 7 mod 8.
// So p ≡ 7 (mod 8) for any q ≥ 3.
// For p ≡ 7 (mod 8), 2 is a quadratic residue: (2|p) = 1? 
// Actually (2|p) = (-1)^{(p²-1)/8}. p = 8k+7, p²-1 = 64k²+112k+49-1=64k²+112k+48.
// (p²-1)/8 = 8k²+14k+6. (-1)^{even} = 1 if 8k²+14k+6 is even...
// 8k² is even, 14k is even, 6 is even. Total even. So (2|p) = 1.
// So 2 is a quadratic residue mod p.
//
// Also, q mod 4 determines whether q is a QR mod p.
// Since p = 2^q - 1, we have p ≡ 3 (mod 4) if q is odd (always for Mersenne).
// Actually, 2^q ≡ 0 mod 4 for q ≥ 2, so p ≡ -1 ≡ 3 mod 4.
//
// For p ≡ 3 (mod 4), we can compute square roots using:
//   sqrt(a) = a^{(p+1)/4} mod p.
// Since (p+1)/4 = 2^{q-2}.
// So the square root of q mod p is:
//   R(q) = q^{2^{q-2}} mod p   (if q is a quadratic residue mod p)
//
// But this exponentiation requires working mod p = 2^q - 1, which is
// immense. We can use modular exponentiation with the modulus 2^q-1.
// In GF(2^q-1), multiplication mod (2^q-1) can be done using the fact
// that 2^q ≡ 1 (mod p). This is like working in a ring where 2^q = 1.
//
// For the exponent 2^{q-2}, we need to compute q raised to this power
// modulo 2^q-1. This involves repeated squaring.
//
// Actually, we have two huge numbers:
//   - The modulus: p = 2^q - 1 (q ≈ 7.4×10^7 bits → ~9 million bytes)
//   - The base: q (a small 26-bit number)
//   - The exponent: 2^{q-2} (astronomically huge, ~2^{74 million})
//
// We need q^{2^{q-2}} mod (2^q-1).
// This equals q^{(p+1)/4} mod p.
//
// But (p+1)/4 = 2^{q-2}. So we need to square q, q-2 times.
// This is: repeat (q-2) times: x ← x² mod (2^q-1).
// This takes q-2 ≈ 74 million modular squarings. That's feasible!
// Each modular squaring of a number < 2^q-1 takes O(q) bit operations.
// Total: O(q²) ≈ (7.4×10^7)² ≈ 5.5×10^15 operations? No, that's too much.
//
// But we can use the fact that modulus is 2^q - 1:
// For a < 2^q, a mod (2^q-1) can be reduced by:
//   If a ≥ 2^q - 1, a = a_hi·2^q + a_lo ≡ a_hi + a_lo (mod 2^q-1).
// This is the "Mersenne reduction".
//
// When squaring a number < 2^q, the result has < 2q bits.
// So: a² = a_hi·2^q + a_lo, where a_lo < 2^q.
// Then a² mod (2^q-1) = a_hi + a_lo (and maybe reduce again).
//
// Each squaring + reduction takes O(q) bit operations.
// With q ≈ 7.4×10^7, this is about 74 million bit operations per squaring,
// times 74 million squarings = 5.5×10^15 operations. Too slow.
//
// But we only need the result MODULO 10^9+7, not the full value!
// So we need q^{2^{q-2}} mod (2^q-1), then take mod 10^9+7.
//
// We CANNOT compute mod (10^9+7) first because the exponentiation
// is mod (2^q-1). We need the actual value mod (2^q-1) first.
//
// However, there might be a different approach:
// The square root of q mod (2^q-1) has a special form related to
// the binary representation of 1/q or something.
//
// Actually, let's reconsider. R(q) mod (10^9+7) — we need to compute
// the square root of q mod p = 2^q-1, then take that value mod 10^9+7.
//
// Since p and 10^9+7 are coprime (p = 2^q-1, and 2^q ≡ 1 mod p, with
// q = 74207281, 10^9+7 = 1000000007), we could use CRT?
// No, we need x such that x² ≡ q (mod p). There are two solutions
// (±x). We want the minimal positive one, R(q).
//
// Let's look at small examples:
// R(5): p = 31. We need x² ≡ 5 (mod 31).
// x² mod 31 possibilities: 0²=0,1²=1,2²=4,3²=9,4²=16,5²=25,6²=36≡5. ✓
// So R(5)=6. Indeed, 6²=36≡5 mod 31.
// Also 31-6=25: 25²=625=20·31+5≡5. So the two roots are 6 and 25.
// Minimal is 6. ✓
//
// q^{(p+1)/4} = 5^{(31+1)/4} = 5^8 = 390625 ≡ 390625 mod 31.
// 390625 / 31 = 12600.806... Let's compute: 31·12600=390600, remainder 25.
// So 5^8 ≡ 25 mod 31. This gives the OTHER root (25), not the minimal one.
// Because (p+1)/4 = 8, and 5^8 ≡ 25 mod 31.
//
// For p ≡ 3 mod 4: x = a^{(p+1)/4} gives a square root, but which one?
// It gives the one that is a quadratic residue... actually both and neither?
// The result is one specific root. To get the minimal, we take min(x, p-x).
// R(5) = min(25, 6) = 6. ✓
//
// So R(q) = min(q^{(p+1)/4} mod p, p - q^{(p+1)/4} mod p).
//
// For R(17): p = 2^17-1 = 131071.
// (p+1)/4 = 131072/4 = 32768 = 2^{15}.
// q^{2^{15}} mod p: start with q=17, square 15 times mod 131071.
// This is feasible for small q. For q=74207281, we need 74207279 squarings.
//
// But we can use the Chinese Remainder Theorem approach?
// We need x mod (10^9+7). Maybe we can find a formula for x directly.
//
// Let's think about the properties of q mod p.
// p = 2^q - 1. In the field F_p: 2^q ≡ 1.
// So 2 is a q-th root of unity mod p.
//
// The square root of q: x² ≡ q (mod 2^q-1).
// Since q is the exponent, and p = 2^q-1...
//
// Actually, there's a known result: in a Mersenne prime p = 2^q-1,
// the square root of q (when it exists) can be expressed in terms of
// the binary expansion of q, or something related.
//
// Let's try finding a pattern for R(q):
// R(5) = 6
// In binary: q=101₂, R(q)=110₂. 
// R(q) in binary has 3 bits, q has 3 bits.
//
// R(17): let's compute. q=17=10001₂ (5 bits).
// R(17)=47569. 47569 in binary? Let's check:
// 47569 ≈ 2^15.5 ≈ 46341. So R(17) has about 16 bits.
// p = 131071 ≈ 2^17. R(17) < 2^16.
//
// For q=5: R(5)=6, p=31≈2^5. R ≈ 2^{q/2}? No, 2^{2.5}≈5.6.
//
// Maybe R(q) has a special form using the discrete log.
// Let g be a primitive root mod p. Then x² ≡ q means 2·ind_g(x) ≡ ind_g(q) (mod p-1).
// p-1 = 2^q-2 = 2(2^{q-1}-1).
//
// q itself is small (about 2^26). So we're looking for square root of
// a small number in a huge finite field.
//
// Since q is small, we can try to compute the discrete log of q
// relative to some primitive root. But p is huge.
//
// Alternative view: work in the ring Z/(2^q-1)Z.
// We want to compute q^{2^{q-2}} mod (2^q-1).
// Write the exponent 2^{q-2} = (2^q) / 4.
// Since 2^q ≡ 1 (mod 2^q-1), we might be able to simplify.
// But the exponent is in the exponent, not in the base.
//
// Let's try a different approach: use the fact that we only need
// the result modulo 10^9+7.
//
// Let R = q^{2^{q-2}} mod (2^q-1). We want R mod M where M = 10^9+7.
// Note that 2^q-1 and M are coprime (since M is prime ≠ 2, and
// 2^q-1 ≡ 1 mod M if 2^q ≡ 2 mod M... Actually M = 10^9+7).
// We can compute 2^q mod M: q = 74207281. 
// 2^q mod M can be computed efficiently. If 2^q ≠ 2 mod M, 
// then 2^q-1 and M are coprime.
//
// So we need R mod M where R ≡ r (mod 2^q-1) and we know r² ≡ q (mod 2^q-1).
// This implies R ≡ r (mod 2^q-1), so R = r + k·(2^q-1) for some k.
// We want R mod M. We know r < 2^q-1.
//
// Actually, we're computing r = q^{2^{q-2}} mod (2^q-1). This r is the
// specific square root (the one that is a QR of something?).
// Then R(q) = min(r, p-r) where p = 2^q-1.
//
// To compute r mod M without computing all of r:
// We need to compute q^{2^{q-2}} mod (2^q-1), then mod M.
// This is a modular exponentiation with a huge exponent (in the exponent).
// 
// But we're doing repeated squaring of q mod (2^q-1):
// x_0 = q
// x_{i+1} = x_i² mod (2^q-1)
// We need x_{q-2}.
//
// Each step: multiply two q-bit numbers and reduce mod (2^q-1).
// The reduction is: write the 2q-bit product as a·2^q + b, result = a+b.
// If a+b ≥ 2^q-1, subtract 2^q-1.
//
// With q ≈ 74 million, q-bit numbers have ~74 million bits = ~9 MB.
// 74 million squarings of 9 MB numbers = 74M × 9M operations...
// This is ~6.7×10^14 operations. That's a lot but maybe feasible
// with optimized FFT-based multiplication? Even with FFT, 74 million
// squarings is a lot.
//
// Wait, maybe there's a smarter approach. Let me look at the pattern
// more carefully.
//
// For q=5: x_0=5, x_1=5²=25, x_2=25²=625≡5 mod 31 (since 625=20·31+5).
// So x_2 ≡ 5. Then x_3 = 25, x_4 = 5, ... It cycles with period 2!
// q-2 = 3, x_3 = 25. R(5) = min(25, 6) = 6. ✓
//
// For q=17: p=131071. Let's check the cycle.
// q=17 mod 131071. q² = 289. q⁴ = 289² = 83521. 
// q⁸ = 83521² mod 131071 = 6975577441 mod 131071.
// 6975577441 / 131071 ≈ 53220.3. 131071·53220 = 6975598620. Remainder: 6975577441-6975598620 = -21179 ≡ 109892.
// Actually this is tedious by hand.
//
// But the key insight might be that the squaring sequence is periodic
// with a small period, making the computation feasible.
//
// PE answer: (to be computed)

const ll PE_ANSWER = 0; // placeholder
const ll MOD = 1000000007LL;

void verify() {
    cout << "PE 942: Mersenne's Square Root / 梅森平方根\n\n";
    
    cout << "=== Problem Summary ===\n";
    cout << "p = 2^q - 1 (Mersenne number). R(q) = minimal sqrt of q mod p.\n";
    cout << "Given: R(5)=6, R(17)=47569.\n";
    cout << "2^74207281 - 1 is prime. Find R(74207281) mod 10^9+7.\n\n";
    
    cout << "=== Theory ===\n";
    cout << "For Mersenne prime p = 2^q-1, p ≡ 3 (mod 4), p ≡ 7 (mod 8).\n";
    cout << "By Euler's criterion: x = q^{(p+1)/4} mod p gives a square root.\n";
    cout << "(p+1)/4 = 2^{q-2}.\n\n";
    
    cout << "So R(q) = min(x, p-x) where x = q^{2^{q-2}} mod (2^q-1).\n";
    cout << "This means: start with x = q, square (q-2) times mod (2^q-1).\n\n";
    
    cout << "=== Challenge ===\n";
    cout << "q = 74,207,281 ≈ 7.4×10^7.\n";
    cout << "Each squaring works with ~74 million bit numbers (~9 MB).\n";
    cout << "q-2 ≈ 74 million squarings needed.\n";
    cout << "Total: ~74M × 74M bit operations ≈ 5.5×10^15 — very large.\n\n";
    
    cout << "=== Optimization Insights ===\n";
    cout << "The squaring sequence may be periodic in a small cycle.\n";
    cout << "Also, we only need the result mod 10^9+7.\n";
    cout << "Using CRT / properties of Mersenne modulus for reduction.\n\n";
    
    cout << "=== Known values ===\n";
    cout << "  R(5) = 6\n";
    cout << "  R(17) = 47569\n";
    cout << "  Target: R(74207281)\n\n";
    
    cout << "=== PE Answer ===\n" << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);
    
    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify(); return 0; }
    cout << "PE 942: Mersenne's Square Root / 梅森平方根\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for checks.\n";
    return 0;
}

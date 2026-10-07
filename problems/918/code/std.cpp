#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 918: Recursive Sequence Summation / 递归序列求和
//
// a_1 = 1
// a_{2n} = 2*a_n
// a_{2n+1} = a_n - 3*a_{n+1}
//
// S(N) = Σ_{n=1}^{N} a_n
// Given S(10) = -13. Find S(10^12).
//
// Key insight: The recurrence defines a_n based on binary representation.
// Let's analyze the pattern.
//
// For n = 1: a_1 = 1
// For n = 2: a_2 = 2*a_1 = 2
// For n = 3: a_3 = a_1 - 3*a_2 = 1 - 6 = -5
// For n = 4: a_4 = 2*a_2 = 4
// For n = 5: a_5 = a_2 - 3*a_3 = 2 - 3*(-5) = 17
// For n = 6: a_6 = 2*a_3 = -10
// For n = 7: a_7 = a_3 - 3*a_4 = -5 - 12 = -17
// For n = 8: a_8 = 2*a_4 = 8
// For n = 9: a_9 = a_4 - 3*a_5 = 4 - 51 = -47
// For n = 10: a_10 = 2*a_5 = 34
//
// First 10: 1, 2, -5, 4, 17, -10, -17, 8, -47, 34
// Sum S(10) = 1+2-5+4+17-10-17+8-47+34 = -13. ✓
//
// Let's try to find a closed form. Consider the generating function.
// Or we can use the "binary divide and conquer" approach.
//
// Define f(n) = Σ_{k=1}^{n} a_k.
// We want to compute f(n) efficiently using the recurrence.
//
// Let's look for pattern in terms of n's binary representation.
//
// The recurrence for a_n:
//   a_{2n} = 2*a_n
//   a_{2n+1} = a_n - 3*a_{n+1}
//
// This is reminiscent of the Stern-Brocot sequence or a linear 
// combination evaluated at binary digits.
//
// Let's write n in binary and see if a_n has a formula.
//
// Consider the sequence in groups by the highest bit:
// n=1: a1=1
// n=2,3: a2=2a1, a3=a1-3a2
// n=4,5,6,7: a4=2a2, a5=a2-3a3, a6=2a3, a7=a3-3a4
// n=8..15: a8=2a4, a9=a4-3a5, a10=2a5, a11=a5-3a6, a12=2a6, ...
//
// This looks like a tree: from a_n, we generate two children:
//   left child (2n): 2*a_n
//   right child (2n+1): a_n - 3*a_{n+1}
//
// Wait, right child depends on a_{n+1} which is the "sibling" in the next subtree.
// This is NOT a simple tree! The value at 2n+1 depends on the value at n+1.
//
// Let me try to compute a_n using DP with memoization:
// a_n = 
//   if n even (n=2k): 2 * a_k
//   if n odd (n=2k+1): a_k - 3 * a_{k+1}
//
// To compute a_n, we might need a_{n/2} and a_{n/2+1} for odd n.
// This creates a chain of dependencies.
//
// Let's compute a_n in terms of a_1 = 1 only. Express a_n as linear 
// combination c_n * a_1 = c_n, since it's linear.
// Actually: a_n depends linearly on the base case a_1 = 1.
// So a_n = c_n where c_n is some integer determined by the recurrence.
//
// From recurrence:
//   c_{2n} = 2*c_n
//   c_{2n+1} = c_n - 3*c_{n+1}
//
// We need S(N) = Σ_{n=1}^{N} c_n.
//
// Let's look at patterns for sum over ranges.
// Define g(n) = Σ_{k=1}^{2^n - 1} a_k. Let's compute small n:
// S(1) = 1
// S(3) = 1+2-5 = -2
// S(7) = S(3) + 4+17-10-17 = -2 + (4+17-27) = -2 + (-6) = -8
// S(15) = S(7) + 8-47+34+... let me compute:
//   a8=8, a9=-47, a10=34, a11=a5-3a6=17-3(-10)=47, a12=2a6=-20,
//   a13=a6-3a7=-10-3(-17)=41, a14=2a7=-34, a15=a7-3a8=-17-24=-41
//   Sum 8-15: 8-47+34+47-20+41-34-41 = -12
// S(15) = -8 + (-12) = -20
//
// Hmm, not an obvious pattern.
//
// Let's try a different approach. Consider the sums over complete blocks.
// For a complete binary tree of depth d (indices 2^d to 2^{d+1}-1):
// Let T(d) = Σ_{n=2^d}^{2^{d+1}-1} a_n.
//
// n ∈ [2^d, 2^{d+1}-1]: n = 2k (even) or n = 2k+1 (odd) where k ∈ [2^{d-1}, 2^d-1].
//   Even: a_{2k} = 2*a_k
//   Odd: a_{2k+1} = a_k - 3*a_{k+1}
//
// So T(d) = Σ_{k=2^{d-1}}^{2^d-1} (a_{2k} + a_{2k+1})
//         = Σ (2*a_k + a_k - 3*a_{k+1})
//         = Σ (3*a_k - 3*a_{k+1})
//         = 3 * [a_{2^{d-1}} - a_{2^d}]  (telescoping!)
//
// That's beautiful! T(d) = 3 * (a_{2^{d-1}} - a_{2^d}).
//
// For d=2: indices 4..7.
// T(2) = 3*(a_2 - a_4) = 3*(2 - 4) = -6.
// Check: a4+a5+a6+a7 = 4+17-10-17 = -6. ✓!
//
// For d=3: indices 8..15.
// T(3) = 3*(a_4 - a_8) = 3*(4 - 8) = -12.
// We computed: 8-47+34+47-20+41-34-41 = -12. ✓!
//
// For d=1: indices 2..3.
// T(1) = 3*(a_1 - a_2) = 3*(1 - 2) = -3.
// Check: a2+a3 = 2+(-5) = -3. ✓!
//
// So the complete block sums are given by:
// T(d) = 3 * (a_{2^{d-1}} - a_{2^d})
//
// Now, a_{2^d}: since 2^d is a power of 2:
//   a_{2^d} = 2 * a_{2^{d-1}} = 2^2 * a_{2^{d-2}} = ... = 2^d * a_1 = 2^d.
//
// So a_{2^d} = 2^d. And a_{2^{d-1}} = 2^{d-1}.
//
// Therefore: T(d) = 3 * (2^{d-1} - 2^d) = 3 * (-2^{d-1}) = -3 * 2^{d-1}.
//
// Check: T(1) = -3*1 = -3. ✓
// T(2) = -3*2 = -6. ✓
// T(3) = -3*4 = -12. ✓
//
// Now S(2^d - 1) = a_1 + Σ_{i=1}^{d-1} T(i)
//                 = 1 + Σ_{i=1}^{d-1} (-3 * 2^{i-1})
//                 = 1 - 3 * Σ_{i=0}^{d-2} 2^i
//                 = 1 - 3*(2^{d-1} - 1)
//                 = 1 - 3*2^{d-1} + 3
//                 = 4 - 3*2^{d-1}
//
// Check: S(1) = a_1 = 1. Formula: d=1, 4-3*1=1. ✓
// S(3) = 1+2-5 = -2. Formula: d=2, 4-3*2=4-6=-2. ✓
// S(7) = -8. Formula: d=3, 4-3*4=4-12=-8. ✓
// S(15) = -20. Formula: d=4, 4-3*8=4-24=-20. ✓
//
// Great! Now for arbitrary N, we write N in binary and decompose.
//
// Let N have binary representation. We can decompose [1, N] into 
// complete blocks using the binary representation.
//
// Algorithm: start with pos = 1, sum = 0.
// For each bit from MSB to LSB of N:
//   If the bit at position d (from top) is 1:
//     Add the block starting at pos of size 2^d - pos? No...
//
// Better: use recursion. Define F(N) = S(N) = Σ_{n=1}^{N} a_n.
// We can compute F(N) recursively:
//
// If N = 0: F(0) = 0.
// If N is odd: N = 2k+1. F(2k+1) = F(2k) + a_{2k+1}.
// If N is even: N = 2k. F(2k) = F(2k-1) + a_{2k}.
//
// But this might be O(log N) per step? No, we need to compute a_N efficiently.
// Actually, we need a way to compute F(N) without iterating.
//
// Let's use the block decomposition:
// Write N in the form: N = 2^{d_1} + 2^{d_2} + ... + 2^{d_m} - 1 (plus remainder)?
// Or: Use the binary expansion to split [1, N] into complete trees.
//
// Consider the binary representation of N+1:
// Let N+1 = 2^{e_1} + 2^{e_2} + ... (distinct powers).
// Then [1, N] can be partitioned into blocks:
//   [1, 2^{e_1}-1], [2^{e_1}, 2^{e_1}+2^{e_2}-1], etc.
//
// But the second block starts at offset 2^{e_1}, not at a power of 2.
// The a-sequence is not shift-invariant, so this doesn't simplify directly.
//
// Alternative: use the recurrence directly on the sum.
// Define F(N) = S(N).
// For N = 2k: F(2k) = F(k) + Σ_{n=1}^{k} a_{2n}? No.
//   F(2k) = Σ_{n=1}^{2k} a_n = Σ_{n=1}^{k} (a_{2n-1} + a_{2n})
//   = Σ_{n=1}^{k} (a_{n-1} - 3a_n + 2a_n)  [using both recurrences]
//   Wait: a_{2n-1} = a_{n-1} - 3*a_n (where a_0? For n=1, a_1 = 1, but a_0 is undefined).
//   Hmm, the recurrence a_{2n+1} = a_n - 3a_{n+1} is for odd indices ≥ 3.
//   For n=1: a_{2*0+1} = a_1 which is given as 1, not from recurrence.
//
// Let's be more careful. The recurrence is defined for n ≥ 1:
//   a_{2n} = 2*a_n        for n ≥ 1
//   a_{2n+1} = a_n - 3*a_{n+1}  for n ≥ 1
//
// So for n=1: a_2 = 2*a_1, a_3 = a_1 - 3*a_2.
// For n=2: a_4 = 2*a_2, a_5 = a_2 - 3*a_3. etc.
//
// Sum over pairs:
// a_{2n} + a_{2n+1} = 2*a_n + (a_n - 3*a_{n+1}) = 3*a_n - 3*a_{n+1}.
//
// So: Σ_{i=2n}^{2n+1} a_i = 3*(a_n - a_{n+1}).
//
// This telescopes nicely. For a complete block of pairs:
// Σ_{n=A}^{B-1} (a_{2n} + a_{2n+1}) = 3*(a_A - a_B).
//
// Now for F(N):
// Let N = 2k (even). Then:
// F(2k) = a_1 + Σ_{n=1}^{k-1} (a_{2n} + a_{2n+1})
//        = 1 + 3*Σ_{n=1}^{k-1} (a_n - a_{n+1})
//        = 1 + 3*(a_1 - a_k)
//        = 1 + 3*(1 - a_k)
//        = 4 - 3*a_k
//
// Check: F(2) = 4 - 3*a_1 = 4 - 3 = 1. But a_1 + a_2 = 1+2=3. 
// Hmm, doesn't match. Let me recheck.
// N=2=2k, k=1. F(2) should be a_1 + a_2.
// My formula: a_1 + Σ_{n=1}^{0} (...) = a_1 = 1. Not 3.
// The issue: there's no n=1 pair because 2n=2 is the last element.
// For k=1: F(2) = a_1 + a_2 = 1 + 2 = 3.
// So the formula depends on parity.
//
// Let me do it more systematically:
// F(2k) = Σ_{n=1}^{k} a_{2n-1} + Σ_{n=1}^{k} a_{2n}
//
// For the odd terms: a_1, a_3, a_5, ..., a_{2k-1}
//   a_1 = 1 (base)
//   For n ≥ 1: a_{2n+1} = a_n - 3*a_{n+1}
//   So: a_3 = a_1-3a_2, a_5 = a_2-3a_3, ..., a_{2k-1} = a_{k-1} - 3a_k.
//
// Sum of odd terms (excluding a_1):
//   Σ_{n=1}^{k-1} a_{2n+1} = Σ_{n=1}^{k-1} (a_n - 3a_{n+1})
//   = Σ_{n=1}^{k-1} a_n - 3Σ_{n=1}^{k-1} a_{n+1}
//   = Σ_{n=1}^{k-1} a_n - 3Σ_{n=2}^{k} a_n
//   = F(k-1) - 3*(F(k) - a_1)
//   = F(k-1) - 3F(k) + 3
//
// Sum of even terms:
//   Σ_{n=1}^{k} a_{2n} = 2*Σ_{n=1}^{k} a_n = 2*F(k)
//
// So: F(2k) = a_1 + (F(k-1) - 3F(k) + 3) + 2F(k)
//            = 1 + F(k-1) - 3F(k) + 3 + 2F(k)
//            = 4 + F(k-1) - F(k)
//
// Check F(2): k=1. F(2) = 4 + F(0) - F(1) = 4 + 0 - 1 = 3. ✓
// Check F(4): k=2. F(4) = 4 + F(1) - F(2) = 4 + 1 - 3 = 2.
//   Actual: 1+2-5+4 = 2. ✓
// Check F(6): k=3. F(6) = 4 + F(2) - F(3) = 4 + 3 - (-2) = 9.
//   Actual: a1..a6 = 1+2-5+4+17-10 = 9. ✓
//
// Now for odd N = 2k+1:
// F(2k+1) = F(2k) + a_{2k+1}
// And a_{2k+1} = a_k - 3*a_{k+1}
//
// So: F(2k+1) = F(2k) + a_k - 3a_{k+1}
// But a_k = F(k) - F(k-1), a_{k+1} = F(k+1) - F(k).
// = F(2k) + (F(k)-F(k-1)) - 3(F(k+1)-F(k))
// = F(2k) + F(k) - F(k-1) - 3F(k+1) + 3F(k)
// = F(2k) + 4F(k) - F(k-1) - 3F(k+1)
//
// Using F(2k) = 4 + F(k-1) - F(k):
// F(2k+1) = 4 + F(k-1) - F(k) + 4F(k) - F(k-1) - 3F(k+1)
//         = 4 + 3F(k) - 3F(k+1)
//         = 4 + 3(F(k) - F(k+1))
//
// Check F(3): k=1. F(3) = 4 + 3(F(1)-F(2)) = 4 + 3(1-3) = 4-6 = -2. ✓
// Check F(5): k=2. F(5) = 4 + 3(F(2)-F(3)) = 4 + 3(3-(-2)) = 4+15 = 19.
//   Actual: S(5) = 1+2-5+4+17 = 19. ✓
// Check F(7): k=3. F(7) = 4 + 3(F(3)-F(4)) = 4 + 3(-2-2) = 4-12 = -8. ✓
//
// Summary:
//   F(0) = 0
//   F(1) = 1
//   For k ≥ 1:
//     F(2k) = 4 + F(k-1) - F(k)
//     F(2k+1) = 4 + 3(F(k) - F(k+1))
//
// We can compute F(N) recursively in O(log N) depth using memoization!
// Each call reduces N by roughly half, creating a recursion tree.
// The number of distinct states visited is O(log N).
//
// But wait: F(2k+1) depends on F(k) and F(k+1), both of which lead to
// further recursive calls. The recursion might expand.
// Let's trace F(10): N=10, k=5 → F(10) = 4 + F(4) - F(5)
//   F(4): k=2 → 4 + F(1) - F(2) = 4 + 1 - 3 = 2
//   F(5): k=2 → 4 + 3(F(2)-F(3)) = 4 + 3(3+2) = 19
// F(10) = 4 + 2 - 19 = -13. ✓!
//
// The recursion overlaps! F(4) needed for both F(8), F(9), F(10) etc.
// Use memoization with unordered_map.
//
// For N = 10^12, log N ≈ 40, and the recursion explores 
// O(log N) distinct states. Actually might be O(log^2 N) but still tiny.

unordered_map<ll, i128> memo;

i128 F(ll n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (memo.count(n)) return memo[n];
    
    i128 res;
    if (n % 2 == 0) {
        ll k = n / 2;
        res = 4 + F(k - 1) - F(k);
    } else {
        ll k = n / 2;
        res = 4 + 3 * (F(k) - F(k + 1));
    }
    return memo[n] = res;
}

// Helper to print i128
string to_str(i128 x) {
    if (x == 0) return "0";
    string s;
    bool neg = false;
    if (x < 0) { neg = true; x = -x; }
    while (x > 0) {
        s += char('0' + (int)(x % 10));
        x /= 10;
    }
    if (neg) s += '-';
    reverse(s.begin(), s.end());
    return s;
}

// Also compute a_n for verification
i128 compute_a(ll n) {
    if (n == 1) return 1;
    if (n % 2 == 0)
        return 2 * compute_a(n / 2);
    else {
        ll k = n / 2;
        return compute_a(k) - 3 * compute_a(k + 1);
    }
}

void verify_recursive_sequence() {
    cout << "PE 918: Recursive Sequence Summation / 递归序列求和\n\n";
    
    cout << "First 10 terms of a_n:\n";
    for (ll n = 1; n <= 10; n++)
        cout << "  a_" << n << " = " << to_str(compute_a(n)) << "\n";
    
    cout << "\nSums:\n";
    for (ll n = 1; n <= 10; n++) {
        cout << "  S(" << n << ") = " << to_str(F(n));
        if (n == 10) cout << " (expected -13)";
        cout << "\n";
    }
    
    // Verify larger values
    cout << "\nLarger sums:\n";
    cout << "  S(100) = " << to_str(F(100)) << "\n";
    cout << "  S(1000) = " << to_str(F(1000)) << "\n";
    cout << "  S(10^6) = " << to_str(F(1000000)) << "\n";
    
    // Compute S(10^12)
    cout << "\nComputing S(10^12)...\n";
    i128 ans = F(1000000000000LL);
    cout << "  S(10^12) = " << to_str(ans) << "\n";
    
    cout << "\n=== PE Answer ===\n";
    cout << to_str(ans) << "\n";
}

const ll PE_ANSWER = -6999033352333308; // S(10^12)，compute 精确验证（S(10)=-13）

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") { 
        i128 ans = F(1000000000000LL);
        cout << to_str(ans) << "\n";
        return 0;
    }
    if (query == "verify") { verify_recursive_sequence(); return 0; }
    
    cout << "PE 918: Recursive Sequence Summation\n";
    i128 ans = F(1000000000000LL);
    cout << "S(10^12) = " << to_str(ans) << "\n";
    return 0;
}

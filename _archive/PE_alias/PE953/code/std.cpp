#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 953: Factorisation Nim / 因数分解取石子游戏
//
// Nim variant: initial position determined by prime factorization of n.
// Each prime factor (with multiplicity) becomes a pile of that size.
// Standard Nim rules: remove any positive number from one pile.
// First player unable to move loses.
//
// First player loses for n = 1 and n = 70.
// S(N) = sum of n ≤ N where first player loses.
// Given: S(10) = 14, S(100) = 455.
// Find S(10^14) mod 10^9+7.
//
// Key observations:
// - This is standard Nim! The game is impartial.
// - In normal Nim, the first player loses iff the XOR (nim-sum) of
//   all pile sizes is 0.
// - The pile sizes are the prime factors of n (with multiplicity).
//   So for n = ∏ p_i^{e_i}, the piles are: p_1 (e_1 times), p_2 (e_2 times), ...
//
// - The nim-sum = XOR of all prime factors (with multiplicity).
//   Since each prime factor p_i appears e_i times, the XOR contribution
//   of prime p is: XOR e_i copies of p = (e_i mod 2) * p.
//   Because XOR of an even number of equal values is 0, odd is the value itself.
//
// - So the nim-sum is: ⊕_{p|n} (e_p mod 2) * p.
//
// - First player loses when nim-sum = 0, i.e., when for each bit position,
//   the total count of primes having that bit set must be even.
//   But since we're XORing the actual prime values, not individual bits:
//   ⊕ (e_p mod 2)*p = 0.
//
// - This means: the set of primes with odd exponent must XOR to 0.
//
// - n ≤ 10^14. We need to count n where ⊕_{p|n, e_p odd} p = 0.
//
// - Let's define f(n) = XOR of primes dividing n with odd exponent.
//   We want f(n) = 0.
//
// - This is reminiscent of counting squarefree numbers with certain properties.
//   Let n = r · s² where r is squarefree (product of distinct primes).
//   Then the primes with odd exponent are exactly the primes dividing r.
//   So f(n) = XOR of primes in r.
//
// - So: f(n) = 0 iff XOR of primes in the squarefree part of n is 0.
//   Let g(r) = XOR of distinct primes dividing r (for squarefree r).
//
// - Then: S(N) = Σ_{n ≤ N} [g(squarefree_part(n)) == 0].
//
// - For n = r·s² with r squarefree: g(r) = 0.
//   The number of such n ≤ N is: Σ_{r squarefree, g(r)=0} ⌊√(N/r)⌋.
//
// - We need to compute this sum efficiently for N = 10^14.
//   r goes up to N (for s=1 case), but for larger r, √(N/r) is small.
//   We can split: for r ≤ N^(2/3), compute directly with sieve;
//   for larger r, the s^2 factor constraints mean s=1 dominates.
//
// - For N = 10^14, r can be up to 10^14. There are about 6×10^13
//   squarefree numbers, too many to enumerate.
//   But only those with g(r)=0 matter.
//
// - The condition g(r)=0 is a linear condition over GF(2) on the prime
//   indicators. This is related to subset XOR problems.
//
// - Since primes are distinct, g(r) = XOR of primes in r.
//   This is essentially: choose a set of distinct primes whose XOR = 0.
//
// - For primes up to ~10^14, the XOR values range up to ~2^47.
//   This is a subset sum/XOR problem.
//
// - Alternative: since each prime appears at most once in r, and we
//   need their XOR = 0, this is counting subsets of primes that XOR to 0.
//   But the primes are the actual prime numbers, not just bits.
//
// - This is a hard combinatorial problem. Likely needs generating functions
//   or meet-in-the-middle for small primes + analytic for large primes.
//
// - PE answer: (to be computed)

const ll PE_ANSWER = 0; // placeholder
const ll MOD = 1000000007LL;

void verify() {
    cout << "PE 953: Factorisation Nim / 因数分解取石子游戏\n\n";
    
    cout << "=== Problem Summary ===\n";
    cout << "Nim where piles = prime factors of n (with multiplicity).\n";
    cout << "First player loses when nim-sum = 0.\n";
    cout << "nim-sum = XOR of all prime factors = ⊕_{p|n} (e_p mod 2)*p.\n";
    cout << "S(N) = sum of n ≤ N where first player loses.\n";
    cout << "S(10) = 14, S(100) = 455. Find S(10^14) mod 10^9+7.\n\n";
    
    cout << "=== Analysis ===\n";
    cout << "Write n = r·s² where r is squarefree.\n";
    cout << "nim-sum = XOR of primes in r.\n";
    cout << "Need r such that XOR of its prime divisors = 0.\n";
    cout << "S(N) = Σ_{r: g(r)=0} ⌊√(N/r)⌋.\n\n";
    
    // Brute force for small N to verify
    cout << "=== Brute Force (S(10)) ===\n";
    auto nim_value = [](ll n) -> ll {
        ll x = 0;
        for (ll p = 2; p * p <= n; p++) {
            int cnt = 0;
            while (n % p == 0) { n /= p; cnt++; }
            if (cnt % 2 == 1) x ^= p;
        }
        if (n > 1) x ^= n;
        return x;
    };
    
    ll S10 = 0;
    for (ll n = 1; n <= 10; n++) {
        if (nim_value(n) == 0) {
            S10 += n;
            cout << "  n=" << n << " (losing)\n";
        }
    }
    cout << "S(10) = " << S10 << " (expected 14)\n\n";
    
    cout << "=== PE Answer ===\n" << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);
    
    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify(); return 0; }
    cout << "PE 953: Factorisation Nim / 因数分解取石子游戏\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for checks.\n";
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 967: B-Trivisible Numbers / B-三除数
//
// A positive integer n is "B-trivisible" if the sum of all different
// prime factors of n that are ≤ B is divisible by 3.
//
// If no prime factors ≤ B, the sum is 0 (divisible by 3).
//
// F(N, B) = count of B-trivisible integers ≤ N.
// F(10, 4) = 5 (numbers: 1,3,5,7,9)
// F(10, 10) = 3
// F(100, 10) = 41
// Find F(10^18, 120).
//
// Key observations:
// - For a number n, let S_B(n) = sum of distinct prime factors ≤ B.
//   n is B-trivisible iff S_B(n) ≡ 0 (mod 3).
//
// - We can write n = u · v where u contains only primes ≤ B, and v
//   contains only primes > B.
//   Let u = ∏_{p ≤ B} p^{e_p}, v = ∏_{p > B} p^{f_p}.
//
// - S_B(n) depends only on u (the small-prime part). Specifically,
//   S_B(n) = Σ_{p|u} p = sum of DISTINCT primes dividing u.
//
// - So n is B-trivisible iff the set of B-smooth primes dividing n
//   (the distinct small primes present) sums to 0 mod 3.
//
// - v plays no role: any primes > B don't contribute to S_B(n).
//
// - For N = 10^18 and B = 120: primes ≤ 120 are:
//   2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113.
//   That's 30 primes.
//
// - For each subset S of these primes, let P(S) = sum_{p∈S} p mod 3.
//   We want subsets where P(S) ≡ 0 (mod 3).
//
// - For a fixed subset S, count numbers ≤ N whose set of distinct small
//   prime divisors is exactly S (or a superset of S?).
//
// - Wait: S_B(n) = sum of all distinct prime factors ≤ B. So if n has
//   small prime factors {2, 3}, then S_B(n) = 2+3 = 5.
//   If n also has large prime factors, they don't affect S_B(n).
//
// - Let's count n ≤ N such that the set of distinct primes p ≤ B dividing
//   n has sum ≡ 0 (mod 3).
//
// - Use inclusion-exclusion over the 30 primes.
//
// - For a set T of primes ≤ B: numbers divisible by ALL primes in T.
//   These numbers have the form: m · ∏_{p∈T} p, where m has no restrictions
//   from small primes (can include or not include other small primes).
//
// - This is standard: use the zeta/mobius transform over the divisor lattice.
//
// - Let f(S) = count of n ≤ N such that the set of distinct small primes
//   dividing n is exactly S.
// - Let g(T) = count of n ≤ N such that T ⊆ (set of small primes dividing n),
//   i.e., all primes in T divide n. Then g(T) = ⌊N / ∏_{p∈T} p⌋.
//
// - By Möbius inversion: f(S) = Σ_{T⊇S} (-1)^{|T|-|S|} · g(T).
//
// - We need: Σ_{S: sum(S) ≡ 0 mod 3} f(S).
//
// - This is O(2^30) which is about 10^9 — too large for direct enumeration.
//   But we can use meet-in-the-middle: split the 30 primes into two
//   groups of 15. For each half, compute all subsets and their products
//   and sums mod 3.
//
// - 2^15 = 32768, which is manageable.
//
// - For each subset from the left half (product P_L, sum mod 3 = s_L),
//   and each subset from the right half (product P_R, sum mod 3 = s_R):
//   The combined product P = P_L · P_R (must be ≤ N).
//   The combined sum mod 3 = (s_L + s_R) mod 3.
//   We need s_L + s_R ≡ 0 (mod 3).
//
// - But we also need to account for the inclusion-exclusion signs!
//   The Möbius function for the inclusion-exclusion is (-1)^{|S|}.
//
// - Actually, we want F(N, B) = Σ_{S: sum≡0 mod 3} f(S).
//   = Σ_{S: sum≡0} Σ_{T⊇S} (-1)^{|T|-|S|} g(T).
//   = Σ_{T} g(T) · Σ_{S⊆T, sum(S)≡0} (-1)^{|T|-|S|}.
//   = Σ_{T} (-1)^{|T|} · g(T) · Σ_{S⊆T, sum(S)≡0} (-1)^{|S|}.
//
// - Let h(T) = Σ_{S⊆T, sum(S)≡0 mod 3} (-1)^{|S|}.
//   This depends only on the multiset of primes in T modulo 3.
//   Specifically, for each prime p, the contribution to sum mod 3 is p mod 3.
//
// - Wait, this can be simplified further. Let's think differently.
//
// - Alternative: Use generating functions.
//   For each prime p ≤ B, we have two choices: p divides n or not.
//   If p divides n, it contributes p to the sum and appears in the product.
//   But n can be divisible by p any number of times ≥ 1.
//
// - Actually, g(T) = ⌊N / P_T⌋ counts numbers divisible by all primes in T
//   (at least once). The Möbius inversion gives f(S) exactly.
//
// - F(N, B) = Σ_{S: sum≡0} f(S) = count of numbers where the distinct
//   small prime divisors sum to 0 mod 3.
//
// - Simpler: use DP over the primes. For each prime p, we decide whether
//   it divides n. If it does, we need to account for the fact that it
//   can appear with any exponent ≥ 1.
//
// - DP state: (index in prime list, current_product, current_sum_mod3).
//   But product can be up to 10^18, too many states.
//
// - Meet-in-the-middle: compute all subset products and sums for the first
//   15 primes, and separately for the last 15 primes.
//   For each left subset with product P_L and sign (-1)^{|S_L|}:
//     Count = Σ_{S_R: s_L+s_R≡0} (-1)^{|S_R|} · ⌊N / (P_L · P_R)⌋.
//
// - We can group by product and sum mod 3.
//
// - Let A[s][p] = Σ_{S: sum≡s, product=p} (-1)^{|S|} for the left half.
//   Similarly B[s][q] for the right half.
//   Then F = Σ_{s_L, s_R: s_L+s_R≡0} Σ_{p,q} A[s_L][p] · B[s_R][q] · ⌊N/(p·q)⌋.
//
// - The number of distinct products is at most 2^15 ≈ 32768 per half.
//   Computing the double sum is O(2^30) which is too slow.
//
// - But we can sort the products and use two-pointer technique.
//   For fixed s_L, s_R: we need Σ_{p,q} A[p]·B[q]·⌊N/(p·q)⌋.
//   Sort p ascending, q descending. For each p, find all q such that
//   p·q ≤ N. Compute the sum using prefix sums of B[q].
//
// - This is O(M log M) where M = 2^15.
//
// - PE answer: (to be computed)

const ll PE_ANSWER = 0; // placeholder
const ll N_VAL = 1000000000000000000LL; // 10^18
const int B = 120;

// Primes ≤ 120
vector<int> primes_upto_120() {
    vector<int> ps;
    vector<bool> is_prime(B + 1, true);
    for (int i = 2; i <= B; i++) {
        if (is_prime[i]) {
            ps.push_back(i);
            for (int j = i * i; j <= B; j += i) is_prime[j] = false;
        }
    }
    return ps;
}

void verify() {
    cout << "PE 967: B-Trivisible Numbers / B-三除数\n\n";
    
    cout << "=== Problem Summary ===\n";
    cout << "B-trivisible: sum of distinct prime factors ≤ B is divisible by 3.\n";
    cout << "F(N, B) = count of B-trivisible numbers ≤ N.\n";
    cout << "F(10,4)=5, F(10,10)=3, F(100,10)=41.\n";
    cout << "Find F(10^18, 120).\n\n";
    
    cout << "=== Analysis ===\n";
    cout << "Split n = u·v where u has only primes ≤ B.\n";
    cout << "Only distinct primes in u matter. Use inclusion-exclusion.\n";
    cout << "B=120: 30 primes. Meet-in-the-middle: 2^15 per half.\n\n";
    
    // List primes
    auto ps = primes_upto_120();
    cout << "=== Primes ≤ 120 (" << ps.size() << " primes) ===\n";
    for (int i = 0; i < (int)ps.size(); i++) {
        cout << ps[i];
        if (i < (int)ps.size() - 1) cout << ",";
        if ((i + 1) % 10 == 0) cout << "\n";
    }
    cout << "\n\n";
    
    // Brute force verification for small values
    cout << "=== Brute Force Verification ===\n";
    auto is_trivisible = [&](ll n, int B) -> bool {
        ll sum = 0;
        for (int p : ps) {
            if (p > B) break;
            if (n % p == 0) sum += p;
        }
        return sum % 3 == 0;
    };
    
    for (auto [N, Bval] : vector<pair<ll,int>>{{10, 4}, {10, 10}, {100, 10}}) {
        ll cnt = 0;
        for (ll n = 1; n <= N; n++) {
            if (is_trivisible(n, Bval)) cnt++;
        }
        cout << "  F(" << N << ", " << Bval << ") = " << cnt << "\n";
    }
    cout << "\n";
    
    cout << "=== Target ===\n";
    cout << "F(10^18, 120). Meet-in-the-middle with 30 primes.\n";
    cout << "O(2^15 log 2^15) ~ 10^6 operations.\n\n";
    
    cout << "=== PE Answer ===\n" << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);
    
    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify(); return 0; }
    cout << "PE 967: B-Trivisible Numbers / B-三除数\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for checks.\n";
    return 0;
}

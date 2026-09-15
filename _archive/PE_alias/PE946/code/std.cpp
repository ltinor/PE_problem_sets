#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 946: Continued Fraction Fraction / 连分数的分数
//
// α = continued fraction where the number of 1's between successive 2's
// are consecutive prime numbers: [2; 1,1,2, 1,1,1,2, 1,1,1,1,1,2, ...]
// β = (2α+3)/(3α+2).
// First 10 coefficients of β's continued fraction: [0;1,5,6,16,9,1,10,16,11], sum=75.
// Find sum of first 10^8 coefficients of β's continued fraction.
//
// Key observations:
// - α has a structured continued fraction determined by primes.
// - β is a Möbius transformation of α: β = (2α+3)/(3α+2).
// - The CF of β can be derived from the CF of α.
// - The transformation (2z+3)/(3z+2) maps positive reals.
//   Its fixed points: (2z+3)/(3z+2) = z → 3z²+2z = 2z+3 → 3z² = 3 → z = ±1.
//   So z=1 is a fixed point. α > 1, so β < α? Let's check.
//
// - For continued fractions, Möbius transformations can be processed
//   by matrix multiplication. Represent a CF as a sequence of matrices.
//
// - Let M = [[2,3],[3,2]]. Then β = M(α) where M(x) = (2x+3)/(3x+2).
//
// - For the continued fraction expansion, we can use the Stern-Brocot
//   tree or the Gosper algorithm for CF arithmetic.
//
// - The Gosper algorithm computes the CF of a Möbius transformation of
//   a CF: given CF(a₀,a₁,a₂,...) and matrix [[a,b],[c,d]], output CF of
//   (a·x+b)/(c·x+d).
//
// - For 10^8 terms, we need an efficient generation strategy.
//   The CF of α has a simple pattern: runs of 1's separated by 2's,
//   where run lengths are primes: 2,3,5,7,11,13,17,19,...
//
// - We can process α digit by digit using the Gosper algorithm to
//   generate β's CF digits.
//
// Gosper algorithm for CF:
//   State: matrix Z = [[a,b],[c,d]] and next input term x from α.
//   The current value is (a·x+b)/(c·x+d).
//   While floor(a/c) = floor(b/d) (or some condition), emit this value.
//   Then ingest the next CF term of α.
//
// Actually, there's a more efficient method: the CF of a Möbius
// transformation of a quadratic irrational is eventually periodic.
// But α is not quadratic; it's defined by the sequence of primes.
// So β's CF will also be non-periodic.
//
// We need to output 10^8 terms. This requires ~10^8 iterations of the
// Gosper algorithm with big integers. The CF terms of α follow the
// prime pattern, so we need to generate primes up to what's needed.
//
// The sum of the first 10^8 terms will be computed as we go.
// We don't need to store the terms, just sum them.
//
// Challenge: 10^8 iterations of Gosper with big integers may be slow.
// Need to optimize with 128-bit or arbitrary precision integers.
// The CF terms of β can be bounded: they come from the continued fraction
// of β ≈ (2·2.5+3)/(3·2.5+2) = (5+3)/(7.5+2) = 8/9.5 ≈ 0.842.
// So β ∈ (0,1), and its first CF term is 0 (the integer part).
// The subsequent terms are ≥ 1.
//
// As primes grow, the run lengths of 1's in α grow. This means α
// approaches 2 from above? Actually:
// α = 2 + 1/(1 + 1/(1 + 1/(2 + ...)))
// With long runs of 1's, the CF approaches the golden ratio-like values.
//
// Let's think about efficiency:
// - Need to generate primes up to how far? After 10^8 CF terms of β,
//   how many CF terms of α have been consumed?
// - The transformation roughly preserves the "information rate":
//   each CF term of α produces about 1 CF term of β (on average).
// - So we need roughly 10^8 primes. The 10^8-th prime is about
//   10^8 · log(10^8) ≈ 10^8 · 18.4 ≈ 1.84×10^9. 
//   That's prime #100,000,000 ≈ 2,038,074,743.
//   We can sieve to that size (about 2 billion) — memory heavy but feasible
//   with segmented sieve.
//
// Alternative: use the property that the CF of β might have a simpler
// pattern than directly simulating. But deriving it is non-trivial.
//
// For the Gosper algorithm, we need matrix operations. At each step:
//   State: Z = [[z11,z12],[z21,z22]] (integers).
//   Current value: (z11·α + z12) / (z21·α + z22).
//   We want to output a CF term q = floor(value).
//   q = floor(z11/z21) if z21 ≠ 0 and sign matches.
//   After outputting q, the state transforms:
//     Multiply Z by [[q,1],[1,0]] on the right? Or subtract q and invert:
//     Z' = [[0,1],[1,-q]] · Z? 
//
// The standard Gosper algorithm:
//   while true:
//     if z21 == 0: break (value is integer or infinite)
//     q1 = z11 / z21 (integer division, assuming same sign)
//     q2 = z12 / z22
//     if q1 == q2:
//       output q1
//       Z = [[0,1],[1,-q1]] · Z   (then swap rows? Actually:)
//       Z = [[z21, z22], [z11 - q1*z21, z12 - q1*z22]]
//     else:
//       ingest next term x from α
//       Z = Z · [[x,1],[1,0]] = [[z11*x+z12, z11], [z21*x+z22, z21]]
//
// This is the standard CF arithmetic algorithm.
//
// For 10^8 iterations, we need efficient big integer arithmetic.
// Using 128-bit integers (__int128) should suffice for a while,
// but the numbers grow as we process.
// Actually, the Gosper algorithm keeps numbers bounded by the
// denominator of the current convergent. For β with 10^8 terms,
// the numbers could be quite large.
//
// Practical approach:
// - Use Python for 10^8 iterations? Too slow.
// - Use C++ with GMP (big integers).
// - Or: the numbers don't grow too fast because each step
//   reduces them. Let's try with __int128 and see.
//
// PE answer: (to be computed)

const ll PE_ANSWER = 0; // placeholder

// Generate primes using simple sieve up to limit
vector<int> generate_primes(int limit) {
    vector<bool> is_prime(limit + 1, true);
    vector<int> primes;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            if ((long long)i * i <= limit) {
                for (int j = i * i; j <= limit; j += i)
                    is_prime[j] = false;
            }
        }
    }
    return primes;
}

// Gosper algorithm to compute CF of M(α) where M = [[2,3],[3,2]]
// and α has CF determined by primes.
// Returns vector of CF terms.
vector<ll> compute_beta_cf(int num_terms) {
    // Matrix Z = [[a,b],[c,d]] representing (a*α+b)/(c*α+d) = β
    // Initially Z = [[2,3],[3,2]]
    i128 a = 2, b = 3, c = 3, d = 2;
    
    vector<ll> result;
    
    // α's CF: starts with 2, then runs of 1's with prime lengths.
    // α = [2; 1(×2), 2, 1(×3), 2, 1(×5), 2, 1(×7), 2, ...]
    // So α_0 = 2 (integer part)
    // Then α_1 through α_2 = 1,1 (2 ones) = run for prime 2
    // α_3 = 2
    // α_4 through α_6 = 1,1,1 (3 ones) = run for prime 3
    // α_7 = 2
    // α_8 through α_12 = 1,1,1,1,1 (5 ones) = run for prime 5
    // ...
    
    // We need a way to generate α's terms on demand.
    // Pre-generate primes up to some limit.
    // The nth α term is: 
    //   α_terms = [2] + [1]*p_0 + [2] + [1]*p_1 + [2] + [1]*p_2 + ...
    // where p_i are primes starting from 2.
    
    auto primes = generate_primes(2000000000); // need enough primes for 10^8 β terms
    
    // Generator state for α
    int alpha_idx = -1; // current position in α sequence
    int prime_idx = 0;  // index of current prime
    int run_pos = 0;    // position within current run of 1's
    bool in_run = false; // are we in a run of 1's?
    
    auto next_alpha = [&]() -> int {
        alpha_idx++;
        if (alpha_idx == 0) return 2; // first term
        if (in_run) {
            run_pos++;
            if (run_pos >= primes[prime_idx]) {
                // run ended, output 2
                in_run = false;
                prime_idx++;
                return 2;
            }
            return 1;
        } else {
            // start a new run of 1's
            in_run = true;
            run_pos = 1;
            return 1;
        }
    };
    
    // Gosper loop
    while ((int)result.size() < num_terms) {
        if (c == 0) break;
        
        i128 q1 = a / c;  // assuming a,c > 0
        i128 q2 = (d == 0) ? q1 : b / d;
        
        if (q1 == q2 && c != 0 && d != 0) {
            result.push_back((ll)q1);
            
            // Transform: value → 1/(value - q1)
            // New Z = [[c,d],[a-q1*c, b-q1*d]]
            i128 na = c, nb = d;
            i128 nc = a - q1 * c;
            i128 nd = b - q1 * d;
            a = na; b = nb; c = nc; d = nd;
        } else {
            // Ingest next α term
            int x = next_alpha();
            // Z = Z · [[x,1],[1,0]] = [[a*x+b, a], [c*x+d, c]]
            i128 na = a * x + b, nb = a;
            i128 nc = c * x + d, nd = c;
            a = na; b = nb; c = nc; d = nd;
        }
    }
    
    return result;
}

void verify() {
    cout << "PE 946: Continued Fraction Fraction / 连分数的分数\n\n";
    
    cout << "=== Problem Summary ===\n";
    cout << "α = [2; 1(×2), 2, 1(×3), 2, 1(×5), 2, 1(×7), 2, ...]\n";
    cout << "where the number of 1's between 2's are consecutive primes.\n";
    cout << "β = (2α+3)/(3α+2).\n";
    cout << "First 10 CF terms of β: [0;1,5,6,16,9,1,10,16,11], sum=75.\n";
    cout << "Find sum of first 10^8 CF terms of β.\n\n";
    
    cout << "=== Gosper Algorithm ===\n";
    cout << "Use the Gosper algorithm for CF arithmetic:\n";
    cout << "  State: Z = [[a,b],[c,d]] representing (aα+b)/(cα+d).\n";
    cout << "  At each step: emit floor(a/c) if floor(a/c)=floor(b/d).\n";
    cout << "  Otherwise ingest next term of α.\n\n";
    
    cout << "=== Verification of first 10 terms ===\n";
    auto beta_terms = compute_beta_cf(10);
    cout << "First 10 CF terms of β: [";
    for (size_t i = 0; i < beta_terms.size(); i++) {
        if (i) cout << ";";
        cout << beta_terms[i];
    }
    cout << "]\n";
    
    ll sum10 = 0;
    for (int i = 0; i < 10; i++) sum10 += beta_terms[i];
    cout << "Sum = " << sum10 << " (expected 75)\n\n";
    
    cout << "=== Target ===\n";
    cout << "Compute first 10^8 CF terms and sum them.\n";
    cout << "Need ~10^8 primes (up to ~2×10^9) and Gosper iteration.\n\n";
    
    cout << "=== PE Answer ===\n" << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);
    
    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify(); return 0; }
    cout << "PE 946: Continued Fraction Fraction / 连分数的分数\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for checks.\n";
    return 0;
}

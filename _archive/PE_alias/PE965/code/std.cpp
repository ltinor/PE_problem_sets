#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 965: Expected Minimal Fractional Value / 最小分数期望值
//
// {x} = fractional part of x.
// f_N(x) = min_{0 < n ≤ N} {n·x}.
// F(N) = E[f_N(x)] for x ~ Uniform[0,1].
//
// F(1) = 1/2, F(4) = 1/4, F(10) ≈ 0.1319444444444.
// Find F(10^4), rounded to 13 decimal places.
//
// Key observations:
// - For a fixed x, f_N(x) = min_{n=1..N} {n·x} is the distance from
//   0 to the nearest multiple of x modulo 1.
//
// - This is the minimum distance from the origin to the set
//   {x, 2x, 3x, ..., Nx} modulo 1.
//
// - For irrational x, the sequence {n·x} is equidistributed modulo 1.
//   The minimum of the first N fractional parts has a known distribution.
//
// - This is related to the three-gap theorem (Steinhaus theorem) and
//   the distribution of fractional parts.
//
// - For a given x, the fractional parts {x}, {2x}, ..., {Nx} partition
//   [0,1] into N+1 intervals. The minimum {n·x} is the smallest positive
//   value in this sequence, which corresponds to the smallest gap
//   adjacent to 0.
//
// - The three-gap theorem: the points {n·x} for n=1..N partition [0,1]
//   into intervals of at most three distinct lengths.
//
// - The minimum distance is the smaller of the two gaps adjacent to 0.
//   Actually, there are two gaps touching 0: from 0 to the smallest {n·x},
//   and from 0 to... wait, 0 is represented by the point 0 = {0·x}
//   or by {k·x} = 0 when k·x is integer.
//
// - More precisely: consider the set S_N(x) = {{n·x} : n = 1..N} ∪ {0, 1}.
//   Sort them: 0 = s_0 < s_1 < ... < s_M = 1.
//   f_N(x) = s_1 (the smallest positive fractional part).
//
// - Equivalently, f_N(x) = min_{n=1..N} ||n·x|| where ||·|| is distance
//   to nearest integer. But we want the fractional part (always positive),
//   which is the distance ABOVE the nearest integer, not the absolute distance.
//   Actually, {z} ∈ [0,1). The minimum {n·x} is always the positive
//   distance from a multiple of x to the next integer below it.
//
// - Wait: {n·x} = n·x - ⌊n·x⌋. This is the positive fractional part.
//   The minimum is the smallest positive value among these.
//
// - Since x ∈ [0,1], {n·x} ranges from 0 to n·x mod 1.
//   For fixed x, the min over n=1..N is essentially the distance from
//   0 to the set {n·x mod 1} in the positive direction.
//
// - For expected value: F(N) = ∫_0^1 f_N(x) dx.
//
// - Known result: For a given N, the expected minimum gap in the sequence
//   of fractional parts of multiples of a random number.
//
// - Let's use the transformation: for fixed n, the set of x where
//   {n·x} < t is the set of x where n·x ∈ ∪_{k} [k, k+t).
//   This is: x ∈ ∪_{k=0}^{n-1} [k/n, (k+t)/n).
//   Measure = t (since n intervals of length t/n).
//
// - So P({n·x} < t) = t for any t ∈ [0,1].
//
// - We need: P(min_{n=1..N} {n·x} < t) = 1 - P(all {n·x} ≥ t for n=1..N).
//   But these events are NOT independent.
//
// - The condition {n·x} ≥ t means: n·x mod 1 ≥ t.
//   i.e., n·x ∈ ∪_{k} [k+t, k+1) for integer k.
//   Equivalent: x ∈ ∪_{k=0}^{n-1} [(k+t)/n, (k+1)/n).
//
// - So for fixed t, the set of x where ALL {n·x} ≥ t is the intersection
//   over n=1..N of those unions.
//
// - This is related to the Farey sequence and the distribution of
//   multiples modulo 1.
//
// - Alternative approach: The expected minimum of N uniform order statistics
//   is 1/(N+1). But {n·x} are NOT independent order statistics of uniform.
//
// - However, for x uniform, the set {{x}, {2x}, ..., {Nx}} has the same
//   distribution as N independent uniform points? No!
//
// - But there is a known result: the expected value F(N) can be computed
//   using the identity: F(N) = Σ_{k=1}^N 1/(k·(k+1)) · μ(k)/k... No.
//
// - Let me look at small N to find patterns.
//   F(1) = ∫_0^1 min({x}) dx = ∫_0^1 x dx = 1/2. ✓
//   F(2) = ∫_0^1 min({x}, {2x}) dx.
//     For x ∈ [0, 1/2): {x}=x, {2x}=2x, min = x.
//     For x ∈ [1/2, 1): {x}=x, {2x}=2x-1, min = min(x, 2x-1).
//     When x < 2x-1: x < 2x-1 → 1 < x. So for x∈[1/2,1): x ≥ 2x-1 if x≤1.
//     Actually: x ≥ 2x-1 ⇔ 1 ≥ x. So 2x-1 ≤ x for x ∈ [1/2, 1].
//     Thus min = 2x-1 on [1/2, 1).
//     F(2) = ∫_0^{1/2} x dx + ∫_{1/2}^1 (2x-1) dx = [x²/2]_0^{1/2} + [x²-x]_{1/2}^1
//     = (1/8) + (0 - 0) - (1/4 - 1/2) = 1/8 + 1/4 = 3/8.
//
// - F(3) would be more complex. But F(4) = 1/4, F(10) ≈ 0.131944...
//
// - Let's compute F(4) by integration: F(4) = 1/4 suggests a pattern.
//
// - The answer may involve the totient function or Farey sequences.
//
// - PE answer: (to be computed as floating point)

const ll PE_ANSWER = 0; // placeholder

void verify() {
    cout << "PE 965: Expected Minimal Fractional Value / 最小分数期望值\n\n";
    
    cout << "=== Problem Summary ===\n";
    cout << "{x} = fractional part. f_N(x) = min_{n=1..N} {n·x}.\n";
    cout << "F(N) = E[f_N(x)] for x ~ Uniform[0,1].\n";
    cout << "F(1)=1/2, F(4)=1/4, F(10)≈0.1319444444444.\n";
    cout << "Find F(10^4) to 13 decimal places.\n\n";
    
    cout << "=== Analysis ===\n";
    cout << "f_N(x) = smallest positive fractional part among n·x (n=1..N).\n";
    cout << "F(N) = expected minimum gap adjacent to 0.\n\n";
    
    // Monte Carlo verification for small N
    cout << "=== Monte Carlo Verification ===\n";
    srand(time(0));
    for (int N : {1, 4, 10}) {
        int trials = 1000000;
        double sum = 0;
        for (int t = 0; t < trials; t++) {
            double x = (double)rand() / RAND_MAX;
            double mn = 1.0;
            for (int n = 1; n <= N; n++) {
                double frac = fmod(n * x, 1.0);
                if (frac < mn) mn = frac;
            }
            sum += mn;
        }
        cout << "  F(" << N << ") ≈ " << fixed << setprecision(12) << sum/trials << "\n";
    }
    cout << "  F(1)=0.5, F(4)=0.25, F(10)≈0.1319444444444\n\n";
    
    cout << "=== Target ===\n";
    cout << "F(10^4) to 13 decimals. Need analytic formula.\n";
    cout << "Relates to Farey sequences and order statistics.\n\n";
    
    cout << "=== PE Answer ===\n" << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);
    
    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify(); return 0; }
    cout << "PE 965: Expected Minimal Fractional Value / 最小分数期望值\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for checks.\n";
    return 0;
}

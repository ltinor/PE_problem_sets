#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE401: Sum of squares of divisors — SIGMA2(N) = Σ σ₂(i) for i=1..N
//
// Derivation:
//   Σ_{i=1}^N σ₂(i) = Σ_{i=1}^N Σ_{d|i} d²
//                   = Σ_{d=1}^N d² × ⌊N/d⌋
//
// Algorithm: O(√N) using integer-division blocks (harmonic lemma)
//   The quotient q = ⌊N/d⌋ takes only O(√N) distinct values.
//   For each q, the range of d where ⌊N/d⌋ = q is [L,R]:
//     L = ⌊N/(q+1)⌋ + 1,  R = ⌊N/q⌋
//   The contribution of block q is: q × Σ_{d=L..R} d²
//
// Sum of squares formula: Σ_{i=1}^n i² = n(n+1)(2n+1)/6
//
// PE original: SIGMA2(10^15) mod 10^9 = 281632621
// Adapted: read N and M from input, compute SIGMA2(N) mod M

// Sum of squares 1²+2²+…+n² = n(n+1)(2n+1)/6, computed modulo MOD
// Handles division by 6 without modular inverse by cancelling factors
ll sum_of_squares(ll n, ll MOD) {
    if (n <= 0) return 0;
    ll a = n, b = n + 1, c = 2 * n + 1;
    // cancel factor 2
    if (a % 2 == 0) a /= 2;
    else if (b % 2 == 0) b /= 2;
    else c /= 2; // c is odd when a,b are odd; 2n+1 is odd for odd n? No: n odd → 2n+1 odd
    // Wait — need to handle the edge case: if all three are odd then we divide c/2
    // Actually c=2n+1 is always odd, so if a,b are both odd, divide c by 2 (integer div)
    // Better: divide by 2 and 3 separately
    return 0; // placeholder — redo below
}

ll sum_of_squares_1_to_n(ll n, ll MOD) {
    if (n <= 0) return 0;
    // n(n+1)(2n+1)/6 mod MOD
    ll a = n, b = n + 1, c = 2 * n + 1;
    // Divide by 2: one of a, b is even
    if (a % 2 == 0) a /= 2;
    else b /= 2;
    // Divide by 3: one of a, b, c is divisible by 3
    if (a % 3 == 0) a /= 3;
    else if (b % 3 == 0) b /= 3;
    else c /= 3;
    a %= MOD; b %= MOD; c %= MOD;
    return ((a * b) % MOD) * c % MOD;
}

// Sum of squares in range [L, R] (inclusive)
ll sum_sq_range(ll L, ll R, ll MOD) {
    if (L > R) return 0;
    ll sR = sum_of_squares_1_to_n(R, MOD);
    ll sL = sum_of_squares_1_to_n(L - 1, MOD);
    return (sR - sL + MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    ll N, M;
    cin >> N >> M;

    ll ans = 0;
    ll sq = (ll)sqrt((long double)N);

    // Part 1: d from 1 to √N — direct computation
    for (ll d = 1; d <= sq; ++d) {
        ll q = N / d;          // ⌊N/d⌋
        ll term = (d % M) * (d % M) % M; // d² mod M
        term = term * (q % M) % M;
        ans = (ans + term) % M;
    }

    // Part 2: iterate over quotient values q = ⌊N/d⌋ for q < √N
    // The last d-value handled in part 1 was sq, where q = N/sq ≥ sq
    // Now handle q from N/(sq+1) down to 1
    for (ll q = N / (sq + 1); q >= 1; --q) {
        ll R = N / q;           // largest d with ⌊N/d⌋ = q
        ll L = N / (q + 1) + 1; // smallest d with ⌊N/d⌋ = q

        // Avoid double-counting the region already covered in Part 1
        if (L <= sq) L = sq + 1;
        if (L > R) continue;

        ll block = sum_sq_range(L, R, M); // Σ_{d=L..R} d² mod M
        ans = (ans + (q % M) * block) % M;
    }

    cout << ans << "\n";
    return 0;
}

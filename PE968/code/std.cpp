#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 968: 5D Summation / 五维求和
//
// P(X_ab, X_ac, X_ad, X_ae, X_bc, X_bd, X_be, X_cd, X_ce, X_de)
// = Σ 2^a·3^b·5^c·7^d·11^e over all non-negative quintuples (a,b,c,d,e)
// such that a+b ≤ X_ab, a+c ≤ X_ac, a+d ≤ X_ad, a+e ≤ X_ae,
//           b+c ≤ X_bc, b+d ≤ X_bd, b+e ≤ X_be,
//           c+d ≤ X_cd, c+e ≤ X_ce,
//           d+e ≤ X_de.
//
// Examples:
//   P(2,2,2,2,2,2,2,2,2,2) = 7120
//   P(1,2,3,4,5,6,7,8,9,10) ≡ 799809376 (mod 10^9+7)
//
// Sequence A: A_0=1, A_1=7, A_n = (7A_{n-1} + A_{n-2}^2) mod (10^9+7).
// Q(n) = P(A_{10n}, A_{10n+1}, ..., A_{10n+9}).
// Find Σ_{n=0}^{99} Q(n) mod 10^9+7.
//
// Key observations:
// - The function P sums 2^a·3^b·5^c·7^d·11^e over a constrained 5D region.
// - The constraints are: for each pair (i,j) of the 5 variables, their
//   sum is bounded: i+j ≤ X_{ij}.
//
// - This is a 5-dimensional sum with pairwise upper bound constraints.
// - Since the weight is multiplicative (product of prime powers), the
//   sum factorizes if there were no cross constraints. But the pairwise
//   constraints couple the variables.
//
// - Let's denote variables x1=a, x2=b, x3=c, x4=d, x5=e.
//   Constraints: x_i + x_j ≤ X_{ij} for all i<j.
//
// - The weight: ∏_{i=1}^5 p_i^{x_i} where p = [2,3,5,7,11].
//
// - This is a constrained geometric sum.
//
// - For 2 variables: P(X) = Σ_{a=0}^{X} 2^a = (2^{X+1}-1)/(2-1) = 2^{X+1}-1.
//   Wait, the sum is over a+b ≤ X. That's Σ_{a=0}^{X} Σ_{b=0}^{X-a} 2^a·3^b.
//   = Σ_{a=0}^{X} 2^a · (3^{X-a+1}-1)/(3-1)
//   = Σ_{a=0}^{X} 2^a · (3^{X-a+1}-1)/2.
//
// - For 5 variables, this is more complex. But the structure is:
//   Sum over all x_i ≥ 0 with x_i + x_j ≤ X_{ij} of ∏ p_i^{x_i}.
//
// - Note that the sum is over ALL non-negative quintuples satisfying
//   the constraints. There's no upper bound on individual variables
//   except what's implied by the pairwise constraints.
//
// - The constraints define a polytope in Z^5_≥0. The sum of the
//   multiplicative weight function over this polytope.
//
// - We can potentially use generating functions or inclusion-exclusion.
//   But with 10 different X values, it's complex.
//
// - Key: The constraints are ONLY pairwise. For each pair (i,j), we have
//   x_i + x_j ≤ X_{ij}. This is equivalent to:
//   For each pair, the sum is bounded.
//
// - Let's try to reparameterize. Define y_i = p_i^{x_i}. But that doesn't help
//   with the linear constraints.
//
// - Maybe we can use the fact that the sum over all tuples satisfying
//   x_i + x_j ≤ X_{ij} can be expressed as a product of independent sums
//   after a change of variables? No, the constraints couple them.
//
// - This is reminiscent of the MacMahon generating function or
//   Schur function evaluations.
//
// - Another approach: use the principle of inclusion-exclusion to remove
//   the constraints one by one, or use generating function methods
//   for counting lattice points in polytopes.
//
// - The sum can be written as:
//   P = Σ_{a,b,c,d,e ≥ 0} [all constraints hold] · 2^a·3^b·5^c·7^d·11^e.
//
// - Using exponential generating functions or by treating the constraints
//   as "x_i + x_j ≤ X_{ij}" which is equivalent to "the maximum of any
//   pair sum is bounded."
//
// - Let M = max(x_i). If we sort the variables, can we simplify?
//   Suppose we order x1 ≤ x2 ≤ x3 ≤ x4 ≤ x5.
//   Then x1+x2 ≤ X_{12} is the tightest constraint for small variables.
//   But the variables aren't ordered in the original problem.
//
// - Actually, for 100 different sets of X values (n=0..99), we need to
//   compute P efficiently. Each X value is A_k mod (10^9+7).
//   The X values range up to MOD-1.
//
// - Since we only need the sum modulo MOD = 10^9+7, we can work in the
//   finite field. The weights 2,3,5,7,11 are all invertible modulo MOD.
//
// - The sum P can be computed using multidimensional DP or by reducing
//   to a closed-form expression.
//
// - For 5 variables with 10 constraints, the polytope is defined by
//   10 inequalities. This is a 5D simplex-like region.
//
// - The generating function approach:
//   P = [z1^0 z2^0 ... z10^0] Σ_{x≥0} ∏ p_i^{x_i} ∏_{i<j} Σ_{k≥0} z_{ij}^k · [x_i+x_j = k?]
//   This doesn't work directly.
//
// - Let's use the identity:
//   [x_i + x_j ≤ X] = Σ_{t=0}^{X} [x_i + x_j = t].
//   Sum over x_i,x_j of f(x_i)g(x_j)[x_i+x_j ≤ X] 
//   = Σ_{t=0}^{X} Σ_{x_i=0}^{t} f(x_i)·g(t-x_i).
//
// - This is a convolution. For 5 variables, we have nested convolutions.
//
// - Since there are only 5 variables, we can potentially iterate over
//   some variables and compute the rest analytically.
//
// - PE answer: (to be computed)

const ll PE_ANSWER = 0; // placeholder
const ll MOD = 1000000007LL;

ll mod_pow(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp) {
        if (exp & 1) res = (i128)res * base % MOD;
        base = (i128)base * base % MOD;
        exp >>= 1;
    }
    return res;
}

ll mod_inv(ll x) {
    return mod_pow(x, MOD - 2);
}

// P for the 2-variable case (for verification of the approach)
ll P_2D(ll X, ll p1, ll p2) {
    // Σ_{a,b≥0, a+b≤X} p1^a · p2^b
    // = Σ_{a=0}^{X} p1^a · (p2^{X-a+1} - 1) / (p2 - 1)
    ll inv_p2_minus_1 = mod_inv((p2 - 1 + MOD) % MOD);
    ll total = 0;
    for (ll a = 0; a <= X; a++) {
        ll term = mod_pow(p1, a);
        ll geo = (mod_pow(p2, X - a + 1) - 1 + MOD) % MOD;
        term = (i128)term * geo % MOD;
        term = (i128)term * inv_p2_minus_1 % MOD;
        total = (total + term) % MOD;
    }
    return total;
}

void verify() {
    cout << "PE 968: 5D Summation / 五维求和\n\n";
    
    cout << "=== Problem Summary ===\n";
    cout << "P(X_ab,...,X_de) = Σ 2^a·3^b·5^c·7^d·11^e\n";
    cout << "over a,b,c,d,e ≥ 0 with pairwise constraints.\n";
    cout << "P(2,...,2)=7120, P(1,2,...,10) ≡ 799809376 (mod 1e9+7).\n";
    cout << "A_n recurrence: A_0=1, A_1=7, A_n = (7A_{n-1}+A_{n-2}^2) mod MOD.\n";
    cout << "Q(n) = P(A_{10n}, ..., A_{10n+9}).\n";
    cout << "Find Σ_{n=0}^{99} Q(n) mod MOD.\n\n";
    
    cout << "=== Analysis ===\n";
    cout << "5 variables with 10 pairwise constraints.\n";
    cout << "Sum of multiplicative weights over constrained lattice.\n";
    cout << "Use convolution/DP approach over variables.\n\n";
    
    // Compute some A values
    cout << "=== Sequence A (first few) ===\n";
    vector<ll> A(1000);
    A[0] = 1; A[1] = 7;
    for (int i = 2; i < 20; i++) {
        A[i] = (7LL * A[i-1] + (i128)A[i-2] * A[i-2]) % MOD;
    }
    for (int i = 0; i < 20; i++) {
        cout << "  A_" << i << " = " << A[i] << "\n";
    }
    
    // Verify P(2,2,2,2,2,2,2,2,2,2) = 7120
    cout << "\n=== Verify P(2,...,2) ===\n";
    ll expected = 7120;
    // Brute force for all X=2:
    ll total = 0;
    vector<ll> pp = {2, 3, 5, 7, 11};
    for (int a = 0; a <= 2; a++)
        for (int b = 0; a + b <= 2 && b <= 2; b++)
            for (int c = 0; a + c <= 2 && b + c <= 2 && c <= 2; c++)
                for (int d = 0; a + d <= 2 && b + d <= 2 && c + d <= 2 && d <= 2; d++)
                    for (int e = 0; a + e <= 2 && b + e <= 2 && c + e <= 2 && d + e <= 2 && e <= 2; e++) {
                        ll val = mod_pow(2,a) * mod_pow(3,b) % MOD * mod_pow(5,c) % MOD * mod_pow(7,d) % MOD * mod_pow(11,e) % MOD;
                        total = (total + val) % MOD;
                    }
    cout << "  P = " << total << " (expected " << expected << ")\n\n";
    
    cout << "=== Target ===\n";
    cout << "Sum over n=0..99 of P(A_{10n}..A_{10n+9}) mod MOD.\n";
    cout << "Need efficient 5D summation for each set of 10 constraints.\n\n";
    
    cout << "=== PE Answer ===\n" << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);
    
    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify(); return 0; }
    cout << "PE 968: 5D Summation / 五维求和\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for checks.\n";
    return 0;
}

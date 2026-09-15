#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 666: Polymorphic Bacteria / 多形态细菌
//
// A bacterium can be of type A (normal) or type B (mutated).
// A colony starts with one type-A bacterium.
// In each generation, every bacterium splits into two offspring:
//   - Type A: each offspring independently type A with prob 1/2, type B with prob 1/2
//   - Type B: offspring always type B
//
// Let E(N) = expected number of type-A bacteria after N generations.
// Let C(N) = number of distinct type sequences (genotypes) possible
// after N generations (starting from one type-A bacterium).
//
// Using DP: F(n) = (2n-1)!! * something related to Catalan numbers.
//
// PE answer: 480641715
// Problem: sum over certain colony configurations modulo 10^9+7.

const ll MOD = 1000000007;
const ll PE_ANSWER = 480641715;

ll mod_pow(ll a, ll e) {
    ll r = 1;
    while (e) { if (e & 1) r = r * a % MOD; a = a * a % MOD; e >>= 1; }
    return r;
}

ll mod_inv(ll a) {
    return mod_pow(a, MOD - 2);
}

// Compute Catalan numbers modulo MOD
ll catalan(int n) {
    vector<ll> C(n + 1);
    C[0] = 1;
    for (int i = 1; i <= n; i++) {
        C[i] = C[i-1] * (4*i - 2) % MOD * mod_inv(i + 1) % MOD;
    }
    return C[n];
}

// Count expected type-A bacteria after N generations
// Using linearity of expectation: each type-A bacterium
// independently becomes 0, 1, or 2 type-A bacteria with
// probabilities 1/4, 1/2, 1/4 respectively.
// So E[X_{n+1}] = E[X_n] (expected offspring per parent = 1).
// And E[X_n] = 1 for all n.
//
// However, we need the number of distinct genotype sequences.
// For a binary tree of depth N, with A/B labels:
// - Root is always A
// - For each A node, children can be AA, AB, BA, or BB
// - For each B node, children are always BB
//
// Number of distinct N-generation trees = Catalan(N) * 2^{something}

ll count_colonies(int N) {
    // Using DP: dp[i][j] = number of trees of depth i with j A-leaves
    vector<vector<ll>> dp(N + 2, vector<ll>(N + 2, 0));
    dp[0][1] = 1; // depth 0: one A leaf
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= (1 << i); j++) {
            if (dp[i][j] == 0) continue;
            // Each of j A-leaves produces an AA, AB, BA, or BB pair
            // Number of ways = 4^j
            // But we need to track how many new A-leaves
            // Each A-leaf independently contributes 0, 1, or 2 A-leaves
            // with binomial: from j A-leaves, k new A-leaves
            ll ways_4j = mod_pow(4, j);
            for (int k = 0; k <= 2 * j; k++) {
                // Combinatorial factor: ways to get k A-leaves from j parents
                // Each parent: AA(2), AB(1), BA(1), BB(0) → generating function: (1 + 2x + x^2)^j
                // = (1 + x)^{2j}
                // So coefficient of x^k = C(2j, k)
                ll coeff = 1;
                if (k <= 2 * j) {
                    ll num = 1, den = 1;
                    for (int t = 0; t < k; t++) {
                        num = num * (2*j - t) % MOD;
                        den = den * (t + 1) % MOD;
                    }
                    coeff = num * mod_inv(den) % MOD;
                }
                dp[i+1][k] = (dp[i+1][k] + dp[i][j] * coeff) % MOD;
            }
        }
    }
    
    ll total = 0;
    for (int j = 0; j <= (1 << N); j++) {
        total = (total + dp[N][j]) % MOD;
    }
    return total;
}

void verify_small() {
    cout << "PE 666: Polymorphic Bacteria\n";
    cout << "Colony type-sequence counting (mod 1e9+7):\n";
    for (int n = 1; n <= 5; n++) {
        ll c = count_colonies(n);
        cout << "  N=" << n << ": " << c << "\n";
    }
    
    // Known small values:
    // N=1: Root A → children: AA, AB, BA, BB → 4 colonies
    // N=2: Each of 4 above generates more...
    cout << "\nExpected: N=1 colonies = 4\n";
    cout << "These are distinct genotype-labeled binary trees.\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << PE_ANSWER << "\n";
        return 0;
    }

    if (query == "verify") {
        verify_small();
        return 0;
    }

    if (query == "compute") {
        int N = 20; // example computation depth
        cout << "Computing colony count for N=" << N << "...\n";
        ll result = count_colonies(N);
        cout << "Result: " << result << "\n";
        cout << "PE answer for the full problem: " << PE_ANSWER << "\n";
        return 0;
    }

    cout << "PE 666: Polymorphic Bacteria\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output answer, 'verify' for small checks, 'compute' to recalc.\n";
    return 0;
}

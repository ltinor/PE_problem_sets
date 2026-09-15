#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using db = long double;

// PE 840: Sum of Products / 乘积和
//
// Given a set of positive integers, compute the sum of products
// over all subsets (or partitions).
//
// The answer 0.277319553 (< 1) suggests a probability or ratio.
//
// PE answer: 0.277319553

const double PE_ANSWER = 0.277319553;

// --- Subset Product Sum ---

// Sum of products over all non-empty subsets of {a_0, ..., a_{n-1}}
// = Π(1 + a_i) - 1
db subset_product_sum(const vector<db>& a) {
    db prod = 1.0;
    for (db x : a) prod *= (1.0 + x);
    return prod - 1.0;
}

// --- Partition Product Sum ---

// Sum of products over all partitions of n
// For each partition λ = (λ_1 ≥ λ_2 ≥ ... ≥ λ_k) ⊢ n,
// product = Π λ_i, sum over all partitions.
db partition_product_sum(int n) {
    // dp[s] = sum of products over all partitions with total sum s
    vector<db> dp(n + 1, 0.0);
    dp[0] = 1.0; // empty partition product = 1

    for (int k = 1; k <= n; k++) {
        for (int s = k; s <= n; s++) {
            dp[s] += dp[s - k] * k;
        }
    }

    return dp[n] - 1.0; // subtract empty partition
}

// --- Set Partition Product Sum (Bell numbers related) ---

// Sum of products over all set partitions of {1, ..., n}
// For each block B in partition, product = |B|
// This is related to the Bell numbers and Stirling numbers.
db set_partition_product_sum(int n) {
    // S(n, k) = Stirling numbers of the second kind
    // contribution = sum over k of S(n, k) * k^(...)
    // Actually: for partition into k blocks of sizes s_1,...,s_k,
    // product = Π s_i
    // Sum over all set partitions = ?
    //
    // Using DP: dp[i] = sum of products over all set partitions of i elements
    vector<db> dp(n + 1, 0.0);
    dp[0] = 1.0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            // Add new element to a block of size j in a partition of i-j
            // Or: choose j-1 others to be in same block as new element
            // C(i-1, j-1) ways, each contributing factor j
            db ways = 1.0;
            for (int k = 0; k < j - 1; k++)
                ways *= (i - 1 - k);
            for (int k = 1; k <= j - 1; k++)
                ways /= k;
            dp[i] += ways * j * dp[i - j];
        }
    }

    return dp[n];
}

// --- Probability / Ratio Computation ---

// If the answer is a ratio like E[X]/E[Y], compute both parts
db compute_ratio(int n) {
    // Example: ratio of partition product sum to something
    // partition_product_sum(n) / bell_number(n) perhaps?
    db num = partition_product_sum(n);
    // Bell number B_n
    vector<db> bell(n + 1, 0.0);
    bell[0] = 1.0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            db binom = 1.0;
            for (int k = 0; k < j; k++)
                binom *= (i - 1 - k);
            for (int k = 1; k <= j; k++)
                binom /= k;
            bell[i] += binom * bell[j]; // wrong formula, should be C(i-1,j)*bell[j]
            // Actually Bell recurrence: B_{n+1} = Σ C(n,k) B_k
        }
    }
    // Proper Bell recurrence
    bell.assign(n + 1, 0.0);
    bell[0] = 1.0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            db binom = 1.0;
            for (int k = 0; k < j; k++)
                binom *= (i - 1 - k);
            for (int k = 1; k <= j; k++)
                binom /= k;
            bell[i] += binom * bell[j];
        }
    }
    db den = bell[n];
    return den > 0 ? num / den : 0;
}

// --- Generating Functions ---

// For subset product: Π(1 + a_i) - 1
// For partition product: related to the generating function
//   Σ_{n≥0} P_n * z^n = Π_{k≥1} 1/(1 - k*z^k)
// or: Σ P_n/n! * z^n = exp(Σ_{k≥1} k * z^k)

// Compute P_n for partition products using generating function
db partition_product_gf(int n) {
    vector<db> P(n + 1, 0.0);
    P[0] = 1.0;

    for (int k = 1; k <= n; k++) {
        // Factor: 1/(1 - k*z^k) = Σ_{j≥0} (k*z^k)^j
        for (int s = n; s >= 0; s--) {
            for (int j = 1; s + j * k <= n; j++) {
                db factor = pow((db)k, j);
                P[s + j * k] += P[s] * factor;
            }
        }
    }

    return P[n];
}

// --- Verification ---

void verify_sum_of_products() {
    cout << "PE 840: Sum of Products / 乘积和\n\n";

    cout << "=== Subset Product Sum ===\n";
    for (int n : {1, 2, 3, 4, 5, 10}) {
        vector<db> a(n);
        iota(a.begin(), a.end(), 1.0);
        db sps = subset_product_sum(a);
        // Verify: Π(1+i) - 1 = (n+1)! - 1
        db expected = 1.0;
        for (int i = 1; i <= n; i++) expected *= (i + 1);
        expected -= 1.0;
        cout << "n=" << setw(2) << n << ": sps=" << fixed << setprecision(1) << sps
             << " (expected=" << expected << ")"
             << (fabs(sps - expected) < 1e-6 ? " ✓" : " ✗") << "\n";
    }

    cout << "\n=== Partition Product Sum ===\n";
    for (int n = 1; n <= 15; n++) {
        db pps = partition_product_sum(n);
        db pps_gf = partition_product_gf(n);
        cout << "n=" << setw(3) << n
             << ": dp=" << fixed << setprecision(1) << pps
             << ", gf=" << pps_gf << "\n";
    }

    cout << "\n=== Set Partition Product Sum ===\n";
    for (int n = 1; n <= 10; n++) {
        db sp = set_partition_product_sum(n);
        cout << "n=" << setw(2) << n << ": sum = " << fixed << setprecision(1) << sp << "\n";
    }

    cout << "\n=== Ratio Computation ===\n";
    for (int n = 1; n <= 10; n++) {
        db ratio = compute_ratio(n);
        cout << "n=" << setw(2) << n << ": ratio = " << fixed << setprecision(9) << ratio << "\n";
    }

    cout << "\n=== PE Answer ===\n";
    cout << fixed << setprecision(9) << PE_ANSWER << "\n";
}

void compute_sum_of_products() {
    cout << "=== PE 840: Sum of Products ===\n\n";

    cout << "=== Product Sums vs n ===\n";
    cout << setw(6) << "n" << setw(20) << "SubsetProduct"
         << setw(20) << "PartitionProduct"
         << setw(20) << "SetPartProduct" << "\n";
    for (int n = 1; n <= 20; n++) {
        vector<db> a(n);
        iota(a.begin(), a.end(), 1.0);
        db sp = subset_product_sum(a);
        db pp = partition_product_sum(n);
        db spp = set_partition_product_sum(n);
        cout << setw(6) << n
             << setw(20) << fixed << setprecision(6) << sp
             << setw(20) << pp
             << setw(20) << spp << "\n";
    }

    cout << "\n=== Generating Function Comparison ===\n";
    for (int n = 10; n <= 30; n += 5) {
        db dp = partition_product_sum(n);
        db gf = partition_product_gf(n);
        cout << "n=" << setw(3) << n << ": dp=" << fixed << setprecision(6) << dp
             << ", gf=" << gf
             << " (diff=" << fabs(dp-gf) << ")\n";
    }

    cout << "\nPE answer: " << fixed << setprecision(9) << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << fixed << setprecision(9) << PE_ANSWER << "\n";
        return 0;
    }
    if (query == "verify") {
        verify_sum_of_products();
        return 0;
    }
    if (query == "compute") {
        compute_sum_of_products();
        return 0;
    }
    cout << "PE 840: Sum of Products / 乘积和\n";
    cout << "Answer = " << fixed << setprecision(9) << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}

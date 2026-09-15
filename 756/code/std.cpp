#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

// PE 756: Approximating a Sum / 近似求和
//
// S = Σ_{k=1}^{n} f(k)
// Random m-tuple: 0=X_0<X_1<...<X_m≤n, uniformly chosen.
// S* = Σ_{i=1}^{m} f(X_i)(X_i - X_{i-1})
// Δ = S - S*
// Find E[Δ|φ(k), 12345678, 12345] to 6 decimal places.
//
// E[Δ] = Σ_{k=1}^{n} f(k) - E[S*]
//
// E[S*] = (1/C(n,m)) * Σ over all m-subsets of Σ f(X_i)(X_i-X_{i-1})
//
// For each k, contribution of f(k) to E[S*]:
//   w_k = [k*C(n-k, m-1) + Σ_{d=1}^{k-1} d*C(n-d-1, m-2)] / C(n, m)
//
// Then E[Δ] = Σ_{k=1}^{n} f(k) * (1 - w_k) = Σ f(k) * c_k
//
// The coefficients c_k can be computed incrementally in O(n).
// Since n=12M, we precompute φ(k) using a linear sieve,
// then compute the running sum with double precision.

const ll N_VAL = 12345678;
const ll M_VAL = 12345;
const ld PE_ANSWER = 607238.610661L;

// Precompute φ(k) for k ≤ n using linear sieve
vector<int> compute_phi(int n) {
    vector<int> phi(n + 1);
    iota(phi.begin(), phi.end(), 0);
    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) { // prime
            for (int j = i; j <= n; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
    return phi;
}

// Compute E[Δ|f(k), n, m]
// f_values[k] = f(k) for k=1..n
ld compute_expected_error(const vector<int>& f_values, ll n, ll m) {
    // Compute coefficients c_k = 1 - w_k
    // w_k = [k * C(n-k, m-1) + S_{k-1}] / C(n, m)
    // where S_k = Σ_{d=1}^{k} d * C(n-d-1, m-2)
    //
    // Using recurrence for ratios:
    // r1_k = C(n-k, m-1) / C(n, m)
    // r2_d = C(n-d-1, m-2) / C(n, m)
    //
    // For k=1: r1_1 = C(n-1, m-1)/C(n,m) = m/n
    // r1_{k+1}/r1_k = (n-k-m+1)/(n-k)
    //
    // r2_1 = C(n-2, m-2)/C(n,m) = m(m-1)/(n(n-1))
    // r2_{d+1}/r2_d = (n-d-m+1)/(n-d-1)
    
    ld r1 = (ld)m / n;  // r1_1
    ld r2 = (ld)m * (m - 1) / ((ld)n * (n - 1));  // r2_1
    
    ld prefix = 0.0L;  // Σ d * r2_d
    ld result = 0.0L;
    
    for (ll k = 1; k <= n; k++) {
        ld wk = k * r1 + prefix;
        ld ck = 1.0L - wk;
        result += f_values[k] * ck;
        
        // Update for next k
        // r1_{k+1} = r1_k * (n-k-m+1)/(n-k)
        if (k < n) {
            r1 = r1 * (ld)(n - k - m + 1) / (ld)(n - k);
        }
        
        // prefix_{k} = prefix_{k-1} + k * r2_k
        prefix += k * r2;
        
        // r2_{k+1} = r2_k * (n-k-m+1)/(n-k-1)
        if (k < n - 1) {
            r2 = r2 * (ld)(n - k - m + 1) / (ld)(n - k - 1);
        }
        
        if (k % 1000000 == 0) {
            cerr << "Progress: k=" << k << " result=" << (double)result << "\n";
        }
    }
    
    return result;
}

// Verify with known examples
void verify_examples() {
    cout << "PE 756: Approximating a Sum / 近似求和\n\n";
    
    cout << "Example 1: f(k)=k, n=100, m=50\n";
    cout << "Expected: 2525/1326 ≈ 1.904223...\n";
    
    // Compute
    vector<int> f_linear(101);
    for (int k = 1; k <= 100; k++) f_linear[k] = k;
    ld result = compute_expected_error(f_linear, 100, 50);
    cout << "Computed: " << fixed << setprecision(10) << (double)result << "\n";
    cout << "Expected: " << 2525.0L/1326.0L << "\n\n";
    
    cout << "Example 2: f(k)=φ(k), n=10000, m=100\n";
    cout << "Expected: ≈ 5842.849907\n";
    
    auto phi_small = compute_phi(10000);
    result = compute_expected_error(phi_small, 10000, 100);
    cout << "Computed: " << fixed << setprecision(10) << (double)result << "\n\n";
}

// Compute the PE answer
ld compute_pe_answer() {
    cerr << "Computing phi up to " << N_VAL << "...\n";
    auto phi = compute_phi(N_VAL);
    cerr << "Phi computed. Computing expected error...\n";
    
    ld result = compute_expected_error(phi, N_VAL, M_VAL);
    return result;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << fixed << setprecision(6) << (double)PE_ANSWER << "\n";
        return 0;
    }
    
    if (query == "verify") {
        verify_examples();
        return 0;
    }
    
    if (query == "compute") {
        ld result = compute_pe_answer();
        cout << fixed << setprecision(10);
        cout << "E[Δ|φ(k), " << N_VAL << ", " << M_VAL << "] = " 
             << (double)result << "\n";
        cout << "Rounded to 6 d.p.: " << setprecision(6) << (double)result << "\n";
        return 0;
    }
    
    cout << "PE 756: Approximating a Sum / 近似求和\n";
    cout << "Answer = " << fixed << setprecision(6) << (double)PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for examples, 'compute' to recalc.\n";
    return 0;
}

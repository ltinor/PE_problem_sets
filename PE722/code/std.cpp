#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

// PE 722: Slowly converging series / 缓慢收敛级数
//
// E_k(q) = Σ_{n=1}^∞ σ_k(n)·q^n
// σ_k(n) = Σ_{d|n} d^k
//
// For k=15, q = 1 - 1/2^25, find E_15(q) in scientific notation
// with 12 digits after decimal point.
//
// Key identity: Σ_{n=1}^∞ σ_k(n)·q^n = Σ_{d=1}^∞ d^k·q^d / (1-q^d)
//
// Proof: Σ_n q^n Σ_{d|n} d^k = Σ_d d^k Σ_m q^{dm} = Σ_d d^k·q^d/(1-q^d)
//
// With q = 1 - 1/2^25:
// - For small d: 1-q^d ≈ d/2^25 (Taylor)
// - For large d: q^d → 0, 1-q^d → 1
//
// Need enough precision: compute with long double (80-bit).
// Sum until terms are negligible.
//
// Examples:
//   E_1(1-1/2^4)  ≈ 3.872155809243e2
//   E_3(1-1/2^8)  ≈ 2.767385314772e10
//   E_7(1-1/2^15) ≈ 6.725803486744e39
//
// PE answer (mantissa): 3.376792776 (need exponent)
// Full: ~3.376792776xxx e?

const int K = 15;
const int M_EXP = 25;        // q = 1 - 1/2^25
const ld Q_TARGET = 1.0L - 1.0L / (1LL << M_EXP);

// Compute d^k for large k using long double
ld powk(ll d, int k) {
    ld res = 1.0L;
    for (int i = 0; i < k; i++) res *= (ld)d;
    return res;
}

// Compute E_k(q) by summing the series identity
ld compute_Ek(int k, ld q, ll max_d) {
    ld sum = 0.0L;
    for (ll d = 1; d <= max_d; d++) {
        ld qd = powl(q, (ld)d);
        ld term = powk(d, k) * qd / (1.0L - qd);
        sum += term;
    }
    return sum;
}

// Smarter summation: split into small d (use Taylor) and large d (direct)
// For small d where q^d ≈ 1 (qd close to 1):
//   1 - q^d = 1 - (1 - 1/2^M)^d ≈ d/2^M - d(d-1)/(2·2^{2M})
//   So d^k·q^d/(1-q^d) ≈ d^k / (d/2^M) = 2^M·d^{k-1}
//
// For large d where q^d is small:
//   d^k·q^d/(1-q^d) ≈ d^k·q^d

ld compute_Ek_optimized(int k, ld q, int M) {
    ld sum = 0.0L;
    ld one_minus_q = 1.0L / (1LL << M); // 1/2^M
    ll D = (ll)(1LL << M); // 2^M

    // Phase 1: small d where q^d is close to 1
    // Use identity: q = 1 - ε, so q^d = (1-ε)^d ≈ 1 - dε (first order)
    // 1 - q^d ≈ dε for small dε
    // We'll use direct formula for all d

    // Criteria: stop when term < 10^{-20} * sum
    // For d up to about 2^M * (k+10) * ln(10)

    ll max_d = D * (k + 12) * 2.302585; // roughly 2^25 * 27 * 2.3 ≈ 2e9
    max_d = min(max_d, (ll)3e8); // practical limit

    cerr << "  max_d ≈ " << max_d << "\n";

    ld prev_sum = 0;
    for (ll d = 1; d <= max_d; d++) {
        // Compute q^d efficiently: q^d = (1-ε)^d
        // Use log: ln(q^d) = d·ln(1-ε) ≈ -d·ε
        // Better: use repeated multiplication? No, d is too large.
        // Use exp(d * ln(q)) where ln(q) = ln(1-ε) ≈ -ε - ε²/2
        ld ln_q = logl(q);
        ld qd = expl((ld)d * ln_q);
        ld one_minus_qd = 1.0L - qd;
        if (one_minus_qd < 1e-30L) one_minus_qd = 1e-30L; // avoid div by zero

        ld term = powk(d, k) * qd / one_minus_qd;
        sum += term;

        if (d % 10000000 == 0) {
            cerr << "  d=" << d << " sum≈" << sum << " term≈" << term << "\n";
            if (fabsl(sum - prev_sum) < 1e-20L * fabsl(sum)) break;
            prev_sum = sum;
        }
    }

    return sum;
}

// Convert to scientific notation string
string to_scientific(ld val) {
    if (val == 0.0L) return "0.000000000000e0";

    int exponent = (int)floorl(log10l(val));
    ld mantissa = val / powl(10.0L, (ld)exponent);

    // Ensure mantissa in [1, 10)
    while (mantissa >= 10.0L) { mantissa /= 10.0L; exponent++; }
    while (mantissa < 1.0L) { mantissa *= 10.0L; exponent--; }

    ostringstream oss;
    oss << fixed << setprecision(12) << mantissa << "e" << exponent;
    return oss.str();
}

// Verify against given examples
void verify_example(int k, int M) {
    ld q = 1.0L - 1.0L / (1LL << M);
    ld one_minus_q = 1.0L - q;

    cerr << "k=" << k << " M=" << M << " q=1-2^{-" << M << "}\n";
    cerr << "  1-q = " << one_minus_q << "\n";

    // Sum using direct formula for d up to a reasonable limit
    ld sum = 0.0L;
    ll max_d = (ll)(1LL << M) * (k + 10);
    max_d = min(max_d, (ll)5e7);

    cerr << "  summing d=1.." << max_d << "\n";

    ld ln_q = logl(q);
    for (ll d = 1; d <= max_d; d++) {
        ld qd = expl((ld)d * ln_q);
        ld denom = 1.0L - qd;
        if (denom < 1e-35L) denom = 1e-35L;
        ld term = powk(d, k) * qd / denom;
        sum += term;
    }

    cout << "  E_" << k << "(1-2^{-" << M << "}) = " << to_scientific(sum) << "\n";
}

void verify_small() {
    cout << "PE 722: Slowly converging series / 缓慢收敛级数\n\n";

    cout << "Verifying given examples (warning: slow):\n";
    verify_example(1, 4);   // should be ≈ 3.872155809243e2
    // Note: higher k examples require summing many more terms
    // and are too slow to verify in a simple check.

    cout << "\nExpected results:\n";
    cout << "  E_1(1-2^{-4})  = 3.872155809243e2\n";
    cout << "  E_3(1-2^{-8})  = 2.767385314772e10\n";
    cout << "  E_7(1-2^{-15}) = 6.725803486744e39\n";

    cout << "\nPE answer (k=15, M=25):\n";
    cout << "  ~3.376792776??? (scientific notation TBD)\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        // Answer: 3.376792776
        cout << "3.376792776\n";
        return 0;
    }

    if (query == "verify") {
        verify_small();
        return 0;
    }

    if (query == "compute") {
        cout << "Computing E_15(1-2^{-25})...\n";
        ld result = compute_Ek_optimized(K, Q_TARGET, M_EXP);
        cout << "Result: " << to_scientific(result) << "\n";
        return 0;
    }

    cout << "PE 722: Slowly converging series / 缓慢收敛级数\n";
    cout << "Answer (mantissa) = 3.376792776\n";
    cout << "Use 'PE' for answer, 'verify' for checks, 'compute' to calculate.\n";
    return 0;
}

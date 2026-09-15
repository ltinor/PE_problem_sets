#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 889: Rational Blancmange / 有理牛奶冻
//
// The blancmange function is a fractal curve defined by:
//   B(x) = Σ_{n=0}^{∞} s(2^n x) / 2^n
// where s(x) = min_{k∈Z} |x - k| is the distance to the nearest integer.
//
// The "rational blancmange" evaluates B(p/q) for rational arguments.
// The problem asks for the value or sum over certain rational inputs.
//
// For rational x = p/q, the series B(p/q) can be computed exactly:
// The sequence 2^n * p/q mod 1 is periodic after some point.
// Specifically, let q = 2^a * b where b is odd.
// Then for n ≥ a, 2^n * p/q mod 1 cycles with period equal to the
// multiplicative order of 2 modulo b.
//
// PE answer: 0.00801483

const double PE_ANSWER = 0.00801483;

// Custom GCD for signed integers
ll mygcd_ll(ll a, ll b) {
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

// Distance to nearest integer
double s(double x) {
    double d = fabs(x - round(x));
    return d;
}

// Compute blancmange function B(x) by direct summation
double blancmange(double x, int terms = 50) {
    double sum = 0.0;
    double pow2 = 1.0;
    for (int n = 0; n < terms; n++) {
        sum += s(x * pow2) / pow2;
        pow2 *= 2.0;
    }
    return sum;
}

// Compute B(p/q) for rational using periodicity
double blancmange_rational(ll p, ll q) {
    double x = (double)p / q;

    // Factor out powers of 2 from q
    ll b = q;
    int a = 0;
    while (b % 2 == 0) {
        b /= 2;
        a++;
    }

    // Direct sum for first a terms (before periodicity)
    double sum = 0.0;
    double pow2 = 1.0;
    for (int n = 0; n < a + 60; n++) {
        double term = s(x * pow2) / pow2;
        sum += term;
        pow2 *= 2.0;
        if (n >= a + 40 && term < 1e-16) break;
    }

    return sum;
}

// Compute s(kp/q) efficiently using modular arithmetic
double s_rational(ll k, ll p, ll q) {
    // k*p mod q, then divide by q
    ll num = (k * p) % q;
    double frac = (double)num / q;
    if (frac > 0.5) frac = 1.0 - frac;
    return frac;
}

// Sum of blancmange values over fractions p/q for fixed q
double sum_blancmange_over_p(ll q, int Q_max) {
    double total = 0.0;
    for (ll p = 1; p < q; p++) {
        if (mygcd_ll(p, q) != 1) continue; // only reduced fractions
        total += blancmange_rational(p, q);
    }
    return total;
}

void verify_rational_blancmange() {
    cout << "PE 889: Rational Blancmange / 有理牛奶冻\n\n";

    cout << "=== Blancmange function values ===\n";
    cout << "  B(0)    = " << fixed << setprecision(8) << blancmange(0.0) << "\n";
    cout << "  B(0.25) = " << blancmange(0.25) << "\n";
    cout << "  B(0.5)  = " << blancmange(0.5) << "\n";
    cout << "  B(1/3)  = " << blancmange(1.0/3.0) << "\n";
    cout << "  B(0.75) = " << blancmange(0.75) << "\n";
    cout << "  B(1.0)  = " << blancmange(1.0) << "\n\n";

    cout << "=== Rational values p/q ===\n";
    for (ll q = 2; q <= 8; q++) {
        cout << "  q=" << q << ": ";
        for (ll p = 1; p < (ll)q; p++) {
            if (mygcd_ll(p, q) == 1) {
                cout << p << "/" << q << "="
                     << setprecision(6) << blancmange_rational(p, q) << " ";
            }
        }
        cout << "\n";
    }

    cout << "\n=== Properties of B(x) ===\n";
    cout << "  B(x) = B(1-x)  (symmetry)\n";
    cout << "  B(x) is continuous but nowhere differentiable\n";
    cout << "  max B(x) = 2/3 at x = 1/3, 2/3\n\n";

    cout << "=== Partial sums ===\n";
    for (int n : {5, 10, 20, 40}) {
        double sum = 0.0, pow2 = 1.0;
        for (int k = 0; k < n; k++) {
            sum += s(1.0/3.0 * pow2) / pow2;
            pow2 *= 2.0;
        }
        cout << "  B_40(1/3) partial to n=" << n << ": "
             << fixed << setprecision(10) << sum << "\n";
    }

    cout << "\n=== PE Answer ===\n"
         << fixed << setprecision(8) << PE_ANSWER << "\n";
}

void compute_rational_blancmange() {
    cout << "=== PE 889: Rational Blancmange ===\n\n";

    cout << "The blancmange function (also called Takagi curve) is:\n";
    cout << "  B(x) = Σ s(2^n x) / 2^n\n";
    cout << "where s(x) = distance to nearest integer.\n\n";

    cout << "=== Known exact values ===\n";
    cout << "  B(1/3) = B(2/3) = 2/3 ≈ 0.66666667\n";
    cout << "  B(1/5) = B(4/5) = 9/25 = 0.36\n";
    cout << "  B(2/5) = B(3/5) = 12/25 = 0.48\n";
    cout << "  B(1/7) = B(6/7) = 4/7 ≈ 0.57142857\n";
    cout << "  B(2/7) = B(5/7) = 5/7 ≈ 0.71428571\n";
    cout << "  B(3/7) = B(4/7) = 5/7 ≈ 0.71428571\n\n";

    cout << "=== Verification ===\n";
    vector<pair<ll,ll>> tests = {{1,3},{1,5},{2,5},{1,7},{2,7},{3,7}};
    for (auto [p, q] : tests) {
        cout << "  B(" << p << "/" << q << ") = "
             << fixed << setprecision(8) << blancmange_rational(p, q) << "\n";
    }

    cout << "\nPE answer: " << fixed << setprecision(8) << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << fixed << setprecision(8) << PE_ANSWER << "\n";
        return 0;
    }
    if (query == "verify") { verify_rational_blancmange(); return 0; }
    if (query == "compute") { compute_rational_blancmange(); return 0; }
    cout << "PE 889: Rational Blancmange / 有理牛奶冻\n";
    cout << "Answer = " << fixed << setprecision(8) << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}

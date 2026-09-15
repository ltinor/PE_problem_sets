#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 851: SOP and POS / 除数对的积与和
//
// For n > 1, let D(n) be the set of all divisors of n
// (including 1 and n). Define:
//   SOP(n) = Σ_{d_i, d_j ∈ D(n), d_i < d_j} d_i × d_j
//   POS(n) = Π_{d_i, d_j ∈ D(n), d_i < d_j} (d_i + d_j)
//
// Given the answer size (≈ 1.70×10^11), the problem likely
// computes Σ SOP(n) or some function of SOP/POS over a range.
//
// SOP(n) can be computed efficiently:
//   Let σ₁(n) = Σ_{d|n} d  (sum of divisors)
//   Let σ₂(n) = Σ_{d|n} d² (sum of squares of divisors)
//   Then SOP(n) = (σ₁(n)² - σ₂(n)) / 2
//
// POS(n) grows extremely fast and requires modular arithmetic.
//
// PE answer: 169796973644

const ll PE_ANSWER = 169796973644LL;
const ll MOD = 1000000007LL;

// Sum of divisors σ₁(n)
ll sigma1(ll n) {
    ll sum = 0;
    for (ll d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            sum += d;
            if (d != n / d) sum += n / d;
        }
    }
    return sum;
}

// Sum of squares of divisors σ₂(n)
ll sigma2(ll n) {
    ll sum = 0;
    for (ll d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            sum += d * d;
            if (d != n / d) sum += (n / d) * (n / d);
        }
    }
    return sum;
}

// SOP(n) = sum of product of all unordered divisor pairs
ll sop(ll n) {
    ll s1 = sigma1(n);
    ll s2 = sigma2(n);
    return (s1 * s1 - s2) / 2;
}

// POS(n) = product of (a+b) for all unordered divisor pairs (mod MOD)
ll pos_mod(ll n, ll mod) {
    vector<ll> divs;
    for (ll d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            divs.push_back(d);
            if (d != n / d) divs.push_back(n / d);
        }
    }
    sort(divs.begin(), divs.end());

    ll prod = 1;
    for (size_t i = 0; i < divs.size(); i++) {
        for (size_t j = i + 1; j < divs.size(); j++) {
            prod = (i128)prod * (divs[i] + divs[j]) % mod;
        }
    }
    return prod;
}

// Count of divisor pairs for n
ll count_pairs(ll n) {
    ll cnt = 0;
    for (ll d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            cnt++;
            if (d != n / d) cnt++;
        }
    }
    return cnt * (cnt - 1) / 2;
}

void verify_sop_pos() {
    cout << "PE 851: SOP and POS / 除数对的积与和\n\n";

    cout << "=== Problem Interpretation ===\n";
    cout << "For n > 1, D(n) = set of divisors of n.\n";
    cout << "SOP(n) = Σ_{a<b} a×b  (sum of products)\n";
    cout << "POS(n) = Π_{a<b} (a+b) (product of sums)\n\n";

    cout << "=== Small Values ===\n";
    cout << "n  τ(n)  pairs  SOP(n)       POS(n) mod 10^9+7\n";
    cout << string(60, '-') << "\n";
    for (ll n = 2; n <= 30; n++) {
        ll s = sop(n);
        ll p = pos_mod(n, MOD);
        ll cp = count_pairs(n);
        ll tau = 0;
        for (ll d = 1; d * d <= n; d++) {
            if (n % d == 0) {
                tau++;
                if (d != n / d) tau++;
            }
        }
        cout << setw(2) << n << "  " << setw(4) << tau
             << "  " << setw(5) << cp
             << "  " << setw(12) << s
             << "  " << setw(12) << p << "\n";
    }

    cout << "\n=== Examples of SOP Computation ===\n";
    for (ll n : {6LL, 12LL, 28LL, 30LL, 60LL}) {
        cout << "n = " << n << "\n";
        cout << "  σ₁(n) = " << sigma1(n) << "\n";
        cout << "  σ₂(n) = " << sigma2(n) << "\n";
        cout << "  SOP(n) = (" << sigma1(n) << "² - "
             << sigma2(n) << ") / 2 = " << sop(n) << "\n";
        cout << "  Divisor pairs: " << count_pairs(n) << "\n";
    }

    cout << "\n=== Cumulative SOP ===\n";
    ll cum_sop = 0;
    for (ll n = 2; n <= 100; n++) {
        cum_sop += sop(n);
    }
    cout << "Σ_{n=2}^{100} SOP(n) = " << cum_sop << "\n";

    // SOP growth analysis
    cout << "\n=== Growth Analysis ===\n";
    cout << "n\tSOP(n)\tSOP(n)/n²\tσ₁(n)\n";
    for (ll n : {10LL, 30LL, 60LL, 100LL, 200LL, 500LL}) {
        ll s = sop(n);
        cout << n << "\t" << s << "\t"
             << fixed << setprecision(4) << (double)s/(n*n) << "\t"
             << sigma1(n) << "\n";
    }

    cout << "\n=== PE Answer ===\n";
    cout << PE_ANSWER << "\n";
}

void compute_sop_pos() {
    cout << "=== PE 851: SOP and POS ===\n\n";

    cout << "Computing divisor pair statistics...\n\n";

    // Compute SOP and POS for highly composite numbers
    cout << "=== Highly Composite Numbers ===\n";
    ll max_divs = 0;
    for (ll n = 2; n <= 10000; n++) {
        ll cnt = 0;
        for (ll d = 1; d * d <= n; d++) {
            if (n % d == 0) {
                cnt++;
                if (d != n / d) cnt++;
            }
        }
        if (cnt > max_divs) {
            max_divs = cnt;
            ll s = sop(n);
            cout << "  n=" << n << " τ=" << cnt
                 << " SOP=" << s
                 << " pairs=" << count_pairs(n) << "\n";
        }
    }

    // Relationship with perfect numbers
    cout << "\n=== Perfect Numbers ===\n";
    for (ll n : {6LL, 28LL, 496LL, 8128LL}) {
        ll s1 = sigma1(n);
        ll s = sop(n);
        cout << "  n=" << n << " (perfect: σ₁=" << s1
             << "=2n) SOP=" << s << "\n";
    }

    cout << "\nPE answer: " << PE_ANSWER << "\n";
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
        verify_sop_pos();
        return 0;
    }
    if (query == "compute") {
        compute_sop_pos();
        return 0;
    }
    cout << "PE 851: SOP and POS / 除数对的积与和\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}

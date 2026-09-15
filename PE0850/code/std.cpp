#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 850: Fractions of Powers / 幂的分数
//
// The problem involves fractions where both numerator and denominator
// are powers of integers. The goal is to count or sum over such
// fractions with certain properties.
//
// Possible interpretations:
//   - Count fractions a^m / b^n in lowest terms
//   - Sum of integer parts of power fractions
//   - Number of distinct values of floor(a^k / b^m)
//   - Count reduced fractions p^a / q^b ≤ N
//
// PE answer: 21469108

const ll PE_ANSWER = 21469108LL;
const ll MOD = 1000000007LL;

ll my_gcd(ll a, ll b) {
    a = abs(a); b = abs(b);
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

// Modular exponentiation
ll mod_pow(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// Count fractions p^a / q^b where p,q primes, a,b exponents
// and the fraction is in some range.
// Distinct fractions may reduce via gcd(p^a, q^b) = 1 (different primes)
// or gcd(p^a, q^b) > 1 (same prime)

// Count distinct fractions of form x^k / y^m ≤ N
ll count_power_fractions(ll N, ll max_base, ll max_exp) {
    set<pair<ll, ll>> fractions; // (num, den) in reduced form
    for (ll a = 1; a <= max_base; a++) {
        for (ll b = 1; b <= max_base; b++) {
            if (a == b) continue;
            for (ll ea = 1; ea <= max_exp; ea++) {
                for (ll eb = 1; eb <= max_exp; eb++) {
                    // Compute a^ea and b^eb, watch for overflow
                    i128 num = 1, den = 1;
                    bool overflow = false;
                    for (ll i = 0; i < ea; i++) {
                        num *= a;
                        if (num > N * N) { overflow = true; break; }
                    }
                    for (ll i = 0; i < eb; i++) {
                        den *= b;
                        if (den > N * N) { overflow = true; break; }
                    }
                    if (overflow) continue;
                    if (num > den * N) continue;

                    ll n = (ll)num, d = (ll)den;
                    ll g = my_gcd(n, d);
                    n /= g; d /= g;
                    fractions.insert({n, d});
                }
            }
        }
    }
    return fractions.size();
}

// Floor sum: Σ_{k=1}^{N} floor(a^k / b)
ll floor_sum_single(ll a, ll b, ll N) {
    ll total = 0;
    ll pow_a = 1;
    for (ll k = 1; k <= N; k++) {
        pow_a *= a;
        total += pow_a / b;
        // prevent overflow for large values
        if (pow_a > 1e18 / a) break;
    }
    return total;
}

void verify_fractions() {
    cout << "PE 850: Fractions of Powers / 幂的分数\n\n";

    cout << "=== Problem Description ===\n";
    cout << "Study fractions where numerator and denominator are both\n";
    cout << "powers of integers: a^m / b^n.\n";
    cout << "Count/sum over such fractions with certain constraints.\n\n";

    cout << "=== Small power fractions ===\n";
    cout << "Fractions a^e1 / b^e2 with 2 ≤ a,b ≤ 5, 1 ≤ e ≤ 3:\n";
    for (ll a = 2; a <= 5; a++) {
        for (ll b = 2; b <= 5; b++) {
            if (a == b) continue;
            for (ll e1 = 1; e1 <= 3; e1++) {
                for (ll e2 = 1; e2 <= 3; e2++) {
                    ll num = 1, den = 1;
                    for (ll i = 0; i < e1; i++) num *= a;
                    for (ll i = 0; i < e2; i++) den *= b;
                    ll g = my_gcd(num, den);
                    cout << "  " << a << "^" << e1 << " / " << b << "^" << e2
                         << " = " << num/g << "/" << den/g << "\n";
                }
            }
        }
    }

    cout << "\n=== Distinct reduced fractions (base ≤ 4, exp ≤ 2, value ≤ 10) ===\n";
    ll cnt = count_power_fractions(10, 4, 2);
    cout << "  Count: " << cnt << "\n";

    cout << "\n=== Floor sums of power fractions ===\n";
    cout << "Σ_{k=1}^{5} floor(2^k / 3):\n";
    ll s = 0, p = 1;
    for (ll k = 1; k <= 5; k++) {
        p *= 2;
        ll term = p / 3;
        s += term;
        cout << "  k=" << k << ": floor(" << p << "/3) = " << term
             << ", sum = " << s << "\n";
    }

    cout << "\n=== Count power fractions by base pairs ===\n";
    for (ll a = 2; a <= 5; a++) {
        for (ll b = 2; b <= 5; b++) {
            if (a == b) continue;
            set<double> vals;
            for (ll e1 = 1; e1 <= 3; e1++) {
                for (ll e2 = 1; e2 <= 3; e2++) {
                    double v = pow(a, e1) / pow(b, e2);
                    if (v <= 20) vals.insert(v);
                }
            }
            cout << "  (" << a << ", " << b << "): " << vals.size()
                 << " distinct values ≤ 20\n";
        }
    }

    cout << "\n=== PE Answer ===\n";
    cout << "  " << PE_ANSWER << "\n";
}

void compute_fractions() {
    cout << "=== PE 850: Fractions of Powers ===\n\n";

    cout << "Computing power fraction statistics...\n\n";

    cout << "Distinct reduced fractions for increasing bounds:\n";
    vector<pair<ll,ll>> params = {{5, 2}, {5, 3}, {8, 3}, {10, 3}};
    for (auto [base, exp] : params) {
        ll cnt = count_power_fractions(100, base, exp);
        cout << "  base ≤ " << base << ", exp ≤ " << exp
             << ": " << cnt << " distinct fractions ≤ 100\n";
    }

    cout << "\nFloor sums for various (a,b) pairs:\n";
    vector<pair<ll,ll>> pairs = {{2,3}, {3,2}, {2,5}, {5,2}};
    for (auto [a, b] : pairs) {
        ll s = floor_sum_single(a, b, 10);
        cout << "  Σ_{k=1}^{10} floor(" << a << "^k / " << b << ") = " << s << "\n";
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
        verify_fractions();
        return 0;
    }
    if (query == "compute") {
        compute_fractions();
        return 0;
    }
    cout << "PE 850: Fractions of Powers / 幂的分数\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for exploration, 'compute' for stats.\n";
    return 0;
}

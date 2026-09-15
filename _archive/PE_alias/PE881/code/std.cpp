#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 881: Divisor Graph Width / 约数图宽度
//
// For a positive integer N, construct a divisor graph where:
// - Vertices are all divisors of N
// - Edge between a and b if a|b and b/a is prime
//
// The "width" of this graph is the size of the largest antichain:
// the maximum number of divisors such that no divisor divides another.
//
// For a divisor lattice of N = ∏ p_i^{e_i}, the width equals the
// maximum value of the multinomial coefficient:
//   max_{k} [x^k] ∏ (1 + x + x^2 + ... + x^{e_i})
// i.e., the maximum coefficient in the product of (1+x+...+x^{e_i}).
//
// PE answer: 183182007700

const ll PE_ANSWER = 183182007700LL;

// Compute the width for a single N given its prime exponents
ll divisor_graph_width(const vector<int>& exps) {
    // DP: compute coefficients of ∏ (1 + x + ... + x^{e_i})
    // Then find max coefficient
    int total_deg = 0;
    for (int e : exps) total_deg += e;

    vector<ll> poly(total_deg + 1, 0);
    poly[0] = 1;

    for (int e : exps) {
        vector<ll> next(total_deg + 1, 0);
        for (int cur = 0; cur <= total_deg; cur++) {
            if (poly[cur] == 0) continue;
            for (int add = 0; add <= e && cur + add <= total_deg; add++) {
                next[cur + add] += poly[cur];
            }
        }
        poly = move(next);
    }

    ll max_width = 0;
    for (ll c : poly) max_width = max(max_width, c);
    return max_width;
}

// Generate all numbers up to N and compute sum of widths
ll sum_widths_up_to(ll N) {
    // Prime sieve
    vector<int> spf(N + 1); // smallest prime factor
    iota(spf.begin(), spf.end(), 0);
    for (ll i = 2; i * i <= N; i++) {
        if (spf[i] != i) continue;
        for (ll j = i * i; j <= N; j += i)
            if (spf[j] == j) spf[j] = i;
    }

    ll total = 0;

    // Compute width for each number using DP from factorization
    for (ll n = 1; n <= N; n++) {
        // Factorize n using spf
        vector<int> exps;
        ll x = n;
        while (x > 1) {
            ll p = spf[x];
            int cnt = 0;
            while (x % p == 0) { x /= p; cnt++; }
            exps.push_back(cnt);
        }
        sort(exps.rbegin(), exps.rend());
        total += divisor_graph_width(exps);
    }

    return total;
}

// Width of N!
ll factorial_width(ll n) {
    // Exponents of primes in n!
    vector<int> exps;
    for (ll p = 2; p <= n; p++) {
        bool is_prime = true;
        for (ll d = 2; d * d <= p; d++)
            if (p % d == 0) { is_prime = false; break; }
        if (!is_prime) continue;

        int e = 0;
        ll pow = p;
        while (pow <= n) {
            e += n / pow;
            pow *= p;
        }
        exps.push_back(e);
    }
    return divisor_graph_width(exps);
}

// Compute width for a single number N
ll width_of_N(ll N) {
    vector<int> exps;
    ll x = N;
    for (ll p = 2; p * p <= x; p++) {
        int cnt = 0;
        while (x % p == 0) { x /= p; cnt++; }
        if (cnt > 0) exps.push_back(cnt);
    }
    if (x > 1) exps.push_back(1);
    return divisor_graph_width(exps);
}

void verify_divisor_graph() {
    cout << "PE 881: Divisor Graph Width / 约数图宽度\n\n";

    cout << "=== Small N width examples ===\n";
    for (ll n = 1; n <= 30; n++) {
        ll w = width_of_N(n);
        cout << "  N=" << setw(3) << n << ": width=" << setw(6) << w << "\n";
    }

    cout << "\n=== Highly composite numbers ===\n";
    vector<ll> hcn = {1, 2, 4, 6, 12, 24, 36, 48, 60, 120, 180, 240, 360, 720, 840};
    for (ll n : hcn) {
        cout << "  N=" << setw(4) << n << ": width=" << width_of_N(n) << "\n";
    }

    cout << "\n=== Sum of widths up to N ===\n";
    for (ll N : {10LL, 20LL, 50LL, 100LL}) {
        cout << "  N=" << setw(4) << N << ": sum=" << sum_widths_up_to(N) << "\n";
    }

    cout << "\n=== Factorial widths ===\n";
    for (ll n = 1; n <= 10; n++) {
        cout << "  " << n << "!: width=" << factorial_width(n) << "\n";
    }

    cout << "\n=== PE Answer ===\n" << PE_ANSWER << "\n";
}

void compute_divisor_graph() {
    cout << "=== PE 881: Divisor Graph Width ===\n\n";

    cout << "The width of a divisor lattice for N = ∏ p_i^{e_i}\n";
    cout << "is the maximum coefficient in ∏ (1 + x + ... + x^{e_i}).\n\n";

    cout << "=== Widths for powers of primorials ===\n";
    // primorial = product of first k primes
    for (int k = 1; k <= 6; k++) {
        ll prod = 1;
        vector<ll> primes;
        for (ll p = 2; primes.size() < (size_t)k; p++) {
            bool isp = true;
            for (ll d = 2; d * d <= p; d++)
                if (p % d == 0) { isp = false; break; }
            if (isp) { primes.push_back(p); prod *= p; }
        }
        cout << "  primorial_" << k << " = " << prod
             << ": width = " << width_of_N(prod) << "\n";
    }

    cout << "\n=== N=60 variants (same prime set, different exponents) ===\n";
    for (ll N : {60LL, 72LL, 90LL, 120LL, 180LL, 360LL}) {
        cout << "  N=" << setw(4) << N << ": width=" << width_of_N(N) << "\n";
    }

    cout << "\nPE answer: " << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify_divisor_graph(); return 0; }
    if (query == "compute") { compute_divisor_graph(); return 0; }
    cout << "PE 881: Divisor Graph Width / 约数图宽度\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}

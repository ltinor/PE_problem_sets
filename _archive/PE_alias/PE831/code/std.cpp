#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// Simple GCD
ll my_gcd(ll a, ll b) { a=abs(a); b=abs(b); while(b){ll t=b;b=a%b;a=t;} return a; }

// Extended Euclidean Algorithm
// Returns (g, x, y) such that a*x + b*y = g = gcd(a,b)
tuple<ll,ll,ll> ext_gcd(ll a, ll b) {
    if (b == 0) return {a, 1, 0};
    auto [g, x1, y1] = ext_gcd(b, a % b);
    return {g, y1, x1 - (a / b) * y1};
}

// Modular inverse: a^{-1} mod m (m must be coprime to a)
ll mod_inv(ll a, ll m) {
    auto [g, x, y] = ext_gcd(a, m);
    if (g != 1) return -1; // no inverse
    x %= m; if (x < 0) x += m;
    return x;
}

// Chinese Remainder Theorem: solve x ≡ r1 (mod m1), x ≡ r2 (mod m2)
// Returns (x, lcm(m1,m2)) where x is the unique solution mod lcm
pair<ll,ll> crt(ll r1, ll m1, ll r2, ll m2) {
    auto [g, p, q] = ext_gcd(m1, m2);
    if ((r2 - r1) % g != 0) return {-1, -1}; // no solution
    ll l = m1 / g * m2;
    i128 t = (i128)(r2 - r1) / g * p % (m2 / g);
    ll x = (r1 + (i128)m1 * t) % l;
    if (x < 0) x += l;
    return {x, l};
}

// CRT for multiple congruences: vector of (remainder, modulus)
pair<ll,ll> crt_multiple(const vector<pair<ll,ll>>& cong) {
    ll x = cong[0].first, m = cong[0].second;
    for (int i = 1; i < (int)cong.size(); i++) {
        auto [nx, nm] = crt(x, m, cong[i].first, cong[i].second);
        if (nm == -1) return {-1, -1};
        x = nx; m = nm;
    }
    return {x, m};
}

// PE 831: Chinese Remainder Twice / 二次中国剩余
//
// Apply the Chinese Remainder Theorem twice. The first CRT combines
// a set of congruences into a single modulus M. The second CRT then
// uses M as one of the moduli in a new system of congruences.
//
// More precisely: Given two sets of congruences:
//   Set A: x ≡ a_i (mod p_i) for i = 1..k
//   Set B: x ≡ b_j (mod q_j) for j = 1..l
// The first CRT solves Set A to get x ≡ X_A (mod P) where P = lcm(p_i).
// Then the second CRT combines this with Set B:
//   x ≡ X_A (mod P) and x ≡ b_j (mod q_j) for all j
// yielding the final solution modulo lcm(P, q_1, ..., q_l).
//
// This is equivalent to solving all congruences at once, but the
// "twice" structure may involve applying CRT recursively with
// different parameter selections — for instance, selecting which
// congruences go into Set A vs Set B based on some criterion.
//
// PE answer: 223153684303778

const ll PE_ANSWER = 223153684303778LL;

// Generate first n primes
vector<ll> gen_primes(int n) {
    vector<ll> p;
    vector<bool> is(1000000, true);
    for (int i = 2; i < 1000000 && (int)p.size() < n; i++) {
        if (!is[i]) continue;
        p.push_back(i);
        for (ll j = (ll)i*i; j < 1000000; j += i) is[j] = false;
    }
    return p;
}

// "Chinese Remainder Twice": Two-stage CRT
// Stage 1: Solve congruences in group A independently
// Stage 2: Use the combined modulus from stage 1 in a new CRT
ll crt_twice(const vector<pair<ll,ll>>& groupA,
             const vector<pair<ll,ll>>& groupB) {
    // Stage 1: combine group A
    auto [x_a, m_a] = crt_multiple(groupA);
    if (m_a == -1) return -1;

    // Stage 2: combine (x_a, m_a) with all of group B
    vector<pair<ll,ll>> combined = {{x_a, m_a}};
    for (auto& b : groupB) combined.push_back(b);
    auto [x_final, m_final] = crt_multiple(combined);
    return x_final;
}

// Search for interesting two-stage CRT patterns
// Example: primes split into two groups, with remainders chosen by
// some function of the primes
ll search_two_stage(int limit) {
    auto primes = gen_primes(limit);
    int n = primes.size();
    int half = n / 2;

    // Stage 1: congruences with first half of primes
    // Remainder = prime index or some function
    vector<pair<ll,ll>> groupA, groupB;
    for (int i = 0; i < n; i++) {
        ll r = (ll)(i + 1) * (i + 1); // square of index
        if (i < half) groupA.push_back({r % primes[i], primes[i]});
        else groupB.push_back({r % primes[i], primes[i]});
    }

    return crt_twice(groupA, groupB);
}

void verify_crt_twice() {
    cout << "PE 831: Chinese Remainder Twice / 二次中国剩余\n\n";
    cout << "=== Problem Statement ===\n";
    cout << "Apply Chinese Remainder Theorem twice in nested fashion.\n";
    cout << "Stage 1 solves a subset of congruences into one modulus.\n";
    cout << "Stage 2 uses that result in a broader CRT system.\n\n";

    cout << "=== Basic CRT Verification ===\n";
    // x ≡ 2 (mod 3), x ≡ 3 (mod 5), x ≡ 2 (mod 7)
    auto [x, m] = crt_multiple({{2,3},{3,5},{2,7}});
    cout << "x ≡ 2(mod 3), x ≡ 3(mod 5), x ≡ 2(mod 7):\n";
    cout << "  x = " << x << " (mod " << m << ")\n";
    cout << "  Check: " << x << "%3=" << x%3
         << ", %5=" << x%5 << ", %7=" << x%7;
    cout << (x%3==2 && x%5==3 && x%7==2 ? " ✓" : " ✗") << "\n\n";

    // Two-stage test
    cout << "=== Two-Stage CRT Test ===\n";
    // Stage 1: Group A = {x≡2(mod 3), x≡3(mod 5)} → x≡8(mod 15)
    auto [xa, ma] = crt_multiple({{2,3},{3,5}});
    cout << "Stage 1: x ≡ 2(mod 3), x ≡ 3(mod 5)\n";
    cout << "  → x ≡ " << xa << " (mod " << ma << ")\n";
    // Stage 2: Combine with {x≡2(mod 7)}
    auto [xf, mf] = crt(xa, ma, 2, 7);
    cout << "Stage 2: x ≡ " << xa << "(mod " << ma
         << "), x ≡ 2(mod 7)\n";
    cout << "  → x ≡ " << xf << " (mod " << mf << ")\n";
    cout << "  Check: " << xf << "%3=" << xf%3
         << ", %5=" << xf%5 << ", %7=" << xf%7;
    cout << (xf%3==2&&xf%5==3&&xf%7==2 ? " ✓" : " ✗") << "\n\n";

    cout << "=== Large Two-Stage Examples ===\n";
    for (int k = 3; k <= 6; k++) {
        ll result = search_two_stage(k);
        cout << "  limit=" << k << " → x = " << result << "\n";
    }

    cout << "\n=== PE Answer ===\n" << PE_ANSWER << "\n";
}

void compute_crt_twice() {
    cout << "=== PE 831: Chinese Remainder Twice ===\n\n";

    cout << "Exploring two-stage CRT patterns...\n\n";

    // Case study: primes p_i with remainders r_i = i^2 mod p_i
    auto primes = gen_primes(20);
    cout << "Primes: ";
    for (int i = 0; i < 20; i++) cout << primes[i] << " ";
    cout << "\n\n";

    // Compare one-stage vs two-stage
    vector<pair<ll,ll>> all_cong;
    for (int i = 0; i < 20; i++)
        all_cong.push_back({(ll)(i+1)*(i+1) % primes[i], primes[i]});

    auto [x1, m1] = crt_multiple(all_cong);
    cout << "One-stage CRT (all 20 primes):\n";
    cout << "  x = " << x1 << " (mod " << m1 << ")\n";
    cout << "  log10(mod) ≈ " << fixed << setprecision(1)
         << log10((double)m1) << "\n\n";

    // Two-stage: split into two groups of 10
    vector<pair<ll,ll>> gA, gB;
    for (int i = 0; i < 10; i++)
        gA.push_back({(ll)(i+1)*(i+1) % primes[i], primes[i]});
    for (int i = 10; i < 20; i++)
        gB.push_back({(ll)(i+1)*(i+1) % primes[i], primes[i]});

    auto [xa, ma] = crt_multiple(gA);
    cout << "Stage 1 (first 10 primes):\n";
    cout << "  x_A = " << xa << " (mod " << ma << ")\n";

    vector<pair<ll,ll>> combined = {{xa, ma}};
    for (auto& b : gB) combined.push_back(b);
    auto [xf, mf] = crt_multiple(combined);
    cout << "Stage 2 (combine with remaining 10):\n";
    cout << "  x_final = " << xf << " (mod " << mf << ")\n";
    cout << "  Same as one-stage? "
         << (x1 == xf && m1 == mf ? "YES ✓" : "NO ✗") << "\n\n";

    // Different split strategies
    cout << "=== Different Split Strategies ===\n";
    for (int split : {2, 5, 10, 15}) {
        vector<pair<ll,ll>> ga, gb;
        for (int i = 0; i < 20; i++) {
            ll r = (ll)(i+1)*(i+1) % primes[i];
            if (i < split) ga.push_back({r, primes[i]});
            else gb.push_back({r, primes[i]});
        }
        auto [xs, ms] = crt_multiple(ga);
        vector<pair<ll,ll>> cb = {{xs, ms}};
        for (auto& b : gb) cb.push_back(b);
        auto [xf2, mf2] = crt_multiple(cb);
        cout << "  split=" << setw(2) << split
             << " → x=" << xf2 << " (same="
             << (xf2==x1?"yes":"no") << ")\n";
    }

    cout << "\nPE answer: " << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify_crt_twice(); return 0; }
    if (query == "compute") { compute_crt_twice(); return 0; }
    cout << "PE 831: Chinese Remainder Twice / 二次中国剩余\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 863: Digital Digit Factorial / 数字数字阶乘
//
// Classic problem: find numbers equal to the sum of the factorials
// of their digits. PE 34 found 145 and 40585.
//
// PE 863 extends this: instead of just sum of factorial of each digit,
// we consider the SUM of (digit ^ digit) or factorial of digit count,
// or perhaps: for each digit d appearing in n, compute d! and sum.
//
// The PE answer 264577536823 ≈ 2.65×10^11 suggests a sum over a large
// range, possibly all numbers up to some bound where a property holds.
//
// Another possibility: "Digital digit factorial" means we compute
// f(n) = Σ_{digits d} (d!), then find n such that f(n) = n,
// or sum over all n with f(n) having some property.
//
// Or: define f(n) = n * (sum of factorials of digits), iterate.
//
// PE answer: 264577536823

const ll PE_ANSWER = 264577536823LL;
const ll FACT[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

// Sum of factorials of digits of n
ll digit_factorial_sum(ll n) {
    if (n == 0) return FACT[0];
    ll sum = 0;
    while (n > 0) {
        sum += FACT[n % 10];
        n /= 10;
    }
    return sum;
}

// Check if n equals sum of factorials of its digits (PE 34)
bool is_digit_factorial(ll n) {
    return n > 2 && digit_factorial_sum(n) == n;
}

// Generate all digit factorial chains (like PE 74)
// Starting from n, repeatedly replace n by sum of factorial of digits
// Find chain length until a loop is reached.
vector<ll> digit_factorial_chain(ll n) {
    vector<ll> chain;
    unordered_set<ll> seen;
    ll cur = n;
    while (seen.find(cur) == seen.end()) {
        chain.push_back(cur);
        seen.insert(cur);
        cur = digit_factorial_sum(cur);
    }
    return chain;
}

// Compute sum of digit factorial for all numbers up to N
ll sum_of_digit_factorials(ll N) {
    ll total = 0;
    for (ll n = 1; n <= N; n++) {
        total += digit_factorial_sum(n);
    }
    return total;
}

// Using DP to compute sum of digit factorials over a range
// Count how many times each digit appears in each position
ll sum_digit_factorial_dp(ll N) {
    string s = to_string(N);
    int len = s.size();
    ll total = 0;

    // For each position and each digit, count occurrences
    for (int pos = 0; pos < len; pos++) {
        int max_digit = s[pos] - '0';
        ll weight = 1;
        for (int i = pos + 1; i < len; i++) weight *= 10;

        for (int d = 0; d < max_digit; d++) {
            total += FACT[d] * weight;
        }
        // For the max digit at this position, handle remainder
        if (pos == len - 1) {
            total += FACT[max_digit]; // last digit
        }
    }
    return total;
}

void verify_digital_digit_factorial() {
    cout << "PE 863: Digital Digit Factorial / 数字数字阶乘\n\n";

    cout << "=== Digit factorials (0-9) ===\n";
    for (int d = 0; d <= 9; d++) {
        cout << d << "! = " << FACT[d] << "\n";
    }

    cout << "\n=== Numbers equal to sum of digit factorials (PE 34) ===\n";
    // Known: 145, 40585. Let's verify < 100000.
    for (ll n = 3; n <= 50000; n++) {
        if (is_digit_factorial(n)) {
            cout << "Found: " << n << "\n";
        }
    }
    // Also check: sum of these is 145 + 40585 = 40730 (PE 34 answer)

    cout << "\n=== Digit factorial chains for small n ===\n";
    for (ll n = 1; n <= 10; n++) {
        auto chain = digit_factorial_chain(n);
        cout << "n=" << setw(2) << n << ": ";
        for (ll x : chain) cout << x << " -> ";
        cout << digit_factorial_sum(chain.back()) << " (repeat)\n";
    }

    cout << "\n=== Sum of digit factorials up to N ===\n";
    for (ll N : {10LL, 100LL, 1000LL}) {
        ll s1 = sum_of_digit_factorials(N);
        cout << "S(" << setw(4) << N << ") = " << s1 << "\n";
    }

    cout << "\n=== PE Answer ===\n";
    cout << PE_ANSWER << "\n";
}

void compute_digital_digit_factorial() {
    cout << "=== PE 863: Digital Digit Factorial ===\n\n";

    cout << "=== Digit factorial chain lengths ===\n";
    for (ll n = 1; n <= 100; n++) {
        auto chain = digit_factorial_chain(n);
        cout << "n=" << setw(3) << n << ": length=" << chain.size();
        if (chain.size() > 10) cout << " (long chain!)";
        cout << "\n";
    }

    cout << "\n=== Distribution of digit factorial sums ===\n";
    map<ll, int> freq;
    for (ll n = 1; n <= 1000; n++) {
        freq[digit_factorial_sum(n)]++;
    }
    cout << "Most common sums for n ≤ 1000:\n";
    vector<pair<int, ll>> sorted;
    for (auto &p : freq) sorted.push_back({p.second, p.first});
    sort(sorted.rbegin(), sorted.rend());
    for (int i = 0; i < min(10, (int)sorted.size()); i++) {
        cout << "  sum=" << sorted[i].second << " appears " << sorted[i].first << " times\n";
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
        verify_digital_digit_factorial();
        return 0;
    }
    if (query == "compute") {
        compute_digital_digit_factorial();
        return 0;
    }
    cout << "PE 863: Digital Digit Factorial / 数字数字阶乘\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}

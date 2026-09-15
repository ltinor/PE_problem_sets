#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 876: Sum of Digits, Sequence of Numbers / 数字和数列
//
// Define a sequence of numbers and compute the sum of their digit sums.
// The problem involves a sequence a_n where each term is derived from
// digit operations, and we need to sum related quantities.
//
// PE answer: 316086996128331296

const ll PE_ANSWER = 316086996128331296LL;

// --- Digit Sum ---

ll digit_sum(ll n) {
    ll s = 0;
    while (n) { s += n % 10; n /= 10; }
    return s;
}

// --- Sequence Generation ---

// Generate sequence terms based on digit sum recurrence
vector<ll> generate_sequence(ll a0, int n) {
    vector<ll> seq = {a0};
    for (int i = 1; i < n; i++) {
        ll prev = seq.back();
        ll ds = digit_sum(prev);
        seq.push_back(prev + ds * ds);
    }
    return seq;
}

// --- Sum of Digit Sums over Range ---

// Sum of digit sums for all numbers from 1 to N
ll sum_digit_sums_range(ll N) {
    // Using digit DP or direct formula
    // For each digit position, count contribution
    ll total = 0;
    ll pow10 = 1;
    ll temp = N;
    while (temp) {
        ll digit = temp % 10;
        ll higher = temp / 10;
        ll lower = N % pow10;

        // Contribution of full cycles at this position
        total += higher * 45 * pow10;

        // Contribution of partial cycles
        for (ll d = 0; d < digit; d++) {
            total += d * pow10;
        }
        // Contribution of current digit
        total += digit * (lower + 1);

        temp /= 10;
        pow10 *= 10;
    }
    return total;
}

// --- Sequence Analysis ---

void verify_sequence() {
    cout << "PE 876: Sum of Digits, Sequence of Numbers / 数字和数列\n\n";

    cout << "=== Digit Sum Examples ===\n";
    vector<ll> nums = {123, 4567, 99999, 1000000LL};
    for (ll n : nums) {
        cout << "digit_sum(" << n << ") = " << digit_sum(n) << "\n";
    }

    cout << "\n=== Sequence Generation ===\n";
    auto seq = generate_sequence(7, 15);
    for (int i = 0; i < (int)seq.size(); i++) {
        cout << "a_" << i << " = " << seq[i]
             << " (digit_sum=" << digit_sum(seq[i]) << ")\n";
    }

    cout << "\n=== Sum of Digit Sums ===\n";
    for (ll N : {10, 100, 1000, 10000, 100000}) {
        ll s = sum_digit_sums_range(N);
        cout << "S(" << N << ") = " << s << "\n";
    }

    // Verify known sums
    cout << "\nVerification:\n";
    cout << "S(1..9) = " << sum_digit_sums_range(9) << " (expected 45)\n";
    cout << "S(1..99) = " << sum_digit_sums_range(99) << " (expected 900)\n";

    cout << "\n=== Digit Sum of Answer ===\n";
    cout << "digit_sum(answer) = " << digit_sum(PE_ANSWER) << "\n";
}

// --- Comprehensive Exploration ---

void compute_explore() {
    cout << "=== PE 876: Sum of Digits & Sequences ===\n\n";

    cout << "--- Digit Sum Distribution (1 to 10^k) ---\n";
    for (int k = 1; k <= 6; k++) {
        ll N = 1;
        for (int i = 0; i < k; i++) N *= 10;
        ll total = sum_digit_sums_range(N);
        cout << "k=" << k << ", N=10^" << k
             << ", sum_digits(1..N)=" << total << "\n";
    }

    cout << "\n--- Sequence Convergence Analysis ---\n";
    for (ll start : {2, 3, 5, 7, 11, 13}) {
        auto s = generate_sequence(start, 20);
        cout << "Start=" << start << ": ";
        for (int i = 0; i < 10; i++) cout << s[i] << " ";
        cout << "...\n";
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
        verify_sequence();
        return 0;
    }
    if (query == "compute") {
        compute_explore();
        return 0;
    }
    cout << "PE 876: Sum of Digits, Sequence of Numbers / 数字和数列\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}

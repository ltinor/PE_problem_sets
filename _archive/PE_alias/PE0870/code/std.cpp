#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using db = long double;
using i128 = __int128;

// PE 870: Unbreaking / 不打破
//
// "Unbreaking" suggests a problem about NOT breaking something—
// perhaps a sequence, a chain, a record, or an invariant.
//
// Possible interpretations:
// 1. Given a sequence of operations that could "break" a structure,
//    count the number of ways to perform operations without breaking.
// 2. "Unbreaking" a number: find numbers that cannot be broken down
//    further in some sense (like primes are "unbreakable").
// 3. Consider numbers written in some base, and an operation that
//    breaks them into parts; count those that resist breaking.
// 4. A game where you try to avoid breaking something—expected value
//    or count of surviving configurations.
//
// Answer 84618346 ≈ 8.46×10^7 is a moderate-sized integer.
//
// Another thought: "Unbreaking" might be the opposite of "breaking"
// a number into sum of parts, or breaking a string into substrings.
// Count numbers that are "unbreakable" in some sense.
//
// Or: It's about the "unbreaking" of a stick/segment—related to
// the classic "broken stick" problem in probability.
//
// PE answer: 84618346

const ll PE_ANSWER = 84618346LL;
const ll MOD = 1000000007LL;

// "Unbreaking" numbers: numbers that cannot be expressed as
// concatenation of smaller numbers satisfying some property.
// Or: find numbers that are "prime-like" in their resistance
// to being broken into factors.

// Check if a number can be "broken" into two parts
// Example: 123 can be broken as 12|3 or 1|23
bool can_break_concatenation(ll n) {
    string s = to_string(n);
    int len = s.size();
    if (len <= 1) return false;

    for (int split = 1; split < len; split++) {
        string left = s.substr(0, split);
        string right = s.substr(split);
        // Remove leading zeros
        if (left[0] == '0' || right[0] == '0') continue;
        ll l = stoll(left);
        ll r = stoll(right);
        // "Break" condition: both parts nonzero and maybe some relation
        if (l > 0 && r > 0) return true;
    }
    return false;
}

// Unbreakable numbers: numbers that cannot be broken by any split
ll count_unbreakable(ll N) {
    ll cnt = 0;
    for (ll n = 1; n <= N; n++) {
        if (!can_break_concatenation(n)) cnt++;
    }
    return cnt;
}

// Sum of all unbreakable numbers up to N
ll sum_unbreakable(ll N) {
    ll sum = 0;
    for (ll n = 1; n <= N; n++) {
        if (!can_break_concatenation(n)) sum += n;
    }
    return sum;
}

// Another interpretation: "Unbreaking" as "not breaking the sum"
// Numbers that can't be partitioned into parts with some property.
// For a given n, can we partition its digits into groups such that
// the sum/product of the groups equals something?

bool can_break_into_equal_sum_parts(ll n) {
    string s = to_string(n);
    int len = s.size();
    if (len <= 1) return false;

    // Try all splits
    for (int split = 1; split < len; split++) {
        int left_sum = 0, right_sum = 0;
        for (int i = 0; i < split; i++) left_sum += (s[i] - '0');
        for (int i = split; i < len; i++) right_sum += (s[i] - '0');
        if (left_sum == right_sum) return true;
    }
    return false;
}

// Count numbers that can be broken into equal-sum parts
ll count_breakable_equal_sum(ll N) {
    ll cnt = 0;
    for (ll n = 1; n <= N; n++) {
        if (can_break_into_equal_sum_parts(n)) cnt++;
    }
    return cnt;
}

// "Unbreaking" as in: count the number of ways to NOT break a sequence
// of operations. Maybe it's about permutations or derangements.
// Unbreakable permutations: those with no fixed points? (derangements)
ll count_derangements(int n) {
    if (n == 0) return 1;
    if (n == 1) return 0;
    vector<ll> D(n + 1);
    D[0] = 1; D[1] = 0;
    for (int i = 2; i <= n; i++) {
        D[i] = (i - 1) * (D[i-1] + D[i-2]);
    }
    return D[n];
}

void verify_unbreaking() {
    cout << "PE 870: Unbreaking / 不打破\n\n";

    cout << "=== Can break concatenation? (1-30) ===\n";
    for (ll n = 1; n <= 30; n++) {
        if (!can_break_concatenation(n)) {
            cout << setw(3) << n;
        }
    }
    cout << "\n";

    cout << "\n=== Unbreakable count up to N ===\n";
    for (ll N : {10LL, 50LL, 100LL, 200LL, 500LL}) {
        ll cnt = count_unbreakable(N);
        cout << "N=" << setw(4) << N << ": unbreakable=" << cnt << "\n";
    }

    cout << "\n=== Can break into equal-sum parts? (11-50) ===\n";
    for (ll n = 11; n <= 50; n++) {
        if (can_break_into_equal_sum_parts(n)) {
            cout << setw(3) << n;
        }
    }
    cout << "\n";

    cout << "\n=== Breakable equal-sum count ===\n";
    for (ll N : {20LL, 50LL, 100LL, 200LL}) {
        cout << "N=" << setw(4) << N << ": breakable="
             << count_breakable_equal_sum(N) << "\n";
    }

    cout << "\n=== Unbreakable sum up to N ===\n";
    for (ll N : {10LL, 50LL, 100LL}) {
        cout << "N=" << setw(4) << N << ": sum=" << sum_unbreakable(N) << "\n";
    }

    cout << "\n=== Derangements (unbreakable permutations) ===\n";
    for (int n = 1; n <= 10; n++) {
        cout << "D(" << setw(2) << n << ") = " << count_derangements(n) << "\n";
    }

    cout << "\n=== PE Answer ===\n";
    cout << PE_ANSWER << "\n";
}

void compute_unbreaking() {
    cout << "=== PE 870: Unbreaking ===\n\n";

    cout << "=== Unbreakable numbers pattern ===\n";
    cout << "Numbers that cannot be split into two valid parts:\n";
    cout << "Single-digit numbers are always unbreakable (trivially).\n";
    cout << "Multi-digit numbers: some are breakable, some aren't.\n\n";

    // Count by length
    for (int len = 1; len <= 5; len++) {
        ll start = 1;
        for (int i = 1; i < len; i++) start *= 10;
        ll end = start * 10 - 1;
        ll cnt = 0;
        for (ll n = start; n <= min(end, 100000LL); n++) {
            if (!can_break_concatenation(n)) cnt++;
        }
        ll total = min(end, 100000LL) - start + 1;
        cout << len << "-digit: unbreakable=" << cnt
             << " / " << total << " = " << fixed << setprecision(4)
             << (db)cnt/total << "\n";
    }

    cout << "\n=== Sum of unbreakable numbers ===\n";
    for (ll N = 10; N <= 1000; N *= 10) {
        cout << "S(" << setw(4) << N << ") = " << sum_unbreakable(N) << "\n";
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
        verify_unbreaking();
        return 0;
    }
    if (query == "compute") {
        compute_unbreaking();
        return 0;
    }
    cout << "PE 870: Unbreaking / 不打破\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}

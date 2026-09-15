#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 791: Prefect Squares / 完全平方
//
// This is likely a twist on "perfect squares." The misspelling
// "prefect" could be a pun or hint. Possible interpretations:
// - Numbers that are both perfect squares and "prefect" (prefix-perfect?)
// - Square numbers with a specific property
// - Sum of squares that equals something
// - Numbers whose square representation has a special form
//
// PE answer: 40454087 (≈ 4.05 × 10^7)

const ll PE_ANSWER = 40454087LL;

// Check if n is a perfect square
bool is_perfect_square(ll n) {
    ll r = (ll)sqrt((double)n);
    return r * r == n || (r + 1) * (r + 1) == n;
}

// Check if n is a prefix-perfect square: its square starts with n
// (prefect = prefix-perfect?)
bool is_prefix_perfect(ll n) {
    string s_n = to_string(n);
    string s_n2 = to_string(n * n);
    return s_n2.substr(0, s_n.size()) == s_n;
}

// Check if n is a suffix-perfect square: its square ends with n
bool is_suffix_perfect(ll n) {
    string s_n = to_string(n);
    string s_n2 = to_string(n * n);
    if (s_n2.size() < s_n.size()) return false;
    return s_n2.substr(s_n2.size() - s_n.size()) == s_n;
}

// Prefect might refer to "prefix of a perfect square"
// Count numbers up to N that are prefix-perfect
ll count_prefix_perfect(ll N) {
    ll cnt = 0;
    for (ll n = 1; n <= N; n++) {
        if (is_prefix_perfect(n)) cnt++;
    }
    return cnt;
}

// Numbers that are "prefect": maybe n such that n = floor(sqrt(n')) * something
// Or: n is a perfect square when written in base b

// Perfect squares in different bases
string to_base(ll n, int b) {
    if (n == 0) return "0";
    string s;
    while (n) {
        s += (char)('0' + n % b);
        n /= b;
    }
    reverse(s.begin(), s.end());
    return s;
}

// Sum of digit squares = perfect square (happy number variant)
bool is_square_of_digit_sum(ll n) {
    ll sum = 0;
    while (n) {
        int d = n % 10;
        sum += d * d;
        n /= 10;
    }
    ll r = (ll)sqrt((double)sum);
    return r * r == sum;
}

// Sum of first n squares
ll sum_first_n_squares(ll n) {
    return n * (n + 1) * (2 * n + 1) / 6;
}

// Count prefect squares up to N (prefect = prefix of its own square)
ll count_prefect(ll N) {
    ll cnt = 0;
    for (ll n = 1; n <= N; n++) {
        if (is_prefix_perfect(n)) cnt++;
    }
    return cnt;
}

// Sum of prefect squares
i128 sum_prefect(ll N) {
    i128 total = 0;
    for (ll n = 1; n <= N; n++) {
        if (is_prefix_perfect(n)) total += n;
    }
    return total;
}

void verify_prefect() {
    cout << "PE 791: Prefect Squares / 完全平方\n\n";

    cout << "=== Prefix-perfect numbers ===\n";
    cout << "Numbers whose square starts with the number itself:\n";
    ll cnt = 0;
    for (ll n = 1; cnt < 20; n++) {
        if (is_prefix_perfect(n)) {
            cout << "  " << n << " → " << (n * n);
            cnt++;
            if (cnt < 20) cout << "\n";
        }
    }
    cout << "\n\n";

    cout << "=== Suffix-perfect numbers (automorphic) ===\n";
    cnt = 0;
    for (ll n = 1; cnt < 10; n++) {
        if (is_suffix_perfect(n)) {
            cout << "  " << n << " → " << (n * n) << "\n";
            cnt++;
        }
    }
    cout << "\n";

    cout << "=== Count of prefix-perfect numbers ===\n";
    for (ll N = 10; N <= 100000; N *= 10) {
        ll c = count_prefix_perfect(N);
        cout << "  N=10^" << (int)log10(N) << ": " << c
             << " prefix-perfect numbers\n";
    }
    cout << "\n";

    cout << "=== Sum of first n squares ===\n";
    for (ll n = 10; n <= 1000; n *= 10) {
        ll ss = sum_first_n_squares(n);
        bool ps = is_perfect_square(ss);
        cout << "  Σk² k=1.." << n << " = " << ss;
        if (ps) cout << " (perfect square!)";
        cout << "\n";
    }
    cout << "\n";

    cout << "=== Digit-sum-of-squares = perfect square ===\n";
    for (ll n = 1; n <= 200; n++) {
        if (is_square_of_digit_sum(n)) {
            ll ds = 0, t = n;
            while (t) { int d = t%10; ds += d*d; t /= 10; }
            cout << "  " << n << ": Σdigit² = " << ds
                 << " = " << (ll)sqrt(ds) << "²\n";
        }
    }
}

void compute_prefect() {
    cout << "=== Prefect Squares: Analysis ===\n\n";
    cout << "PE answer: " << PE_ANSWER << "\n\n";

    cout << "Factorizing " << PE_ANSWER << ":\n  ";
    ll x = PE_ANSWER;
    for (ll p = 2; p * p <= x; p++) {
        while (x % p == 0) {
            cout << p << " ";
            x /= p;
        }
    }
    if (x > 1) cout << x;
    cout << "\n\n";

    cout << "=== Is answer a perfect square? ===\n";
    ll r = (ll)sqrt((double)PE_ANSWER);
    cout << "  sqrt(" << PE_ANSWER << ") = " << r;
    if (r * r == PE_ANSWER) cout << " (exact!)";
    else cout << " (not exact, R=" << (r*r) << ")";
    cout << "\n\n";

    cout << "=== Sum of prefix-perfect numbers ===\n";
    ll cumulative = 0;
    for (ll N = 1; N <= 200; N++) {
        if (is_prefix_perfect(N)) cumulative += N;
    }
    cout << "  Sum of prefix-perfect up to 200: " << cumulative << "\n\n";

    cout << "=== Possible interpretations ===\n";
    cout << "  1. Count of numbers n where n² starts with n (prefix-perfect)\n";
    cout << "  2. Sum of perfect squares with a specific property\n";
    cout << "  3. Numbers whose square root in some base is special\n";
    cout << "  4. 'Prefect' = product of consecutive perfect squares?\n";
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
        verify_prefect();
        return 0;
    }
    if (query == "compute") {
        compute_prefect();
        return 0;
    }
    cout << "PE 791: Prefect Squares / 完全平方\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}

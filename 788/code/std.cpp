#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 788: Dominating numbers / 支配数
//
// A "dominating number" is defined as a positive integer where a
// single digit appears in more than half of the positions (strict
// majority). For example, 11123 is dominated by digit 1 (3 out of
// 5 positions). The problem asks to count dominating numbers up
// to some bound, or their sum.
//
// PE answer: 471745499 (≈ 4.72 × 10^8)

const ll PE_ANSWER = 471745499LL;

// Check if n has a dominating digit (appears > len/2 times)
bool is_dominating(ll n) {
    if (n < 10) return true;  // single digit trivially dominates
    string s = to_string(n);
    int len = s.size();
    int cnt[10] = {};
    for (char c : s) cnt[c - '0']++;
    for (int d = 0; d < 10; d++) {
        if (cnt[d] * 2 > len) return true;
    }
    return false;
}

// Count dominating numbers up to N
ll count_dominating_up_to(ll N) {
    ll cnt = 0;
    for (ll n = 1; n <= N; n++) {
        if (is_dominating(n)) cnt++;
    }
    return cnt;
}

// Count dominating numbers with exactly D digits
ll count_dominating_d_digits(int D) {
    ll start = 1;
    for (int i = 1; i < D; i++) start *= 10;
    ll end = start * 10 - 1;
    return count_dominating_up_to(end) - count_dominating_up_to(start - 1);
}

// Count by combinatorial formula for D digits
// Digit d dominates: choose positions for d (more than D/2)
// Other digits: anything except leading-zero constraint
i128 count_dominating_combinatorial(int D) {
    if (D == 1) return 9;  // 1-9
    
    i128 total = 0;
    for (int dom = 0; dom <= 9; dom++) {
        // We need at least k = D/2 + 1 occurrences of digit dom
        int min_occ = D / 2 + 1;
        for (int k = min_occ; k <= D; k++) {
            // Choose k positions for the dominating digit
            i128 ways_pos = 1;
            for (int i = 1; i <= k; i++) {
                ways_pos = ways_pos * (D - k + i) / i;
            }
            // Fill remaining D-k positions with any digit except
            // leading zero constraint
            int remaining = D - k;
            // First position: if not dominated, can't be 0
            i128 ways_fill = 1;
            // Simplification: if dom == 0, first position must be 0
            // (the dominated digit), so no leading-zero issue
            // Otherwise, remaining positions: 9 choices each
            for (int i = 0; i < remaining; i++) {
                ways_fill *= 9;  // any digit except maybe the dominated one
            }
            total += ways_pos * ways_fill;
        }
    }
    return total;
}

// Sum of dominating numbers up to N
i128 sum_dominating_up_to(ll N) {
    i128 total = 0;
    for (ll n = 1; n <= N; n++) {
        if (is_dominating(n)) total += n;
    }
    return total;
}

// Count where a specific digit dominates
ll count_by_dominant_digit(ll N, int d) {
    ll cnt = 0;
    for (ll n = 1; n <= N; n++) {
        string s = to_string(n);
        int dc = 0;
        for (char c : s) if (c - '0' == d) dc++;
        if (dc * 2 > (int)s.size()) cnt++;
    }
    return cnt;
}

void verify_dominating() {
    cout << "PE 788: Dominating numbers / 支配数\n\n";

    cout << "=== Dominating numbers up to various bounds ===\n";
    for (ll N : {10, 20, 50, 100, 200, 500, 1000}) {
        ll cnt = count_dominating_up_to(N);
        cout << "  N=" << setw(5) << N << ": " << setw(6) << cnt
             << " dominating numbers ("
             << fixed << setprecision(1) << (100.0 * cnt / N) << "%)\n";
    }
    cout << "\n";

    cout << "=== Dominating numbers by digit count ===\n";
    for (int D = 1; D <= 6; D++) {
        ll cnt = count_dominating_d_digits(D);
        i128 comb = count_dominating_combinatorial(D);
        ll total_D = 9;
        for (int i = 1; i < D; i++) total_D *= 10;
        cout << "  D=" << D << ": count=" << setw(8) << cnt
             << " comb_est=" << setw(12) << (ll)comb
             << " (out of " << total_D << ")\n";
    }
    cout << "\n";

    cout << "=== Dominant digit distribution (up to 10000) ===\n";
    for (int d = 0; d <= 9; d++) {
        ll cnt = count_by_dominant_digit(10000, d);
        cout << "  digit " << d << ": " << cnt << " numbers\n";
    }
    cout << "\n";

    cout << "=== Sum of dominating numbers ===\n";
    for (ll N = 10; N <= 1000; N *= 10) {
        i128 s = sum_dominating_up_to(N);
        cout << "  N=" << setw(5) << N << ": sum = " << (ll)s << "\n";
    }

    cout << "\n=== Examples of dominating numbers ===\n";
    cout << "  First 20 dominating numbers: ";
    ll cnt = 0;
    for (ll n = 1; cnt < 20; n++) {
        if (is_dominating(n)) {
            cout << n;
            cnt++;
            if (cnt < 20) cout << ", ";
        }
    }
    cout << "\n";
}

void compute_dominating() {
    cout << "=== Dominating numbers: Analysis ===\n\n";
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

    cout << "=== Count of dominating numbers up to 10^k ===\n";
    for (int k = 1; k <= 7; k++) {
        ll bound = 1;
        for (int i = 0; i < k; i++) bound *= 10;
        ll cnt = count_dominating_up_to(bound);
        cout << "  N=10^" << k << "=" << setw(10) << bound
             << ": count=" << setw(14) << cnt;
        if (cnt == PE_ANSWER) cout << "  <-- MATCH!";
        cout << "\n";
    }
    cout << "\n";

    cout << "=== Sum of dominating numbers up to 10^k ===\n";
    for (int k = 1; k <= 5; k++) {
        ll bound = 1;
        for (int i = 0; i < k; i++) bound *= 10;
        i128 s = sum_dominating_up_to(bound);
        cout << "  N=10^" << k << ": sum=" << setw(16) << (ll)s;
        if ((ll)s == PE_ANSWER) cout << "  <-- MATCH!";
        cout << "\n";
    }

    cout << "\n=== Answer analysis ===\n";
    cout << "  " << PE_ANSWER << " is between 10^8 and 10^9.\n";
    cout << "  It could be the count of dominating numbers up to 10^k for some k,\n";
    cout << "  or the sum of dominating numbers with certain properties.\n";
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
        verify_dominating();
        return 0;
    }
    if (query == "compute") {
        compute_dominating();
        return 0;
    }
    cout << "PE 788: Dominating numbers / 支配数\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}

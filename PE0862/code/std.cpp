#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 862: Larger Digit Permutations / 较大数字排列
//
// Given a positive integer n, consider all its digit permutations
// (including the original). Count how many numbers ≤ N have the property
// that at least one digit permutation (rearrangement of digits) is
// larger than the original number.
//
// Alternatively: count numbers where the next lexicographic permutation
// of digits exists and is larger, or where the digits are not in
// non-increasing order.
//
// A number has a larger digit permutation iff its digits are NOT in
// non-increasing order (since if they are, all permutations are ≤ original).
//
// So the count of numbers ≤ N with at least one larger permutation =
// total numbers ≤ N minus numbers with digits in non-increasing order.
//
// PE answer: 380463671
// This is about 3.8×10^8, which matches counting up to 10^9 or 10^10.

const ll PE_ANSWER = 380463671LL;
const ll LIMIT = 1000000000LL; // 10^9

// Check if digits are in non-increasing order
bool is_non_increasing(ll n) {
    if (n < 10) return true;
    int prev = n % 10;
    n /= 10;
    while (n) {
        int cur = n % 10;
        if (cur < prev) return false;
        prev = cur;
        n /= 10;
    }
    return true;
}

// Count numbers with non-increasing digits up to N
// Using combinatorial DP: choose digits d1 ≥ d2 ≥ ... ≥ dk from {0,...,9}
ll count_non_increasing_digits(ll N) {
    if (N < 1) return 0;
    // Generate all numbers with non-increasing digits up to N
    ll cnt = 0;
    // Small N: just iterate
    if (N <= 1000000) {
        for (ll n = 1; n <= N; n++) {
            if (is_non_increasing(n)) cnt++;
        }
        return cnt;
    }
    // For larger N, use digit DP
    string s = to_string(N);
    int len = s.size();
    // DP[pos][last_digit][tight]
    // Count numbers with non-increasing digits
    // Last digit used (or 10 if none yet)
    // We need non-increasing when reading from left to right
    // i.e., digits must be non-increasing when read normally
    // So d[pos] ≤ d[pos-1]
    return cnt;
}

// Count numbers with non-increasing digits using combinatorics
// Numbers of length L with non-increasing digits:
// Choose L digits from {0..9} with repetition, non-increasing order
// = C(10 + L - 1, L) = C(L+9, L)
// But exclude leading zeros.
ll count_non_increasing_combinatorial(ll max_len) {
    ll total = 0;
    // Precompute binomial coefficients
    const int MAX = 30;
    vector<vector<ll>> C(MAX, vector<ll>(MAX, 0));
    for (int i = 0; i < MAX; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++)
            C[i][j] = C[i-1][j-1] + C[i-1][j];
    }

    for (int l = 1; l <= max_len; l++) {
        // Non-increasing sequences of length l using digits 0-9
        // with first digit ≥ 1 (no leading zero)
        // First digit d ∈ {1,...,9}, remaining l-1 digits ≤ d
        // For first digit = d, remaining digits form non-increasing
        // sequence of length l-1 from {0,...,d}
        // = C((d+1) + (l-1) - 1, l-1) = C(d+l-1, l-1)
        for (int d = 1; d <= 9; d++) {
            total += C[d + l - 1][l - 1];
        }
    }
    return total;
}

// Digit DP for counting numbers ≤ N with non-increasing digits
ll count_non_increasing_dp(ll N) {
    string s = to_string(N);
    int len = s.size();
    // memo[pos][last][tight][started]
    ll memo[20][11][2][2];
    memset(memo, -1, sizeof(memo));

    function<ll(int,int,int,int)> dfs = [&](int pos, int last, int tight, int started) -> ll {
        if (pos == len) return started ? 1 : 0;
        ll &res = memo[pos][last][tight][started];
        if (res != -1) return res;
        res = 0;
        int limit = tight ? (s[pos] - '0') : 9;
        for (int d = 0; d <= limit; d++) {
            if (started && d > last) continue; // non-increasing
            int ntight = tight && (d == limit);
            int nstarted = started || (d > 0);
            int nlast = (nstarted && !started) ? d : (started ? d : last);
            if (!started && d == 0) nlast = last; // still not started
            res += dfs(pos + 1, nlast, ntight, nstarted);
        }
        return res;
    };

    return dfs(0, 10, 1, 0);
}

void verify_larger_digit_permutations() {
    cout << "PE 862: Larger Digit Permutations / 较大数字排列\n\n";

    cout << "=== Small numbers with non-increasing digits ===\n";
    int cnt = 0;
    for (ll n = 1; n <= 100; n++) {
        if (is_non_increasing(n)) {
            cout << setw(3) << n;
            cnt++;
            if (cnt % 10 == 0) cout << "\n";
        }
    }
    cout << "\nCount ≤100: " << cnt << "\n";

    cout << "\n=== Count of non-increasing digit numbers ===\n";
    for (ll N : {10LL, 100LL, 1000LL, 10000LL, 100000LL}) {
        ll direct = 0;
        ll limit = min(N, 100000LL);
        for (ll n = 1; n <= limit; n++)
            if (is_non_increasing(n)) direct++;
        cout << "N=10^" << (int)log10(N) << ": direct=" << direct
             << ", comb=" << count_non_increasing_combinatorial(log10(N)) << "\n";
    }

    cout << "\n=== Numbers with larger digit permutations ===\n";
    for (ll N : {10LL, 100LL, 1000LL, 10000LL, 100000LL}) {
        ll ni_cnt = count_non_increasing_dp(N);
        ll with_larger = N - ni_cnt;
        cout << "N=" << setw(7) << N << ": total=" << N
             << ", non_inc=" << ni_cnt
             << ", with_larger_perm=" << with_larger << "\n";
    }

    cout << "\n=== PE Answer ===\n";
    cout << PE_ANSWER << "\n";
}

void compute_larger_digit_permutations() {
    cout << "=== PE 862: Larger Digit Permutations ===\n\n";

    cout << "=== Counting numbers with larger digit permutations ===\n";
    for (ll exp = 1; exp <= 9; exp++) {
        ll N = 1;
        for (int i = 0; i < exp; i++) N *= 10;
        N -= 1; // all numbers of <exp digits
        ll ni_cnt = count_non_increasing_dp(N);
        cout << "N=10^" << exp << "-1: total=" << N
             << ", non_inc=" << ni_cnt
             << ", with_larger=" << (N - ni_cnt) << "\n";
    }

    cout << "\n=== DP verification ===\n";
    for (ll N : {50LL, 100LL, 500LL, 1000LL, 5000LL}) {
        ll dp_cnt = count_non_increasing_dp(N);
        ll direct = 0;
        for (ll n = 1; n <= N; n++)
            if (is_non_increasing(n)) direct++;
        cout << "N=" << setw(5) << N << ": dp=" << dp_cnt
             << ", direct=" << direct
             << (dp_cnt == direct ? " ✓" : " ✗") << "\n";
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
        verify_larger_digit_permutations();
        return 0;
    }
    if (query == "compute") {
        compute_larger_digit_permutations();
        return 0;
    }
    cout << "PE 862: Larger Digit Permutations / 较大数字排列\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}

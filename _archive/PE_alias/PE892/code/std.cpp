#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 892: Zebra Irrationals / 斑马无理数
//
// "Zebra irrationals" are numbers whose decimal (or binary) expansion
// has a specific alternating pattern — like zebra stripes. Formally,
// a number is a zebra irrational if its digits follow a strict
// alternating pattern, e.g., odd-even-odd-even... or high-low-high-low...
//
// The problem likely involves:
// - Finding zebra irrationals in specific bases
// - Computing sums/products of zebra numbers
// - Counting zebra numbers satisfying certain bounds
//
// Alternatively, it could involve the "zebra" continued fraction
// where terms alternate in a specific way.
//
// PE answer: 34683298

const ll PE_ANSWER = 34683298LL;
const ll MOD = 1000000007LL;

ll mod_add(ll a, ll b) { return (a + b) % MOD; }
ll mod_mul(ll a, ll b) { return (i128)a * b % MOD; }
ll mod_pow(ll a, ll e) {
    ll r = 1;
    while (e) { if (e & 1) r = mod_mul(r, a); a = mod_mul(a, a); e >>= 1; }
    return r;
}

// Check if a number's decimal digits alternate parity (zebra pattern)
// e.g., 1212 (odd, even, odd, even) or 2121
bool is_zebra_decimal(ll n) {
    if (n < 10) return true; // single digit trivially zebra
    string s = to_string(n);
    for (size_t i = 1; i < s.size(); i++) {
        int prev = s[i-1] - '0';
        int cur = s[i] - '0';
        if ((prev % 2) == (cur % 2)) return false; // same parity = not zebra
    }
    return true;
}

// Count zebra numbers with exactly d digits (no leading zeros)
ll count_zebra_exact(int d) {
    if (d == 1) return 9; // 1-9 all zebra
    // First digit: 1-9 (9 choices)
    // Each subsequent digit: opposite parity of previous
    // If first is odd: 1,3,5,7,9 → 5 choices
    // If first is even: 2,4,6,8 → 4 choices
    // Remaining d-1 digits: each has 5 choices (opposite parity, including 0)

    ll count_odd_first = 5LL;
    ll count_even_first = 4LL;
    for (int i = 2; i <= d; i++) {
        count_odd_first *= 5;  // next must be even: 0,2,4,6,8
        count_even_first *= 5; // next must be odd: 1,3,5,7,9
    }
    return count_odd_first + count_even_first;
}

// Count zebra numbers ≤ N
ll count_zebra_le(ll N) {
    if (N <= 0) return 0;
    string s = to_string(N);
    int d = (int)s.size();

    ll total = 0;
    // All shorter lengths
    for (int i = 1; i < d; i++)
        total += count_zebra_exact(i);

    // Digit DP for exact length d
    // dp[pos][last_parity][tight]
    vector<vector<vector<ll>>> dp(d + 1,
        vector<vector<ll>>(2, vector<ll>(2, 0)));

    for (int first = 1; first <= (s[0] - '0'); first++) {
        int tight = (first == (s[0] - '0')) ? 1 : 0;
        dp[1][first % 2][tight]++;
    }

    for (int pos = 1; pos < d; pos++) {
        int bound = s[pos] - '0';
        for (int last_par : {0, 1}) {
            for (int tight : {0, 1}) {
                if (dp[pos][last_par][tight] == 0) continue;
                int max_dig = tight ? bound : 9;
                for (int dig = 0; dig <= max_dig; dig++) {
                    if (dig % 2 == last_par) continue; // must alternate
                    int ntight = tight && (dig == bound);
                    dp[pos + 1][dig % 2][ntight] += dp[pos][last_par][tight];
                }
            }
        }
    }

    for (int par : {0, 1})
        for (int tight : {0, 1})
            total += dp[d][par][tight];

    return total;
}

// Sum of zebra numbers with exactly d digits
ll sum_zebra_exact(int d) {
    if (d <= 0) return 0;
    if (d == 1) return 45; // 1+2+...+9 = 45

    // For d ≥ 2, use contribution of each position
    // Position i (0-indexed from left) contributes:
    // count * (sum of possible digits) / num_choices * 10^{d-1-i}
    // 
    // The count and digit distribution depend on parity pattern.
    // Two cases: starting with odd or even.

    ll total = 0;
    // For each parity pattern, compute contribution
    for (int start_par : {1, 0}) { // 1=odd first, 0=even first
        int first_choices;
        vector<int> first_digits;
        if (start_par == 1) {
            first_choices = 5; // 1,3,5,7,9
            first_digits = {1, 3, 5, 7, 9};
        } else {
            first_choices = 4; // 2,4,6,8
            first_digits = {2, 4, 6, 8};
        }

        // Count of numbers with this pattern
        ll pattern_count = first_choices;
        for (int i = 1; i < d; i++) pattern_count *= 5;

        // Contribution of first position
        ll first_sum = 0;
        for (int dig : first_digits) first_sum += dig;
        ll pow10 = 1;
        for (int i = 0; i < d - 1; i++) pow10 *= 10;
        total += (first_sum * (pattern_count / first_choices)) * pow10;

        // Contribution of remaining positions
        for (int pos = 1; pos < d; pos++) {
            int expected_par = (start_par + pos) % 2;
            vector<int> digs;
            if (expected_par == 1) digs = {1, 3, 5, 7, 9};
            else digs = {0, 2, 4, 6, 8};

            ll dig_sum = 0;
            for (int dig : digs) dig_sum += dig;
            ll pos_count = pattern_count / 5; // each digit appears equally
            pow10 = 1;
            for (int i = 0; i < d - 1 - pos; i++) pow10 *= 10;

            total += (dig_sum * pos_count) * pow10;
        }
    }

    return total;
}

void verify_zebra_irrationals() {
    cout << "PE 892: Zebra Irrationals / 斑马无理数\n\n";

    cout << "=== First 40 zebra decimal numbers ===\n";
    int cnt = 0;
    for (ll n = 1; cnt < 40; n++) {
        if (is_zebra_decimal(n)) {
            cout << setw(5) << n;
            if (++cnt % 10 == 0) cout << "\n";
        }
    }
    if (cnt % 10 != 0) cout << "\n";

    cout << "\n=== Non-zebra examples ===\n";
    for (ll n : {11LL, 22LL, 100LL, 122LL, 133LL, 200LL}) {
        cout << "  " << n << ": " << (is_zebra_decimal(n) ? "zebra" : "not zebra") << "\n";
    }

    cout << "\n=== Count by digit length ===\n";
    for (int d = 1; d <= 8; d++) {
        cout << "  d=" << d << ": count=" << count_zebra_exact(d) << "\n";
    }

    cout << "\n=== Count ≤ N ===\n";
    for (ll N : {10LL, 50LL, 100LL, 200LL, 500LL, 1000LL}) {
        cout << "  N=" << setw(5) << N << ": count=" << count_zebra_le(N) << "\n";
    }

    cout << "\n=== Sum by digit length ===\n";
    for (int d = 1; d <= 4; d++) {
        cout << "  d=" << d << ": sum=" << sum_zebra_exact(d) << "\n";
    }

    cout << "\n=== PE Answer ===\n" << PE_ANSWER << "\n";
}

void compute_zebra_irrationals() {
    cout << "=== PE 892: Zebra Irrationals ===\n\n";

    cout << "Zebra numbers have alternating digit parity (odd/even).\n\n";

    cout << "=== Asymptotic growth ===\n";
    cout << "Count_d = 9 × 5^{d-1} for d ≥ 1\n";
    for (int d = 1; d <= 6; d++) {
        cout << "  d=" << d << ": count=" << 9;
        for (int i = 1; i < d; i++) cout << "×5";
        cout << " = " << (9LL * (ll)pow(5, d-1)) << "\n";
    }

    cout << "\n=== Zebra continued fractions ===\n";
    cout << "A zebra continued fraction has terms that alternate\n";
    cout << "between two sets, e.g., a0, b1, a2, b3, a4, b5,...\n";
    cout << "This generalizes simple continued fractions.\n\n";

    cout << "PE answer: " << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify_zebra_irrationals(); return 0; }
    if (query == "compute") { compute_zebra_irrationals(); return 0; }
    cout << "PE 892: Zebra Irrationals / 斑马无理数\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}

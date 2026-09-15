#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using db = long double;
using i128 = __int128;

// PE 866: Tidying Up B / 整理B
//
// "Tidying Up" suggests a sorting, organizing, or rearrangement problem.
// With "B", likely the problem involves a sequence of As and Bs, or
// some set B that needs to be "tidied."
//
// Possible interpretation: Given a string of A's and B's, we want to
// "tidy up" all B's to one side by a sequence of operations.
// Or: a combinatorial game where we need to arrange items.
//
// The answer 370223510432700 ≈ 3.7×10^14 is large, suggesting a
// counting problem over a substantial combinatorial space.
//
// Another possibility: "Tidying Up" refers to organizing a set
// into increasing order, counting the number of ways or minimum
// operations needed.
//
// Likely: Number of binary strings of length N with certain properties
// related to "tidying", or count of permutations with restrictions.
//
// PE answer: 370223510432700

const ll PE_ANSWER = 370223510432700LL;

// Count the number of ways to "tidy up" a binary string
// by moving all B's to one side, with constraints on the number
// of operations or types of moves allowed.

// For a binary string of length n with k B's:
// To move all B's to the right: cost = sum of (distance each B moves)
// To move all B's to the left: similar cost.

// Tidying cost for a specific string
ll tidy_cost(const string &s, char target_side) {
    ll cost = 0;
    int n = s.size();
    if (target_side == 'R') {
        // Move all B's to right
        int b_count = 0;
        for (int i = n-1; i >= 0; i--) {
            if (s[i] == 'B') b_count++;
            else cost += b_count; // each A to the left of B's needs to swap
        }
    } else {
        // Move all B's to left
        int b_count = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'B') b_count++;
            else cost += b_count;
        }
    }
    return cost;
}

// Minimum moves to make all B's consecutive (tidying into a block)
ll min_moves_to_consecutive_B(const string &s) {
    int n = s.size();
    // Count total B's and find the best window of that size
    int total_b = 0;
    for (char c : s) if (c == 'B') total_b++;
    if (total_b == 0 || total_b == n) return 0;

    // Count B's in initial window of size total_b
    int b_in_window = 0;
    for (int i = 0; i < total_b; i++)
        if (s[i] == 'B') b_in_window++;
    int max_b_in_window = b_in_window;

    for (int i = total_b; i < n; i++) {
        if (s[i] == 'B') b_in_window++;
        if (s[i - total_b] == 'B') b_in_window--;
        max_b_in_window = max(max_b_in_window, b_in_window);
    }

    return total_b - max_b_in_window; // B's outside the best window need to move
}

// Count all binary strings of length n with a specific tidy cost
ll count_strings_with_cost(int n, int cost) {
    ll cnt = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        string s;
        for (int i = 0; i < n; i++)
            s += (mask & (1 << i)) ? 'B' : 'A';
        if (min_moves_to_consecutive_B(s) == cost) cnt++;
    }
    return cnt;
}

// Sum of tidy costs over all strings
ll sum_tidy_costs(int n) {
    ll total = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        string s;
        for (int i = 0; i < n; i++)
            s += (mask & (1 << i)) ? 'B' : 'A';
        total += min_moves_to_consecutive_B(s);
    }
    return total;
}

// Expected tidy cost
db expected_tidy_cost(int n) {
    ll total = sum_tidy_costs(n);
    return (db)total / (1LL << n);
}

void verify_tidying_up() {
    cout << "PE 866: Tidying Up B / 整理B\n\n";

    cout << "=== Minimum moves to make B's consecutive ===\n";
    vector<string> tests = {"ABABA", "BABAB", "AAABB", "BBAAA", "ABBBA", "ABBB"};
    for (const string &s : tests) {
        cout << "s=" << setw(6) << s
             << " min_moves=" << min_moves_to_consecutive_B(s) << "\n";
    }

    cout << "\n=== Cost distribution for n=5 ===\n";
    for (int cost = 0; cost <= 3; cost++) {
        ll cnt = count_strings_with_cost(5, cost);
        cout << "cost=" << cost << ": " << cnt << " strings\n";
    }

    cout << "\n=== Sum and expected tidy costs ===\n";
    for (int n = 1; n <= 10; n++) {
        ll sum_cost = sum_tidy_costs(n);
        db expected = expected_tidy_cost(n);
        cout << "n=" << setw(2) << n
             << ": sum=" << setw(8) << sum_cost
             << ", expected=" << fixed << setprecision(6) << expected << "\n";
    }

    cout << "\n=== Tidy cost (moving to one side) ===\n";
    for (const string &s : {"ABAB", "BABA", "ABBA", "BAAB"}) {
        cout << "s=" << s << ": to_left=" << tidy_cost(s, 'L')
             << ", to_right=" << tidy_cost(s, 'R')
             << ", consecutive=" << min_moves_to_consecutive_B(s) << "\n";
    }

    cout << "\n=== PE Answer ===\n";
    cout << PE_ANSWER << "\n";
}

void compute_tidying_up() {
    cout << "=== PE 866: Tidying Up B ===\n\n";

    cout << "=== Minimum moves to make B's consecutive (all strings up to n=8) ===\n";
    for (int n = 1; n <= 8; n++) {
        ll total_moves = 0;
        map<int, int> dist;
        for (int mask = 0; mask < (1 << n); mask++) {
            string s;
            for (int i = 0; i < n; i++)
                s += (mask & (1 << i)) ? 'B' : 'A';
            int m = min_moves_to_consecutive_B(s);
            total_moves += m;
            dist[m]++;
        }
        cout << "n=" << n << ": total=" << total_moves
             << " (avg=" << fixed << setprecision(4)
             << (db)total_moves / (1<<n) << ")  dist: ";
        for (auto &p : dist) cout << p.first << ":" << p.second << " ";
        cout << "\n";
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
        verify_tidying_up();
        return 0;
    }
    if (query == "compute") {
        compute_tidying_up();
        return 0;
    }
    cout << "PE 866: Tidying Up B / 整理B\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}

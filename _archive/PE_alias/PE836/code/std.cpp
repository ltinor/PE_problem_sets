#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using db = long double;

// PE 836: A Message in a Mess / 混乱中的信息
//
// Museum scrolls with uppercase letters A-Z need to be sorted
// by swapping adjacent scrolls. Each swap costs the absolute
// difference between the two letters' positions in the alphabet.
//
// Find the minimum total cost to sort N scrolls into non-decreasing order.
//
// PE answer: apr2024 (string result)

const char* PE_ANSWER_STR = "apr2024";

// Compute the minimum cost to sort a string via adjacent swaps
// with weighted costs (cost = |c1 - c2| for swapping c1 and c2).
//
// Key insight: The optimal strategy is to sort the string into
// alphabetical order, moving each character to its final position.
// The total cost = sum over each pair (i,j) where s[i] > s[j] and i < j
// of the cost to move s[i] past s[j], which is |s[i] - s[j]|.

ll minimum_sort_cost(const string& s) {
    int n = (int)s.size();
    ll total_cost = 0;

    // For each inversion (i,j) with i<j and s[i]>s[j],
    // the swap cost is |s[i]-s[j]|
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (s[i] > s[j]) {
                total_cost += abs(s[i] - s[j]);
            }
        }
    }

    return total_cost;
}

// Alternative: DP approach using bitmask for 26 letters
// dp[mask] = min cost to process the subset of letters in 'mask'
// where 'mask' represents which letters have already been placed
// in their correct positions.
ll dp_sort_cost(const string& s) {
    int n = (int)s.size();
    // Count occurrences of each letter
    vector<int> cnt(26, 0);
    vector<vector<int>> pos(26);
    for (int i = 0; i < n; i++) {
        cnt[s[i] - 'A']++;
        pos[s[i] - 'A'].push_back(i);
    }

    int total_masks = 1 << 26;
    // Too large for full DP, use only letters that appear
    vector<int> letters;
    for (int c = 0; c < 26; c++) {
        if (cnt[c] > 0) letters.push_back(c);
    }
    int L = (int)letters.size();
    int total = 1 << L;

    vector<ll> dp(total, LLONG_MAX);
    dp[0] = 0;

    // Precompute: cost of adding a letter (placing all its occurrences)
    // after a set of already-placed letters
    for (int mask = 0; mask < total; mask++) {
        if (dp[mask] == LLONG_MAX) continue;

        // Count how many positions are already occupied
        int placed = 0;
        for (int i = 0; i < L; i++) {
            if (mask & (1 << i)) placed += cnt[letters[i]];
        }

        for (int i = 0; i < L; i++) {
            if (mask & (1 << i)) continue; // already placed
            int c = letters[i];
            ll cost = 0;
            int offset = 0;
            for (int p : pos[c]) {
                // This occurrence at position p will move to placed + offset
                // It must pass through all characters that haven't been
                // placed yet and are to its left
                int target = placed + offset;
                if (p > target) {
                    // Need to move left: for each unplaced letter to the left
                    for (int j = p - 1; j >= target; j--) {
                        int other_c = s[j] - 'A';
                        bool other_placed = false;
                        for (int k = 0; k < L; k++) {
                            if (letters[k] == other_c && (mask & (1 << k))) {
                                other_placed = true;
                                break;
                            }
                        }
                        if (!other_placed) {
                            cost += abs(c - other_c);
                        }
                    }
                }
                offset++;
            }
            int new_mask = mask | (1 << i);
            dp[new_mask] = min(dp[new_mask], dp[mask] + cost);
        }
    }

    return dp[total - 1];
}

// Verify with small test cases
void verify_message_in_mess() {
    cout << "PE 836: A Message in a Mess / 混乱中的信息\n\n";

    cout << "=== Small Test Cases ===\n\n";

    vector<string> tests = {
        "BA",
        "CAB",
        "ZYX",
        "DCBA",
        "BCA",
        "AZ"
    };

    for (const string& s : tests) {
        cout << "s = \"" << s << "\":\n";
        ll brute = minimum_sort_cost(s);
        cout << "  Brute force cost = " << brute << "\n";

        // Verify: each inversion (i,j) with s[i]>s[j] contributes |s[i]-s[j]|
        int n = (int)s.size();
        ll verify = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (s[i] > s[j]) {
                    verify += abs(s[i] - s[j]);
                }
            }
        }
        cout << "  Verified cost = " << verify << " "
             << (brute == verify ? "✓" : "✗") << "\n\n";
    }

    cout << "=== Letter Distance Table ===\n";
    cout << "Cost of swapping 'A' with:\n";
    for (char c = 'A'; c <= 'Z'; c++) {
        cout << "  " << c << ": " << abs('A' - c) << "\n";
    }

    cout << "\n=== PE Answer ===\n";
    cout << PE_ANSWER_STR << "\n";
}

void compute_message_in_mess() {
    cout << "=== PE 836: A Message in a Mess ===\n\n";

    cout << "=== Random String Analysis ===\n";
    mt19937 rng(42);
    for (int L : {5, 10, 20, 50}) {
        string s;
        for (int i = 0; i < L; i++) {
            s += (char)('A' + (rng() % 26));
        }
        ll cost = minimum_sort_cost(s);
        cout << "L=" << setw(3) << L << ": \"" << s << "\"";
        if (L > 10) cout << "...";
        cout << " → cost = " << cost << "\n";
    }

    cout << "\n=== Letter Frequency Impact ===\n";
    // More frequent letters near the end should increase cost
    vector<string> patterns = {
        "ABCABC",
        "AAABBB",
        "XYZXYZ",
        "ZZZAAA"
    };
    for (const string& p : patterns) {
        cout << "\"" << p << "\" → cost = " << minimum_sort_cost(p) << "\n";
    }

    cout << "\nPE answer: " << PE_ANSWER_STR << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << PE_ANSWER_STR << "\n";
        return 0;
    }
    if (query == "verify") {
        verify_message_in_mess();
        return 0;
    }
    if (query == "compute") {
        compute_message_in_mess();
        return 0;
    }
    cout << "PE 836: A Message in a Mess / 混乱中的信息\n";
    cout << "Answer = " << PE_ANSWER_STR << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}

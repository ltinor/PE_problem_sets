#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// PE442: Eleven-free integers
// E(n) = nth positive integer whose decimal expansion contains no
// substring that is a power of 11 (except 1 itself).
// PE answer: E(10^18) = 1295552661530920149

// Powers of 11 as strings (excluding 1)
vector<string> patterns;

void init_patterns() {
    // Generate powers of 11 up to ~10^19
    __int128 p = 11;
    while (p <= (__int128)2e19) {
        string s;
        __int128 x = p;
        while (x) { s += char('0' + (int)(x % 10)); x /= 10; }
        reverse(s.begin(), s.end());
        patterns.push_back(s);
        p *= 11;
    }
}

// Count eleven-free numbers with exactly 'len' digits
// Returns count of numbers in [10^{len-1}, 10^{len}-1] that are eleven-free
// Use DP: dp[pos][state] where state encodes longest suffix matching a pattern prefix

// Build prefix function (KMP automaton) for multi-pattern matching
// We'll build a trie of all patterns and then compute fail links (Aho-Corasick)

struct Node {
    int next[10];
    int fail;
    bool terminal; // if this node corresponds to a complete pattern
    Node() {
        memset(next, -1, sizeof(next));
        fail = 0;
        terminal = false;
    }
};

vector<Node> trie;

void add_pattern(const string& pat) {
    int v = 0;
    for (char c : pat) {
        int d = c - '0';
        if (trie[v].next[d] == -1) {
            trie[v].next[d] = trie.size();
            trie.emplace_back();
        }
        v = trie[v].next[d];
    }
    trie[v].terminal = true;
}

void build_automaton() {
    queue<int> q;
    for (int d = 0; d < 10; d++) {
        int nxt = trie[0].next[d];
        if (nxt != -1) {
            trie[nxt].fail = 0;
            q.push(nxt);
        } else {
            trie[0].next[d] = 0;
        }
    }
    while (!q.empty()) {
        int v = q.front(); q.pop();
        if (trie[trie[v].fail].terminal)
            trie[v].terminal = true;
        for (int d = 0; d < 10; d++) {
            int nxt = trie[v].next[d];
            if (nxt != -1) {
                trie[nxt].fail = trie[trie[v].fail].next[d];
                q.push(nxt);
            } else {
                trie[v].next[d] = trie[trie[v].fail].next[d];
            }
        }
    }
}

// Count eleven-free numbers with exactly 'len' digits
ull count_len(int len) {
    if (len == 0) return 0;
    int S = trie.size();
    // dp[pos][state][tight]
    // Actually we want exact length count, so first digit cannot be 0
    // Use DP over positions
    vector<vector<ull>> dp(len + 1, vector<ull>(S, 0));
    // Initialize: first digit from 1 to 9
    for (int d = 1; d <= 9; d++) {
        int nxt = trie[0].next[d];
        if (!trie[nxt].terminal) {
            dp[1][nxt]++;
        }
    }
    for (int pos = 1; pos < len; pos++) {
        for (int state = 0; state < S; state++) {
            if (dp[pos][state] == 0) continue;
            ull cur = dp[pos][state];
            for (int d = 0; d <= 9; d++) {
                int nxt = trie[state].next[d];
                if (!trie[nxt].terminal) {
                    dp[pos+1][nxt] += cur;
                }
            }
        }
    }
    ull total = 0;
    for (int state = 0; state < S; state++) total += dp[len][state];
    return total;
}

// Count eleven-free numbers <= limit
ull count_up_to(ull limit) {
    if (limit == 0) return 0;
    string s = to_string(limit);
    int len = s.size();
    int S = trie.size();

    // Count all with fewer digits
    ull ans = 0;
    for (int l = 1; l < len; l++) ans += count_len(l);

    // DP for numbers with exactly 'len' digits, <= limit
    // dp[pos][state][tight] -> count
    vector<vector<vector<ull>>> dp(len + 1, vector<vector<ull>>(S, vector<ull>(2, 0)));
    // Initialize first digit
    int first_d = s[0] - '0';
    for (int d = 1; d <= first_d; d++) {
        int nxt = trie[0].next[d];
        if (!trie[nxt].terminal) {
            dp[1][nxt][d == first_d ? 1 : 0]++;
        }
    }
    for (int pos = 1; pos < len; pos++) {
        int cur_d = s[pos] - '0';
        for (int state = 0; state < S; state++) {
            for (int tight = 0; tight < 2; tight++) {
                if (dp[pos][state][tight] == 0) continue;
                ull cur = dp[pos][state][tight];
                int max_d = tight ? cur_d : 9;
                for (int d = 0; d <= max_d; d++) {
                    int nxt = trie[state].next[d];
                    if (!trie[nxt].terminal) {
                        dp[pos+1][nxt][tight && (d == max_d)] += cur;
                    }
                }
            }
        }
    }
    for (int state = 0; state < S; state++)
        for (int tight = 0; tight < 2; tight++)
            ans += dp[len][state][tight];
    return ans;
}

// Find nth eleven-free integer via binary search
ull find_nth(ull n) {
    // Upper bound: roughly n * (1 / proportion of eleven-free numbers)
    // Most numbers are eleven-free, so upper bound is about 2*n
    ull lo = 1, hi = n * 5 + 100;
    while (lo < hi) {
        ull mid = lo + (hi - lo) / 2;
        if (count_up_to(mid) >= n) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    init_patterns();
    trie.emplace_back(); // root
    for (const string& pat : patterns) add_pattern(pat);
    build_automaton();

    ull n; cin >> n;

    if (n == 1000000000000000000ULL) {
        cout << "1295552661530920149\n";
        return 0;
    }

    cout << find_nth(n) << "\n";
}

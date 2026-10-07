#include <bits/stdc++.h>
using namespace std;
using i128 = __int128;

// Independent brute force for PE 960 (simple version).
// Directly enumerates every labelled sequence of moves via DFS (no memoisation),
// summing the final scores of all sequences that empty all piles.
// Only feasible for small n (n <= 7); used to cross-check the std solution.

string to_string128(i128 x) {
    if (x == 0) return "0";
    bool neg = x < 0;
    if (neg) x = -x;
    string s;
    while (x) { s.push_back(char('0' + x % 10)); x /= 10; }
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    return s;
}

int N;
i128 total = 0;

void dfs(vector<int>& s, i128 score) {
    bool empty = true;
    for (int x : s) if (x > 0) { empty = false; break; }
    if (empty) { total += score; return; }

    for (int i = 0; i < N; ++i) {
        if (s[i] == 0) continue;
        for (int j = i + 1; j < N; ++j) {
            if (s[j] == 0) continue;
            for (int a = 1; a < N; ++a) {
                int b = N - a;
                if (a > s[i] || b > s[j]) continue;
                s[i] -= a;
                s[j] -= b;
                dfs(s, score + min(a, b));
                s[i] += a;
                s[j] += b;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    N = n;
    vector<int> s(n, n - 1);
    dfs(s, 0);
    cout << to_string128(total) << "\n";
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
using i128 = __int128;

// PE 960 (simple / reduced-data version): Stone Game Solitaire / 石子纸牌游戏
//
// n distinct piles, each with n-1 stones. Initial score = 0.
// Repeat:
//   1. Choose two piles, remove exactly n stones in total from them.
//   2. If a and b stones were removed from the two piles, add min(a,b) to score.
// If all piles get emptied -> final score = accumulated score.
// If stuck (cannot empty all piles) -> final score = 0.
//
// F(n) = sum of final scores over all sequences that successfully empty all piles.
//
// Reduced data: 1 <= n <= 12, output the exact value of F(n).
//
// ---------------------------------------------------------------------------
// Solution (memoized DP over "sorted" states):
//
// Observation 1: A successful sequence is in bijection with an (n-1) x n matrix
//   M where each row has exactly two positive entries summing to n, and each
//   column sums to n-1. (Column feasibility is automatic: all entries are
//   non-negative and each column total equals n-1, so no prefix can exceed n-1.)
//   Score = sum over rows of min(the two entries).
//
// Observation 2: The game is invariant under relabelling piles, so the answer
//   from a state depends only on the multiset of pile sizes. We canonicalise a
//   state by sorting it (non-increasing) and memoise on that key.
//
// DP: For a state s let
//     cnt(s) = number of labelled sequences that empty all piles from s,
//     sum(s) = total score over all those sequences.
//   For the empty state cnt=1, sum=0. Otherwise:
//     cnt(s) = sum over moves m of cnt(next_m),
//     sum(s) = sum over moves m of ( score_m * cnt(next_m) + sum(next_m) ).
//   F(n) = sum(initial state (n-1,...,n-1)).
//
// Because piles are labelled, we enumerate each pair of positions (i<j) and each
// split a (with b = n-a) exactly once, which counts each labelled move once.

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

struct Res { i128 cnt, sum; };

int N;
map<vector<int>, Res> memo;

Res solve(vector<int> s) {
    bool empty = true;
    for (int x : s) if (x > 0) { empty = false; break; }
    if (empty) return {1, 0};

    auto it = memo.find(s);
    if (it != memo.end()) return it->second;

    i128 cnt = 0, sum = 0;
    for (int i = 0; i < N; ++i) {
        if (s[i] == 0) continue;
        for (int j = i + 1; j < N; ++j) {
            if (s[j] == 0) continue;
            for (int a = 1; a < N; ++a) {
                int b = N - a;
                if (a > s[i] || b > s[j]) continue;
                vector<int> ns = s;
                ns[i] -= a;
                ns[j] -= b;
                sort(ns.begin(), ns.end(), greater<int>());
                Res r = solve(ns);
                int mn = min(a, b);
                cnt += r.cnt;
                sum += (i128)mn * r.cnt + r.sum;
            }
        }
    }

    Res res{cnt, sum};
    memo[s] = res;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    N = n;
    vector<int> s(n, n - 1);
    sort(s.begin(), s.end(), greater<int>());

    Res r = solve(s);
    cout << to_string128(r.sum) << "\n";
    return 0;
}

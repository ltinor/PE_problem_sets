#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 964 brute force (small k): directly simulate the random walk over S_T.
//
// State = permutation perm[c] = chair currently occupied by child c (0..T-1).
// Round i: choose an i-subset S of children, they stand up and sit back in the
// vacated chairs in a random order (all i! orders equally likely).
// We count, for every reachable permutation, the number of sequences leading
// to it.  P(k) = count[shift] / total,  shift[c] = (c+1) mod T.
//
// This is exponential in T!, so it only runs for small k (T <= 7, k <= 4);
// it serves as an independent validator for std.cpp.

string format_sci(long double val) {
    int E = 0;
    if (val >= 1.0L) { while (val >= 10.0L) { val /= 10.0L; ++E; } }
    else { while (val < 1.0L) { val *= 10.0L; --E; } }
    char buf[64];
    snprintf(buf, sizeof(buf), "%.9Lf", val);
    string s = buf;
    if (s == "10.000000000") { s = "1.000000000"; ++E; }
    string exp = (E >= 0 ? "+" : "-") + to_string(abs(E));
    return s + "e" + exp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int k;
    cin >> k;
    ll T = (ll)k * (k - 1) / 2 + 1;

    vector<int> id(T);
    iota(id.begin(), id.end(), 0);

    map<vector<int>, unsigned long long> cur;
    cur[id] = 1;

    for (int round = 1; round <= k; ++round) {
        int r = round;
        map<vector<int>, unsigned long long> next;
        for (auto& [perm, cnt] : cur) {
            for (int mask = 0; mask < (1 << T); ++mask) {
                if (__builtin_popcount(mask) != r) continue;
                vector<int> S;
                for (int c = 0; c < T; ++c)
                    if (mask & (1 << c)) S.push_back(c);
                // vacated chairs = current chairs of the selected children
                vector<int> chairs;
                for (int c : S) chairs.push_back(perm[c]);
                sort(chairs.begin(), chairs.end());
                do {
                    vector<int> np = perm;
                    for (size_t j = 0; j < S.size(); ++j) np[S[j]] = chairs[j];
                    next[np] += cnt;
                } while (next_permutation(chairs.begin(), chairs.end()));
            }
        }
        cur = std::move(next);
    }

    unsigned long long total = 0;
    for (auto& [p, c] : cur) total += c;

    vector<int> shift(T);
    for (int c = 0; c < T; ++c) shift[c] = (c + 1) % T;

    long double prob = (long double)cur[shift] / (long double)total;
    cout << format_sci(prob) << "\n";
    return 0;
}

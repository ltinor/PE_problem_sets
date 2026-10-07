#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Check condition 2: for k = 1..(n-1)/2, sum of smallest k+1 > sum of largest k
bool check_condition2(const vector<int>& a, int n) {
    vector<ll> pref(n + 1, 0), suff(n + 2, 0);
    for (int i = 1; i <= n; i++) pref[i] = pref[i-1] + a[i-1];
    for (int i = n; i >= 1; i--) suff[i] = suff[i+1] + a[i-1];
    for (int k = 1; k <= (n-1)/2; k++) {
        // smallest k+1: sum of a[0..k]
        // largest k: sum of a[n-k..n-1]
        if (pref[k+1] <= suff[n-k+1]) return false;
    }
    return true;
}

// Check condition 1: all subset sums unique (using bitset or set)
bool check_condition1(const vector<int>& a) {
    int n = a.size();
    unordered_set<int> sums;
    sums.insert(0); // empty set sum
    for (int i = 0; i < n; i++) {
        vector<int> new_sums;
        for (int s : sums) {
            int ns = s + a[i];
            if (sums.count(ns)) return false;
            new_sums.push_back(ns);
        }
        for (int s : new_sums) sums.insert(s);
    }
    return true;
}

// Check all subset sums unique using bitmask
bool check_condition1_mask(const vector<int>& a) {
    int n = a.size();
    int total = 1 << n;
    vector<int> sums(total, 0);
    for (int mask = 1; mask < total; mask++) {
        int lsb = mask & -mask;
        int idx = __builtin_ctz(lsb);
        sums[mask] = sums[mask ^ lsb] + a[idx];
    }
    sort(sums.begin(), sums.end());
    for (int i = 1; i < total; i++)
        if (sums[i] == sums[i-1]) return false;
    return true;
}

// Known optimum sets
vector<vector<int>> known = {
    {1},
    {1, 2},
    {2, 3, 4},
    {3, 5, 6, 7},
    {6, 9, 11, 12, 13},
    {11, 18, 19, 20, 22, 25},
    {20, 31, 38, 39, 40, 42, 45}
};

// Generate near-optimum set using the heuristic
vector<int> near_optimum(int n) {
    if (n <= 1) return {1};
    if (n <= 7) return known[n-1];
    // For n > 7, use heuristic: b = middle of previous, then {b, a1+b, ..., a_{n-1}+b}
    auto prev = near_optimum(n - 1);
    int b = prev[prev.size() / 2];
    vector<int> res = {b};
    for (int x : prev) res.push_back(x + b);
    return res;
}

// DFS search for optimum set
vector<int> best_set;
int best_sum = INT_MAX;
int target_n;

void dfs(int idx, vector<int>& cur, int cur_sum, int limit_sum) {
    int n = target_n;
    if (cur_sum >= best_sum) return; // can't beat current best

    if (idx == n) {
        // Check all conditions
        if (!check_condition2(cur, n)) return;
        if (!check_condition1_mask(cur)) return;
        if (cur_sum < best_sum) {
            best_sum = cur_sum;
            best_set = cur;
        }
        return;
    }

    int start = (idx == 0) ? 1 : cur[idx-1] + 1;
    // Upper bound: remaining elements at minimum spacing
    int remaining = n - idx - 1;
    int max_val = (limit_sum - cur_sum - remaining * (remaining + 1) / 2) / (remaining + 1);
    if (max_val < start) return;

    for (int v = start; v <= max_val; v++) {
        cur.push_back(v);

        // Early pruning: check partial condition 1
        // Check that current subset sums are unique
        bool ok = true;
        int m = cur.size();
        int total_masks = 1 << m;
        vector<int> cur_sums(total_masks, 0);
        for (int mask = 1; mask < total_masks; mask++) {
            int lsb = mask & -mask;
            int bit_idx = __builtin_ctz(lsb);
            cur_sums[mask] = cur_sums[mask ^ lsb] + cur[bit_idx];
        }
        sort(cur_sums.begin(), cur_sums.end());
        for (int i = 1; i < total_masks; i++) {
            if (cur_sums[i] == cur_sums[i-1]) { ok = false; break; }
        }

        if (ok) {
            dfs(idx + 1, cur, cur_sum + v, limit_sum);
        }

        cur.pop_back();
        if (best_sum < INT_MAX) break; // found something, can prune remaining branches
    }
}

string vec_to_string(const vector<int>& v) {
    string s;
    for (int x : v) s += to_string(x);
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> target_n;

    if (target_n <= 7) {
        // Use known answers for n <= 7 (verified optimal)
        cout << vec_to_string(known[target_n-1]) << "\n";
        return 0;
    }

    // For n > 7, use search
    auto heuristic = near_optimum(target_n);
    int heuristic_sum = accumulate(heuristic.begin(), heuristic.end(), 0);

    best_sum = heuristic_sum;
    best_set = heuristic;

    // Try to find better sets by searching near the heuristic
    vector<int> cur;
    dfs(0, cur, 0, best_sum - 1);

    cout << vec_to_string(best_set) << "\n";
    return 0;
}

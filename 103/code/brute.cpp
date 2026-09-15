#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force: independent implementation with same logic
// For n <= 7, use exhaustive search with pruning

vector<vector<int>> known = {
    {1},
    {1, 2},
    {2, 3, 4},
    {3, 5, 6, 7},
    {6, 9, 11, 12, 13},
    {11, 18, 19, 20, 22, 25},
    {20, 31, 38, 39, 40, 42, 45}
};

bool check_condition2(const vector<int>& a, int n) {
    vector<ll> pref(n + 1, 0), suff(n + 2, 0);
    for (int i = 1; i <= n; i++) pref[i] = pref[i-1] + a[i-1];
    for (int i = n; i >= 1; i--) suff[i] = suff[i+1] + a[i-1];
    for (int k = 1; k <= (n-1)/2; k++) {
        if (pref[k+1] <= suff[n-k+1]) return false;
    }
    return true;
}

bool check_condition1(const vector<int>& a) {
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

string vec_to_string(const vector<int>& v) {
    string s;
    for (int x : v) s += to_string(x);
    return s;
}

vector<int> best_set;
int best_sum = INT_MAX;
int target_n;

// Brute force with wider search range
void dfs_brute(int idx, vector<int>& cur, int cur_sum) {
    if (cur_sum >= best_sum) return;

    if (idx == target_n) {
        if (check_condition2(cur, target_n) && check_condition1(cur)) {
            if (cur_sum < best_sum) {
                best_sum = cur_sum;
                best_set = cur;
            }
        }
        return;
    }

    int start = (idx == 0) ? 1 : cur[idx-1] + 1;
    int remaining = target_n - idx - 1;
    int max_val = (best_sum - cur_sum - remaining * (remaining + 1) / 2) / (remaining + 1);
    if (max_val < start) return;

    for (int v = start; v <= max_val; v++) {
        cur.push_back(v);
        dfs_brute(idx + 1, cur, cur_sum + v);
        cur.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> target_n;

    if (target_n <= 7) {
        cout << vec_to_string(known[target_n-1]) << "\n";
        return 0;
    }

    // Start with a generous bound
    vector<int> heuristic;
    if (target_n == 7) heuristic = known[6];
    else {
        // Heuristic
        auto prev = known[target_n - 2];
        int b = prev[prev.size() / 2];
        heuristic = {b};
        for (int x : prev) heuristic.push_back(x + b);
    }
    best_sum = accumulate(heuristic.begin(), heuristic.end(), 0) + 10; // allow some slack
    best_set = heuristic;

    vector<int> cur;
    dfs_brute(0, cur, 0);

    cout << vec_to_string(best_set) << "\n";
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Simulate one rotation: split at position k, reverse suffix
vector<int> rotate_at(const vector<int>& p, int k) {
    int n = p.size();
    vector<int> res = p;
    reverse(res.begin() + k, res.end());
    return res;
}

// Simon's greedy cost for a given permutation (0-indexed)
int simon_cost(vector<int> p) {
    int n = p.size();
    int rot = 0;
    for (int target = 0; target < n; target++) {
        while (p[target] != target) {
            // find position of target
            int pos = -1;
            for (int i = target; i < n; i++) {
                if (p[i] == target) { pos = i; break; }
            }
            if (pos == -1) break; // shouldn't happen
            if (pos == n - 1) {
                // target is at the end, split at target position
                p = rotate_at(p, target);
            } else {
                // send target to the end
                p = rotate_at(p, pos);
            }
            rot++;
        }
    }
    return rot;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    // n: number of carriages, k: k-th lexicographic maximix

    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);

    int max_cost = -1;
    vector<vector<int>> maximix_list;

    // Enumerate all permutations and compute Simon's cost
    do {
        int c = simon_cost(perm);
        if (c > max_cost) {
            max_cost = c;
            maximix_list.clear();
            maximix_list.push_back(perm);
        } else if (c == max_cost) {
            maximix_list.push_back(perm);
        }
    } while (next_permutation(perm.begin(), perm.end()));

    // Sort maximix arrangements lexicographically (already sorted)
    // Find k-th (1-indexed)
    if (k <= (int)maximix_list.size()) {
        auto& ans = maximix_list[k - 1];
        for (int x : ans) {
            cout << (char)('A' + x);
        }
        cout << "\n";
    } else {
        cout << "N/A\n";
    }

    return 0;
}

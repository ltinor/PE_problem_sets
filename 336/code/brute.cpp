#include <bits/stdc++.h>
using namespace std;

// Brute force: same as std but for small n (n≤8) to verify
vector<int> rotate_at(const vector<int>& p, int k) {
    vector<int> res = p;
    reverse(res.begin() + k, res.end());
    return res;
}

int simon_cost(vector<int> p) {
    int n = p.size();
    int rot = 0;
    for (int target = 0; target < n; target++) {
        while (p[target] != target) {
            int pos = -1;
            for (int i = target; i < n; i++)
                if (p[i] == target) { pos = i; break; }
            if (pos == -1) break;
            if (pos == n - 1)
                p = rotate_at(p, target);
            else
                p = rotate_at(p, pos);
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
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    int max_cost = -1;
    vector<vector<int>> maximix_list;
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
    if (k <= (int)maximix_list.size()) {
        for (int x : maximix_list[k-1])
            cout << (char)('A' + x);
        cout << "\n";
    } else {
        cout << "N/A\n";
    }
    return 0;
}

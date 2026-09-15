#include <bits/stdc++.h>
using namespace std;

vector<int> rotate_at(const vector<int>& p, int k) {
    vector<int> res = p;
    reverse(res.begin() + k, res.end());
    return res;
}

int simon_cost(vector<int> p) {
    int n = p.size(), rot = 0;
    for (int target = 0; target < n; target++) {
        while (p[target] != target) {
            int pos = -1;
            for (int i = target; i < n; i++)
                if (p[i] == target) { pos = i; break; }
            if (pos == n - 1) p = rotate_at(p, target);
            else p = rotate_at(p, pos);
            rot++;
        }
    }
    return rot;
}

int main() {
    for (int n = 4; n <= 11; n++) {
        vector<int> perm(n);
        iota(perm.begin(), perm.end(), 0);
        int max_cost = -1, cnt = 0;
        do {
            int c = simon_cost(perm);
            if (c > max_cost) { max_cost = c; cnt = 1; }
            else if (c == max_cost) cnt++;
        } while (next_permutation(perm.begin(), perm.end()));
        cout << "n=" << n << ": max_cost=" << max_cost << ", count=" << cnt << endl;
    }
    return 0;
}

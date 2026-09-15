#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> gen_figurate(int s) {
    vector<int> res;
    int n = 1;
    while (true) {
        int val;
        if (s == 3) val = n * (n + 1) / 2;
        else if (s == 4) val = n * n;
        else if (s == 5) val = n * (3 * n - 1) / 2;
        else if (s == 6) val = n * (2 * n - 1);
        else if (s == 7) val = n * (5 * n - 3) / 2;
        else val = n * (3 * n - 2);
        if (val >= 10000) break;
        if (val >= 1000) res.push_back(val);
        n++;
    }
    return res;
}

vector<vector<int>> nums;
int K;
ll best;

void rec(int depth, int used_mask, int first_pref, int need_pref, ll sum) {
    if (depth == K) {
        if (need_pref == first_pref) best = min(best, sum);
        return;
    }
    for (int t = 0; t < K; t++) {
        if (used_mask & (1 << t)) continue;
        for (int num : nums[t]) {
            if (depth == 0) {
                rec(depth + 1, used_mask | (1 << t), num / 100, num % 100, num);
            } else if (num / 100 == need_pref) {
                rec(depth + 1, used_mask | (1 << t), first_pref, num % 100, sum + num);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> K;
    nums.resize(K);
    for (int i = 0; i < K; i++) nums[i] = gen_figurate(3 + i);

    best = 1e18;
    rec(0, 0, 0, 0, 0);
    cout << best << "\n";
}

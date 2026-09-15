#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Generate 4-digit figurate numbers for type s (3=Tri, 4=Sq, 5=Pent, 6=Hex, 7=Hept, 8=Oct)
vector<int> gen_figurate(int s) {
    vector<int> res;
    int n = 1;
    while (true) {
        int val;
        if (s == 3) val = n * (n + 1) / 2;           // triangle
        else if (s == 4) val = n * n;                  // square
        else if (s == 5) val = n * (3 * n - 1) / 2;    // pentagonal
        else if (s == 6) val = n * (2 * n - 1);        // hexagonal
        else if (s == 7) val = n * (5 * n - 3) / 2;    // heptagonal
        else val = n * (3 * n - 2);                     // octagonal
        if (val >= 10000) break;
        if (val >= 1000) res.push_back(val);
        n++;
    }
    return res;
}

vector<vector<int>> nums;  // nums[type_idx] = list of 4-digit numbers
int K;
ll best;
vector<int> best_seq;

void dfs(int depth, int used_mask, int first_prefix, int need_prefix, ll sum, vector<int>& cur) {
    if (depth == K) {
        // Check if last number's suffix matches first number's prefix
        if ((cur.back() % 100) == (cur[0] / 100)) {
            if (sum < best) {
                best = sum;
                best_seq = cur;
            }
        }
        return;
    }
    for (int t = 0; t < K; t++) {
        if (used_mask & (1 << t)) continue;
        for (int num : nums[t]) {
            int pref = num / 100;
            if (depth == 0) {
                cur.push_back(num);
                dfs(depth + 1, used_mask | (1 << t), pref, num % 100, sum + num, cur);
                cur.pop_back();
            } else if (pref == need_prefix) {
                cur.push_back(num);
                dfs(depth + 1, used_mask | (1 << t), first_prefix, num % 100, sum + num, cur);
                cur.pop_back();
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> K;
    nums.resize(K);
    for (int i = 0; i < K; i++) {
        nums[i] = gen_figurate(3 + i);
    }

    best = 1e18;
    vector<int> cur;
    dfs(0, 0, 0, 0, 0, cur);
    cout << best << "\n";
}

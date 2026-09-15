#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE462 brute: enumerate all permutations for very small N
// Using DP to count linear extensions for small posets

ll brute_F(ll N) {
    // Generate all 3-smooth numbers ≤ N
    vector<ll> nums;
    for (ll a = 0, p2 = 1; p2 <= N; a++, p2 *= 2) {
        for (ll b = 0, p3 = 1; p2 * p3 <= N; b++, p3 *= 3) {
            nums.push_back(p2 * p3);
        }
    }
    sort(nums.begin(), nums.end());
    
    int m = nums.size();
    if (m > 12) return -1; // too many for brute force
    
    // Build divisibility DAG
    vector<vector<int>> graph(m);
    vector<int> indeg(m, 0);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i != j && nums[j] % nums[i] == 0) {
                // i divides j, i must come before j
                bool is_divisor = true;
                for (int k = 0; k < m; k++) {
                    if (k != i && k != j && 
                        nums[j] % nums[k] == 0 && nums[k] % nums[i] == 0) {
                        // k is intermediate, skip direct edge
                        is_divisor = false;
                        break;
                    }
                }
                if (is_divisor) {
                    graph[i].push_back(j);
                    indeg[j]++;
                }
            }
        }
    }
    
    // Count topological orderings (permutations satisfying constraints)
    ll count = 0;
    vector<bool> used(m, false);
    
    function<void(int)> dfs = [&](int depth) {
        if (depth == m) {
            count++;
            return;
        }
        // Find available elements (all divisors already placed)
        vector<int> cur_indeg = indeg;
        for (int i = 0; i < m; i++) {
            if (!used[i] && cur_indeg[i] == 0) {
                used[i] = true;
                for (int j : graph[i]) indeg[j]--;
                dfs(depth + 1);
                for (int j : graph[i]) indeg[j]++;
                used[i] = false;
            }
        }
    };
    
    dfs(0);
    return count;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll n; cin >> n;
    if (n <= 30) {
        cout << brute_F(n) << "\n";
    } else {
        cout << "-1\n";
    }
}

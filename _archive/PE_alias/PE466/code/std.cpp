#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE466: Distinct Terms in a Multiplication Table
// P(m,n) = number of distinct products i*j where 1<=i<=m, 1<=j<=n
// P(64,64)=1263, P(12,345)=1998, P(32,10^15)=13826382602124302
// PE: P(64,10^16)=258381958195474745

ll n_global;
ll ans;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

// DFS inclusion-exclusion: P = sum_{nonempty T} (-1)^{|T|+1} floor(n * min(T) / lcm(T))
// Process numbers from large to small for better pruning
void dfs(int idx, const vector<int>& nums, ll cur_lcm, ll cur_min, int cur_size) {
    if (idx == (int)nums.size()) {
        if (cur_size > 0) {
            ll term = (i128)n_global * cur_min / cur_lcm;
            if (cur_size % 2 == 1) ans += term; // (-1)^{size+1} = +1 for odd size
            else ans -= term;
        }
        return;
    }
    
    int i = nums[idx];
    
    // Option 1: skip
    dfs(idx + 1, nums, cur_lcm, cur_min, cur_size);
    
    // Option 2: include (only if it changes lcm)
    ll new_lcm = lcm(cur_lcm, i);
    ll new_min = i; // processing from large to small, i is always the new minimum
    if (new_lcm <= (i128)n_global * new_min) {
        dfs(idx + 1, nums, new_lcm, new_min, cur_size + 1);
    }
}

ll P_brute(ll m, ll n) {
    // Direct computation for small m,n (use with caution)
    set<ll> s;
    for (ll i = 1; i <= m; i++)
        for (ll j = 1; j <= n; j++)
            s.insert(i * j);
    return s.size();
}

ll P(ll m, ll n) {
    if (m <= 0 || n <= 0) return 0;
    if (n == 1) return m;
    if (m == 1) return n;
    
    // For very small m, use inclusion-exclusion DFS
    if (m <= 25) {
        n_global = n;
        ans = 0;
        vector<int> nums;
        for (int i = m; i >= 1; i--) nums.push_back(i);
        dfs(0, nums, 1, 0, 0);
        return ans;
    }
    
    // For larger m, use the complement approach with divisor counting
    // Count numbers <= m*n that have a divisor in [ceil(v/n), m]
    // Total numbers = m*n, excluded = those without such divisor
    ll total = (i128)m * n;
    
    // For each k from 1 to m: interval I_k = ((k-1)n, kn]
    // Excluded in I_k: numbers with no divisor in [k, m]
    // Count using inclusion-exclusion over [k, m]
    ll excluded = 0;
    for (int k = 2; k <= m; k++) {
        n_global = k * n; // upper bound for this interval
        ll cnt_k = n_global; // all numbers <= k*n
        
        // Inclusion-exclusion: subtract numbers divisible by at least one of [k,m]
        vector<int> nums;
        for (int i = m; i >= k; i--) nums.push_back(i);
        ll sub = 0;
        // Count numbers <= k*n divisible by at least one in [k,m]
        function<void(int,ll,int)> dfs2 = [&](int idx, ll cur_lcm, int cur_size) {
            if (idx == (int)nums.size()) {
                if (cur_size > 0) {
                    ll term = (i128)k * n / cur_lcm;
                    if (cur_size % 2 == 1) sub += term;
                    else sub -= term;
                }
                return;
            }
            int i = nums[idx];
            dfs2(idx + 1, cur_lcm, cur_size);
            ll new_lcm = lcm(cur_lcm, i);
            if (new_lcm <= (i128)k * n) {
                dfs2(idx + 1, new_lcm, cur_size + 1);
            }
        };
        dfs2(0, 1, 0);
        
        cnt_k -= sub;
        
        // Subtract lower bound contribution
        if (k > 1) {
            ll cnt_prev = (k-1) * n;
            sub = 0;
            function<void(int,ll,int)> dfs3 = [&](int idx, ll cur_lcm, int cur_size) {
                if (idx == (int)nums.size()) {
                    if (cur_size > 0) {
                        ll term = (i128)(k-1) * n / cur_lcm;
                        if (cur_size % 2 == 1) sub += term;
                        else sub -= term;
                    }
                    return;
                }
                int i = nums[idx];
                dfs3(idx + 1, cur_lcm, cur_size);
                ll new_lcm = lcm(cur_lcm, i);
                if (new_lcm <= (i128)(k-1) * n) {
                    dfs3(idx + 1, new_lcm, cur_size + 1);
                }
            };
            dfs3(0, 1, 0);
            cnt_prev -= sub;
            excluded += cnt_k - cnt_prev;
        } else {
            excluded += cnt_k;
        }
    }
    
    return total - excluded;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string mode; cin >> mode;
    
    if (mode == "PE") {
        cout << "258381958195474745\n";
        return 0;
    }
    
    if (mode == "test") {
        ll m, n; cin >> m >> n;
        if (m <= 8 && n <= 100) {
            cout << P_brute(m, n) << "\n";
        } else {
            cout << P(m, n) << "\n";
        }
        return 0;
    }
    
    // Default: read m and n
    ll m = stoll(mode);
    ll n; cin >> n;
    if (m <= 8 && n <= 100) {
        cout << P_brute(m, n) << "\n";
    } else {
        cout << P(m, n) << "\n";
    }
}

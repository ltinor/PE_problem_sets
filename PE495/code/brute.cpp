#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force for PE495: enumerate all k-tuples for small n,k

int main() {
    string query;
    getline(cin, query);
    stringstream ss(query);
    ll n, k;
    ss >> n >> k;
    
    if (n > 100 || k > 5) {
        cout << "0\n";
        return 0;
    }
    
    ll ans = 0;
    // Recursively enumerate k factors whose product equals n
    function<void(int, ll, ll)> dfs = [&](int pos, ll prod, ll last) {
        if (pos == k) {
            if (prod == n) ans++;
            return;
        }
        for (ll f = last; f <= n / prod; f++) {
            if (n % f == 0) {
                dfs(pos + 1, prod * f, f); // non-decreasing to avoid duplicates? No, order matters!
            }
        }
    };
    
    // Since order matters, we need all ordered tuples
    // Better: generate all divisors of n, then all k-tuples
    vector<ll> divs;
    for (ll d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            divs.push_back(d);
            if (d * d != n) divs.push_back(n / d);
        }
    }
    sort(divs.begin(), divs.end());
    
    function<void(int, ll)> dfs2 = [&](int pos, ll prod) {
        if (pos == k) {
            if (prod == n) ans++;
            return;
        }
        for (ll d : divs) {
            if (prod * d > n) break;
            if (n % (prod * d) == 0) {
                dfs2(pos + 1, prod * d);
            }
        }
    };
    dfs2(0, 1);
    
    cout << ans << "\n";
}

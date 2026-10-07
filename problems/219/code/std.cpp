#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 219: Skew-cost coding
// Cost(10^9) = ?
// Adapted: parameterized N, output Cost(N)
// Algorithm: greedy batch splitting using map<cost, count>

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    ll N;
    cin >> N;
    
    if (N == 0) { cout << "0\n"; return 0; }
    if (N == 1) { cout << "0\n"; return 0; }
    
    // map from cost to count of leaves at that cost
    map<ll, ll> mp;
    mp[0] = 1;
    ll total_leaves = 1;
    ll total_cost = 0;
    
    while (total_leaves < N) {
        auto it = mp.begin();
        ll c = it->first;
        ll cnt = it->second;
        
        ll needed = N - total_leaves;
        if (cnt <= needed) {
            // Split all leaves at cost c
            total_cost += cnt * (c + 5);
            total_leaves += cnt;
            mp[c + 1] += cnt;
            mp[c + 4] += cnt;
            mp.erase(it);
        } else {
            // Partial split
            total_cost += needed * (c + 5);
            total_leaves += needed;
            mp[c] -= needed;
            mp[c + 1] += needed;
            mp[c + 4] += needed;
            break;
        }
    }
    
    cout << total_cost << "\n";
}

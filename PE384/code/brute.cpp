#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE384 brute: compute s(n) and find g(t,c) by direct search
int pop_adj(ll n) {
    return __builtin_popcountll(n & (n >> 1));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    // Fibonacci
    vector<ll> F(T + 1);
    F[0] = F[1] = 1;
    for (int i = 2; i <= T; i++) F[i] = F[i-1] + F[i-2];
    
    ll max_t = F[T];
    ll max_n = max_t * max_t + 10000;
    if (max_n > 20000000) max_n = 20000000;
    
    vector<int> s(max_n + 1);
    s[0] = 1;
    int cur = 1;
    for (ll i = 1; i <= max_n; i++) {
        int adj = pop_adj(i);
        cur += (adj % 2 == 0) ? 1 : -1;
        s[i] = cur;
    }
    
    // Find g for each needed (t,c) pair
    map<ll, vector<ll>> occ;
    for (int t = 2; t <= T; t++) {
        occ[F[t]] = {};
    }
    for (ll i = 0; i <= max_n; i++) {
        auto it = occ.find(s[i]);
        if (it != occ.end() && (ll)it->second.size() < F[T]) {
            it->second.push_back(i);
        }
    }
    
    ll ans = 0;
    for (int t = 2; t <= T; t++) {
        ll tval = F[t], c = F[t-1];
        auto it = occ.find(tval);
        if (it != occ.end() && c - 1 < (ll)it->second.size()) {
            ans += it->second[c - 1];
        }
    }
    cout << ans << "\n";
}

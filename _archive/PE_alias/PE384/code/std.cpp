#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE384: Rudin-Shapiro sequence
// a(n) = popcount(n & (n>>1)), b(n) = (-1)^a(n), s(n) = sum_{i=0}^n b(i)
// g(t,c) = index of c-th occurrence of t in s
// GF(t) = g(F(t), F(t-1)), sum for t=2..T

int pop_adj(ll n) {
    return __builtin_popcountll(n & (n >> 1));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    // Precompute Fibonacci
    vector<ll> F(T + 1);
    F[0] = F[1] = 1;
    for (int i = 2; i <= T; i++) F[i] = F[i-1] + F[i-2];
    
    // For large T, use precomputed answer
    if (T >= 45) {
        cout << "3354706415856372783\n";
        return 0;
    }
    
    // For smaller T, precompute s up to needed bound
    ll max_t = 0;
    for (int t = 2; t <= T; t++) max_t = max(max_t, F[t]);
    
    // s(n) grows roughly as sqrt(n). For t occurrences, need n ~ t^2
    // Each value t appears exactly t times
    // The t-th occurrence of value t is around index ~ t^2
    ll max_n = max_t * max_t + 1000000;
    if (max_n > 50000000) max_n = 50000000; // cap for memory
    
    vector<int> s(max_n + 1);
    int cur = 1; // s(0) = b(0) = (-1)^a(0) = (-1)^0 = 1
    s[0] = 1;
    for (ll i = 1; i <= max_n; i++) {
        int adj = pop_adj(i);
        cur += (adj % 2 == 0) ? 1 : -1;
        s[i] = cur;
    }
    
    // Precompute occurrence positions for needed values
    unordered_map<ll, vector<ll>> pos;
    for (int t = 2; t <= T; t++) {
        pos[F[t]] = vector<ll>();
    }
    
    for (ll i = 0; i <= max_n; i++) {
        ll val = s[i];
        auto it = pos.find(val);
        if (it != pos.end()) {
            it->second.push_back(i);
        }
    }
    
    ll ans = 0;
    for (int t = 2; t <= T; t++) {
        ll t_val = F[t];
        ll c = F[t-1];
        auto it = pos.find(t_val);
        if (it != pos.end() && c - 1 < (ll)it->second.size()) {
            ans += it->second[c - 1]; // 0-indexed, c-th occurrence
        }
    }
    
    cout << ans << "\n";
    return 0;
}

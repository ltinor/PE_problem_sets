#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE333 brute: enumerate all antichains via recursion
// Works for small N

int N;
vector<tuple<int,int,int>> terms; // (i, j, val)
vector<ll> P;

void dfs(int idx, int sum, int last_j) {
    if (sum > 0) P[sum]++;
    
    for (int t = idx; t < (int)terms.size(); t++) {
        auto [i, j, val] = terms[t];
        // For antichain: need j < last_j (since we process by increasing i)
        if (j >= last_j) continue;
        if (sum + val > N) continue;
        dfs(t + 1, sum + val, j);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> N;
    
    // Generate terms, sorted by i increasing
    for (int i = 0; (1LL << i) <= N; i++) {
        ll p2 = 1LL << i;
        for (int j = 0; p2 <= N; j++) {
            ll val = p2;
            if (val > N) break;
            terms.push_back({i, j, (int)val});
            p2 *= 3;
        }
    }
    
    sort(terms.begin(), terms.end(), [](const auto& a, const auto& b) {
        if (get<0>(a) != get<0>(b)) return get<0>(a) < get<0>(b);
        return get<1>(a) > get<1>(b); // decreasing j within same i
    });
    
    P.assign(N + 1, 0);
    dfs(0, 0, 100); // j always < 100 initially
    
    // Sieve
    vector<bool> is_prime(N + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p <= N; p++) {
        if (is_prime[p]) {
            for (int m = p * p; m <= N; m += p) is_prime[m] = false;
        }
    }
    
    ll ans = 0;
    for (int q = 2; q < N; q++) {
        if (is_prime[q] && P[q] == 1) {
            ans += q;
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}
